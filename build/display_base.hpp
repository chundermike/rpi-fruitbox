#pragma once

#include "fruitbox.hpp"

using namespace std;

class DisplayBaseClass : public ConfigBaseClass {
public:
  virtual void init(const uints2_t sze, const uint32_t emsk) {
    size = sze;
    event_mask = emsk;
    bitmap = al_create_bitmap(size.x, size.y);
    if (bitmap == nullptr) error("Couldn't create %d x %d display object bitmap", size.x, size.y);
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgba(0,0,0,0));
  }

  virtual void init(const uints2_t sze, const uint32_t emsk, const string bitmap_name) {
    size = sze;
    event_mask = emsk;
    if (bitmap_name.size() == 0) return;
    bitmap = al_load_bitmap(bitmap_name.c_str());
    if (bitmap == nullptr) error("Couldn't load display object bitmap '%s'", bitmap_name.c_str());
  }

  virtual void update(const uint32_t event) {};

  virtual void renew(void) {};

  virtual void draw(void) {
    if (no_draw) return;
    if (bitmap != nullptr) {
      if (angle)
      {
        float ang = static_cast<float>(angle) * (ALLEGRO_PI / 180.0);
        int bw { al_get_bitmap_width(bitmap) };
        int bh { al_get_bitmap_height(bitmap) };
        float cx { static_cast<float>(bw >> 1) };
        float cy { static_cast<float>(bh >> 1) };
        float sx { static_cast<float>(size.x) / static_cast<float>(bw) };
        float sy { static_cast<float>(size.y) / static_cast<float>(bh) };
        al_draw_scaled_rotated_bitmap(bitmap, cx, cy, position.x + (size.x >> 1), position.y + (size.y >> 1), sx, sy, ang, 0);
      }
      else
      {
        al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), position.x, position.y, size.x, size.y, 0);
      }
    }
  }

  void cfgRead(string line) {
    if (GetParam(line, cfgKeyword_Size, size)) return;
    if (GetParam(line, cfgKeyword_Position, position)) return;
    if (GetParam(line, cfgKeyword_Angle, angle)) return;
  }

  void cfgShow(const char *indent) {
    cfgShowEntry(indent, cfgKeyword_Size    , cfgKeywordDesc_Size    , false);
    cfgShowEntry(indent, cfgKeyword_Position, cfgKeywordDesc_Position, false);
    cfgShowEntry(indent, cfgKeyword_Angle   , cfgKeywordDesc_Angle   , false);
  }

  virtual DisplayBaseClass* clone() const = 0;

  uints2_t size {};
  ints2_t position {};
  uint32_t angle { 0 };
  bool no_draw { false };

protected:
  ALLEGRO_BITMAP *bitmap {};
  uint32_t event_mask { StatusEvent_initEmpty };
};
