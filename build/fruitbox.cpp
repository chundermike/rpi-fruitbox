#include "fruitbox.hpp"

using namespace std;

bool debug_song_nums { false };
bool config_buttons { false };
bool calibrate_touch { false };
bool test_buttons { false };
ConfigClass *Config {};
PlayQueueClass *PlayQueue {};
AudioClass *Audio {};
InputClass *Input {};
DatabaseClass *Database {};
EngineClass *Engine {};
DisplayClass *Display {};
ChooserConfigClass *Chooser {};

status_t status { };
string save_playlist_filename {};
string load_playlist_filename {};
string choose_cfg_filename {};

// void CleanUp(void)
// {
  // al_uninstall_keyboard();
  // if (Audio) delete (Audio);
  // if (Engine) delete (Engine);
  // if (Database) delete (Database);
  // if (PlayQueue) delete (PlayQueue);
  // if (Display) delete (Display);
// }

void error(const char *fmt, ...)
{
  char s[512];
  va_list args;
  va_start(args, fmt);
  vsprintf(s, fmt, args);
  va_end(args);
  cout << ERROR << s << endl;
  // CleanUp();
  exit(-1);
}

void Help(void)
{
  uint32_t version = al_get_allegro_version();
  int major = version >> 24;
  int minor = (version >> 16) & 255;
  int revision = (version >> 8) & 255;
  int release = version & 255;
  cout << endl << "Command line arguments..." << endl << endl;
  cout << commandLineArgCfg            << commandLineOptCfg            << ": select (skin) configuration file" << endl;
  cout << commandLineArgDatabase       << commandLineOptDatabase       << ": select database file (overrides skin cfg Database)" << endl;
  cout << commandLineArgMusicPath      << commandLineOptMusicPath      << ": select music path (overrides skin cfg MusicPath)" << endl;
  cout << commandLineArgChooseCfg      << commandLineOptChooseCfg      << ": choose a skin using the menu defined in <filename>" << endl;
  cout << commandLineArgUserGuide      << commandLineOptUserGuide      << ": shows the user guide" << endl;
  cout << commandLineArgSavePlaylist   << commandLineOptSavePlaylist   << ": on exit, save the current playlist to <filename>" << endl;
  cout << commandLineArgLoadPlaylist   << commandLineOptLoadPlaylist   << ": load the playlist from <filename>" << endl;
  cout << commandLineArgDebugSongNums  << commandLineOptDebugSongNums  << ": show song/albums numbers next to songs to help identify them" << endl;
  cout << commandLineArgConfigButtons  << commandLineOptConfigButtons  << ": configure button mappings" << endl;
  cout << commandLineArgCalibrateTouch << commandLineOptCalibrateTouch << ": calibrate touch screen" << endl;
  cout << commandLineArgTestButtons    << commandLineOptTestButtons    << ": test button codes" << endl;
  cout << commandLineArgInputDevice    << commandLineOptInputDevice    << ": Add input device when configuring / testing buttons " << endl;
  cout << commandLineArgTouchDevice    << commandLineOptTouchDevice    << ": Specify touch device when configuring / testing buttons " << endl;
  cout << commandLineArgScreenshot     << commandLineOptScreenshot     << ": save a screenshot of the skin" << endl;
  cout << commandLineArgNoScale        << commandLineOptNoScale        << ": Don't scale the skin to fit the display" << endl;
  // cout << commandLineArgTouchMin      << commandLineOptTouchMin      << ": Top Left touch co-ordinates" << endl;
  // cout << commandLineArgTouchMax      << commandLineOptTouchMax      << ": Bottom Right touch co-ordinates" << endl;
  cout << commandLineArgButtonMap     << commandLineOptButtonMap     << ": Button mapping file (default fruitbox.btn)" << endl;
  // cout << commandLineArgGPIOScanRow   << commandLineOptGPIOScanRow   << ": GPIO pins used for scan rows" << endl;
  // cout << commandLineArgGPIOScanCol   << commandLineOptGPIOScanCol   << ": GPIO pins used for scan columns" << endl;
  cout << endl << endl << "Acknowledgments..." << endl << endl;
  cout << "Allegro v" << major << "." << minor << "." << revision << "[" << release << "] Game Programming library for Graphics, Sound and Input." << endl;
  cout << "libmpg123 v1.24.0 for MP3 decoding." << endl;
  cout << "DWJukebox for inspiration!" << endl << endl;
  exit(-1);
}

// void SegfaultCatch(int32_t sig_num)
// {
  // CleanUp();
// }

int32_t main(int32_t argc, char *argv[])
{
  bool quit { false };
  struct timeval t1;
  string cfg_file { };

  cout << endl << FRUITBOX_DESCRIPTION << endl;
  cout << FRUITBOX_SUMMARY << endl;

  Config = new ConfigClass();

  // parse the command line options...
  if (argc > 1)
  {
    int32_t ac = argc - 1;
    char **av = &argv[1];
    #define NEXT_ARG if (ac) {*av++;ac--;}
    #define PREV_ARG {ac++;*av--;}
    while (ac--)
    {
      if (strcmp(*av, "--help") == 0)
      {
        Help();
      }

      if (strcmp(*av, commandLineArgUserGuide) == 0)
      {
        UserGuide();
        exit(-1);
      }

      if (strcmp(*av, commandLineArgCfg) == 0)
      {
        NEXT_ARG; cfg_file = *av;
      }

      if (strcmp(*av, commandLineArgSavePlaylist) == 0)
      {
        NEXT_ARG; 
        save_playlist_filename = *av;
      }

      if (strcmp(*av, commandLineArgDatabase) == 0)
      {
        NEXT_ARG; 
        Config->general->database_filename = *av;
        cout << NOTE << "Database '" << *av << "' will override Database in skin config file" << endl;
      }

      if (strcmp(*av, commandLineArgMusicPath) == 0)
      {
        Config->general->command_line_music_path = true;
        NEXT_ARG;
        Config->general->music_path.push_back(*av);
        cout << NOTE << "MusicPath '" << *av << "' will override MusicPath in skin config file" << endl;
      }

      if (strcmp(*av, commandLineArgLoadPlaylist) == 0)
      {
        NEXT_ARG; 
        load_playlist_filename = *av;
      }

      if (strcmp(*av, commandLineArgChooseCfg) == 0)
      {
        NEXT_ARG; 
        choose_cfg_filename = *av;
        Config->choose_cfg = true;
      }

      if (strcmp(*av, commandLineArgDebugSongNums) == 0)
      {
        debug_song_nums = true;
      }

      if (strcmp(*av, commandLineArgConfigButtons) == 0)
      {
        config_buttons = true;
      }

      if (strcmp(*av, commandLineArgCalibrateTouch) == 0)
      {
        calibrate_touch = true;
      }

      if (strcmp(*av, commandLineArgTestButtons) == 0)
      {
        test_buttons = true;
      }

      if (strcmp(*av, commandLineArgInputDevice) == 0)
      {
        NEXT_ARG; 
        Config->buttons->input_device.push_back(make_pair(*av, 0));
      }

      if (strcmp(*av, commandLineArgTouchDevice) == 0)
      {
        NEXT_ARG; 
        Config->buttons->touch_device = *av;
      }

      if (strcmp(*av, commandLineArgScreenshot) == 0)
      {
        Config->screenshot = true;
      }

      if (strcmp(*av, commandLineArgNoScale) == 0)
      {
        Config->no_scale = true;
      }

      if (strcmp(*av, commandLineArgButtonMap) == 0)
      {
        NEXT_ARG; 
        Config->button_map = string(*av);
      }

      *av++;
    }
  }
  else 
  {
    Help();
  }

  if ((cfg_file.size() == 0) && (Config->choose_cfg == false) && (config_buttons == false) && (test_buttons == false))
  {
    Help();
  }

  /////////////////////////////////////////////////////////////////////////////
  // Initialise Allegro...

  if (!al_init()) error("Failed to initialize Allegro");
  al_init_font_addon();
  al_init_primitives_addon();
  al_init_ttf_addon();
  al_init_image_addon();

  if (!al_install_audio()) error("Couldn't install audio");
  if (!al_init_acodec_addon()) error("Couldn't init acodec addon");
  if (!al_init_video_addon()) error("Couldn't init video addon");

  gettimeofday(&t1, nullptr); // generate time-based seed for random song play...
  srand(t1.tv_usec * t1.tv_sec);

  /////////////////////////////////////////////////////////////////////////////
  // Create display...

  Display = new DisplayClass();

  Display->LogoSpinUp();

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the input...

  Input = new InputClass(config_buttons, test_buttons, calibrate_touch);

  /////////////////////////////////////////////////////////////////////////////
  // Create chooser...

  Chooser = new ChooserConfigClass();
  
  /////////////////////////////////////////////////////////////////////////////
  // Load Button mappings...

  Config->LoadButtons(Config->button_map);

  /////////////////////////////////////////////////////////////////////////////
  // now configure GPIO input and outputs, and start the input threads...

  Input->Start();
  
  /////////////////////////////////////////////////////////////////////////////
  // Skin chooser menu...

  if (Config->choose_cfg)
  {
    Config->ChooseMenu(choose_cfg_filename, cfg_file);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Load configuration...

  if (Config->Load(cfg_file) == false) exit(-1);

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the song play queue...

  PlayQueue = new PlayQueueClass();

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the audio...

  Audio = new AudioClass();

  /////////////////////////////////////////////////////////////////////////////
  // Load / create database...
  // If we had chosen the skin with the Chooser, then reload the (last screenshot)
  // as this is the backdrop to the database InfoBox (if building new database)...

  if (Config->choose_cfg)
  {
    Chooser->LoadScreenshot();
  }

  Database = new DatabaseClass(Config->general->database_filename);

  if (Chooser->screenshot_bm)
  {
    al_destroy_bitmap(Chooser->screenshot_bm);
    Chooser->screenshot_bm = nullptr;
  }
  /////////////////////////////////////////////////////////////////////////////
  // engine...

  Engine = new EngineClass();

  /////////////////////////////////////////////////////////////////////////////
  // load playqueue...
  
  PlayQueue->Load(load_playlist_filename);

  /////////////////////////////////////////////////////////////////////////////
  // Pre-run checks...

  Config->PostProcess();

  /////////////////////////////////////////////////////////////////////////////
  // Main loop...

  Engine->Run();

  return 0;
}

