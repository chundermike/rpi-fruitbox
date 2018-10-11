#pragma once

#include "fruitbox.hpp"

using namespace std;

class BitmapDisplayClass : public DisplayBaseClass {
public:
  void update(const uint32_t event) override;

  void init(const uints2_t sze, const uint32_t emsk);

  void cfgRead(string line)
  {
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_File, bitmap_name)) return;
    if (GetParam(line, cfgKeyword_HorzScale, horz_scale)) return;
    if (GetParam(line, cfgKeyword_HorzScaleMode, horz_scale_mode)) return;
    if (GetParam(line, cfgKeyword_VertScale, vert_scale)) return;
    if (GetParam(line, cfgKeyword_VertScaleMode, vert_scale_mode)) return;
    if (GetParam(line, cfgKeyword_ReverseClip, reverse_clip)) return;
  }

  void cfgShow(const char *indent)
  {
    DisplayBaseClass::cfgShow(indent);
    cfgShowEntry(indent, cfgKeyword_File, cfgKeywordDesc_BitmapFile, false);
    cfgShowEntry(indent, cfgKeyword_HorzScale, cfgKeywordDesc_HorzScale, false);
    cfgShowEntry(indent, cfgKeyword_HorzScaleMode, cfgKeywordDesc_HorzScaleMode, false);
    cfgShowEntry(indent, cfgKeyword_VertScale, cfgKeywordDesc_VertScale, false);
    cfgShowEntry(indent, cfgKeyword_VertScaleMode, cfgKeywordDesc_VertScaleMode, false);
    cfgShowEntry(indent, cfgKeyword_ReverseClip, cfgKeywordDesc_ReverseClip, false);
  }

  BitmapDisplayClass* clone() const { return new BitmapDisplayClass(*this); }

  void draw(void);

private:
  string bitmap_name {};
  float h_scale_factor { 1.0 };
  float v_scale_factor { 1.0 };
  uint32_t h_clip { 0 };
  uint32_t v_clip { 0 };
  bool reverse_clip { false };
  bitmap_scale_e horz_scale { bitmap_scale_e::None };
  bitmap_scale_mode_e horz_scale_mode { bitmap_scale_mode_e::Scaled };
  bitmap_scale_e vert_scale { bitmap_scale_e::None };
  bitmap_scale_mode_e vert_scale_mode { bitmap_scale_mode_e::Scaled };
};

