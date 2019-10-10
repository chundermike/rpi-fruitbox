///////////////////////////////////////////////////////////////////////////////
// Project fruitbox.  A Retro MP3 Jukebox for the Raspberry Pi.
// Mike Kingsley 2016.
//
// Reads fruitbox and skin configuration files.
///////////////////////////////////////////////////////////////////////////////

#include "fruitbox.hpp"

using namespace std;

string ConfigBaseClass::filepath {};

ConfigClass::ConfigClass(void)
{
  general        = new GeneralConfigClass();
  buttons        = new ButtonsConfigClass();
  touch_areas    = new TouchAreasConfigClass();
  sounds         = new SoundConfigClass();

  tmp_font       = new FontConfigClass ();
  tmp_page       = new PageDisplayClass ();
  tmp_status     = new StatusDisplayClass ();
  tmp_bitmap     = new BitmapDisplayClass ();
  tmp_joystick   = new JoystickDisplayClass ();
  tmp_touch_song = new TouchSongDisplayClass();
}

void ConfigClass::ChooseMenu(const string choose_cfg_filename, string &filename)
{
  bool select { false };
  ifstream chooserFile;
  string line;

  // open choose_cfg_filename
  log_file << "Reading skin chooser file '" << choose_cfg_filename << "'..." << endl;
  chooserFile.open(choose_cfg_filename, ios::in);
  if (!chooserFile.is_open()) error("Couldn't open '%s' for input", choose_cfg_filename.c_str());

  // read all entries in cfg_file array (i.e. all Files = ... lines)
  while (getline(chooserFile, line))
  {
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    Chooser->cfgRead(line); // get File name from chooser file
  }
  chooserFile.close();

  if (Chooser->cfg_file.size() == 0)
  {
     error("No 'File' entries in '%s'", choose_cfg_filename.c_str());
  }

  // configure touch areas for chooser screen

  uint32_t posx = Display->info_box_pos.x;
  uint32_t posy = Display->info_box_pos.y;

  for (uint32_t b = 0; b < NUM_BUTTONS; ++b)
  {
   // all buttons touch areas default to info box ...
    touch_areas->touch_area.at(b).x = posx;
    touch_areas->touch_area.at(b).y = posy;
    touch_areas->touch_area.at(b).w = InfoBoxWidth;
    touch_areas->touch_area.at(b).h = InfoBoxHeight;
  }
  // touch on left arrow
  touch_areas->touch_area.at(BUTTON_LEFT).x = 0;
  touch_areas->touch_area.at(BUTTON_LEFT).w = posx;

  // touch on right arrow
  touch_areas->touch_area.at(BUTTON_RIGHT).x = posx + InfoBoxWidth;
  touch_areas->touch_area.at(BUTTON_RIGHT).w = posx;

  // for buttons napped to touch, we (temporarily) copy the choser touch areas to the button touch areas...
  for (uint32_t b = 0; b < buttons->button.size(); ++b)
  {
    if (buttons->button.at(b).type == input_type_e::Touch)
    {
      buttons->button.at(b).param.at(0) = touch_areas->touch_area.at(b).x;
      buttons->button.at(b).param.at(1) = touch_areas->touch_area.at(b).y;
      buttons->button.at(b).param.at(2) = touch_areas->touch_area.at(b).w;
      buttons->button.at(b).param.at(3) = touch_areas->touch_area.at(b).h;
    }
  }

  Chooser->current_cfg = 0;

  Chooser->LoadScreenshot();
  Display->DrawChooseMenu(false);

  while (select == false)
  {
    if (Input->queue.size())
    {
      Input->queue_mtx.lock();
      uint32_t event_code = Input->queue.front();
      uint32_t keycode = event_code & BUTTON_MASK;
      Input->queue.pop_front();
      Input->queue_mtx.unlock();
      if ((event_code & (BUTTON_RELEASED | TOUCH_SONG)) == 0)
      {
        switch (keycode)
        {
          case BUTTON_LEFT :
            if (Chooser->current_cfg == 0)
            {
              Chooser->current_cfg = Chooser->cfg_file.size() - 1;
            }
            else
            {
              Chooser->current_cfg--;
            }
            Chooser->LoadScreenshot();
            break;

          case BUTTON_RIGHT :
            if (Chooser->current_cfg == Chooser->cfg_file.size() - 1)
            {
              Chooser->current_cfg = 0;
            }
            else
            {
              Chooser->current_cfg++;
            }
            Chooser->LoadScreenshot();
            break;

          default :
            select = true;
            break;
        }
      }
    }
    Display->DrawChooseMenu(select);
  }

  if (Chooser->screenshot_bm)
  {
    al_destroy_bitmap(Chooser->screenshot_bm);
    Chooser->screenshot_bm = nullptr;
  }

  filename = Chooser->cfg_file.at(Chooser->current_cfg);
}

void ConfigClass::LoadButtons(const string filename)
{
  ifstream btnFile;
  string line;

  btnFile.open(filename, ios::in);
  if (!btnFile.is_open()) return;

  log_file << "Loading button mapping file '" << filename << "'..." << endl;

  while (getline(btnFile, line))
  {
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    buttons->cfgRead(line); // get buttons
  }

  btnFile.close();

  // check if we need touchscreen...
  for (auto &b : buttons->button)
  {
    if (b.type == input_type_e::Touch) need_touchscreen = true;
  }

  // // check if we need GPIO input...
  for (auto &b : buttons->button)
  {
    if (b.type == input_type_e::GPIO)
    {
      int32_t pin { b.param.at(EVENT_PARAM_VAL1) };

      if (pin < NUM_GPIO)
      {
        Gpio->ConfigurePinAsInput(pin);
      }
      else
      {
        error("Invalid GPIO number (%d)", pin);
      }
    }
  }

}

bool ConfigClass::Load(const string cfg_filename)
{
  ifstream cfgFile;
  string line;
  uint32_t cfgFile_line_number {};

  ConfigBaseClass::filepath = cfg_filename.substr(0, cfg_filename.find_last_of("/"));

  filename =  cfg_filename;

  cfgFile.open(cfg_filename, ios::in);

  if (!cfgFile.is_open())
  {
    error("Couldn't open configuration file '%s' for input", cfg_filename.c_str());
  }

  log_file << "Reading configuration '" << cfg_filename << "'..." << endl;

  ConfigBaseClass *obj { general };

  while (getline(cfgFile, line))
  {
    cfgFile_line_number++;
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    if (line.at(0) == cfgFile_section_start)
    { // a new section...
      addObject(obj); // add previous object to list (as appropriate)
      log_file << endl << "  " << line << endl;
      if (line.find(cfgSection_general) != string::npos)
      {
        obj = general;
      }
      else if (line.find(cfgSection_touch_song) != string::npos)
      {
        obj = tmp_touch_song;
      }
      else if (line.find(cfgSection_touch_areas) != string::npos)
      {
        obj = touch_areas;
      }
      else if (line.find(cfgSection_sounds) != string::npos)
      {
        obj = sounds;
      }
      else if (line.find(cfgSection_font) != string::npos)
      {
        obj = tmp_font;
      }
      else if (line.find(cfgSection_page) != string::npos)
      {
        obj = tmp_page;
        general->num_pages++;
      }
      else if (line.find(cfgSection_status) != string::npos)
      {
        obj = tmp_status;
      }
      else if (line.find(cfgSection_bitmap) != string::npos)
      {
        obj = tmp_bitmap;
      }
      else if (line.find(cfgSection_joystick) != string::npos)
      {
        obj = tmp_joystick;
      }
      else
      {
        log_file << WARNING << "Unrecognised section (line " << cfgFile_line_number << ")" << endl;
        obj = nullptr;
      }
    } else { // no section character, so assume a config parameter...
      if (obj != nullptr) obj->cfgRead(line);
    }
  }
  addObject(obj); // add last object to list

  cfgFile.close();

  log_file << endl;

  if (general->num_pages == 0) error("Must define at least one [page]");

  return true;
}

void ConfigClass::PostProcess(void)
{
  // sanity / dependency checks...
  if ((general->skin_size.x == 0 ) || (general->skin_size.y == 0)) error("SkinSize not specified");

  Display->jukebox = al_create_bitmap(general->skin_size.x, general->skin_size.y);
  if (Display->jukebox == nullptr) error("Failed to create %d x %d jukebox bitmap", general->skin_size.x, general->skin_size.y);

  if (general->num_pages == 0) error("Must define at least one [page]");
  if (general->songs_per_page == 0) error("%s must be greater than zero", cfgKeyword_SongsPerPage);
  if (general->max_playlist_length == 0) error("%s must be greater than zero", cfgKeyword_MaxPlaylistLength);
  for (auto &p : general->plays_per_coin)
  {
    if (p) general->free_play = false; // plays_per_coin not zero so turn free play off
  }
  if ((general->songs_per_page == 1) && general->pair_songs != pair_songs_e::No) error("Can't enable %s if %s is less than 2", cfgKeyword_PairSongs, cfgKeyword_SongsPerPage);
  if (general->page_move_style.effect >= num_page_move_effects) error("%s effect should be less than %d", cfgKeyword_PageMoveStyle, num_page_move_effects);
  if (general->auto_play) auto_genre_select = 1 ; // force starting auto_genre to GenreAnyStr if auto_play set to 1

  // Add extra sound channels to default ones if status objects contain video clips...
  Config->num_sound_channels += StatusDisplayClass::num_sound_channels;

  if (!al_reserve_samples(Config->num_sound_channels)) error("Couldn't reserve audio samples");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  if (general->select_buttons.size() == 0) // cfg file has defined any select keys so use default
  {
    general->select_buttons.push_back(defaultFirstSelectButtons);
    general->select_buttons.push_back(defaultSecondSelectButtons);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////
  // processing of select buttons...

  status.select_code_str.assign(general->select_buttons.size(), '-');  // initialise empty select code string

  // check that there are enough select key code combinations for the number of songs on screen...

  uint32_t visible_pages { 0 };

  for (auto &i : display_object)
  {
    if (dynamic_cast<PageDisplayClass*>(i) != nullptr) visible_pages++;
  }

  uint32_t select_codes  { 1 };

  for (auto &s : general->select_buttons) 
  {
    select_codes *= s.size();
  }

  uint32_t selectable_entries { visible_pages };
  
  if (general->page_mode == page_mode_e::Singles)
  {
    selectable_entries *= general->songs_per_page;
  }
  
  if (select_codes < selectable_entries) error("Not enough select key combinations (%d) for number of selectable entries (%d)", select_codes, selectable_entries);

  // compute bases for each select digit...  
  for (auto b = 0; b < general->select_buttons.size(); ++b)
  {
    uint32_t base {1};
  if (general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
  {
    for (auto x = b+1; x < general->select_buttons.size(); ++x)
    {
       base *= general->select_buttons.at(x).size();
    }
  }
  else
  {
    for (auto x = 0; x < b; ++x)
    {
       base *= general->select_buttons.at(x).size();
    }
  }
    select_digit_base.push_back(base); // base of this digit is product of number of select codes all lower digits
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // Setup touch input offset and scaling...

  if (buttons->touch_min.x > Config->buttons->touch_max.x)  // swap min and max around 
  {
    ints2_t temp {buttons->touch_max};
    buttons->touch_max = buttons->touch_min;
    buttons->touch_min = temp;
    Input->reversed_touch = true;
  }

  // If max touch co-ordinates not defined, we set them to the size of the display...
  if (buttons->touch_max.x == 0) buttons->touch_max.x = Display->display_size.width;
  if (buttons->touch_max.y == 0) buttons->touch_max.y = Display->display_size.height;

  uint32_t touch_range_x = static_cast<uint32_t>(buttons->touch_max.x - buttons->touch_min.x);
  uint32_t touch_range_y = static_cast<uint32_t>(buttons->touch_max.y - buttons->touch_min.y);

  Input->touch_offset_x = buttons->touch_min.x ;
  Input->touch_offset_y = buttons->touch_min.y ;

  if (touch_range_x)
  {
    Input->touch_scale_x  = static_cast<double>(general->skin_size.x) / static_cast<double>(touch_range_x);
  }
  if (touch_range_y)
  {
    Input->touch_scale_y  = static_cast<double>(general->skin_size.y) / static_cast<double>(touch_range_y);
  }

  if (no_scale)
  {
    // jukebox is positioned in centre of the touch area...

    // x and y are offsets in display resolution for skin to be centred...
    float x { static_cast<float>((Display->display_size.width - general->skin_size.x) / 2) };
    float y { static_cast<float>((Display->display_size.height - general->skin_size.y) / 2) };

    // ...but the touch offsets are in touch resolution...
    Input->touch_offset_x += static_cast<uint32_t>((x * static_cast<float>(touch_range_x)) / static_cast<float>(Display->display_size.width));
    Input->touch_offset_y += static_cast<uint32_t>((y * static_cast<float>(touch_range_y)) / static_cast<float>(Display->display_size.height));

    // skin is not visually scaled, but touch scale is as it's in touch co-ordinates not display resolution...
    Input->touch_scale_x = static_cast<float>(Display->display_size.width)  / static_cast<float>(touch_range_x);
    Input->touch_scale_y = static_cast<float>(Display->display_size.height) / static_cast<float>(touch_range_y);
  }

  for (uint32_t b = 0; b < buttons->button.size(); ++b)
  {
    if (buttons->button.at(b).type == input_type_e::Touch)
    {
      buttons->button.at(b).param.at(0) = touch_areas->touch_area.at(b).x;
      buttons->button.at(b).param.at(1) = touch_areas->touch_area.at(b).y;
      buttons->button.at(b).param.at(2) = touch_areas->touch_area.at(b).w;
      buttons->button.at(b).param.at(3) = touch_areas->touch_area.at(b).h;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  status.first_visible_page_str = to_string(1 + PageDisplayClass::start_page);
  status.last_visible_page_str = to_string(PageDisplayClass::start_page + general->num_pages);

  // unspecified text max_width will default to zero, so force them to be the width of the page they're on...
  if (general->artist_text.max_width == 0) general->artist_text.max_width = general->page_size.x;
  if (general->album_text.max_width == 0) general->album_text.max_width = general->page_size.x;
  if (general->extra_text.max_width == 0) general->extra_text.max_width = general->page_size.x;
  if (general->song_text.max_width == 0) general->song_text.max_width = general->page_size.x;

  if (general->paired_song_text.font_number == -1) // not defined, so make it the same as song_text
  {
     general->paired_song_text = general->song_text;
  }
  if (general->paired_song_text.max_width == 0) general->paired_song_text.max_width = general->page_size.x;

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // initialise the display objects now that we have all the config parameters...
  for (auto &i : display_object)
  {

    if (dynamic_cast<PageDisplayClass*>(i) != nullptr)
    {
      i->init(general->page_size, StatusEvent_pages);
    }

    if ((dynamic_cast<TouchSongDisplayClass*>(i) != nullptr)
      || (dynamic_cast<JoystickDisplayClass*>(i) != nullptr))
    {
      uints2_t obj_size { };

      if (dynamic_cast<TouchSongDisplayClass*>(i) != nullptr)
      {
        general->select_mode = select_mode_e::TouchSong;
      }
      else
      {
        general->select_mode = select_mode_e::JoyStick;
      }

      if (i->size.y == 0) // size not defined in config file so calculate it based on page characteristics
      {
        obj_size = general->page_size;
        if (general->page_mode == page_mode_e::Singles)
        {
          if (general->pair_songs != pair_songs_e::No)
          {
            obj_size.y /= (3 * general->songs_per_page) / 2;
          }
          else
          {
            obj_size.y /= (4 * general->songs_per_page) / 2;
          }
        }
      }
      else // the size from the config file takes precedence
      {
        obj_size = i->size;
      }
      i->init(obj_size, StatusEvent_joystick);
    }

    if (dynamic_cast<BitmapDisplayClass*>(i) != nullptr)
    {
      i->init({}, StatusEvent_bitmap);
    }

    if (dynamic_cast<StatusDisplayClass*>(i) != nullptr)
    {
      i->init({}, StatusEvent_status);
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////

  // now for the joystick / touch_song object(s) we need to populate its page entry position
  // lookup table with (x,y) co-ordinates for each song entry in the display...

  for (auto &j : display_object)
  {
    if (dynamic_cast<JoystickDisplayClass*>(j) != nullptr) // object is a joystick object
    {
      for (auto &i : display_object) // search again to find all pages...
      {
        if (dynamic_cast<PageDisplayClass*>(i) != nullptr)
        {
          vector<ints2_t> page_pos {};
          ints2_t pos {};
          uint32_t sinc = i->size.y / general->songs_per_page;
          uint32_t yinc = 4 * sinc / (4 - (general->pair_songs != pair_songs_e::No ? 1 : 0));
          for (uint32_t s = 0; s < general->songs_per_page; ++s)
          {
            uint32_t y { s * sinc };
            pos.x = i->position.x + static_cast<JoystickDisplayClass*>(j)->offset.x;
            pos.y = i->position.y + y + static_cast<JoystickDisplayClass*>(j)->offset.y;

            if (general->pair_songs != pair_songs_e::No)
            {
              page_pos.push_back(pos);
              pos.y = i->position.y + y + yinc;
              s++;
            }

            page_pos.push_back(pos);
          }
          static_cast<JoystickDisplayClass*>(j)->entry_position.push_back(page_pos);
          static_cast<JoystickDisplayClass*>(j)->setPosition(0, 0);
          static_cast<JoystickDisplayClass*>(j)->entry_position.shrink_to_fit();
        }
      }
    }

    if (dynamic_cast<TouchSongDisplayClass*>(j) != nullptr) // object is a touch song object
    {
      for (auto &i : display_object) // search again to find all pages...
      {
        if (dynamic_cast<PageDisplayClass*>(i) != nullptr)
        {
          vector<ints2_t> page_pos {};
          ints2_t pos {};
          uint32_t sinc = i->size.y / general->songs_per_page;
          uint32_t yinc = 4 * sinc / (4 - (general->pair_songs != pair_songs_e::No ? 1 : 0));
          for (uint32_t s = 0; s < general->songs_per_page; ++s)
          {
            uint32_t y { s * sinc };
            pos.x = i->position.x + static_cast<TouchSongDisplayClass*>(j)->offset.x;
            pos.y = i->position.y + y + static_cast<TouchSongDisplayClass*>(j)->offset.y;

            if (general->pair_songs != pair_songs_e::No)
            {
              page_pos.push_back(pos);
              pos.y = i->position.y + y + yinc;
              s++;
            }

            page_pos.push_back(pos);
          }
          static_cast<TouchSongDisplayClass*>(j)->entry_position.push_back(page_pos);
          static_cast<TouchSongDisplayClass*>(j)->setPosition(0, 0);
          static_cast<TouchSongDisplayClass*>(j)->entry_position.shrink_to_fit();
          touch_song = static_cast<TouchSongDisplayClass*>(j); // THIS LINE SHOULD BE OUTSIDE NEXT TWO BRACES!!!
          touch_song->no_draw = true;// THIS LINE SHOULD BE OUTSIDE NEXT TWO BRACES!!!
        }
      }
    }

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // check if we have any joystick or touch_song objects defined...
  // then choose select mode based on those and whether we have a touchscreen...

  bool joystick_defined { false };
  bool touch_song_defined { false };

  for (auto &j : display_object)
  {
    if (dynamic_cast<TouchSongDisplayClass*>(j) != nullptr)
    {
      touch_song_defined = true;
      // need_touchscreen = true;
      // if (Input->touch_fd.size() == 0) // no touch buttons defined but we need touchscreen for touch song mode
      // {
        // Input->openDevice(Config->buttons->touch_device, Input->touch_fd);
      // }
    }
    else if (dynamic_cast<JoystickDisplayClass*>(j) != nullptr) joystick_defined = true;
  }

  // if (touch_song_defined && Input->touch_fd.size() == 0) // if we can't install touchscreen in touch song mode, we fall back to joystick or button mode...
  if (touch_song_defined && Input->touch_installed == false) // if we can't install touchscreen in touch song mode, we fall back to joystick or button mode...
  {
    if (joystick_defined)
    {
      general->select_mode = select_mode_e::JoyStick;
    }
    else
    {
      general->select_mode = select_mode_e::SelectCode;
    }
  }

  // after establishing select mode, if it's joystick we must turn off auto select...
  if (general->select_mode == select_mode_e::JoyStick)
  {
    general->auto_select = false; // a joystick defined means auto select must be turned off
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // check for duplicated button mappings...
  for (uint32_t b1 = 0; b1 < NUM_BUTTONS; ++b1)
  {
    if (Config->buttons->button.at(b1).type == input_type_e::Touch) continue; // Touch don't count
    for (uint32_t b2 = 0; b2 < NUM_BUTTONS; ++b2)
    {
      if (b1 == b2) continue; // don't compare a button with itself
      if (Config->buttons->button.at(b1).type == Config->buttons->button.at(b2).type)
      {
        if (Config->buttons->button.at(b1).param == Config->buttons->button.at(b2).param)
        {
          error("Duplicated Button mapping : %s and %s", Config->buttons->button.at(b1).name.c_str(), Config->buttons->button.at(b2).name.c_str());
        }
      }
    }
  }

}
