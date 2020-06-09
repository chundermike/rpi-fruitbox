#include "fruitbox.hpp"

#define BLOCK_SIZE (4*1024)

GpioClass::GpioClass()
{
}

void GpioClass::OpenDevice(void)
{
  #ifdef _RPI
  uint32_t mem_fd;
  void *reg_map;

  if (gpio_base != nullptr) return; // already opened

  // /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem

  if ((mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC) ) < 0)
  {
    error("can't open /dev/gpiomem");
  }
  reg_map = mmap
  (
    NULL,                                        // Address at which to start local mapping (null means don't-care)
    BLOCK_SIZE,                                  // Size of mapped memory block
    PROT_READ|PROT_WRITE,                        // Enable both reading and writing to the mapped memory
    MAP_SHARED,                                  // This program does not have exclusive access to this memory
    mem_fd,                                      // Map to /dev/mem
    bcm_host_get_peripheral_address() + 0x200000 // Offset to GPIO peripheral
  );

  if (reg_map == MAP_FAILED)
  {
    close(mem_fd);
    error("gpio mmap error");
  }

  gpio_base = (volatile uint32_t *)reg_map;

  // first save the state of the GPIO registers so they can be restored later...
  for (uint32_t r=0; r<6; ++r)
  {
    gpio_regs.gpfsel[r] = GPFSEL[r];
  }
  // gpio_regs.gpren[0] = GPREN[0];
  // gpio_regs.gpren[1] = GPREN[1];
  // gpio_regs.gpfen[0] = GPFEN[0];
  // gpio_regs.gpfen[1] = GPFEN[1];
  gpio_regs.saved = true;

  log_file << NOTE << "Opened GPIO" << endl;
  #endif
}

GpioClass::~GpioClass()
{
  #ifdef _RPI
  // restore the state of the GPIO registers...
  if (gpio_regs.saved)
  {
    for (uint32_t r=0; r<6; ++r)
    {
      GPFSEL[r] = gpio_regs.gpfsel[r];
    }
  }
  #endif
}

void GpioClass::ConfigurePinAsInput(const uint32_t pin)
{
  log_file << NOTE << "Setting GPIO " << pin << " as input" << endl;
  #ifdef _RPI
    // Determine FPSEL register offset and bit shift
    OpenDevice();
    uint32_t offset, shift;
    offset = pin / 10;
    shift = (pin % 10) * 3;

    //Clear the bits in FSELn
    GPFSEL[offset] &= ~(0b111 << shift);

    //Set the bits to the input function (0)
    GPFSEL[offset] |= (0 << shift);

    // if input mode, add pull-up and set rising and falling edge detection...
    offset = (pin < 32) ? 0 : 1;
    uint32_t pin_mask = 0x1 << (pin % 32);
    GPPUL[0] = 2;
    usleep(100);
    GPPCK[offset] = pin_mask;
    usleep(100);
    GPPUL[0] = 0;
    GPPCK[offset] = 0;
    // GPREN[offset] = pin_mask;
    // GPFEN[offset] = pin_mask;

    gpio_input_mask |= (1 << pin);
  #endif
  Config->general->gpio.at(pin) = gpio_e::Input;
}

void GpioClass::ConfigurePinAsOutput(const uint32_t pin)
{
  log_file << NOTE << "Setting GPIO " << pin << " as output" << endl;
  #ifdef _RPI
    // Determine FPSEL register offset and bit shift
    OpenDevice();
    uint32_t offset, shift;
    offset = pin / 10;
    shift = (pin % 10) * 3;

    //Clear the bits in FSELn
    GPFSEL[offset] &= ~(0b111 << shift);

    //Set the bits to the output function (1)
    GPFSEL[offset] |= (1 << shift);
  #endif
  Config->general->gpio.at(pin) = gpio_e::Output;
}

void GpioClass::SetPin(const uint32_t pin)
{
  #ifdef _RPI
    uint32_t offset = static_cast<uint32_t>((pin < 32) ? 0 : 1);
    uint32_t pin_mask { static_cast<uint32_t>(0x1 << (pin % 32)) };
    GPSET[offset] = pin_mask;
  #else
    log_file << NOTE << "Setting GPIO " << pin << " output high" << endl;
  #endif
}

void GpioClass::ClrPin(const uint32_t pin)
{
  #ifdef _RPI
    uint32_t offset = static_cast<uint32_t>((pin < 32) ? 0 : 1);
    uint32_t pin_mask { static_cast<uint32_t>(0x1 << (pin % 32)) };
    GPCLR[offset] = pin_mask;
  #else
    log_file << NOTE << "Setting GPIO " << pin << " output low" << endl;
  #endif
}

uint32_t GpioClass::ReadPin(const uint32_t pin)
// Reads from GPIO pin. Read value is returned as int
{
  #ifdef _RPI
    uint32_t offset { static_cast<uint32_t>((pin < 32) ? 0 : 1) };
    uint32_t pin_mask { static_cast<uint32_t>(0x1 << (pin % 32)) };

    return GPLEV[offset] & pin_mask ? 1 : 0;
  #else
    return 0;
  #endif
}

int32_t GpioClass::DebounceInput(const uint32_t pin)
{
  #ifdef _RPI
    if (((1<<pin) & gpio_input_mask) == 0) return -1; // GPIO pin not an input

    volatile uint32_t gpio_levels { GPLEV[0] }; // only check first 32 GPIO pins

    // to de-bounce each pin, maintain a shift register of the levels for each pin...
    gpio_history.at(pin) <<= 1;
    gpio_history.at(pin) |= gpio_levels & (1 << pin) ? 1 : 0;
    gpio_history.at(pin) &= DEBOUNCE_MASK;

    uint32_t history { gpio_history.at(pin) };
    if (history == DEBOUNCE_PRESSED) gpio_pressed.at(pin) = true; // ...DEBOUNCE_PERIOD zeroes in a row
    else if (history == DEBOUNCE_RELEASED) gpio_pressed.at(pin) = false; // ...DEBOUNCE_PERIOD ones in a row

    if (gpio_pressed.at(pin) != prev_gpio_pressed.at(pin))
    {
      prev_gpio_pressed.at(pin) = gpio_pressed.at(pin);
      return history;
    }
  #endif
  return -2; // nothing changed
}

