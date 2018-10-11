#include "fruitbox.hpp"

using namespace std;

void JoystickDisplayClass::init
(
  const uints2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(sze, emsk, bitmap_name);
}

void JoystickDisplayClass::draw(void)
{
  if (status.pages_idle) DisplayBaseClass::draw();
}

void TouchSongDisplayClass::draw(void)
{
  DisplayBaseClass::draw();
}

