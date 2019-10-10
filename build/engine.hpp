#pragma once

#include "fruitbox.hpp"

constexpr uint32_t SEL_DIG0_FIRST  { 0 };
constexpr uint32_t SEL_DIG0_LAST   { 1 };
constexpr uint32_t SEL_DIG1_FIRST  { 2 };
constexpr uint32_t SEL_DIG1_LAST   { 3 };

class EngineClass {
public:
  EngineClass();
  ~EngineClass();
  void Run(void);
  string IntToSel(const int32_t selection);
  uint32_t SelToInt(const string &sel_code);
  uint32_t max_select_code;
  uint32_t sel_code_timer { };
  uint32_t auto_page_turn_timer { };
  uint32_t auto_play_timer { };
  uint32_t status_event { };
  uint32_t next_status_event { };
  uint32_t joy_x { };
  uint32_t joy_y { };
  bool mute { false };
  bool invalid_choice { false };
  bool duplicate_choice { false };
  string StrMS(uint32_t ms) {
    stringstream s;
    s << setfill('0') << setw(2) << SecondsToMinutes(ms) << ":"
      << setfill('0') << setw(2) << SecondsToSeconds(ms);
    return s.str();
  }
  uint64_t button_pressed_mask {0};
  video_t song_video {};
  bool song_playing { false };
  
private:
  void UpdateSelectCode(const uint32_t page, const uint32_t entry);
  void UpdateSelectCode(const char c);
  void CheckAndAddSelection(void);
  void UpdateJoystickPositions(const uint32_t x, const uint32_t y);
  song_t* SelectSong(const string &sel_code);
  song_t* SelectSong(const uint32_t x, const uint32_t y);
  int32_t select_code_digit { };
  int32_t start_page { };
  int32_t selected_song_page { };
  uint32_t page_jump { 1 };
  uint32_t now_playing_paused_time { };
};
