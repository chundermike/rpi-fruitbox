#pragma once

#include "fruitbox.hpp"

using namespace std;

class JoystickDisplayClass : public DisplayBaseClass {
public:

  void init(const uints2_t sze, const uint32_t emsk);

  void cfgRead(string line) {
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Bitmap, bitmap_name)) return;
    if (GetParam(line, cfgKeyword_Offset, offset)) return;
  }

  virtual JoystickDisplayClass* clone() const { return new JoystickDisplayClass(*this); }

  virtual void cfgShow(const char *indent) {
    cfgShowEntry(indent, cfgKeyword_Bitmap, cfgKeywordDesc_Bitmap, false);
    cfgShowEntry(indent, cfgKeyword_Offset, cfgKeywordDesc_JoystickOffset, false);
    cfgShowEntry(indent, cfgKeyword_Size,   cfgKeywordDesc_JoystickSize, false);
    cfgShowEntry(indent, cfgKeyword_Angle,  cfgKeywordDesc_Angle, false);
  }

  void setPosition(const uint32_t x, const uint32_t y)
  {
    // here, the base class position is an offset to the calculated position...
    // position.x = static_cast<uint32_t>(static_cast<int32_t>(entry_position.at(x).at(y).x) + offset.x);
    // position.y = static_cast<uint32_t>(static_cast<int32_t>(entry_position.at(x).at(y).y) + offset.y);
    position.x = static_cast<uint32_t>(static_cast<int32_t>(entry_position.at(x).at(y).x));
    position.y = static_cast<uint32_t>(static_cast<int32_t>(entry_position.at(x).at(y).y));
  }

  vector< vector<ints2_t> > entry_position { };

  ints2_t offset {};

  virtual void draw(void);

private:
  string bitmap_name {};
};

class TouchSongDisplayClass : public JoystickDisplayClass {
public:

  void cfgShow(const char *indent) {
    cfgShowEntry(indent, cfgKeyword_Bitmap, cfgKeywordDesc_Bitmap, false);
    cfgShowEntry(indent, cfgKeyword_Offset, cfgKeywordDesc_TouchSongOffset, false);
    cfgShowEntry(indent, cfgKeyword_Size,   cfgKeywordDesc_JoystickSize, false);
    cfgShowEntry(indent, cfgKeyword_Angle,  cfgKeywordDesc_Angle, false);
  }

  TouchSongDisplayClass* clone() const { return new TouchSongDisplayClass(*this); }

  void draw(void); // we don't want to inherit the JoystickDisplayClass::draw as it is specific to joysticks

};
