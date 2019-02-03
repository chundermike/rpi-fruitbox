#pragma once

using namespace std;

#define NOTE      "NOTE: "
#define WARNING   "WARNING: "
#define ERROR     "ERROR: "

constexpr char commandLineArgCfg[]              { "--cfg" };
constexpr char commandLineArgDatabase[]         { "--database" };
constexpr char commandLineArgMusicPath[]        { "--music-path" };
constexpr char commandLineArgChooseCfg[]        { "--choose-cfg" };
constexpr char commandLineArgUserGuide[]        { "--user-guide" };
constexpr char commandLineArgSavePlaylist[]     { "--save-playlist" };
constexpr char commandLineArgLoadPlaylist[]     { "--load-playlist" };
constexpr char commandLineArgDebugSongNums[]    { "--debug-song-nums" };
constexpr char commandLineArgConfigButtons[]    { "--config-buttons" };
constexpr char commandLineArgCalibrateTouch[]   { "--calibrate-touch" };
constexpr char commandLineArgTestButtons[]      { "--test-buttons" };
// constexpr char commandLineArgInputDevice[]      { "--input-device" };
// constexpr char commandLineArgTouchDevice[]      { "--touch-device" };
constexpr char commandLineArgScreenshot[]       { "--screenshot" };
constexpr char commandLineArgNoScale[]          { "--no-scale" };
// constexpr char commandLineArgTouchMin[]         { "--touch-min" };
// constexpr char commandLineArgTouchMax[]         { "--touch-max" };
constexpr char commandLineArgButtonMap[]        { "--button-map" };
// constexpr char commandLineArgGPIOScanRow[]      { "--gpio-scan-row" };
// constexpr char commandLineArgGPIOScanCol[]      { "--gpio-scan-col" };

constexpr char commandLineOptCfg[]              { " <filename>           " };
constexpr char commandLineOptDatabase[]         { " <filename>      " };
constexpr char commandLineOptMusicPath[]        { " <filepath>    " };
constexpr char commandLineOptChooseCfg[]        { " <filename>    " };
constexpr char commandLineOptUserGuide[]        { "               " };
constexpr char commandLineOptSavePlaylist[]     { " <filename> "};
constexpr char commandLineOptLoadPlaylist[]     { " <filename> "};
constexpr char commandLineOptDebugSongNums[]    { "          "};
constexpr char commandLineOptConfigButtons[]    { "           "};
constexpr char commandLineOptCalibrateTouch[]   { "          "};
constexpr char commandLineOptTestButtons[]      { "             "};
// constexpr char commandLineOptInputDevice[]      { " <name>      "};
// constexpr char commandLineOptTouchDevice[]      { " <name>      "};
constexpr char commandLineOptScreenshot[]       { "               "};
constexpr char commandLineOptNoScale[]          { "                 "};
// constexpr char commandLineOptTouchMin[]         { " <x> <y>        "};
// constexpr char commandLineOptTouchMax[]         { " <x> <y>        "};
constexpr char commandLineOptButtonMap[]        { " <filename>    "};
// constexpr char commandLineOptGPIOScanRow[]      { " <list of gpio pins>" };
// constexpr char commandLineOptGPIOScanCol[]      { " <list of gpio pins>" };


constexpr char defaultButtonFilename[]      { "fruitbox.btn" };
constexpr char defaultScreenshotFilename[]  { "screenshot.jpg" };
// constexpr char defaultTouchDevice[]         { "FT5406" };
constexpr char defaultFirstSelectButtons[]  { "ABCDEFGHIJK" };
constexpr char defaultSecondSelectButtons[] { "0123456789" };

constexpr char multiCfgParameter[]          { " * " };
constexpr char invalidTimeHMS[]             { "--:--:--" };
constexpr char invalidTimeMS[]              { "--:--" };
constexpr char zeroTimeHMS[]                { "00:00:00" };
constexpr char timeFormatHMS[]              { "%02d:%02d:%02d" };
constexpr char zeroTimeMS[]                 { "00:00" };
constexpr char timeFormatMS[]               { "%02d:%02d" };

auto SecondsToHours   = [](uint32_t A) -> uint32_t { return A / 3600; } ;
auto SecondsToMinutes = [](uint32_t A) -> uint32_t { return (A / 60) % 60; } ;
auto SecondsToSeconds = [](uint32_t A) -> uint32_t { return A % 60; } ;

constexpr char ButtonTypeKeyStr[]           { "Key" };
constexpr char ButtonTypeJoystickStr[]      { "Joystick" };
constexpr char ButtonTypeGPIOStr[]          { "GPIO" };
constexpr char ButtonTypeTouchStr[]         { "Touch" };

constexpr char UnknownTitleStr[]            { "Unknown Title" };
constexpr char UnknownArtistStr[]           { "Unknown Artist" };
constexpr char UnknownAlbumStr[]            { "Unknown Album" };
constexpr char UnknownAlbumArtistStr[]      { "Unknown Album Artist" };
constexpr char UnknownYearStr[]             { "Unknown Year" };

constexpr char GenreUnknownStr[]            { "Unknown" };
constexpr char GenreAnyStr[]                { "Any" };
constexpr char GenreOffStr[]                { "Off" };

constexpr char m3uFile_ExtInf[]             { "#EXTINF" };
constexpr char URLPrefix[]                  { "http" };
constexpr char plsFile_File[]               { "File" };
constexpr char plsFile_Title[]              { "Title" };
constexpr char plsFile_length[]             { "Length" };


enum class play_type_e : bool
{
  free_play = false,
  credit_play = true,
};

enum class bitmap_scale_e
{
  None,
  Volume,
  NowPlayingElapsedTime,
};

enum class bitmap_scale_mode_e
{
  Scaled,
  Clipped
};

enum class select_buttons_sequence_e
{
  RowCol,
  ColRow
};

enum class sort_songs_by_e
{
  Title,
  Artist,
  Album,
  AlbumArtist,
  Year,
  Genre,
  TrackNumber,
  Publisher,
  ISRC,
  Custom,
  Random,
  Unsorted
};

enum class pair_songs_e
{
  No,
  Yes,
  Dual
};

enum class page_mode_e
{
  Singles,
  Albums
};

enum class title_desc_e
{
  String,
  SongTitle,
  Artist,
  AlbumTitle,
  AlbumArtist,
  Year,
  Genre,
  TrackNumber,
  Publisher,
  ISRC,
  Custom,
  PairedSongTitle,
  PairedArtist,
  PairedAlbumTitle,
  PairedAlbumArtist,
  PairedYear,
  PairedGenre,
  PairedTrackNumber,
  PairedPublisher,
  PairedISRC,
  PairedCustom
};

enum class select_mode_e
{
  SelectCode,
  Joystick,
  TouchSong
};

enum class artwork_mode_e
{
  Auto,
  None,
  Embedded,
  Specified,
  Folder,
  Logo
};

enum class input_type_e
{
  None,
  Key,
  Joystick,
  Touch,
  GPIO
};

enum class gpio_e
{
  Unused = 0,
  Reserved,
  Input,
  Output
};

enum class song_type_e
{
  unknown,
  mp3,
  ogv,
  url
};

struct ints2_t
{
  int32_t x {};
  int32_t y {};
};

struct uints2_t
{
  uint32_t x {};
  uint32_t y {};
};

struct rgba_t
{
  uint32_t r { 0xff };
  uint32_t g { 0xff };
  uint32_t b { 0xff };
  uint32_t a { 0xff };
};

struct splash_state_t
{
  float ang {};
  size_t dw;
  size_t dh;
  size_t lw;
  size_t lh;
  int32_t s;
  float w;
  float h;
  ALLEGRO_COLOR bk;
  ALLEGRO_COLOR fcol;
};

struct text_t
{
  int32_t font_number { -1 };
  rgba_t colour {};
  int32_t alignment {};
  bool capitalise {};
  bool condense {};
  bool quoted {};
  ints2_t offset {};
  uint32_t max_width {};
};

struct bitmap_t
{
  string filename {};
  ALLEGRO_BITMAP *handle {};
  bool destroy_needed { false };
};

struct video_t
{
  string filename {};
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_EVENT event;
  ALLEGRO_VIDEO *handle {};
  ALLEGRO_BITMAP *bm_handle {};
  bool playing {};
};

struct sound_t
{
  string filename {};
  ALLEGRO_SAMPLE *handle {};
  ALLEGRO_SAMPLE_ID id {};
  uint32_t length {};
  float volume { 1.0 };
};

struct font_t
{
  string filename {};
  ALLEGRO_FONT *handle {};
  int32_t size {};
};

struct page_style_t
{
  uint32_t effect {0};
  uint32_t speed {8};
  bool fading {true};
};

struct song_t
{
  string filename {};
  string title {};
  string artist {};
  string albumArtist {};
  string album {};
  string year {};
  string publisher {};
  string isrc {};
  string custom_tag {};
  string genre {};
  uint32_t trackNumber {};
  string trackNumberStr {};
  uint32_t length {};
  bitmap_t artwork {};
  song_type_e type {song_type_e::unknown};
};

struct touch_area_t
{
  uint32_t x {};
  uint32_t y {};
  uint32_t w {};
  uint32_t h {};
};

struct input_event_t
{
  input_type_e type;
  array<int32_t, 4> param {{0, 0, 0, 0}};
};

struct button_t
{
  string name {};
  input_type_e type { input_type_e::None };
  array<int32_t, 4> param {{0, 0, 0, 0}};
};

struct status_t
{
  uint32_t credits { 0 };
  song_t *now_playing { };
  song_t *last_played { };
  string select_code_str {  };
  string num_songs_str {  };
  string num_pages_str {  };
  string first_visible_page_str {};
  string last_visible_page_str {};
  uint32_t now_playing_start_time { 0 };
  string now_playing_elapsed_time_str { invalidTimeMS };
  string now_playing_time_remaining_str { invalidTimeMS };
  string now_playing_length_str { invalidTimeMS };
  string last_played_length_str { invalidTimeMS };
  float now_playing_time_remaining_scale { 0.0 };
  string credits_str { "00" };
  string volume_str { "---" };
  string coming_up_num_songs_str { "0" };
  string coming_up_total_length_str { zeroTimeHMS };
  bool pages_idle {};
};

