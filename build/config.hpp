#pragma once

#include "fruitbox.hpp"

using namespace std;

class ConfigClass  : public ConfigBaseClass
{
public:
  ConfigClass(void);
  bool Load(const string cfg_filename);
  void LoadButtons(const string filename);
  void ChooseMenu(const string choose_cfg_filename, string &filename);
  void LoadChooserScreenshot(ChooserConfigClass *chooser);
  void PostProcess(void);

  GeneralConfigClass       *general {};
  TouchAreasConfigClass    *touch_areas {};
  ButtonsConfigClass       *buttons {};
  TouchSongDisplayClass    *touch_song {};
  SoundConfigClass         *sounds {};
  vector<FontConfigClass*>  fonts {};
  vector<DisplayBaseClass*> display_object {};

  void cfgShow(const char *indent)
  {
    if (userguidecfgShow) // messy hack
    {
      userguide << indent << cfgSection_general << endl;
      general->cfgShow(indent);

      userguide << endl << indent << cfgSection_touch_areas << endl;
      touch_areas->cfgShow(indent);

      userguide << endl << indent << cfgSection_sounds << endl;
      sounds->cfgShow(indent);

      userguide << endl << indent << cfgSection_font << multiCfgParameter << endl;
      tmp_font->cfgShow(indent);

      userguide << endl << indent << cfgSection_page << multiCfgParameter << endl;
      tmp_page->cfgShow(indent);

      userguide << endl << indent << cfgSection_status << multiCfgParameter << endl;
      tmp_status->cfgShow(indent);

      userguide << endl << indent << cfgSection_bitmap << multiCfgParameter << endl;
      tmp_bitmap->cfgShow(indent);

      userguide << endl << indent << cfgSection_joystick << multiCfgParameter << endl;
      tmp_joystick->cfgShow(indent);

      userguide << endl << indent << cfgSection_touch_song << endl;
      tmp_touch_song->cfgShow(indent);

      userguide << endl;
    }
    else
    {
      log_file << indent << cfgSection_general << endl;
      general->cfgShow(indent);

      log_file << endl << indent << cfgSection_touch_areas << endl;
      touch_areas->cfgShow(indent);

      log_file << endl << indent << cfgSection_sounds << endl;
      sounds->cfgShow(indent);

      log_file << endl << indent << cfgSection_font << multiCfgParameter << endl;
      tmp_font->cfgShow(indent);

      log_file << endl << indent << cfgSection_page << multiCfgParameter << endl;
      tmp_page->cfgShow(indent);

      log_file << endl << indent << cfgSection_status << multiCfgParameter << endl;
      tmp_status->cfgShow(indent);

      log_file << endl << indent << cfgSection_bitmap << multiCfgParameter << endl;
      tmp_bitmap->cfgShow(indent);

      log_file << endl << indent << cfgSection_joystick << multiCfgParameter << endl;
      tmp_joystick->cfgShow(indent);

      log_file << endl << indent << cfgSection_touch_song << endl;
      tmp_touch_song->cfgShow(indent);

      log_file << endl;
    }
  }

  void cfgRead(string line) {};

  bool need_touchscreen { false };
  bool screenshot { false };
  bool choose_cfg { false };
  bool no_scale { false };
  uint32_t auto_genre_select {};
  array<bool, 4> status_flag {};

  uint32_t num_sound_channels { 7 }; /* mp3, coin, page move, load_song, unload_song, invalid song, song video ... video sound channels are added when video onjects are defined */

  string filename {};
  string button_map { defaultButtonFilename };
  vector<uint32_t> select_digit_base {};

private:
  FontConfigClass *tmp_font {};
  PageDisplayClass *tmp_page {};
  StatusDisplayClass *tmp_status {};
  BitmapDisplayClass *tmp_bitmap {};
  JoystickDisplayClass *tmp_joystick {};
  TouchSongDisplayClass *tmp_touch_song {};

  bool addObject(ConfigBaseClass * obj)
  {
    DisplayBaseClass *o = dynamic_cast<DisplayBaseClass*>(obj);
    if (o != nullptr)
    { // object is a display object...
      display_object.push_back(o->clone());
      o->renew();
      return true;
    }

    FontConfigClass *f = dynamic_cast<FontConfigClass*>(obj);
    if (f != nullptr)
    { // object is a font...
      if ((f->font.handle = al_load_ttf_font(f->font.filename.c_str(), -f->font.size, 0)) == nullptr) error("Failed to create %d-pt font '%s'", f->font.size, f->font.filename.c_str());
      fonts.push_back(f->clone());
      return true;
    }
    return false;
  };
};
