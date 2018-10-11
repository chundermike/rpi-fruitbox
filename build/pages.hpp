#pragma once

#include "fruitbox.hpp"

using namespace std;

constexpr uint32_t animation_pages       { 2 };
constexpr uint32_t num_page_move_effects { 7 };

enum class animate_direction_e {
 animate_left,
 animate_right
};

struct ani_t {
  int32_t x, y, w, h, a;
};

struct animate_t {
  ani_t init;
  ani_t delta;
  int32_t fade;      // 0 = no fade, 1 = fade to/from black, 2 = fade to/from alpha
  int32_t top_layer; // page drawn second
  int32_t horz;      // horizontal movement (needed for calculation of animation_steps)
};

enum class page_state_t {
  init, idle, wait_move_delay, moving
};

class PageDisplayClass : public DisplayBaseClass {
public:
  void init(const uints2_t sze, const uint32_t emsk);

  void update(const uint32_t event) override;

  void cfgRead(string line) {
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Background, background_bitmap)) return;
    if (GetParam(line, cfgKeyword_MoveDelay, move_delay)) return;
  }

  void cfgShow(const char *indent) {
    // DisplayBaseClass::cfgShow(indent); // don't use this as don't use base class size (use Config->general->page_size instead)
    cfgShowEntry(indent, cfgKeyword_Position  , cfgKeywordDesc_Position  , false);
    cfgShowEntry(indent, cfgKeyword_Angle     , cfgKeywordDesc_Angle     , false);
    cfgShowEntry(indent, cfgKeyword_Background, cfgKeywordDesc_Background, false);
    cfgShowEntry(indent, cfgKeyword_MoveDelay , cfgKeywordDesc_MoveDelay , false);
  }

  PageDisplayClass* clone() const { return new PageDisplayClass(*this); }

  // remember that static class member variables are shared amongst all page class instances...
  static uint32_t page_offset; // page offset within display
  static uint32_t start_page;  // start page in database
  static bool idle;  // true if all pages idle

  void renew(void) {
    if (background_bitmap.handle)
    // background defined from previous page so make this null otherwise any new page backgrounds
    // for different pages will be ignored (by GetParam)
    {
      background_bitmap.handle = nullptr;
    }
  };
  
  
private:
  bitmap_t background_bitmap {};
  uint32_t move_delay {};
  uint32_t move_delay_timer {};

  page_state_t state { page_state_t::init };
  array <ALLEGRO_BITMAP*, animation_pages> page_bitmap {};
  array <bitmap_t, animation_pages> album_coverart_bitmap {};
  void ConstructDescription(const vector<pair<title_desc_e, string>> &var, string &desc, const song_t *song, const song_t *paired_song);
  void ConstructSinglesPage(void);
  void ConstructAlbumsPage(void);
  void ConstructPage(void);
  uint32_t page_toggle {};
  
  uint32_t animateInit(const uint32_t ani_num);
  bool animatePage(void);
  animate_direction_e animate_direction {};
  float animation_steps {};
  ani_t move[animation_pages];
  ani_t move_delta[animation_pages];
  const animate_t *Animate[animation_pages];
};

