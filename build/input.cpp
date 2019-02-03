#include "fruitbox.hpp"

#define ABS_CENTRE_LO     112
#define ABS_CENTRE_HI     144
#define ABS_LEFT_UP_HI    32
#define ABS_RIGHT_DOWN_LO 224

#define BLOCK_SIZE (4*1024)

constexpr char ButtonTestTitleStr[]             { "Button Test" };
constexpr char ButtonTestMessageStr[]           { "... press keyboard <ESC> to finish ..." };
constexpr char ConfigureButtonsTitleStr[]       { "Configure Buttons" };
constexpr char ConfigureButtonsMessageStr[]     { "... press keyboard <ESC> to skip this button ..." };
constexpr char CalibrateTouchTitleStr[]         { "Touch Screen Calibration" };

InputClass::InputClass(bool i_config_buttons, bool i_test_buttons, bool i_calibrate_touch)
{
  config_buttons = i_config_buttons;
  test_buttons = i_test_buttons;
  calibrate_touch = i_calibrate_touch;

  openDevices();

  if (test_buttons || config_buttons) return; // don't LoadButtons()

  Config->LoadButtons(Config->button_map);
}

InputClass::~InputClass()
{
}

void InputClass::openDevices(void)
{
  string line {};
  string name {};
  size_t pos {};
  ifstream devices_file {};
  int fd {};

  devices_file.open("/proc/bus/input/devices", ios::in);
  if (!devices_file.is_open()) return;
  while (getline(devices_file, line))
  {
    input_device_t device {};
    // search for our device...
    istringstream ss { line };

    // find name and save for later after Handler field extracted...
    if ((pos = line.find("Name=")) != string::npos)
    {
      pos += 5; // skip over "Name="
      if (pos <= string::npos)
      {
        name = &line.at(pos);
      }
    }

    // Extract handler event number
    if (line.find("Handlers=") != string::npos)
    {
      if ((pos = line.find("event")) != string::npos)
      {
        string event_path {"/dev/input/"};

        event_path.append(&line.at(pos));
        pos = event_path.find_first_not_of(' ');
        if (pos != string::npos)
        {
          event_path.erase(0, pos);
        }
        pos = event_path.find_first_of(' ');
        if (pos != string::npos)
        {
          event_path.erase(event_path.find_first_of(' '), event_path.back());
        }
        device.name = name;
        device.event_path = event_path;
        name.clear();

        // we then try and open this device file...
        if ((device.fd = open(event_path.c_str(), O_RDONLY | O_RSYNC | O_NONBLOCK) ) == -1)
        {
          cout << WARNING << "Couldn't Open ";
        }
        else
        {
          // check for keyboard device type...
          if ((pos = line.find("kbd")) != string::npos)
          {
            device.type = input_type_e::Key;
          }

          // check for joystick device type and extract number (if any)...
          if ((pos = line.find("js")) != string::npos)
          {
            device.type = input_type_e::Joystick;
            try { device.js_num = static_cast<uint32_t>(stoi(line.substr(pos+2))); }
            catch (const std::invalid_argument &err) { }
            catch (const std::out_of_range &err) { }
          }

          // check for mouse device type (touchscreen or touchpad) and extract number (if any)...
          if ((pos = line.find("mouse")) != string::npos)
          {
            // try { device.mouse_num = static_cast<uint32_t>(stoi(line.substr(pos+5))); }
            // catch (const std::invalid_argument &err) { }
            // catch (const std::out_of_range &err) { }

            // check for touch button capability...
            {
              unsigned long evbit { 0 };
              unsigned int key { BTN_TOUCH };
              // Get the bit field of available event types.
              ioctl(device.fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
              if (evbit & (1 << EV_KEY))
              {
                size_t nchar = KEY_MAX/8 + 1;
                unsigned char bits[nchar];
                // Get the bit fields of available keys.
                ioctl(device.fd, EVIOCGBIT(EV_KEY, sizeof(bits)), &bits);
                if (bits[key/8] & (1 << (key % 8)))
                {
                  device.type = input_type_e::Touch;
                  device.state = input_device_state_e::idle;
                  touch_installed = true;
                }
              }
            }
          }

          // save the opened device to the vector list...
          cout << NOTE << "Opened ";
          input_device.push_back(device);
        }
        cout << device.name << " (" << device.event_path << ")" << endl;
      }
    }
  }
  devices_file.close();

  // now add gpio to device vector...
  input_device_t device {};
  device.type = input_type_e::GPIO;
  device.name = "GPIO";
  device.event_path = "";
  device.fd = 0;
  input_device.push_back(device);
}

// #include <termios.h>

void InputClass::Start(void)
{
  if (config_buttons || test_buttons)
  {
    for (uint32_t g = 0; g < NUM_GPIO; ++g)
    // in these modes, make all potential gpio pins inputs...
    {
      if (Config->general->gpio.at(g) != gpio_e::Reserved) Gpio->ConfigurePinAsInput(g);
    }
  }


  // struct termios raw;
  // tcgetattr(STDIN_FILENO, &raw);
  // raw.c_lflag &= ~(ECHO);
  // tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  // 
  // start the input thread which reads input devices and processes button presses using FindButton()
  // FindButton() either places button matches on the Input button queue, or processes the input events
  // directly in test_buttons or config_buttons mode(s).
  thread InputThread { &InputClass::InputThread, this };
  InputThread.detach();

  if (config_buttons) ConfigButtons();
  else if (test_buttons) TestButtons();
}

void InputClass::CalibrateTouch(void)
{
  ints2_t touch_tl {};
  ints2_t touch_br {};
  ints2_t quarter {};

  Display->DrawInfoBox(CalibrateTouchTitleStr, "Press Top Left Target", "", nullptr, false, false);
  Display->DrawTouchTarget(Display->display_size.width/4, Display->display_size.height/4);
  al_flip_display();

  bool done { false };
  do
  {
    unique_lock<mutex> raw_guard(raw.mtx);
    raw.valid.wait(raw_guard);

    if (raw.event.type == input_type_e::Touch)
    {
      touch_tl.x = raw.event.param.at(EVENT_PARAM_VAL1);
      touch_tl.y = raw.event.param.at(EVENT_PARAM_VAL2);
      done = true;
    }
    raw_guard.unlock();
  } while (!done);

  Display->DrawInfoBox(CalibrateTouchTitleStr, "Press Bottom Right Target", "", nullptr, false, false);
  Display->DrawTouchTarget(3 * Display->display_size.width/4, 3 * Display->display_size.height/4);
  al_flip_display();

  done = false;
  do
  {
    unique_lock<mutex> raw_guard(raw.mtx);
    raw.valid.wait(raw_guard);

    if (raw.event.type == input_type_e::Touch)
    {
      touch_br.x = raw.event.param.at(EVENT_PARAM_VAL1);
      touch_br.y = raw.event.param.at(EVENT_PARAM_VAL2);
      done = true;
    }
    raw_guard.unlock();
  } while (!done);

  quarter.x = (touch_br.x - touch_tl.x) / 2;
  quarter.y = (touch_br.y - touch_tl.y) / 2;

  Config->buttons->touch_min.x = touch_tl.x - quarter.x;
  Config->buttons->touch_min.y = touch_tl.y - quarter.y;
  Config->buttons->touch_max.x = touch_br.x + quarter.x;
  Config->buttons->touch_max.y = touch_br.y + quarter.y;

  Display->DrawInfoBox(CalibrateTouchTitleStr, "Calibraton Complete", "");
  sleep(1);
}

void InputClass::TestButtons(void)
{
  raw.enable = true;

  Display->DrawInfoBox(ButtonTestTitleStr, "... press any input button ...", ButtonTestMessageStr);

  while (1)
  {
    unique_lock<mutex> raw_guard(raw.mtx);
    raw.valid.wait(raw_guard);

    if (raw.kbd_esc_pressed) break;

    Display->DrawInfoBox(ButtonTestTitleStr, raw.str, ButtonTestMessageStr);

    raw_guard.unlock();

    this_thread::sleep_for(chrono::milliseconds(10)); // no point in scanning for buttons more than 100 times a second!
  }
}

void InputClass::ConfigButtons(void)
{
  raw.enable = true;

  ofstream btn_file;

  btn_file.open(Config->button_map, ios::out);
  if (!btn_file.is_open())
  {
    error("Can't open %s for output", Config->button_map.c_str());
  }

  btn_file << "# fruitbox " << FRUITBOX_VERSION << " button mapping file" << endl;
  btn_file << "# Missing buttons will assume their default values (see user guide)" << endl << endl;

  if (calibrate_touch)
  {
    CalibrateTouch();
    btn_file << left << setw(16) << cfgKeyword_TouchMin << " = " << Config->buttons->touch_min.x << " " << Config->buttons->touch_min.y << endl;
    btn_file << left << setw(16) << cfgKeyword_TouchMax << " = " << Config->buttons->touch_max.x << " " << Config->buttons->touch_max.y << endl << endl;
  }

  for (uint32_t b = 0; b < Config->buttons->button.size(); ++b)
  {
    Display->DrawInfoBox(ConfigureButtonsTitleStr, "Press input for : " + Config->buttons->button.at(b).name + " ...", ConfigureButtonsMessageStr);

    unique_lock<mutex> raw_guard(raw.mtx);
    raw.valid.wait(raw_guard);

    if (raw.kbd_esc_pressed == false)
    {
      Display->DrawInfoBox(ConfigureButtonsTitleStr, raw.str, ConfigureButtonsMessageStr);
      btn_file << left << setw(16) << Config->buttons->button.at(b).name << " = " << raw.str << endl;
      sleep(1);
    }

    raw_guard.unlock();
  }

  Display->DrawInfoBox(ConfigureButtonsTitleStr, "", "Job Done! Button mappings written to '" + Config->button_map + "'");
  sleep(3);
  btn_file.close();
}

void InputClass::scanGPIO(input_event_t &event)
{
  event.type = input_type_e::None;
  for (uint32_t i = 0; i < NUM_GPIO; ++i)
  {
    if (Config->general->gpio.at(i) == gpio_e::Input)
    {
      int32_t level { Gpio->DebounceInput(i) };
      if (level >= 0)
      {
        event.type = input_type_e::GPIO;
        event.param.at(EVENT_PARAM_ID) = 0;
        event.param.at(EVENT_PARAM_VAL1) = i; // GPIO pin number
        event.param.at(EVENT_PARAM_VAL2) = 0;
        if (level & 1) // GPIO not pressed
        {
          event.param.at(EVENT_PARAM_PRESSED) = 0;
        }
        else // pressed (shorted to GND)
        {
          event.param.at(EVENT_PARAM_PRESSED) = 1;
        }

        FindButton(event);
      }
    }
  }
}

void InputClass::scanDevice(input_device_t &device, input_event_t &event)
{
  struct input_event ev[64];
  int rb {read(device.fd, ev, sizeof(struct input_event)*64)};
  if (rb != -1) // data available
  {
    for (auto i = 0;  i <  (rb / sizeof(struct input_event)); ++i)
    {
      event.type = input_type_e::None;

      switch (device.state)
      {
        case input_device_state_e::idle :
          if (ev[i].type == EV_KEY)
          {
            if (ev[i].code == BTN_TOUCH)
            {
              event.param.at(EVENT_PARAM_PRESSED) = ev[i].value;
              if (ev[i].value == 1) // pressed (touched)
              {
                device.state = input_device_state_e::waiting_for_touch_abs_x;
              }
            }
            else // keyboard or joystick button press/release
            {
              event.type = input_type_e::Key;
              event.param.at(EVENT_PARAM_ID) = device.js_num;
              event.param.at(EVENT_PARAM_VAL1) = ev[i].code;
              event.param.at(EVENT_PARAM_VAL2) = 0;
              event.param.at(EVENT_PARAM_PRESSED) = ev[i].value;
            }
          }
          else if (ev[i].type == EV_ABS) // analogue (joy)stick movement
          {
            bool is_stick { false };

            if (ev[i].code >= ABS_X && ev[i].code <= ABS_RZ) is_stick = true;
            else if (ev[i].code >= ABS_HAT0X && ev[i].code <= ABS_HAT3Y) is_stick = true;

            if (!is_stick) break;
            
            // get the min and max values
            int abs[6] = {0};
            int32_t abs_min {};
            int32_t abs_max {};
            int32_t abs_mid {};

            ioctl(device.fd, EVIOCGABS(ev[i].code), abs);

            abs_mid = abs[0];
            abs_min = abs[1];
            abs_max = abs[2];

            if (device.joystick_moved == false)
            {
              if (ev[i].value == abs_max)
              {
                event.type = input_type_e::Joystick;
                event.param.at(EVENT_PARAM_ID) = device.js_num;
                event.param.at(EVENT_PARAM_VAL1) = ev[i].code; // ABS_* (axis)
                event.param.at(EVENT_PARAM_VAL2) = 0; // left or up
                event.param.at(EVENT_PARAM_PRESSED) = 1;
                device.joystick_moved_code = ev[i].code;
                device.joystick_moved = true;
              }

              else if (ev[i].value == abs_min)
              {
                event.type = input_type_e::Joystick;
                event.param.at(EVENT_PARAM_ID) = device.js_num;
                event.param.at(EVENT_PARAM_VAL1) = ev[i].code; // ABS_* (axis)
                event.param.at(EVENT_PARAM_VAL2) = 1; // right or down
                event.param.at(EVENT_PARAM_PRESSED) = 1;
                device.joystick_moved_code = ev[i].code;
                device.joystick_moved = true;
              }

            }
            else
            {
              if (ev[i].value == abs_mid && ev[i].code == device.joystick_moved_code)
              {
                event.type = input_type_e::Joystick;
                event.param.at(EVENT_PARAM_ID) = device.js_num;
                event.param.at(EVENT_PARAM_VAL1) = ev[i].code; // ABS_* (axis)
                event.param.at(EVENT_PARAM_VAL2) = 0; // unused
                event.param.at(EVENT_PARAM_PRESSED) = 0;
                device.joystick_moved = false;
              }
            }

          }
          break;

        // states for detecting ABS_X and ABS_Y immediately following a BTN_TOUCH (touchscreen) event...
        case input_device_state_e::waiting_for_touch_abs_x :
          if ((ev[i].type == EV_ABS) && (ev[i].code == ABS_X))
          {
            // we transform the touch co-ordinates by first adding the user defined offsets, and then scaling by the user defined scale...
            int32_t value { reversed_touch ? static_cast<int32_t>(Config->buttons->touch_max.x + Config->buttons->touch_min.x - ev[i].value) : static_cast<int32_t>(ev[i].value) };
            event.param.at(EVENT_PARAM_VAL1) = static_cast<uint32_t>(touch_scale_x * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_x)));
            device.state = input_device_state_e::waiting_for_touch_abs_y;
          }
          break;

        case input_device_state_e::waiting_for_touch_abs_y :
          if ((ev[i].type == EV_ABS) && (ev[i].code == ABS_Y))
          {
            int32_t value { reversed_touch ? static_cast<int32_t>(Config->buttons->touch_max.y + Config->buttons->touch_min.y - ev[i].value) : static_cast<int32_t>(ev[i].value) };
            event.type = input_type_e::Touch;
            event.param.at(EVENT_PARAM_ID) = 0;
            // event.param.at(EVENT_PARAM_ID) = device.mouse_num;
            event.param.at(EVENT_PARAM_VAL2) = static_cast<uint32_t>(touch_scale_y * static_cast<double>(static_cast<uint32_t>(value - touch_offset_y)));
            event.param.at(EVENT_PARAM_PRESSED) = 1; // pressed
            device.state = input_device_state_e::waiting_for_touch_release;
          }
          break;

        case input_device_state_e::waiting_for_touch_release :
          if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 0))
          {
            // if touch released, disable drawing of touch song bitmap...
            // (even if it doesn't correspond to a touch song region; touch release
            //  implies the user is not touching the screen, so can't by definition
            //  be touching any song region)
            {
              if ((Config->general->select_mode == select_mode_e::TouchSong))
              {
                Config->touch_song->no_draw = true;
              }
            }
            device.state = input_device_state_e::idle;
          }
          break;

        default :
          device.state = input_device_state_e::idle;
          break;
      }

      // we check for button release outside of state machine so we can use it to resync the state machine if x/y not received after button press...
      if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 0))
      {
        event.type = input_type_e::Touch;
        event.param.at(EVENT_PARAM_PRESSED) = 0; // released
        device.state = input_device_state_e::idle;
      }

      if (event.type != input_type_e::None)
      {
        if (FindButton(event) == false)
        {
          // no button match found, so if the event is a touch, and we are in TouchSong selection mode,
          // we check to see if the touch is inside any of the song title areas (which include cfg offset and size)...
          if ((Config->general->select_mode == select_mode_e::TouchSong) && (event.type == input_type_e::Touch))
          {
            uint32_t song_entry {};
            uint32_t song_page {};
            uint32_t sw {Config->touch_song->size.x};
            uint32_t sh {Config->touch_song->size.y};
            bool done { false };

            for (song_page=0; song_page < Config->touch_song->entry_position.size(); ++song_page)
            {
              for (song_entry=0; song_entry < Config->touch_song->entry_position[song_page].size(); ++song_entry)
              {
                int32_t sx {Config->touch_song->entry_position.at(song_page).at(song_entry).x};
                int32_t sy {Config->touch_song->entry_position.at(song_page).at(song_entry).y};
                if (event.param.at(EVENT_PARAM_VAL1) < sx) continue;       // touch x < song title region x
                if (event.param.at(EVENT_PARAM_VAL2) < sy) continue;       // touch y < song title region y
                if (event.param.at(EVENT_PARAM_VAL1) >= (sx+sw)) continue; // touch x >= song title region (x+w)
                if (event.param.at(EVENT_PARAM_VAL2) >= (sy+sh)) continue; // touch y >= song title region (y+h)
                // if we get here then the touch is inside the song title touch area...
                // if (!(button & BUTTON_RELEASED))
                if (event.param.at(EVENT_PARAM_PRESSED) == 1)
                {
                  Config->touch_song->position.x = sx;
                  Config->touch_song->position.y = sy;
                  if (PlayQueue->full == false) Config->touch_song->no_draw = false;
                  uint32_t button { TOUCH_SONG | (song_entry << SONG_ENTRY_POS) | (song_page << SONG_PAGE_POS) };
                  queue_mtx.lock();
                  queue.push_back(button); // button code
                  queue.push_back(BUTTON_SELECT); // select song immediately
                  queue_mtx.unlock();
                }
                done = true;
                break;
              }
              if (done) break;
            }
          }
        }
      }
    }
  }
}

void InputClass::InputThread(void)
{
  input_event_t event;
  while (1)
  {
    for (auto &d : input_device)
    {
        if (d.type == input_type_e::GPIO)
        {
          scanGPIO(event); // scan and debounce GPIO inputs
        }
        else
        {
          scanDevice(d, event);
        }
    }
    this_thread::sleep_for(chrono::milliseconds(10)); // no point in scanning for buttons more than 100 times a second!
  }
}

bool InputClass::FindButton(const input_event_t &event)
{
  if (raw.enable) // capture the raw button type and values rather than try and match it...
  {
    if (event.param.at(EVENT_PARAM_PRESSED) == 1) // only show pressed events (rather than released or repeated)
    {
      stringstream ss { ios_base::app | ios_base::out };
      switch (event.type)
      {
        case input_type_e::Key      : ss << ButtonTypeKeyStr << " " << event.param.at(EVENT_PARAM_VAL1); break;
        case input_type_e::Joystick : ss << ButtonTypeJoystickStr << " " << event.param.at(EVENT_PARAM_ID) << " " << event.param.at(EVENT_PARAM_VAL1) << " " << event.param.at(EVENT_PARAM_VAL2); break;
        case input_type_e::Touch    : ss << ButtonTypeTouchStr; break; // << " " << event.param.at(EVENT_PARAM_ID); break;
        case input_type_e::GPIO     : ss << ButtonTypeGPIOStr << " " << event.param.at(EVENT_PARAM_VAL1); break;
        default : ss << "Unknown"; break;
      }

      raw.event = event;
      raw.str = ss.str();

      if (event.type == input_type_e::Key && event.param.at(EVENT_PARAM_VAL1) == KEY_ESC)
      {
        raw.kbd_esc_pressed = true;
      }
      else
      {
        raw.kbd_esc_pressed = false;
      }
      raw.valid.notify_all();
    }
  }
  else // try and find a user button that matches this event...
  {
    uint32_t b;
    int32_t bx;
    int32_t by;
    int32_t bw;
    int32_t bh;
    bool done { false };

    for (b = 0; b < NUM_BUTTONS; ++b)
    {
      if (Config->buttons->button.at(b).type == event.type)
      {
        switch (event.type)
        {
          case input_type_e::Touch : // need to check touch is within the size of the button area...
            bx = Config->buttons->button.at(b).param.at(0);
            by = Config->buttons->button.at(b).param.at(1);
            bw = Config->buttons->button.at(b).param.at(2);
            bh = Config->buttons->button.at(b).param.at(3);

            if (event.param.at(EVENT_PARAM_VAL1) < bx) continue;       // touch x < button x
            if (event.param.at(EVENT_PARAM_VAL2) < by) continue;       // touch y < button y
            if (event.param.at(EVENT_PARAM_VAL1) >= (bx+bw)) continue; // touch x >= button (x+w)
            if (event.param.at(EVENT_PARAM_VAL2) >= (by+bh)) continue; // touch y >= button (y+h)
            done = true; // touch inside button area :)
            break;

          case input_type_e::Key :
            if (Config->buttons->button.at(b).param.at(EVENT_PARAM_VAL1) == event.param.at(EVENT_PARAM_VAL1)) done = true;
            break;

          case input_type_e::GPIO :
            if (Config->buttons->button.at(b).param.at(EVENT_PARAM_VAL1) == event.param.at(EVENT_PARAM_VAL1)) done = true;
            break;

          case input_type_e::Joystick :
            if ((Config->buttons->button.at(b).param.at(EVENT_PARAM_ID) == event.param.at(EVENT_PARAM_ID)) && 
                (Config->buttons->button.at(b).param.at(EVENT_PARAM_VAL1) == event.param.at(EVENT_PARAM_VAL1)) && 
                (Config->buttons->button.at(b).param.at(EVENT_PARAM_VAL2) == event.param.at(EVENT_PARAM_VAL2))) done = true;
            break;
        }
      }
      if (done) break;
    }

    if (b < NUM_BUTTONS)
    {
      if (event.param.at(EVENT_PARAM_PRESSED) == 0)
      {
        b |= BUTTON_RELEASED;
      }
      queue_mtx.lock();
      queue.push_back(b);
      queue_mtx.unlock();
      return true;
    }
  }
  return false;
}
