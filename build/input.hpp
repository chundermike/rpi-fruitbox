#pragma once

#include "fruitbox.hpp"

#define BUTTON_QUIT              0
#define BUTTON_INSERT_COIN1      1
#define BUTTON_INSERT_COIN2      2
#define BUTTON_INSERT_COIN3      3
#define BUTTON_INSERT_COIN4      4
#define BUTTON_VOL_UP            5
#define BUTTON_VOL_DOWN          6
#define BUTTON_ADD_RANDOM        7
#define BUTTON_SELECT            8
#define BUTTON_SKIP              9
#define BUTTON_PAUSE             10
#define BUTTON_UP                11
#define BUTTON_DOWN              12
#define BUTTON_LEFT              13
#define BUTTON_RIGHT             14
#define BUTTON_LEFT_JUMP         15
#define BUTTON_RIGHT_JUMP        16
#define BUTTON_LEFT_ALPHA        17
#define BUTTON_RIGHT_ALPHA       18
#define BUTTON_AUTO_PLAY_TOG     19    
#define BUTTON_LOOP_TOG          20    
#define BUTTON_FREEPLAY_TOG      21    
#define BUTTON_CLEAR_QUEUE       22    
#define BUTTON_MUTE              23    
#define BUTTON_POWER_OFF         24
#define BUTTON_0                 25    
#define BUTTON_1                 26    
#define BUTTON_2                 27    
#define BUTTON_3                 28    
#define BUTTON_4                 29    
#define BUTTON_5                 30    
#define BUTTON_6                 31    
#define BUTTON_7                 32    
#define BUTTON_8                 33    
#define BUTTON_9                 34    
#define BUTTON_A                 35    
#define BUTTON_B                 36    
#define BUTTON_C                 37    
#define BUTTON_D                 38    
#define BUTTON_E                 39    
#define BUTTON_F                 40    
#define BUTTON_G                 41    
#define BUTTON_H                 42    
#define BUTTON_I                 43    
#define BUTTON_J                 44  
#define BUTTON_K                 45
#define BUTTON_FLAG_1            46
#define BUTTON_FLAG_2            47
#define BUTTON_FLAG_3            48
#define BUTTON_FLAG_4            49
#define NUM_BUTTONS              50

#define BUTTON_MASK              0x000000ff
#define BUTTON_RELEASED          0x80000000
#define TOUCH_SONG               0x40000000
#define SONG_PAGE_POS            8
#define SONG_ENTRY_POS           16
#define SONG_POS_MASK            0xff


#define NUM_GPIO                 28

struct gpio_regs_t
{
  uint32_t gpfsel[6];
  uint32_t gpren[2];
  uint32_t gpfen[2];
  bool saved {false};
};

class InputClass
{
public:
  InputClass(bool i_config_buttons, bool i_test_buttons, bool i_calibrate_touch);
  void Start(void);
  ~InputClass();
  deque<uint32_t> queue { };
  std::mutex queue_mtx {};
  void GPIOConfigurePinAsInput(const uint32_t pin);
  void GPIOConfigurePinAsOutput(const uint32_t pin);
  uint32_t GPIOReadPin(const uint32_t pin);
  void GPIOSetPin(const uint32_t pin);
  void GPIOClrPin(const uint32_t pin);
  bool touch_installed {false};
  // int32_t touch_max_x { 0 };
  // int32_t touch_max_y { 0 };
  // int32_t touch_min_x { 0 };
  // int32_t touch_min_y { 0 };
  double touch_scale_x { 1.0 };
  double touch_scale_y { 1.0 };
  int32_t touch_offset_x { 0 };
  int32_t touch_offset_y { 0 };
  bool openDevice(const string &name, int &fd);
  int touch_fd;
  bool reversed_touch {false};
private:
  gpio_regs_t gpio_regs {};
  bool config_buttons {false};
  bool test_buttons {false};
  bool calibrate_touch {false};
  void GenerateButtonFile(void);
  void ButtonInputThread(void);
  // bool openTouchScreen(void);
  uint32_t FindButton(const button_type_e type, const array<uint32_t, 4> &param);
  void GPIOInit(void);
  void CalibrateTouch(void);
  void OtherInputThread(void);
  // void GetTouchMaxMin(int fd);
  ALLEGRO_EVENT event {};
  ALLEGRO_EVENT_QUEUE *EventQueue {};
  ALLEGRO_EVENT_SOURCE other_input_event_source;
  volatile uint32_t *gpio {};
  uint32_t gpio_input_mask {};
  array<uint32_t, NUM_GPIO> gpio_history {};
  array<bool, NUM_GPIO> gpio_pressed {};
  array<bool, NUM_GPIO> prev_gpio_pressed {};
  float prev_joystick_pos {};
  vector <ALLEGRO_JOYSTICK*> joystick {};
};
