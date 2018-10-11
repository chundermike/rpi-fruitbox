#pragma once

#include "fruitbox.hpp"

using namespace std;

constexpr uint32_t InfoBoxWidth       { 620 };
constexpr uint32_t InfoBoxHeight      { 200 };
constexpr int32_t  InfoBoxTextHeight  { 26 };

class DisplayClass {
public:
  DisplayClass();
  ~DisplayClass();
  void DrawJukebox(const bool flip_display);
  void DrawChooseMenu(const bool selected);
  void DrawText(ALLEGRO_BITMAP *bitmap, const text_t &text, const int32_t x, const int32_t y, const string &str);
  ALLEGRO_DISPLAY_MODE display_size {};
  // uints2_t actual_display_size {};
  ALLEGRO_BITMAP *fruitbox_logo_bm {};
  ALLEGRO_BITMAP *jukebox {};
  ALLEGRO_DISPLAY *display {};
  void LogoSpinUp(void);
  void JukeboxFadeIn(void);
  void LogoFadeOut(void);
  void DrawInfoBox(const string &title, const string &info1, const string &info2, ALLEGRO_BITMAP *background, bool draw_arrows, bool flip);
  void DrawTouchTarget(uint32_t x, uint32_t y);
  uints2_t info_box_pos {};
  // bool redraw { false };
private:
  splash_state_t splash_state {};
  ALLEGRO_BITMAP *info_bkgnd_bm {};
  ALLEGRO_BITMAP *chooser_arrow_bm {};
  uint32_t choose_arrow_pos {};
  bool choose_arrow_pos_inc {true};
  ALLEGRO_FILE *info_font_f {};
  ALLEGRO_FONT *info_font {};
  text_t info_title_text {};
  text_t info_status1_text {};
  text_t info_status2_text {};
  void CapitaliseAndQuote(string &str, const bool cap_en, const bool quo_en);
  void SetText(text_t &text, const int32_t font_number,const uint32_t colour_r, const uint32_t colour_g, const uint32_t colour_b,
               const uint32_t colour_a, const int32_t alignment, const bool capitalise, const bool condense, const bool quoted,
               const int32_t offset_x, const int32_t offset_y, const uint32_t max_width);
  string caq_str;
};

