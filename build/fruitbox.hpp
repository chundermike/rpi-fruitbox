#pragma once

// Developer notes:
//
// I've noticed that there seems to be a memory leak on Album Coverart (Granite skin) possibly
// due to an issue loading and freeing multiple bitmaps of different sizes (as I can't reproduce
// the issue with a simple test program loading/destroying the same image multiple times).
// So perhaps the worksaround is to recommend that all covert art (folder and embedded) has
// the same dimensions?  This way any freed bitmaps memory can be used again without segmentation?

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <sys/mman.h>
#include <signal.h>
#include <ctime>
#include <cmath>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <iomanip>
#include <functional>
#include <condition_variable>
#include <poll.h>
#include <linux/input.h>
#ifdef _RPI
#include "bcm_host.h"
#endif

#include <mpg123.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>

#include "fruitbox_types.hpp"
#include "input.hpp"
#include "status_events.hpp"
#include "config_base.hpp"
#include "display_base.hpp"
#include "playqueue.hpp"
#include "engine.hpp"
#include "pages.hpp"
#include "display.hpp"
#include "bitmap.hpp"
#include "status.hpp"
#include "joystick.hpp"
#include "audio.hpp"
#include "config.hpp"
#include "database.hpp"
#include "userguide.hpp"

#ifdef _RPI
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  #include "bcm_host.h"
  #pragma GCC diagnostic pop
#endif

// _CURL is defined if we would like to include code to implement internet radio (streaming)
// This is still to be debugged though - it appears the data is being read ok but not passed to the mp3 decoder properly.

// #define _CURL

#define FRUITBOX_VERSION                      "v1.12.2"
#define FRUITBOX_DESCRIPTION                  "fruitbox " FRUITBOX_VERSION " (" __DATE__ ", " __TIME__ ") by Mike Kingsley"
#define FRUITBOX_SUMMARY                      "A customisable MP3 Retro Jukebox for the Raspberry Pi"

void error(const char *fmt, ...);

extern status_t status;
extern bool debug_song_nums;
extern ALLEGRO_DISPLAY *display;
extern string save_playlist_filename;
extern string load_playlist_filename;

extern ConfigClass *Config;
extern AudioClass *Audio;
extern InputClass *Input;
extern DatabaseClass *Database;
extern PlayQueueClass *PlayQueue;
extern EngineClass *Engine;
extern DisplayClass *Display;
extern ChooserConfigClass *Chooser;
