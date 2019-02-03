#pragma once

#include "fruitbox.hpp"

#define NUM_GPIO  28

#define GPFSEL   ((volatile uint32_t *) (gpio_base + 0))
#define GPSET    ((volatile uint32_t *) (gpio_base + 7))
#define GPCLR    ((volatile uint32_t *) (gpio_base + 10))
#define GPLEV    ((volatile uint32_t *) (gpio_base + 13))
#define GPEDS    ((volatile uint32_t *) (gpio_base + 17))
#define GPREN    ((volatile uint32_t *) (gpio_base + 19))
#define GPFEN    ((volatile uint32_t *) (gpio_base + 22))
#define GPPUL    ((volatile uint32_t *) (gpio_base + 37))
#define GPPCK    ((volatile uint32_t *) (gpio_base + 38))

#define DEBOUNCE_PERIOD       8
#define DEBOUNCE_MASK         ((1 << (DEBOUNCE_PERIOD+1)) - 1)
#define DEBOUNCE_PRESSED      (0)
#define DEBOUNCE_RELEASED     (DEBOUNCE_MASK)

struct gpio_regs_t
{
  uint32_t gpfsel[6];
  uint32_t gpren[2];
  uint32_t gpfen[2];
  bool saved {false};
};

class GpioClass
{
public:
  GpioClass();
  ~GpioClass();
  void ConfigurePinAsInput(const uint32_t pin);
  void ConfigurePinAsOutput(const uint32_t pin);
  uint32_t ReadPin(const uint32_t pin);
  void SetPin(const uint32_t pin);
  void ClrPin(const uint32_t pin);
  int32_t DebounceInput(const uint32_t pin);
private:
  void OpenDevice(void);
  gpio_regs_t gpio_regs {};
  volatile uint32_t *gpio_base { nullptr };
  uint32_t gpio_input_mask {};
  array<uint32_t, NUM_GPIO> gpio_history {};
  array<bool, NUM_GPIO> gpio_pressed {};
  array<bool, NUM_GPIO> prev_gpio_pressed {};
};
