#include "fruitbox.hpp"

using namespace std;

EngineClass::EngineClass()
{
  int32_t sel {};
  int32_t i {};

  song_video.event_queue = al_create_event_queue();
  if (song_video.event_queue == nullptr) error("Couldn't create song video event queue");
  auto_page_turn_timer = Config->general->auto_page_turn_time;
  auto_play_timer = Config->general->auto_play ? 1 + Config->general->auto_play_gap : 0;

  if (Config->general->page_mode == page_mode_e::Singles)
  {
    max_select_code = Config->general->songs_per_page * Config->general->num_pages;
  }
  else
  {
    max_select_code = Config->general->num_pages;
  }
}

EngineClass::~EngineClass()
{
#if 1
  // al_destroy_event_queue(EventQueue);
#endif
}

void EngineClass::UpdateSelectCode
(
  const uint32_t page,
  const uint32_t entry
)
{
  uint32_t sel_num { entry + (Config->general->songs_per_page * page) };
  status.select_code_str = IntToSel(sel_num);
  status_event |= StatusEvent_selCodeChange;
}

void EngineClass::UpdateSelectCode
(
  const char c
)
{
  if (Config->general->select_mode == select_mode_e::Joystick) return; // select code is persistent in joystick mode

  if (c == '-') // blank select code (for both SelectCode and TouchSong modes)
  {
    status.select_code_str.assign(Config->general->select_buttons.size(), '-');
    select_code_digit = 0;
    status_event |= StatusEvent_selCodeChange;
    return;
  }

  if ((Config->general->free_play == false) && (status.credits == 0)) return; // no money left!

  if (Config->general->select_mode == select_mode_e::TouchSong) return; // don't check keys in touch song mode

  char k {};
  for (auto &key : Config->general->select_buttons.at(select_code_digit))
  {
    if (c == toupper(key))
    {
      k = key;
      break;
    }
  }

  if (k)
  { // pressed key within range, so update the corresponding digit of the select code string, and decide if any action needed
    status.select_code_str.at(select_code_digit) = k;
    if (select_code_digit == Config->general->select_buttons.size() - 1) // last digit
    {
      select_code_digit = 0; // so move to first digit for next time
      if (Config->general->auto_select)
      {
        CheckAndAddSelection(); // don't need to press SELECT key in this mode
      }
      else
      {
        sel_code_timer = Config->general->select_timeout; // start timer ... if user doesn't press Select key within a certain time we clear the select code
      }
    }
    else 
    {
      select_code_digit++; // move to next digit for next time
      for (auto d = select_code_digit; d < Config->general->select_buttons.size(); d++)  status.select_code_str.at(d) = '-';  // reset all select digits to the right of current one
      sel_code_timer = Config->general->select_timeout; // start timer ... if user doesn't press second digit within a certain time we clear the select code
    }

  }
  status_event |= StatusEvent_selCodeChange;
}

///////////////////////////////////////////////////////////////////////////////
// SelectSong()
// convert (joystick) x and y into page and entry, then retrieve song from database

song_t* EngineClass::SelectSong
(
  const uint32_t x,
  const uint32_t y
)
{
  uint32_t page = start_page + x;
  uint32_t entry = y;

  selected_song_page = page;

  if (page >= Database->number_of_pages) return nullptr;

  return Database->GetSong(page, entry);
}

///////////////////////////////////////////////////////////////////////////////
// SelectSong()
// convert 2-digit select code to page and entry, then retrieve song from database

song_t* EngineClass::SelectSong
(
  const string &sel_code
)
{
  song_t *song;
  uint32_t entry;

  int32_t sel_num_in_page_group = static_cast<int32_t>(SelToInt(sel_code));

  if (sel_num_in_page_group == -1) return nullptr;

  if (sel_num_in_page_group >= max_select_code) return nullptr;

  if (Config->general->page_mode == page_mode_e::Singles)
  {
    selected_song_page = start_page + (sel_num_in_page_group / Config->general->songs_per_page);
    entry = sel_num_in_page_group % Config->general->songs_per_page;
  }
  else
  {
    selected_song_page = start_page + sel_num_in_page_group;
    entry = 0;
  }

  if (selected_song_page >= Database->number_of_pages) return nullptr;

  return Database->GetSong(selected_song_page, entry);
}

string EngineClass::IntToSel
(
  const int32_t selection
)
{
  string code {};
  uint32_t sel = selection;

  // if (selection >= num_select_codes) return nullptr;

  if (Config->general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
  {
    for (auto dig = 0; dig < Config->general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      code += Config->general->select_buttons.at(dig).at(sel / Config->select_digit_base.at(dig));
      sel = sel % Config->select_digit_base.at(dig);
    }
  }
  else
  {
    for (auto dig = 0; dig < Config->general->select_buttons.size(); ++dig) // for each select button digit string...
    {
       code += Config->general->select_buttons.at(dig).at(sel % Config->general->select_buttons.at(dig).size());
       sel = sel / Config->general->select_buttons.at(dig).size();
    }
  }
  return code;
}

uint32_t EngineClass::SelToInt
(
  const string &sel_code
)
{
  uint32_t sel_num_in_page_group;

  if (sel_code.size() != Config->general->select_buttons.size()) return -1; // number of select code characters doesn't match number of select_buttons digits
  
  // search each select_buttons string and update select_digit_value array
  // each element select_digit_value array holds the position (value) or the sel_code button press for that digit

  if (Config->general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
  {
    sel_num_in_page_group = 0;
    for (auto dig = 0; dig < Config->general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      size_t val { static_cast<size_t>(Config->general->select_buttons.at(dig).find_first_of(sel_code.at(dig))) };
      if (val == string::npos) return -1; // invalid character
      sel_num_in_page_group += val * Config->select_digit_base.at(dig);
    }
  }
  else
  {
    sel_num_in_page_group = 0;
    for (auto dig = 0; dig < Config->general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      size_t val { static_cast<size_t>(Config->general->select_buttons.at(dig).find_first_of(sel_code.at(dig))) };
      if (val == string::npos) return -1; // invalid character
      sel_num_in_page_group += val * Config->select_digit_base.at(dig);
    }
  }

  return sel_num_in_page_group;
}


///////////////////////////////////////////////////////////////////////////////
// CheckAndAddSelection()
// checks if a valid song is at the selected slot, and if so adds it to the playqueue
//

void EngineClass::CheckAndAddSelection(void)
{
  song_t *song { };

  if (Config->general->select_mode == select_mode_e::SelectCode)
  {
    song = SelectSong(status.select_code_str);
  }
  else // Joystick or TouchSong
  {
    song = SelectSong(joy_x, joy_y);
  }

  invalid_choice = false; // assume user has made a valid choice

  if (song == nullptr)
  {
    Audio->PlaySound(Config->sounds->invalid_song);
    invalid_choice = true;
  }
  else
  {
    if (Config->general->page_mode == page_mode_e::Singles)
    {
      PlayQueue->Add(song, play_type_e::credit_play);
    }
    else // add all songs in the album, i.e. from this song to all others following it on the rest of the page...
    {
      for (uint32_t s = 0; s < Config->general->songs_per_page; ++s)
      {
        song = SelectSong(selected_song_page - start_page, s);
        if (song == nullptr) break;
        PlayQueue->Add(song, play_type_e::credit_play);
      }
    }
    auto_play_timer = 0; // cancel any pending auto play addition
  }

  sel_code_timer = Config->general->select_hold_timeout; // start timer ... hold the selected code for a short while

  status_event |= StatusEvent_chooseSong;
}

void EngineClass::UpdateJoystickPositions
(
  const uint32_t x,
  const uint32_t y
)
{
  for (auto &j : Config->display_object)
  {
    if (dynamic_cast<JoystickDisplayClass*>(j) != nullptr) // object is a joystick object
    {
      static_cast<JoystickDisplayClass*>(j)->setPosition(x, y);
    }
  }
  UpdateSelectCode(x, y);
}

void EngineClass::Run(void)
{

  bool quit {false};
  bool page_turn_right {false};
  bool page_turn_left {false};
  uint32_t display_fade_level { 200 };
  time_t time_prev { };

  if (Config->screenshot)
  {
    for (auto i : Config->display_object)
    {
      i->update(StatusEvent_timerChange);
    }
    // save screenshot...
    string screenshot_filename { Config->filename.substr(0, Config->filename.find_last_of("/")) + "/" + Config->general->screenshot };
    cout << "Saving screenshot '" << screenshot_filename << "'" << endl;
    Display->DrawJukebox(false);
    al_save_bitmap(screenshot_filename.c_str(), Display->jukebox);
    return;
  }

  Audio->SetVolume(Config->sounds->song_volume);

  cout << "Let's Rock!" << endl;

  if (Config->choose_cfg == false)
  {
    Display->JukeboxFadeIn();
  }

  Display->LogoFadeOut();

  Audio->Run();

  // clear the input button queue before we start...
  Input->queue_mtx.lock();
  Input->queue.clear();
  Input->queue_mtx.unlock();

  while (quit == false)
  {

    // Display->redraw = false;

    ///////////////////////////////////////////////////////////////////////////
    // check for button events
    
    if (Input->queue.size()) // user input controls jukebox itself
    {
      Input->queue_mtx.lock();
      uint32_t event_code = Input->queue.front();
      uint32_t keycode = event_code & BUTTON_MASK;
      Input->queue.pop_front();
      Input->queue_mtx.unlock();
      // cout << std::hex << time(nullptr) << " INPUT QUEUE POP " << Input->queue.size() << " " << keycode << endl;
      if (event_code & BUTTON_RELEASED)
      {
        // cout << "BUTTON_RELEASED" << endl;
        button_pressed_mask &= ~static_cast<uint64_t>(1 << keycode);
      }
      else if (event_code & TOUCH_SONG)
      {
        // cout << "TOUCH_SONG" << endl;
        joy_x = (event_code >> SONG_PAGE_POS) & SONG_POS_MASK;
        joy_y = (event_code >> SONG_ENTRY_POS) & SONG_POS_MASK;
        UpdateSelectCode(joy_x, joy_y);
      }
      else
      {
        button_pressed_mask |= static_cast<uint64_t>(1 << keycode);
        // cout << std::hex << time(nullptr) << " BUTTON PRESSED MASK " << button_pressed_mask << " " << keycode << endl;
        switch (keycode)
        {
          case BUTTON_LEFT :
            page_jump = 1;
            if (Config->general->select_mode == select_mode_e::Joystick)
            {
              if (joy_x > 0)
              {

                joy_x--;
                UpdateJoystickPositions(joy_x, joy_y);
              }
              else
              {
                page_turn_left = true;
              }
            }
            else
            {
              page_turn_left = true;
            }
            break;

          case BUTTON_RIGHT :
            page_jump = 1;
            if (Config->general->select_mode == select_mode_e::Joystick)
            {
              if (joy_x < Config->general->num_pages - 1)
              {
                joy_x++;
                UpdateJoystickPositions(joy_x, joy_y);
              }
              else
              {
                page_turn_right = true;
              }
            }
            else
            {
              page_turn_right = true;
            }
            break;

          case BUTTON_LEFT_JUMP :
            page_jump = Config->general->page_jump;
            page_turn_left = true;
            break;

          case BUTTON_RIGHT_JUMP :
            page_jump = Config->general->page_jump;
            page_turn_right = true;
            break;

          case BUTTON_LEFT_ALPHA :
            if (Database->jump_sort_page.size() > 1)
            {
              uint32_t i;
              if (start_page == 0)
              {
                i = Database->jump_sort_page.size() -1 ;
              }
              else
              {
                for (i = 1; i < Database->jump_sort_page.size(); ++i)
                {
                  if (Database->jump_sort_page.at(i) >= start_page)
                  {
                    i--;
                    break;
                  }
                }
                if (i == Database->jump_sort_page.size()) i = 0;
              }

              int32_t jump = abs(static_cast<int32_t>(Database->jump_sort_page.at(i)) -  static_cast<int32_t>(start_page));
              page_jump = static_cast<uint32_t>(jump) / Config->general->num_pages;
              page_turn_left = true;
            }
            break;

          case BUTTON_RIGHT_ALPHA :
            if (Database->jump_sort_page.size() > 1)
            {
              uint32_t i;
              for (i = 0; i < Database->jump_sort_page.size(); ++i)
              {
                if ((Database->jump_sort_page.at(i) > start_page)) // && (Database->jump_sort_page.at(i+1) < start_page))
                {
                  break;
                }
              }

              if (i == Database->jump_sort_page.size()) i = 0;
              int32_t jump = abs(static_cast<int32_t>(start_page) - static_cast<int32_t>(Database->jump_sort_page.at(i)));
              page_jump = static_cast<uint32_t>(jump) / Config->general->num_pages;
              page_turn_right = true;
            }
            break;

          case BUTTON_UP :
            if (Config->general->select_mode == select_mode_e::Joystick)
            {
              if (joy_y > 0)
              {
                joy_y--;
                UpdateJoystickPositions(joy_x, joy_y);
              }
            }
            break;

          case BUTTON_DOWN :
            if (Config->general->select_mode == select_mode_e::Joystick)
            {
              if (Config->general->page_mode == page_mode_e::Singles) // y_pos stays at zero in albums mode
              {
                if (joy_y < Config->general->songs_per_page - 1)
                {
                  joy_y++;
                  UpdateJoystickPositions(joy_x, joy_y);
                }
              }
            }
            break;

          case BUTTON_SELECT :
            if (Config->general->auto_select && (Config->general->select_mode == select_mode_e::SelectCode)) break;
            CheckAndAddSelection();
            break;

          case BUTTON_SKIP :
            Audio->StopSong(true);
            break;

          case BUTTON_PAUSE :
            Audio->PauseSong();
            break;

          case BUTTON_CLEAR_QUEUE :
            PlayQueue->Clear();
            break;

          case BUTTON_0 : UpdateSelectCode('0'); break;
          case BUTTON_1 : UpdateSelectCode('1'); break;
          case BUTTON_2 : UpdateSelectCode('2'); break;
          case BUTTON_3 : UpdateSelectCode('3'); break;
          case BUTTON_4 : UpdateSelectCode('4'); break;
          case BUTTON_5 : UpdateSelectCode('5'); break;
          case BUTTON_6 : UpdateSelectCode('6'); break;
          case BUTTON_7 : UpdateSelectCode('7'); break;
          case BUTTON_8 : UpdateSelectCode('8'); break;
          case BUTTON_9 : UpdateSelectCode('9'); break;

          case BUTTON_A : UpdateSelectCode('A'); break;
          case BUTTON_B : UpdateSelectCode('B'); break;
          case BUTTON_C : UpdateSelectCode('C'); break;
          case BUTTON_D : UpdateSelectCode('D'); break;
          case BUTTON_E : UpdateSelectCode('E'); break;
          case BUTTON_F : UpdateSelectCode('F'); break;
          case BUTTON_G : UpdateSelectCode('G'); break;
          case BUTTON_H : UpdateSelectCode('H'); break;
          case BUTTON_I : UpdateSelectCode('I'); break;
          case BUTTON_J : UpdateSelectCode('J'); break;
          case BUTTON_K : UpdateSelectCode('K'); break;

          case BUTTON_INSERT_COIN1 :
            if (!Config->general->free_play)
            {
              status.credits += Config->general->plays_per_coin.at(0);
              status_event |= StatusEvent_creditsChange;
              Audio->PlaySound(Config->sounds->insert_coin);
            }
            break;

          case BUTTON_INSERT_COIN2 :
            if (!Config->general->free_play)
            {
              status.credits += Config->general->plays_per_coin.at(1);
              status_event |= StatusEvent_creditsChange;
              Audio->PlaySound(Config->sounds->insert_coin);
            }
            break;

          case BUTTON_INSERT_COIN3 :
            if (!Config->general->free_play)
            {
              status.credits += Config->general->plays_per_coin.at(2);
              status_event |= StatusEvent_creditsChange;
              Audio->PlaySound(Config->sounds->insert_coin);
            }
            break;

          case BUTTON_INSERT_COIN4 :
            if (!Config->general->free_play)
            {
              status.credits += Config->general->plays_per_coin.at(3);
              status_event |= StatusEvent_creditsChange;
              Audio->PlaySound(Config->sounds->insert_coin);
            }
            break;

          case BUTTON_VOL_UP :
            Audio->VolumeUp();
            break;

          case BUTTON_VOL_DOWN :
            Audio->VolumeDown();
            break;

          case BUTTON_MUTE :
            if (mute)
            {
              Audio->UnMute();
              mute = false;
            }
            else
            {
              Audio->Mute();
              mute = true;
            }
            status_event |= StatusEvent_muteChange;
            break;

          case BUTTON_ADD_RANDOM :
            PlayQueue->Add(Database->GetSong(), play_type_e::credit_play);
            break;

          case BUTTON_AUTO_PLAY_TOG :
            if (++Config->auto_genre_select == Config->general->auto_genre.size()) Config->auto_genre_select = 0;
            if (Config->general->auto_genre.at(Config->auto_genre_select) == GenreOffStr) // turn off auto play
            {
              Config->general->auto_play = false;
              auto_play_timer = 0;
            }
            else // turn on auto play
            {
              Config->general->auto_play = true;
              // if (Audio->song_play_state == song_play_state_e::stopped && !PlayQueue->NumSongsTotal()) auto_play_timer = 1 + Config->general->auto_play_gap; // if queue empty, start autoplay timer if auto play enabled (add 1 because 0 is disabled)
              if (!PlayQueue->NumSongsTotal()) auto_play_timer = 1 + Config->general->auto_play_gap; // if queue empty, start autoplay timer if auto play enabled (add 1 because 0 is disabled)
            }
            status_event |= StatusEvent_autoPlayModeChange;
            break;

          case BUTTON_LOOP_TOG :
            Config->general->loop_playlist = !Config->general->loop_playlist;
            status_event |= StatusEvent_loopModeChange;
            break;

          case BUTTON_FLAG_1 :
            Config->status_flag.at(0) = !Config->status_flag.at(0);
            status_event |= StatusEvent_flagChange;
            break;

          case BUTTON_FLAG_2 :
            Config->status_flag.at(1) = !Config->status_flag.at(1);
            status_event |= StatusEvent_flagChange;
            break;

          case BUTTON_FLAG_3 :
            Config->status_flag.at(2) = !Config->status_flag.at(2);
            status_event |= StatusEvent_flagChange;
            break;

          case BUTTON_FLAG_4 :
            Config->status_flag.at(3) = !Config->status_flag.at(3);
            status_event |= StatusEvent_flagChange;
            break;

          case BUTTON_FREEPLAY_TOG :
            Config->general->free_play = !Config->general->free_play;
            // if playing in freeplay mode, plays_per_coin will be zero, so set it to 1 (because when we subsequently enter
            // credit mode, inserting coins won't increase our song plays)
            for (auto p = 0; p < Config->general->plays_per_coin.size(); ++p)
            {
              if (Config->general->plays_per_coin.at(p) == 0) Config->general->plays_per_coin.at(p) = 1;
              Config->general->plays_per_coin_str.at(p) = to_string(Config->general->plays_per_coin.at(p));
            }
            status_event |= StatusEvent_freeplayModeChange;
            break;

          case BUTTON_QUIT :
            quit = true;
            break;

          case BUTTON_POWER_OFF :
            PlayQueue->Clear();
            Audio->StopSong(false);
            int s = system("sudo shutdown now");
            while (1);
            break;
        }
      }
      status_event |= StatusEvent_buttonChanged;
    }

    ///////////////////////////////////////////////////////////////////////////
    // update timers .. timers expressed in video frames (not seconds)

    status_event |= StatusEvent_timerChange;

    if (sel_code_timer)
    { 
      if (--sel_code_timer == 0) {
      UpdateSelectCode('-'); // timeout for partially selected code
}
    }

    if (auto_play_timer)
    {
      if (--auto_play_timer == 0)
      { // auto play gap elapsed, so start a random song
        PlayQueue->Add(Database->GetGenreSong(Config->general->auto_genre.at(Config->auto_genre_select)), play_type_e::free_play);
      }
    }

    if (auto_page_turn_timer)
    {
      if (--auto_page_turn_timer == 0)
      { // move page right
        page_jump = 1;
        page_turn_right = true; // will restart timer later in code
      }
    }

    time_t time_now { time(nullptr) };
    if (time_now != time_prev) { // one second elapsed since last check
      time_prev = time_now;
      status_event |= StatusEvent_oneSecondChange;
    }

    ///////////////////////////////////////////////////////////////////////////
    // update page event status if page turn initiated...

    if (page_turn_right)
    {
      if (PageDisplayClass::idle)
      {
        if (Database->number_of_pages > Config->general->num_pages) // don't scroll if not enough pages
        {
          start_page += page_jump * Config->general->num_pages;
          if (start_page >= Database->number_of_pages) start_page = 0;

          auto_page_turn_timer = Config->general->auto_page_turn_time; // restart auto timer (manual page move overrides auto timer)
          Audio->PlaySound(Config->sounds->page_move);
          PageDisplayClass::start_page = start_page;
          status.first_visible_page_str = to_string(1 + PageDisplayClass::start_page);
          status.last_visible_page_str = to_string(PageDisplayClass::start_page + Config->general->num_pages);
          status_event |= StatusEvent_pageMoveRightInit;
          page_turn_right = false;
        }
      }
    }
    else if (page_turn_left)
    {
      if (PageDisplayClass::idle)
      {
        if (Database->number_of_pages > Config->general->num_pages) // don't scroll if not enough pages
        {
          start_page -= page_jump * Config->general->num_pages;
          if (start_page < 0) start_page = Config->general->num_pages * ((Database->number_of_pages - 1) / Config->general->num_pages);

          auto_page_turn_timer = Config->general->auto_page_turn_time;
          Audio->PlaySound(Config->sounds->page_move);
          PageDisplayClass::start_page = start_page;
          status.first_visible_page_str = to_string(1 + PageDisplayClass::start_page);
          status.last_visible_page_str = to_string(PageDisplayClass::start_page + Config->general->num_pages);
          status_event |= StatusEvent_pageMoveLeftInit;
          page_turn_left = false;
        }
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    // check for song video events

    if (song_video.handle)
    {
      if ((Audio->paused == true) && (al_is_video_playing(song_video.handle)))
      {
        al_set_video_playing(song_video.handle, false); // pause video
      }
      else if ((Audio->paused == false) && (!al_is_video_playing(song_video.handle)))
      {
        al_set_video_playing(song_video.handle, true); // un-pause video
      }
    }

    if (al_get_next_event(song_video.event_queue, &song_video.event))
    {
      switch (song_video.event.type)
      {
        // case ALLEGRO_EVENT_VIDEO_FRAME_SHOW :
          // status_event |= StatusEvent_songVideoShow;
          // break;
        
        case ALLEGRO_EVENT_VIDEO_FINISHED :
          Audio->StopSong(false);
          break;
      }
    }

    if (song_video.playing)
    {
      status_event |= StatusEvent_songVideoShow;
    }

    ///////////////////////////////////////////////////////////////////////////
    // update certain status strings depending on certain status events...

    status_event |= Audio->SongPlayThread_status_event.fetch_and(0);
    status_event |= Audio->LoadArtworkThread_status_event.fetch_and(0);

    if (status_event)
    {

      if (status_event & StatusEvent_songVideoStop)
      {
        if (song_video.handle)
        {
          al_close_video(song_video.handle);
          al_unregister_event_source(song_video.event_queue, al_get_video_event_source(song_video.handle));
          song_video.handle = nullptr;
        }
        song_video.playing = false;
      }

      if (status_event & StatusEvent_songVideoStart)
      {
        song_video.handle = al_open_video(status.now_playing->filename.c_str());
        if (song_video.handle == nullptr)
        {
          cout << WARNING << "Can't open Video file '" << status.now_playing->filename << "'" << endl;
          Audio->StopSong(false);
        }
        else
        {
          al_register_event_source(song_video.event_queue, al_get_video_event_source(song_video.handle));
          al_start_video(song_video.handle, al_get_default_mixer());
          al_set_video_playing(song_video.handle, true); // un-pause video
          song_video.playing = true;
        }
      }

      if (status_event & StatusEvent_oneSecondChange)
      {
        if (Audio->song_play_state == song_play_state_e::playing)
        {
          uint32_t l { status.now_playing->length };
          if (Audio->paused) now_playing_paused_time++;
          uint32_t et { static_cast<uint32_t>(time_now - static_cast<time_t>(status.now_playing_start_time) - now_playing_paused_time) };
          status.now_playing_elapsed_time_str = StrMS(et);
          if (l)
          {
            uint32_t tr { l - et };
            status.now_playing_time_remaining_scale = 1.0 - (static_cast<float>(tr) / static_cast<float>(l));
            status.now_playing_length_str = StrMS(l);
            status.now_playing_time_remaining_str = StrMS(tr);
          }
          else // undefined time (ogv or url)
          {
            status.now_playing_time_remaining_scale = 0;
            status.now_playing_length_str = invalidTimeMS;
            status.now_playing_time_remaining_str = invalidTimeMS;
          }
        }
      }

      if (status_event & StatusEvent_songLoad)
      {
        now_playing_paused_time = 0;
        Audio->PlaySound(Config->sounds->load_song);
      }

      if (status_event & StatusEvent_songUnload)
      {
        Audio->PlaySound(Config->sounds->unload_song);
      }

      if (status_event & StatusEvent_playqueueChange)
      {
        status.coming_up_num_songs_str = PlayQueue->NumSongsComingUpStr();
        status.coming_up_total_length_str = PlayQueue->TotalTimeComingUp();
      }

      if (status_event & StatusEvent_creditsChange)
      {
        stringstream s {};
        s << setfill('0') << setw(2) << status.credits;
        status.credits_str = s.str();
      }

      if (status_event & StatusEvent_playqueueChange)
      {
        if (Config->general->auto_play && !PlayQueue->NumSongsTotal()) auto_play_timer = 1 + Config->general->auto_play_gap; // if queue empty, start autoplay timer if auto play enabled (add 1 because 0 is disabled)
      }

    }

    ///////////////////////////////////////////////////////////////////////////
    // update all display objects...

    status.pages_idle = PageDisplayClass::idle;
    PageDisplayClass::page_offset = 0; // first page in display is zero
    PageDisplayClass::idle = true; // assume all pages are idle (update()s below will change this flag if any page not idle)

    // reset status counters for coming up lists...
    StatusDisplayClass::if_song_coming_ups          = 0;
    StatusDisplayClass::coming_up_song_title        = 0;
    StatusDisplayClass::coming_up_song_artist       = 0;
    StatusDisplayClass::coming_up_song_year         = 0;
    StatusDisplayClass::coming_up_song_genre        = 0;
    StatusDisplayClass::coming_up_song_album        = 0;
    StatusDisplayClass::coming_up_song_length       = 0;
    StatusDisplayClass::coming_up_song_album_artist = 0;
    StatusDisplayClass::coming_up_song_track_number = 0;
    StatusDisplayClass::coming_up_song_publisher    = 0;
    StatusDisplayClass::coming_up_song_isrc         = 0;
    StatusDisplayClass::coming_up_song_custom_tag   = 0;
    StatusDisplayClass::num_sound_channels          = 0;

    for (auto i : Config->display_object)
    {
      i->update(status_event);
    }

    ///////////////////////////////////////////////////////////////////////////
    // render the display...

    Display->DrawJukebox(false);
    al_flip_display();

    ///////////////////////////////////////////////////////////////////////////
    // clear status events for next loop...
    // next_status_event contains status which could have been generated by above update() calls

    status_event = next_status_event;
    next_status_event = 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  // finish up...

  PlayQueue->Save(save_playlist_filename); // save playqueue before stopping song otherwise it will be excluded from the playlist

  Audio->StopSong(false);

}
