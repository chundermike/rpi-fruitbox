#include "fruitbox.hpp"

#define OTHER_INPUT_USER_EVENT     999

#define BLOCK_SIZE (4*1024)

#define GPFSEL   ((volatile uint32_t *) (gpio + 0))
#define GPSET    ((volatile uint32_t *) (gpio + 7))
#define GPCLR    ((volatile uint32_t *) (gpio + 10))
#define GPLEV    ((volatile uint32_t *) (gpio + 13))
#define GPEDS    ((volatile uint32_t *) (gpio + 17))
#define GPREN    ((volatile uint32_t *) (gpio + 19))
#define GPFEN    ((volatile uint32_t *) (gpio + 22))
#define GPPUL    ((volatile uint32_t *) (gpio + 37))
#define GPPCK    ((volatile uint32_t *) (gpio + 38))

constexpr char ButtonTestTitleStr[]             { "Button Test" };
constexpr char ButtonTestMessageStr[]           { "... press keyboard <ESC> to finish ..." };
constexpr char ConfigureButtonsTitleStr[]       { "Configure Buttons" };
constexpr char ConfigureButtonsMessageStr[]     { "... press keyboard <ESC> to skip this button ..." };
constexpr char CalibrateTouchTitleStr[]         { "Touch Screen Calibration" };

enum class other_device_e {
  GPIO,
  Touch,
  UserDevice
};

bool InputClass::openDevice(const string &name, int &fd)
{
  string line;
  string device_filename {"/dev/input/"};
  size_t pos;
  ifstream devices_file;
  bool device_found { false };

  devices_file.open("/proc/bus/input/devices", ios::in);
  if (!devices_file.is_open()) return false;

  while (getline(devices_file, line))
  {
    // search for our device...
    istringstream ss { line };
    if (line.find("Name") != string::npos)
    {
      pos = line.find(name);
      if (pos != string::npos)
      // our device is found, so extract the event handler name from it...
      {
        while (getline(devices_file, line))
        {
          istringstream ss { line };
          if (line.find("Handlers") != string::npos)
          {
            pos = line.find("event");
            if (pos != string::npos)
            {
              device_filename.append(&line.at(pos));
              device_found = true;
              break;
            }
          }
        }
        break;
      }
    }
  }
  devices_file.close();

  if (device_found)
  {
    pos = device_filename.find_first_not_of(' ');
    if (pos != string::npos)
    {
      device_filename.erase(0, pos);
    }
    pos = device_filename.find_first_of(' ');
    if (pos != string::npos)
    {
      device_filename.erase(device_filename.find_first_of(' '), device_filename.back());
    }

    // we then open this device file...
    if ((fd = open(device_filename.c_str(), O_RDONLY | O_RSYNC | O_NONBLOCK) ) == -1)
    {
      cout << WARNING << "Couldn't open input device '" << name << "' (" << device_filename << ")" << endl;
      return false;
    }
    cout << NOTE << "Opened input device '" << name << "' (" << device_filename << ")" << endl;
  }
  else
  {
    fd = -1; // not found/opened
    cout << WARNING << "Couldn't find device '" << name << "'" << endl;
  }

  return device_found;
}

// void InputClass::GetTouchMaxMin(int fd)
// {
  // struct input_absinfo abs;
  // ioctl (fd, EVIOCGABS (ABS_X), &abs);
  // touch_min_x = abs.minimum;
  // touch_max_x = abs.maximum;
  // ioctl (fd, EVIOCGABS (ABS_Y), &abs);
  // touch_min_y = abs.minimum;
  // touch_max_y = abs.maximum;
// }

InputClass::InputClass(bool i_config_buttons, bool i_test_buttons, bool i_calibrate_touch)
{
  config_buttons = i_config_buttons;
  test_buttons = i_test_buttons;
  calibrate_touch = i_calibrate_touch;

  if (!al_install_keyboard()) cout << NOTE << "Couldn't install keyboard" << endl;
  if (!al_install_joystick())
  {
    cout << NOTE << "Couldn't install joystick" << endl;
  }
  else // store all joystick IDs in a vector...
  {
    uint32_t joys { static_cast<uint32_t>(al_get_num_joysticks()) };
    if (joys) cout << NOTE << joys << " joystick(s) detected" << endl;
    for (size_t j = 0; j < joys; ++j)
    {
      joystick.push_back(al_get_joystick(j));
    }
  }

  if (config_buttons | test_buttons) GenerateButtonFile();
}

InputClass::~InputClass()
{
  // restore the state of the GPIO registers...
  if (gpio_regs.saved)
  {
    for (uint32_t r=0; r<6; ++r)
    {
      GPFSEL[r] = gpio_regs.gpfsel[r];
    }
  }
}

void InputClass::Start(void)
{
  GPIOInit();

  if (Config->need_touchscreen)
  {
    touch_installed = openDevice(Config->buttons->touch_device, touch_fd);
    if (touch_installed == false) error("Need touchscreen for button input but touchscreen device '%s' not available", Config->buttons->touch_device.c_str());
    // GetTouchMaxMin(touch_fd);
  }

  // open user-defined input devices...
  for (auto &device : Config->buttons->input_device)
  {
    openDevice(device.first, device.second);
  }

  thread ButtonInputThread { &InputClass::ButtonInputThread, this };
  ButtonInputThread.detach();
}

void InputClass::CalibrateTouch(void)
{
  ints2_t touch_tl {};
  ints2_t touch_br {};
  ints2_t quarter {};
  bool got_touch { false };


  Display->DrawInfoBox(CalibrateTouchTitleStr, "Press Top Left Target", "", nullptr, false, false);
  Display->DrawTouchTarget(Display->display_size.width/4, Display->display_size.height/4);
  al_flip_display();

  while (!got_touch)
  {
    al_wait_for_event(EventQueue, &event);
    switch (event.type)
    {
      case OTHER_INPUT_USER_EVENT :
        if (event.user.data4 == 0) // press (not release) event
        {
          if (event.user.data1 == static_cast<uint32_t>(other_device_e::Touch))
          {
            touch_tl.x = event.user.data2;
            touch_tl.y = event.user.data3;
            got_touch = true;
          }
        }
        break;
    }
  }

  Display->DrawInfoBox(CalibrateTouchTitleStr, "Press Bottom Right Target", "", nullptr, false, false);
  Display->DrawTouchTarget(3 * Display->display_size.width/4, 3 * Display->display_size.height/4);
  al_flip_display();

  got_touch = false;

  while (!got_touch)
  {
    al_wait_for_event(EventQueue, &event);
    switch (event.type)
    {
      case OTHER_INPUT_USER_EVENT :
        if (event.user.data4 == 0) // press (not release) event
        {
          if (event.user.data1 == static_cast<uint32_t>(other_device_e::Touch))
          {
            touch_br.x = event.user.data2;
            touch_br.y = event.user.data3;
            got_touch = true;
          }
        }
        break;
    }
  }

  quarter.x = (touch_br.x - touch_tl.x) / 2;
  quarter.y = (touch_br.y - touch_tl.y) / 2;

  Config->buttons->touch_min.x = touch_tl.x - quarter.x;
  Config->buttons->touch_min.y = touch_tl.y - quarter.y;
  Config->buttons->touch_max.x = touch_br.x + quarter.x;
  Config->buttons->touch_max.y = touch_br.y + quarter.y;

  Display->DrawInfoBox(CalibrateTouchTitleStr, "Calibraton Complete", "", nullptr, false, true);
  sleep(1);
}

void InputClass::GenerateButtonFile(void)
{
  Config->need_gpio_input = true;

  GPIOInit();

  for (uint32_t g = 0; g < NUM_GPIO; ++g)
  // in debug mode, make all potential gpio pins inputs...
  {
    if (Config->general->gpio.at(g) != gpio_e::Reserved) GPIOConfigurePinAsInput(g);
  }

  EventQueue = al_create_event_queue();
  if (EventQueue == nullptr) error("Couldn't create event queue");

  if (al_is_keyboard_installed()) al_register_event_source(EventQueue, al_get_keyboard_event_source());
  if (al_is_joystick_installed()) al_register_event_source(EventQueue, al_get_joystick_event_source());
  touch_installed = openDevice(Config->buttons->touch_device, touch_fd);

  for (auto &device : Config->buttons->input_device)
  {
    openDevice(device.first, device.second);
  }

  al_init_user_event_source(&other_input_event_source);
  al_register_event_source(EventQueue, &other_input_event_source);

  thread OtherInputThread { &InputClass::OtherInputThread, this };

  if (test_buttons)
  {
    bool done { false };

    Display->DrawInfoBox(ButtonTestTitleStr, "... press any input button ...", ButtonTestMessageStr, nullptr, false, true);

    while (done == false)
    {
      bool got_input { false };
      stringstream ss { };
      al_wait_for_event(EventQueue, &event);
      switch (event.type)
      {
        case ALLEGRO_EVENT_KEY_DOWN :
          got_input = true;
          ss << ButtonTypeKeyboardStr << " " << event.keyboard.keycode;
          if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
          {
            done = true;
          }
          break;

        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN :
          uint32_t id;
          for (id = 0; id < joystick.size(); ++id)
          {
            if (event.joystick.id == joystick.at(id)) break;
          }
          ss << ButtonTypeJoyButtonStr << " " << event.joystick.button << " " << id;
          // ss << ButtonTypeJoyButtonStr << " " << event.joystick.button;
          got_input = true;
          break;

        case ALLEGRO_EVENT_JOYSTICK_AXIS :
          if ((event.joystick.pos == 1) || (event.joystick.pos == -1))
          {
            uint32_t id;
            for (id = 0; id < joystick.size(); ++id)
            {
              if (event.joystick.id == joystick.at(id)) break;
            }
            int32_t pos = static_cast<int32_t>(event.joystick.pos);
            if (pos == -1) pos = 2; // left = 2, right = 1, centre = 0
            ss << ButtonTypeJoyAxisStr << " " << event.joystick.stick << " " << event.joystick.axis << " " << pos << " " << id;
            got_input = true;
          }
          break;

        case OTHER_INPUT_USER_EVENT :
          if (event.user.data4 == 0) // press (not release) event
          {
            if (event.user.data1 == static_cast<uint32_t>(other_device_e::Touch))
            {
              ss << ButtonTypeTouchStr << " " << event.user.data2 << " " << event.user.data3;
              got_input = true;
            }
            else if (event.user.data1 == static_cast<uint32_t>(other_device_e::GPIO))
            {
              ss << ButtonTypeGPIOStr << " " << event.user.data2;
              got_input = true;
            }
            else if (event.user.data1 == static_cast<uint32_t>(other_device_e::UserDevice))
            {
              ss << ButtonTypeUserDeviceStr << " " << event.user.data2 << " " << event.user.data3;
              got_input = true;
            }
          }
          break;
      }
      if (got_input)
      {
        string info1 { ss.str() };
        Display->DrawInfoBox(ButtonTestTitleStr, info1, ButtonTestMessageStr, nullptr, false, true);
      }
    }
  }
  else
  {
    ofstream btn_file;

    btn_file.open(Config->button_map, ios::out);
    if (!btn_file.is_open())
    {
      error("Can't open %s for output", Config->button_map.c_str());
    }

    btn_file << "# fruitbox " << FRUITBOX_VERSION << " button mapping file" << endl;
    btn_file << "# Missing buttons will assume their default values (see user guide)" << endl << endl;

    for (auto &i : Config->buttons->input_device)
    {
      btn_file << left << setw(16) << cfgKeyword_InputDevice << " = " << i.first << endl;
    }

    if (Config->buttons->touch_device != defaultTouchDevice)
    {
      btn_file << left << setw(16) << cfgKeyword_TouchDevice << " = " << Config->buttons->touch_device << endl;
    }

    if (calibrate_touch && touch_installed)
    {
      CalibrateTouch();
      btn_file << left << setw(16) << cfgKeyword_TouchMin << " = " << Config->buttons->touch_min.x  << " " << Config->buttons->touch_min.y << endl;
      btn_file << left << setw(16) << cfgKeyword_TouchMax << " = " << Config->buttons->touch_max.x  << " " << Config->buttons->touch_max.y << endl;
    }

    btn_file << endl;

    cout << "*****************************************************************" << endl;
    cout << "Configure Buttons : Press input for each button in turn." << endl;
    cout << "Button mappings will be written to '" << Config->button_map << "'" << endl;
    cout << "(This file can be edited afterwards if changes need to be made)" << endl;
    cout << "If you press <ESC> on the keyboard the button will be ignored" << endl;
    cout << "(if you want to map the keyboard <ESC> key to a button, edit " << endl;
    cout << "'" << Config->button_map << "' afterwards and assign the button to 'Keyboard " << ALLEGRO_KEY_ESCAPE << "')." << endl;
    cout << "*****************************************************************" << endl << endl;

    for (uint32_t b = 0; b < Config->buttons->button.size();)
    {
      al_flush_event_queue(EventQueue);
      Display->DrawInfoBox(ConfigureButtonsTitleStr, "Press input for : " + Config->buttons->button.at(b).name + " ...", ConfigureButtonsMessageStr, nullptr, false, true);
      stringstream ss { };

      bool got_input { false };
      bool skip_button { false };

      al_wait_for_event(EventQueue, &event);
      switch (event.type)
      {
        case ALLEGRO_EVENT_KEY_DOWN :
          if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
          {
            skip_button = true;
          }
          else
          {
            ss << ButtonTypeKeyboardStr << " " << event.keyboard.keycode;
            got_input = true;
          }
          break;

        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN :
          uint32_t id;
          for (id = 0; id < joystick.size(); ++id)
          {
            if (event.joystick.id == joystick.at(id)) break;
          }
          ss << ButtonTypeJoyButtonStr << " " << event.joystick.button << " " << id;
          // ss << ButtonTypeJoyButtonStr << " " << event.joystick.button;
          got_input = true;
          break;

        case ALLEGRO_EVENT_JOYSTICK_AXIS :
          if ((event.joystick.pos == -1) || (event.joystick.pos == 1))
          {
            uint32_t id;
            for (id = 0; id < joystick.size(); ++id)
            {
              if (event.joystick.id == joystick.at(id)) break;
            }
            int32_t pos = static_cast<int32_t>(event.joystick.pos);
            if (pos == -1) pos = 2; // left = 2, right = 1, centre = 0
            ss << ButtonTypeJoyAxisStr << " " << event.joystick.stick << " " << event.joystick.axis << " " << pos << " " << id;
            got_input = true;
          }
          break;

        case OTHER_INPUT_USER_EVENT :
          if (event.user.data4 == 0) // press (not release) event
          {
            if (event.user.data1 == static_cast<uint32_t>(other_device_e::Touch))
            {
              ss << ButtonTypeTouchStr;
              got_input = true;
            }
            else if (event.user.data1 == static_cast<uint32_t>(other_device_e::GPIO))
            {
              ss << ButtonTypeGPIOStr << " " << event.user.data2;
              got_input = true;
            }
            else if (event.user.data1 == static_cast<uint32_t>(other_device_e::UserDevice))
            {
              ss << ButtonTypeUserDeviceStr << " " << event.user.data2 << " " << event.user.data3;
              got_input = true;
            }
          }
          break;

      }
      if (got_input)
      {
        Display->DrawInfoBox(ConfigureButtonsTitleStr, "* " + ss.str() + " *", ConfigureButtonsMessageStr, nullptr, false, true);
        sleep(1);
        btn_file << left << setw(16) << Config->buttons->button.at(b).name << " = " << ss.str() << endl;
        ++b;
      }
      else if (skip_button)
      {
        ++b;
      }
    }

    Display->DrawInfoBox(ConfigureButtonsTitleStr, "", "Job Done! Button mappings written to '" + Config->button_map + "'", nullptr, false, true);
    sleep(3);
    btn_file.close();
  }

  al_destroy_event_queue(EventQueue);
  exit(-1);
}

void InputClass::ButtonInputThread(void)
{
  EventQueue = al_create_event_queue();
  if (EventQueue == nullptr) error("Couldn't create event queue");

  if (al_is_keyboard_installed()) al_register_event_source(EventQueue, al_get_keyboard_event_source());
  if (al_is_joystick_installed()) al_register_event_source(EventQueue, al_get_joystick_event_source());
  // if (Config->need_touchscreen)
  // {
    // cout << "DEBUG1 " << Config->buttons->touch_device << endl;
    // touch_installed = openDevice(Config->buttons->touch_device, touch_fd);
    // cout << "DEBUG2" << endl;
    // if (touch_installed == false) error("Couldn't install touchscreen device '%s'", Config->buttons->touch_device.c_str());
    // cout << "DEBUG3" << endl;
  // }

  // open user-defined input devices...
  // for (auto &device : Config->buttons->input_device)
  // {
    // openDevice(device.first, device.second);
  // }

  al_init_user_event_source(&other_input_event_source);
  al_register_event_source(EventQueue, &other_input_event_source);

  thread OtherInputThread { &InputClass::OtherInputThread, this };

  float fpos;

  while (1)
  {
    al_wait_for_event(EventQueue, &event);
    {
      uint32_t id;
      array<uint32_t, 4> param {0, 0, 0, 0};
      button_type_e type { button_type_e::None };
      uint32_t button_flags { 0 };

      // cout << std::hex << time(nullptr) << " INPUT EVENT " << std::dec << event.type << endl;

      switch (event.type)
      {
        case ALLEGRO_EVENT_KEY_DOWN :
        case ALLEGRO_EVENT_KEY_UP :
          type = button_type_e::Keyboard;
          param.at(0) = static_cast<uint32_t>(event.keyboard.keycode);
          button_flags = (event.type == ALLEGRO_EVENT_KEY_UP) ? BUTTON_RELEASED : 0;
          // cout << std::hex << time(nullptr) << " ALLEGRO_EVENT_KEY " << button_flags << endl;
          break;

        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN :
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP :
          type = button_type_e::JoyButton;
          param.at(0) = static_cast<uint32_t>(event.joystick.button);
          for (id = 0; id < joystick.size(); ++id)
          {
            if (event.joystick.id == joystick.at(id)) break;
          }
          param.at(1) = id;
          button_flags = (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP) ? BUTTON_RELEASED : 0;
          // cout << std::hex << time(nullptr) << " ALLEGRO_EVENT_JOYSTICK_BUTTON " << button_flags << endl;
          break;

        case ALLEGRO_EVENT_JOYSTICK_AXIS :
          param.at(0) = static_cast<uint32_t>(event.joystick.stick);
          param.at(1) = static_cast<uint32_t>(event.joystick.axis);
          fpos = event.joystick.pos;
          if ((fpos == -1) || (fpos == 1)) // left or right
          {
            int32_t pos = static_cast<int32_t>(fpos);
            if (pos == -1) pos = 2; // left = 2, right = 1, centre = 0
            param.at(2) = static_cast<uint32_t>(pos);
            type = button_type_e::JoyAxis;
            prev_joystick_pos = pos; // remember for release condition
          }
          else if (fpos < 0.01) // released back to centre
          {
            param.at(2) = static_cast<uint32_t>(prev_joystick_pos); // param.at(2) should reference direction - the release is connected with the direction
            type = button_type_e::JoyAxis;
            button_flags = BUTTON_RELEASED;
          }
          for (id = 0; id < joystick.size(); ++id)
          {
            if (event.joystick.id == joystick.at(id)) break;
          }
          param.at(3) = id;
          // cout << std::hex << time(nullptr) << " ALLEGRO_EVENT_JOYSTICK_AXIS " << button_flags << endl;
          break;

        case OTHER_INPUT_USER_EVENT :
          param.at(0)  = static_cast<uint32_t>(event.user.data2);
          param.at(1)  = static_cast<uint32_t>(event.user.data3);
          button_flags = (static_cast<uint32_t>(event.user.data4)) ? BUTTON_RELEASED : 0;
          if (event.user.data1 == static_cast<uint32_t>(other_device_e::Touch))
          {
            type = button_type_e::Touch;
            if (button_flags & BUTTON_RELEASED)
            // if touch released, disable drawing of touch song bitmap...
            // (even if it doesn't correspond to a touch song region; touch release
            //  implies the user is not touching the screen, so can't by definition
            //  be touching any song region)
            {
              if ((Config->general->select_mode == select_mode_e::TouchSong)) Config->touch_song->no_draw = true;
            }
          }
          else if (event.user.data1 == static_cast<uint32_t>(other_device_e::GPIO))
          {
            type = button_type_e::GPIO;
          }
          else if (event.user.data1 == static_cast<uint32_t>(other_device_e::UserDevice))
          {
            type = button_type_e::UserDevice;
          }
          // cout << std::hex << time(nullptr) << " OTHER_INPUT_USER_EVENT " << button_flags << endl;
          break;
      }
      // now search through our buttons to see if we can match it to a button definition...
      uint32_t button {FindButton(type, param)};

      if (button < NUM_BUTTONS)
      {
        button |= button_flags;
        queue_mtx.lock();
        queue.push_back(button);
        queue_mtx.unlock();
        // cout << std::hex << time(nullptr) << " INPUT QUEUE PUSH " << queue.size() << " " << (button | button_flags) << endl;
      }
      // else if ((Config->general->select_mode == select_mode_e::TouchSong) && (type == button_type_e::Touch))
      else if ((Config->general->select_mode == select_mode_e::TouchSong))
      // no button match found, so if the event is a touch, and we are in TouchSong selection mode,
      // we check to see if the touch is inside any of the song title areas (which include cfg offset and size)...
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
            if (param.at(0) < sx) continue;       // touch x < song title region x
            if (param.at(1) < sy) continue;       // touch y < song title region y
            if (param.at(0) >= (sx+sw)) continue; // touch x >= song title region (x+w)
            if (param.at(1) >= (sy+sh)) continue; // touch y >= song title region (y+h)
            // if we get here then the touch is inside the song title touch area...
            if (!(button_flags & BUTTON_RELEASED))
            {
              Config->touch_song->position.x = sx;
              Config->touch_song->position.y = sy;
              if (PlayQueue->full == false) Config->touch_song->no_draw = false;
              button = TOUCH_SONG | (song_entry << SONG_ENTRY_POS) | (song_page << SONG_PAGE_POS);
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

    this_thread::sleep_for(chrono::milliseconds(10)); // no point in scanning for buttons more than 100 times a second!
  }

  al_destroy_event_queue(EventQueue);
}

uint32_t InputClass::FindButton(const button_type_e type, const array<uint32_t, 4> &param)
{
  if (type == button_type_e::None) return NUM_BUTTONS;


  for (uint32_t b = 0; b < NUM_BUTTONS; ++b)
  {
    if (Config->buttons->button.at(b).type == type)
    {
      if (type == button_type_e::Touch) // need to check touch is within the size of the button area...
      {
        uint32_t bx {Config->buttons->button.at(b).param.at(0)};
        uint32_t by {Config->buttons->button.at(b).param.at(1)};
        uint32_t bw {Config->buttons->button.at(b).param.at(2)};
        uint32_t bh {Config->buttons->button.at(b).param.at(3)};

        if (param.at(0) < bx) continue;       // touch x < button x
        if (param.at(1) < by) continue;       // touch y < button y
        if (param.at(0) >= (bx+bw)) continue; // touch x >= button (x+w)
        if (param.at(1) >= (by+bh)) continue; // touch y >= button (y+h)
        return b; // touch inside button area :)
      }
      else
      {
        if (Config->buttons->button.at(b).param == param) return b;
      }
    }
  }

  return NUM_BUTTONS;
}

///////////////////////////////////////////////////////////////////////////////
// GPIO / Touch Routines

enum class touch_state_e
{
  waiting_for_btn_touch,
  waiting_for_abs_x,
  waiting_for_abs_y,
  idle
};

void InputClass::OtherInputThread(void)
// Polls the GPIO peripheral level register (every 50ms), and if it has changed send an event to the ButtonInputThread
// Polls the touch input device and sends touch events to the ButtonInputThread
// Implements the GPIO Matrix scan
{
  ALLEGRO_EVENT other_input_event;
  other_input_event.user.type = OTHER_INPUT_USER_EVENT;
  volatile uint32_t gpio_levels {};
  touch_state_e touch_state { touch_state_e::waiting_for_btn_touch };
  uint32_t touch_x, touch_y;

  #define DEBOUNCE_PERIOD       8
  #define DEBOUNCE_MASK         ((1 << (DEBOUNCE_PERIOD+1)) - 1)
  #define DEBOUNCE_PRESSED      (0)
  #define DEBOUNCE_RELEASED     (DEBOUNCE_MASK)

  while (1)
  {
    this_thread::sleep_for(chrono::milliseconds(1)); // only check gpio and touch inputs every 1ms (NOTE larger values seem to create more bounce and false edges for some reason!)

    // GPIO ...
    if (Config->need_gpio_input)
    {
      #ifdef _RPI
        gpio_levels = GPLEV[0]; // only check first 32 GPIO pins
      #else
        gpio_levels = 0;
      #endif

      for (uint32_t i = 0; i < NUM_GPIO; ++i)
      {
        if (((1<<i) & gpio_input_mask) == 0) continue; // GPIO pin not an input

        // to de-bounce each pin, maintain a shift register of the levels for each pin...
        gpio_history.at(i) <<= 1;
        gpio_history.at(i) |= gpio_levels & (1 << i) ? 1 : 0;
        gpio_history.at(i) &= DEBOUNCE_MASK;

        uint32_t history { gpio_history.at(i) };
        if (history == DEBOUNCE_PRESSED) gpio_pressed.at(i) = true; // ...DEBOUNCE_PERIOD zeroes in a row
        else if (history == DEBOUNCE_RELEASED) gpio_pressed.at(i) = false; // ...DEBOUNCE_PERIOD ones in a row

        if (gpio_pressed.at(i) != prev_gpio_pressed.at(i))
        {
          other_input_event.user.data1 = static_cast<uint32_t>(other_device_e::GPIO);
          other_input_event.user.data2 = i; // GPIO pin number
          other_input_event.user.data3 = 0; // not used
          other_input_event.user.data4 = history & 1; // 1 = released, 0 = pressed
          // cout << std::hex << time(nullptr) << " GPIO EVENT EMIT " << endl;
          al_emit_user_event(&other_input_event_source, &other_input_event, 0);
          prev_gpio_pressed.at(i) = gpio_pressed.at(i);
        }
      }
    }

    // if (Config->need_gpio_matrix)
    // {
      // for (auto &r : Config->gpio_scan_row) Config->general->gpio.at(r) == gpio_e::Output;
      // for (auto &c : Config->gpio_scan_col) Config->general->gpio.at(c) == gpio_e::Input;
    // }

    // TOUCH ...
    if (touch_installed)
    {
      int i;
      struct input_event ev[64];
      int rb;
      rb = read(touch_fd, ev, sizeof(struct input_event)*64);
      if (rb != -1) // data available
      {
        for (i = 0;  i <  (rb / sizeof(struct input_event)); i++)
        {
          switch (touch_state)
          {
            case touch_state_e::waiting_for_btn_touch :
              if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 1))
              {
                touch_state = touch_state_e::waiting_for_abs_x;
              }
              break;

            case touch_state_e::waiting_for_abs_x :
              if ((ev[i].type == EV_ABS) && (ev[i].code == 0))
              {
                // we transform the touch co-ordinates by first adding the user defined offsets, and then scaling by the user defined scale...
                int32_t value { reversed_touch ? static_cast<int32_t>(Config->buttons->touch_max.x + Config->buttons->touch_min.x - ev[i].value) : static_cast<int32_t>(ev[i].value) };
                touch_x = static_cast<uint32_t>(touch_scale_x * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_x)));
                touch_state = touch_state_e::waiting_for_abs_y;
              }
              break;

            case touch_state_e::waiting_for_abs_y :
              if ((ev[i].type == EV_ABS) && (ev[i].code == 1))
              {
                int32_t value { reversed_touch ? static_cast<int32_t>(Config->buttons->touch_max.y + Config->buttons->touch_min.y - ev[i].value) : static_cast<int32_t>(ev[i].value) };
                touch_y = static_cast<uint32_t>(touch_scale_y * static_cast<double>(static_cast<uint32_t>(value - touch_offset_y)));
                other_input_event.user.data1 = static_cast<uint32_t>(other_device_e::Touch);
                other_input_event.user.data2 = touch_x;
                other_input_event.user.data3 = touch_y;
                other_input_event.user.data4 = 0; // pressed

                // cout << std::hex << time(nullptr) << " TOUCH EVENT EMIT " << endl;
                al_emit_user_event(&other_input_event_source, &other_input_event, 0);
                touch_state = touch_state_e::idle;
              }
              break;

            case touch_state_e::idle :
              break;
          }

          // we check for button release outside of state machine so we can use it to resync the state machine if x/y not received after button press...
          if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 0))
          {
            other_input_event.user.data1 = static_cast<uint32_t>(other_device_e::Touch);
            other_input_event.user.data2 = touch_x;
            other_input_event.user.data3 = touch_y;
            other_input_event.user.data4 = 1; // released
            // cout << std::hex << time(nullptr) << " TOUCH RELEASE EVENT EMIT " << endl;
            al_emit_user_event(&other_input_event_source, &other_input_event, 0);
            touch_state = touch_state_e::waiting_for_btn_touch;
          }
        }
      }
    }

    // USER SPECIFIED DEVICE(S) ...

    for (uint32_t device = 0; device < Config->buttons->input_device.size(); ++device)
    {
      int i;
      struct input_event ev[64];
      int rb;
      int fd {Config->buttons->input_device.at(device).second};
      if (fd == -1) continue;
      rb = read(fd, ev, sizeof(struct input_event)*64);
      if (rb != -1) // data available
      {
        for (i = 0;  i <  (rb / sizeof(struct input_event)); i++)
        {
          if (ev[i].type == EV_KEY)
          {
            other_input_event.user.data1 = static_cast<uint32_t>(other_device_e::UserDevice);
            other_input_event.user.data2 = ev[i].code;
            other_input_event.user.data3 = device;
            if (ev[i].value)
            {
              other_input_event.user.data4 = 0; // pressed
            }
            else
            {
              other_input_event.user.data4 = 1; // released
            }
            // cout << std::hex << time(nullptr) << " OTHER EVENT EMIT " << endl;
            al_emit_user_event(&other_input_event_source, &other_input_event, 0);
          }
        }
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
// GPIO
///////////////////////////////////////////////////////////////////////////////

void InputClass::GPIOInit(void)
// Initialize memory mapped GPIO peripherals */
{
  #ifdef _RPI
    uint32_t mem_fd;
    void *reg_map;

    // check GPIO matrix...
    // Config->need_gpio_matrix = true; // assume we need matrix

    // if (gpio_scan_row.size() == 0) Config->need_gpio_matrix = false;
    // if (gpio_scan_col.size() == 0) Config->need_gpio_matrix = false;

    // make sure rows / columns don't share any GPIO pins...
    // for (auto &r : gpio_scan_row)
    // {
      // if (r > NUM_GPIO) error("Row GPIO %d out of range", r);
      // for (auto &c : gpio_scan_col)
      // {
         // if (c > NUM_GPIO) error("Column GPIO %d out of range", c);
         // if (r == c) error("matrix column GPIO %d already used by matrix row", c);
      // }
    // }

    // set up directions for GPIo matrix (rows = output, columns = inputs)
    // for (auto &r : Config->gpio_scan_row) Config->general->gpio.at(r) == gpio_e::Output;
    // for (auto &c : Config->gpio_scan_col) Config->general->gpio.at(c) == gpio_e::Input;


    if (Config->need_gpio_input || Config->need_gpio_output) // || Config->need_gpio_matrix)
    {
      // /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem
      if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
      {
        error("can't open /dev/mem");
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
        error("gpio mmap error.\nTry running fruitbox as sudo (i.e. sudo ./fruitbox --cfg ...)");
      }

      gpio = (volatile uint32_t *)reg_map;

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

      // setup pin directions for all used inputs (buttons) and outputs (status)
      for (uint32_t g = 0; g < NUM_GPIO; ++g)
      {
        if (Config->general->gpio.at(g) == gpio_e::Input) GPIOConfigurePinAsInput(g);
        // if (Config->general->gpio.at(g) == gpio_e::Output) GPIOConfigurePinAsOutput(g);
      }

    }

  #endif
}

void InputClass::GPIOConfigurePinAsInput(const uint32_t pin)
{
  #ifdef _RPI
    // Determine FPSEL register offset and bit shift
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
  #else
    cout << NOTE << "Setting GPIO " << pin << " as input" << endl;
  #endif
}

void InputClass::GPIOConfigurePinAsOutput(const uint32_t pin)
{
  #ifdef _RPI
    // Determine FPSEL register offset and bit shift
    uint32_t offset, shift;
    offset = pin / 10;
    shift = (pin % 10) * 3;

    //Clear the bits in FSELn
    GPFSEL[offset] &= ~(0b111 << shift);

    //Set the bits to the output function (1)
    GPFSEL[offset] |= (1 << shift);
  #else
    cout << NOTE << "Setting GPIO " << pin << " as output" << endl;
  #endif
}

void InputClass::GPIOSetPin(const uint32_t pin)
{
  #ifdef _RPI
    uint32_t offset = static_cast<uint32_t>((pin < 32) ? 0 : 1);
    uint32_t pin_mask { static_cast<uint32_t>(0x1 << (pin % 32)) };
    GPSET[offset] = pin_mask;
  #else
    cout << NOTE << "Setting GPIO " << pin << " output high" << endl;
  #endif
}

void InputClass::GPIOClrPin(const uint32_t pin)
{
  #ifdef _RPI
    uint32_t offset = static_cast<uint32_t>((pin < 32) ? 0 : 1);
    uint32_t pin_mask { static_cast<uint32_t>(0x1 << (pin % 32)) };
    GPCLR[offset] = pin_mask;
  #else
    cout << NOTE << "Setting GPIO " << pin << " output low" << endl;
  #endif
}

uint32_t InputClass::GPIOReadPin(const uint32_t pin)
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

