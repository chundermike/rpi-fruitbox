///////////////////////////////////////////////////////////////////////////////
// Project fruitbox.  A Retro MP3 Jukebox forthe Raspberry Pi.
// Mike Kingsley 2016.
//
// userguide.cpp :
//
// Prints the user guide.
//
///////////////////////////////////////////////////////////////////////////////

#include "fruitbox.hpp"
#include "userguide.hpp"

using namespace std;

constexpr uint32_t rightMargin           { 80 };
constexpr uint32_t maxWordSize           { 20 };
constexpr char sectionNumberSepStr[]     { ": " };
constexpr char sectionindentStr[]        { "  " };
constexpr char subSectionindentStr []    { "    " };
constexpr char subSubSectionindentStr[]  { "      " };

size_t section_number = 0;
size_t sub_section_number = 0;

void UserGuideLine(const char *body, const char *indent)
{
  const char *b = body;
  char c;
  uint32_t x {};

  cout << indent;
  while (c = *b++)
  {
    if (((x == 0) && ( c == ' ')) || (c == '\n')); else putchar(c);
    x++;
    if ((x == rightMargin) || (c == '\n') || ((c == ' ') && (x > rightMargin - maxWordSize)))
    {
      cout << endl << indent;
      x = 0;
    }
  };
  cout << endl;
}

void UserGuideBody(const char *body, const char *indent)
{
  UserGuideLine(body, indent);
  cout << endl;
}

void UserGuideSection(const char *heading, const char *body)
{
  section_number++;
  sub_section_number = 0;
  cout << endl << sectionindentStr << static_cast<int>(section_number) << sectionNumberSepStr << heading << endl << endl;

  UserGuideBody(body, sectionindentStr);
}

void UserGuideSubSection(const char *heading, const char *sub_heading, const char *body)
{
  if (heading[0])
  {
    sub_section_number++;
    cout << endl << sectionindentStr << static_cast<int>(section_number) << "." << static_cast<int>(sub_section_number) << sectionNumberSepStr << heading << sub_heading << endl << endl;
  }
  UserGuideBody(body, subSectionindentStr);
}

void UserGuideShowStatusVariables(const char *indent)
{
  for (auto &s : status_vars) {
    UserGuideLine(s.name.c_str(), indent);
    UserGuideBody(s.desc.c_str(), indent);
  }
}

void UserGuideShowConfigParameters(const char *indent)
{
  Config->cfgShow(indent);
}

void UserGuideShowGenres(const char *indent)
{
  cout << endl << sectionindentStr << "** Recognised AutoGenre values are..." << endl << endl << sectionindentStr;
  for (uint32_t g = 0; g < NUM_GENRES; ++g)
  {
    cout << setw(30) << GenreStr.at(g);
    if ((g % 4) == 3) cout << endl << sectionindentStr;
  }
  cout << endl;
  cout << sectionindentStr << "Note that you can also define your own Genres and fruitbox will recognise these if the 'AutoGenre' " << endl;
  cout << sectionindentStr << "field matches the name in the MP3 (ID3v2) genre tag." << endl << endl;
  cout << sectionindentStr << "fruitbox will make every effort to choose a song from the specified AutoGenre, but is constrained" << endl;
  cout << sectionindentStr << "by the song history and number of songs available to choose from.  If it cannot choose a song" << endl;
  cout << sectionindentStr << "in a reasonable time, it will play any song." << endl << endl;
}

void UserGuideShowButtonFileParameters(const char *indent)
{
  Config->buttons->cfgShow(indent);
  cout << endl;
}

void UserGuide(void)
{
  UserGuideSection("Introduction", introduction_str);
  UserGuideSection("Starting Up", starting_up_str);
  UserGuideSection("Operation", operation_str);
  UserGuideSection("Command Line Options", command_line_options_str);
  UserGuideSubSection("--help", "", command_line_help_option_str);
  UserGuideSubSection(commandLineArgCfg, commandLineOptCfg, command_line_cfg_option_str);
  UserGuideSubSection(commandLineArgDatabase, commandLineOptDatabase, command_line_database_option_str);
  UserGuideSubSection(commandLineArgMusicPath, commandLineOptMusicPath, command_line_musicpath_option_str);
  UserGuideSubSection(commandLineArgUserGuide, commandLineOptUserGuide, command_line_user_guide_option_str);
  UserGuideSubSection(commandLineArgDebugSongNums, commandLineOptDebugSongNums, command_line_debug_song_nums_option_str);
  UserGuideSubSection(commandLineArgConfigButtons, commandLineOptConfigButtons, command_line_gen_button_file_option_str);
  UserGuideSubSection(commandLineArgCalibrateTouch, commandLineOptCalibrateTouch, command_line_calibrate_touch_option_str);
  UserGuideSubSection(commandLineArgTestButtons, commandLineOptTestButtons, command_line_test_buttons_option_str);
  UserGuideSubSection(commandLineArgInputDevice, commandLineOptInputDevice, command_line_gen_input_device_option_str);
  UserGuideSubSection(commandLineArgTouchDevice, commandLineOptTouchDevice, command_line_gen_touch_device_option_str);
  UserGuideSubSection(commandLineArgLoadPlaylist, commandLineOptLoadPlaylist, command_line_load_playlist_str);
  UserGuideSubSection(commandLineArgSavePlaylist, commandLineOptSavePlaylist, command_line_save_playlist_str);
  UserGuideSubSection(commandLineArgChooseCfg, commandLineOptChooseCfg, command_line_choose_cfg_str);
  UserGuideSubSection(commandLineArgScreenshot, commandLineOptScreenshot, command_line_screenshot_str);
  UserGuideSubSection(commandLineArgNoScale, commandLineOptNoScale, command_line_no_scale_str);
  // UserGuideSubSection(commandLineArgTouchMin, commandLineOptTouchMin, command_line_touch_min_str);
  // UserGuideSubSection(commandLineArgTouchMax, commandLineOptTouchMax, command_line_touch_max_str);
  UserGuideSubSection(commandLineArgButtonMap, commandLineOptButtonMap, command_line_button_map_str);
  // UserGuideSubSection(commandLineArgGPIOScanRow, commandLineOptGPIOScanRow, command_line_gpio_scan_row_str);
  // UserGuideSubSection(commandLineArgGPIOScanCol, commandLineOptGPIOScanCol, command_line_gpio_scan_col_str);
  UserGuideSection("Configuration (Skin) Files", cfg_file_str);
  UserGuideShowConfigParameters(subSubSectionindentStr);
  UserGuideShowGenres(subSubSectionindentStr);
  UserGuideSubSection("Time Values", "", timers_str);
  UserGuideSubSection("Status Bitmaps", "", status_bitmaps_str);
  UserGuideSubSection("Status Videos", "", status_videos_str);
  UserGuideSubSection("Fonts and Text", "", font_text_def_str);
  UserGuideSubSection("Coin Mode", "", coin_str);
  UserGuideSubSection("Joystick Mode", "", joystick_str);
  UserGuideSubSection("Touch Song Mode", "", touch_song_str);
  UserGuideSubSection("Random Songs", "", random_songs_str);
  UserGuideSubSection("Albums / Singles Mode", "", albums_singles_mode_str);
  UserGuideSection("Database Creation", database_creation_str);
  UserGuideSection("Screen Layout", screen_layout_str);
  UserGuideSubSection("Pages", "", pages_str);
  UserGuideSubSection("Status Boxes", "", status_boxes_pre_var_str);
  UserGuideShowStatusVariables(subSubSectionindentStr);
  UserGuideSubSection("", "", status_boxes_post_var_str);
  UserGuideSection("Status Flags", status_flags_str);
  UserGuideSection("GPIO Input/Output", gpio_str);
  UserGuideSection("Input Control Buttons", buttons_def_str);
  UserGuideSubSection("Default Buttons", "", button_control_summary_str);
  UserGuideSubSection("Button Mapping File", "", button_mapping_file_str);
  UserGuideShowButtonFileParameters(subSubSectionindentStr);
  UserGuideSubSection("", "", button_mapping_file_post_str);
  UserGuideSection("Troubleshooting", troubleshooting_str);
  UserGuideSection("Hints and Tips", hints_and_tips_str);
}
