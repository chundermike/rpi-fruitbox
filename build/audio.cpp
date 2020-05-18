
#include "fruitbox.hpp"

using namespace std;

constexpr uint32_t mp3_buffer_size_fraction { 4 };
constexpr uint32_t audio_stream_fragments { 4 };

mpg123_handle *AudioClass::mp3 {};
unsigned char *AudioClass::mp3_buffer {};
size_t AudioClass::bytes_remaining {};
size_t AudioClass::mp3_buffer_size {};
bool AudioClass::url_get_format {};
atomic<bool>AudioClass::play_song {};
ALLEGRO_AUDIO_STREAM *AudioClass::mp3_stream {};

void AudioClass::RemoveSong
(
  bool skipped
)
{
  AudioClass::play_song = false;
  PlayQueue->Remove();
  if (!skipped && Config->general->loop_playlist)
  {
    PlayQueue->Add(status.now_playing, play_type_e::credit_play);
  }

  #if 0
  // this causes double free at program exit!!!!
  // destroy any artwork bitmap associated with now playing song...
  if (status.now_playing->artwork.handle)
  {
    al_destroy_bitmap(status.now_playing->artwork.handle);
    status.now_playing->artwork.handle = nullptr;
    status.now_playing->artwork.destroy_needed = false;
  }
  #endif
  status.last_played = status.now_playing;
  status.last_played->artwork.handle = nullptr;
  status.last_played_length_str = status.now_playing_length_str;

  status.now_playing = &no_song;
  status.now_playing_length_str = invalidTimeMS;
  status.now_playing_elapsed_time_str = invalidTimeMS;
  status.now_playing_time_remaining_str = invalidTimeMS;
  status.now_playing_time_remaining_scale = 0.0;

  SongPlayThread_status_event |= StatusEvent_playqueueChange;
}

void AudioClass::LoadAlbumArtwork(const song_t *song, bitmap_t *bitmap)
{

  if (bitmap->destroy_needed) {
      // cout << "1 destroy bitmap" << endl;
    al_destroy_bitmap(bitmap->handle);
    // bitmap->handle = nullptr;
    bitmap->destroy_needed = false;
  }

  bitmap->handle = nullptr;
  
  switch (Config->general->album_page_artwork_mode) {

    case artwork_mode_e::None :
      break; // keep as nullptr

    case artwork_mode_e::Specified :
      bitmap->handle = Config->general->album_page_missing_artwork.handle;
      break;

    case artwork_mode_e::Logo :
      bitmap->handle = Display->fruitbox_logo_bm;
      break;

    case artwork_mode_e::Folder :
      {
        // try and load artwork from song->filename (path excluding filename)
        string folder_artwork { song->filename.substr(0, song->filename.find_last_of("/")) + "/folder.jpg" };
        bitmap->handle = al_load_bitmap(folder_artwork.c_str());
      // cout << "1 load bitmap" << endl;
        if (bitmap->handle)
        {
          bitmap->destroy_needed = true;
        }
        break;
      }

    case artwork_mode_e::Auto :
      {
        string folder_artwork { song->filename.substr(0, song->filename.find_last_of("/")) + "/folder.jpg" };
        bitmap->handle = al_load_bitmap(folder_artwork.c_str());
      // cout << "2 load bitmap" << endl;
        if (bitmap->handle)
        {
          bitmap->destroy_needed = true;
        }
        else if (Config->general->album_page_missing_artwork.handle != nullptr) // none available so use the bitmap specified in the config file
        {
          bitmap->handle = Config->general->album_page_missing_artwork.handle;
        }
        else // none specified, so use the fruitbox logo
        {
          bitmap->handle = Display->fruitbox_logo_bm;
        }
        break;
      }

  }
}

void AudioClass::LoadArtworkThread(void)
{
  unique_lock<mutex> artwork_guard(artwork_mtx);
  while (1)
  {
    get_artwork.wait(artwork_guard);

    int err { MPG123_OK };
    mpg123_id3v1 *v1 {};
    mpg123_id3v2 *v2 {};
    mpg123_handle *mp {};
    int meta {};

    artwork_song->artwork.handle = nullptr;

    if (artwork_song->artwork.destroy_needed) {
      // cout << "2 destroy bitmap" << endl;
      al_destroy_bitmap(artwork_song->artwork.handle);
      artwork_song->artwork.handle = nullptr;
      artwork_song->artwork.destroy_needed = false;
    }

    switch (Config->general->now_playing_artwork_mode) {

      case artwork_mode_e::None :
        break; // keep as nullptr

      case artwork_mode_e::Specified :
        artwork_song->artwork.handle = Config->general->now_playing_missing_artwork.handle;
        break;

      case artwork_mode_e::Logo :
        artwork_song->artwork.handle = Display->fruitbox_logo_bm;
        break;

      case artwork_mode_e::Folder :
        {
          string folder_artwork { artwork_song->filename.substr(0, artwork_song->filename.find_last_of("/")) + "/folder.jpg" };
          artwork_song->artwork.handle = al_load_bitmap(folder_artwork.c_str());
      // cout << "3 load bitmap" << endl;
          if (artwork_song->artwork.handle)
          {
            artwork_song->artwork.destroy_needed = true;
          }
        }
        break;

      case artwork_mode_e::Auto :
      case artwork_mode_e::Embedded :
        if ((mp = mpg123_new(nullptr, &err)) == nullptr) return;
        mpg123_param(mp, MPG123_FLAGS, MPG123_QUIET | MPG123_PICTURE, 0);
        if (mpg123_open(mp, artwork_song->filename.c_str()) != MPG123_OK) return;
        mpg123_scan(mp); // SLOW!
        meta = mpg123_meta_check(mp);
        if (meta & MPG123_ID3 && mpg123_id3(mp, &v1, &v2) == MPG123_OK)
        {
          if (v2 != nullptr)
          {
            uint32_t type_sel { 0 };

            // look for type = 3 (cover art); if not found just use first one

            if (v2->pictures)
            {
              for (size_t i=0;i<v2->pictures; ++i)
              {
                if (static_cast<uint32_t>(v2->picture[i].type) == mpg123_id3_pic_back_cover) type_sel = i;
              }
              ALLEGRO_FILE *cover_artwork_f = al_open_memfile(v2->picture[type_sel].data, v2->picture[type_sel].size, "rb");
              if (cover_artwork_f) // use artwork from MP3 file...
              {
                artwork_song->artwork.handle = al_load_bitmap_f(cover_artwork_f, ".jpg");
      // cout << "4 load bitmap f" << endl;
                al_fclose(cover_artwork_f);
                artwork_song->artwork.destroy_needed = true;
              }
            }
          }
        }

        if ((Config->general->now_playing_artwork_mode == artwork_mode_e::Auto) && (artwork_song->artwork.destroy_needed == false)) // auto mode, and no embedded image found, so use missing artwork image or fruitbox logo...
        {
          // try and load artwork from artwork_song->filename (path excluding filename)
          string folder_artwork { artwork_song->filename.substr(0, artwork_song->filename.find_last_of("/")) + "/folder.jpg" };
          artwork_song->artwork.handle = al_load_bitmap(folder_artwork.c_str());
      // cout << "5 load bitmap" << endl;
          if (artwork_song->artwork.handle)
          {
            artwork_song->artwork.destroy_needed = true;
          }
          else if (Config->general->now_playing_missing_artwork.handle != nullptr) // none available so use the bitmap specified in the config file
          {
            artwork_song->artwork.handle = Config->general->now_playing_missing_artwork.handle;
          }
          else // none specified, so use the fruitbox logo
          {
            artwork_song->artwork.handle = Display->fruitbox_logo_bm;
          }
        }

        mpg123_close(mp);
        mpg123_delete(mp);

        break;
    }

    LoadArtworkThread_status_event |= StatusEvent_newArtwork;
  }
}

bool AudioClass::AttachMP3ToMixer
(
  const string &filename
)
{
  ALLEGRO_CHANNEL_CONF allegro_channels;

  mpg123_getformat(AudioClass::mp3, &rate, &channels, &encoding);

  if (channels == MPG123_MONO)
  {
    stereo = false;
    allegro_channels = ALLEGRO_CHANNEL_CONF_1;
  }
  else
  {
    stereo = true;
    allegro_channels = ALLEGRO_CHANNEL_CONF_2;
  }

  samples = AudioClass::mp3_buffer_size/(channels*mpg123_encsize(encoding));

  if (rate == 0)
  {
    log_file << WARNING << "Audio Rate zero! for file '" << filename << "'" << endl;
    RemoveSong(false);
    return false;
  }
  // cout << "AttachMP3ToMixer" << endl;
  AudioClass::mp3_stream = al_create_audio_stream(audio_stream_fragments, samples, rate, ALLEGRO_AUDIO_DEPTH_INT16, allegro_channels);
  if (!AudioClass::mp3_stream) error("Couldn't create mp3_stream");
  if (al_get_audio_stream_attached(AudioClass::mp3_stream))
  {
    al_detach_audio_stream(AudioClass::mp3_stream);
  }
  if (!al_attach_audio_stream_to_mixer(AudioClass::mp3_stream, al_get_default_mixer())) error("Couldn't attach mp3_stream");
  return true;
}

size_t AudioClass::CurlGetFormat
(
  void *buffer,
  size_t size,
  size_t nmemb,
  void *userp
)
{
  off_t frame_offset;
  size_t decoded_bytes {};
  int err;

#ifdef _CURL
  // cout << "CurlGetFormat" << endl;
  mpg123_feed(AudioClass::mp3, (const unsigned char*) buffer, size * nmemb);

  do
  {
    if (mpg123_decode_frame(AudioClass::mp3, &frame_offset, &AudioClass::mp3_buffer, &decoded_bytes) == MPG123_NEW_FORMAT)
    {
      // cout << "MPG123_NEW_FORMAT" << endl;
      Audio->AttachMP3ToMixer(status.now_playing->filename);
      return decoded_bytes;
    }
  } while (AudioClass::play_song);

  // cout << "CurlGetFormat return" << endl;
#endif
  return decoded_bytes;
}

size_t AudioClass::CurlGetMP3
(
  void *buffer,
  size_t size,
  size_t nmemb,
  void *userp
)
{
  off_t frame_offset;
  size_t decoded_bytes {};
  int err;

#ifdef _CURL
  // cout << "CurlGetMP3" << endl;
  mpg123_feed(AudioClass::mp3, (const unsigned char*) buffer, size * nmemb);
  // cout << "size * nmemb " << size * nmemb << endl;

  if (AudioClass::mp3_stream)
  {
    do
    {
      AudioClass::mp3_buffer = (unsigned char *)al_get_audio_stream_fragment(AudioClass::mp3_stream); // get ptr to a free fragment
      if (AudioClass::mp3_buffer != nullptr) // we have somewhere to store decoded data
      {
        // keep reading until have AudioClass::mp3_buffer_size bytes to play out...
        // cout << "mpg123_read : bytes_remaining " << AudioClass::bytes_remaining << endl;
        if (mpg123_read(AudioClass::mp3, static_cast<unsigned char*>(AudioClass::mp3_buffer + AudioClass::mp3_buffer_size - bytes_remaining), bytes_remaining, &decoded_bytes) == MPG123_OK)
        {
          // cout << "decoded_bytes " << decoded_bytes << endl;
          AudioClass::bytes_remaining -= decoded_bytes;
          if (AudioClass::bytes_remaining == 0)
          {
            // cout << "al_set_audio_stream_fragment" << endl;
            al_set_audio_stream_fragment(AudioClass::mp3_stream, AudioClass::mp3_buffer); // ready to play out
            AudioClass::bytes_remaining = AudioClass::mp3_buffer_size;
          }
        }
      }
    } while (AudioClass::play_song && AudioClass::bytes_remaining);
  }

  // cout << "CurlGetMP3 return" << endl;
#endif
  return size * nmemb;
}

void AudioClass::PlaySongThread(void)
{
  size_t decoded_bytes {};

  #ifdef _CURL
  curl = curl_easy_init();
  #endif

  while (1)
  {
    switch (song_play_state)
    {
      case song_play_state_e::playing :
        switch (status.now_playing->type)
        {
          ///////////////////////////////////////////////
          // Playback of MP3 files...
          case song_type_e::mp3 :
            do
            {
              if (paused == false)
              {
                AudioClass::mp3_buffer = (unsigned char *)al_get_audio_stream_fragment(AudioClass::mp3_stream); // get ptr to a free fragment
                if (AudioClass::mp3_buffer != nullptr)
                {
                  mpg123_read(AudioClass::mp3, AudioClass::mp3_buffer, AudioClass::mp3_buffer_size, &decoded_bytes); // ...if fragment available, decode mp3 data into it
                  al_set_audio_stream_fragment(AudioClass::mp3_stream, AudioClass::mp3_buffer); // ready to play out
                }
              }
            }
            while (decoded_bytes && AudioClass::play_song);

            // song finished naturally or play_song set false (song skipped)...
            al_detach_audio_stream(AudioClass::mp3_stream);
            al_destroy_audio_stream(AudioClass::mp3_stream);
            AudioClass::mp3_stream = nullptr;
            mpg123_close(AudioClass::mp3);
            SongPlayThread_status_event |= StatusEvent_songStop;
            break;

          ///////////////////////////////////////////////
          // Playback of MP3 URL (M3U/PLS) files...done in CurlWriteCallback()
          #ifdef _CURL
          case song_type_e::url :
            curl_easy_perform(curl);

            // song finished naturally or play_song set false (song skipped)...
            if (AudioClass::mp3_stream)
            {
              al_detach_audio_stream(AudioClass::mp3_stream);
              al_destroy_audio_stream(AudioClass::mp3_stream);
              AudioClass::mp3_stream = nullptr;
            }
            mpg123_close(AudioClass::mp3);
            SongPlayThread_status_event |= StatusEvent_songStop;
            break;
          #endif

          ///////////////////////////////////////////////
          // Playback of OGV files...
          case song_type_e::ogv :
            do
            {
            }
            while (AudioClass::play_song);

            SongPlayThread_status_event |= StatusEvent_songStop | StatusEvent_songVideoStop;

            break;

          default : // song_type_e::unknown
            break;
        }

        // RemoveSong(skipped); // also clears status.now_playing information

        song_play_state = song_play_state_e::unloading;
        SongPlayThread_status_event |= StatusEvent_songUnload;
        break;

      case song_play_state_e::unloading :
        // NEED THE NEXT DELAY OTHERWISE SONG VIDEO HAS STUTTER AFTER MP3 PLAY !!!???!?! (SEEMS TO NEEDS TO BE MORE THAN ONE VIDEO FRAME PERIOD, SO MAKE IT TWO TO BE SURE)
        this_thread::sleep_for(chrono::milliseconds(2000 / Display->display_size.refresh_rate));
        this_thread::sleep_for(chrono::milliseconds((1000 * Config->general->song_unload_time) / Display->display_size.refresh_rate)); // song_unload_time in frame ticks, sleep in msec
        RemoveSong(skipped); // also clears status.now_playing information
        song_play_state = song_play_state_e::stopped;
        break;

      case song_play_state_e::stopped :
        if (PlayQueue->NumSongsTotal())
        { // a song in the queue ready to be played...
          song_t *next_up { PlayQueue->QuerySong(0) };
          if (next_up != nullptr)
          {

            switch (next_up->type)
            {
              ///////////////////////////////////////////////
              // Load MP3 file...
              case song_type_e::mp3 :
                status.now_playing = next_up;
                if (mpg123_open(AudioClass::mp3, next_up->filename.c_str()) != MPG123_OK)
                {
                  RemoveSong(false);
                  continue;
                }
                if (AttachMP3ToMixer(next_up->filename))
                {
                  AudioClass::play_song = true;
                  GetSongCoverArt(next_up);
                }
                break;

              ///////////////////////////////////////////////
              // Load MP3 URL file...
              #ifdef _RPI
              case song_type_e::url :
                status.now_playing = next_up;
                if (mpg123_open_feed(AudioClass::mp3) != MPG123_OK)
                {
                  RemoveSong(false);
                  continue;
                }
                AudioClass::play_song = true;
                break;
              #endif

              ///////////////////////////////////////////////
              // Load OGV file...
              case song_type_e::ogv :
                status.now_playing = next_up;
                AudioClass::play_song = true;
                break;

              default : // song_type_e::unknown
                log_file << WARNING << "Unknown file type '" << next_up->filename << "'" << endl;
                RemoveSong(false);
                continue;
                break;
            }

            song_play_state = song_play_state_e::loading;
            SongPlayThread_status_event |= StatusEvent_songLoad;
          }
        }
        else
        {
          this_thread::sleep_for(chrono::milliseconds(100));
        }
        break;

        case song_play_state_e::loading :
          #ifdef _CURL
          if (status.now_playing->type == song_type_e::url)
          {
            AudioClass::url_get_format = true;
            // cout << "URL filename '" << status.now_playing->filename << "' opened" << endl;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlGetFormat);
            curl_easy_setopt(curl, CURLOPT_URL, status.now_playing->filename.c_str());
            // cout << "debug7" << endl;
            curl_easy_perform(curl);
            AudioClass::bytes_remaining = AudioClass::mp3_buffer_size;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlGetMP3);
            // if (!AudioClass::play_song) break; // user has skipped 
            // cout << "debug8" << endl;
            // if (AudioClass::play_song)
            // {
              // cout << "debug9" << endl;
              // if (AttachMP3ToMixer(status.now_playing->filename))
              // {
              // }
              // cout << "debug10" << endl;
            // }
            // else
            // {
              // cout << "debug11" << endl;
              // RemoveSong(false);
              // continue;
            // }
            // #else
            // RemoveSong(false);
            // continue;
          }
          else
          {
            this_thread::sleep_for(chrono::milliseconds((1000 * Config->general->song_load_time) / Display->display_size.refresh_rate)); // song_load_time in frame ticks, sleep in msec
          }
          #else
            this_thread::sleep_for(chrono::milliseconds((1000 * Config->general->song_load_time) / Display->display_size.refresh_rate)); // song_load_time in frame ticks, sleep in msec
          #endif
          status.now_playing_start_time = time(nullptr);
          PlayQueue->AddToHistory(0);
          paused = false;
          song_play_state = song_play_state_e::playing;
          SongPlayThread_status_event |= (StatusEvent_songStart | StatusEvent_songPauseChange);
          if (status.now_playing->type == song_type_e::ogv)
          {
            SongPlayThread_status_event |= StatusEvent_songVideoStart;
          }
          break;

    }
  }
  #ifdef _CURL
  curl_easy_cleanup(curl);
  #endif
}

AudioClass::AudioClass(void)
{
  int err {MPG123_OK};

  log_file << "Initialising audio ..." << endl;

  skipped = false;
  AudioClass::play_song = false;
  song_play_state = song_play_state_e::stopped;

  err = mpg123_init();
  if (err != MPG123_OK || (AudioClass::mp3 = mpg123_new(nullptr, &err)) == nullptr) error("Failed to initialise audio decoder: %s", mpg123_plain_strerror(err));

  AudioClass::mp3_buffer_size = mpg123_outblock(AudioClass::mp3) / mp3_buffer_size_fraction;

  // load gain_db steps for log volume...
  gain_db.push_back(0); // first entry is mute
  for (uint32_t i = MinSongVolume + SongVolumeInc; i <= MaxSongVolume; i += SongVolumeInc)
  {
    uint32_t percent { (i - MinSongVolume) * (MaxSongVolume - MinSongVolume) / 100};
    double factor {static_cast<double>(percent) / 100.0};
    double g { pow(factor, 2)};
    gain_db.push_back(g);
  }

  // for (size_t i=0;i<gain_db.size();++i) cout << i << " " << gain_db.at(i) << endl;

  // make sure we don't get messy error messages on the console...
  mpg123_param(AudioClass::mp3, MPG123_FLAGS, MPG123_QUIET, 0);
  status.now_playing = &no_song;

  // video_event_queue = al_create_event_queue();

}

void AudioClass::Run(void)
{
  thread PlaySongThread { &AudioClass::PlaySongThread, this };
  PlaySongThread.detach();

  thread LoadArtworkThread { &AudioClass::LoadArtworkThread, this };
  LoadArtworkThread.detach();
}

AudioClass::~AudioClass()
{
  song_play_state = song_play_state_e::stopped;
  mpg123_close(AudioClass::mp3);
  mpg123_delete(AudioClass::mp3);
  mpg123_exit();
}

void AudioClass::PlaySound
(
  sound_t sound
)
{
  if (sound.handle == nullptr) return;

  float vol { (sound.volume * Config->sounds->song_volume) / 100};
  al_stop_sample(&sound.id);
  al_play_sample(sound.handle, vol, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sound.id);
}

void AudioClass::GetSongCoverArt
(
  song_t *song
)
{
  artwork_song = song;
  get_artwork.notify_all();
}

void AudioClass::GetMP3SongInfo
(
  const char *filename,
  vector<song_t> &song
)
{
  song_t s {};
  s.type = song_type_e::mp3;

  mpg123_handle *mp {};
  int meta {};
  int ch {}, enc {};
  long rt {};
  mpg123_id3v1 *v1 {};
  mpg123_id3v2 *v2 {};
  int err { MPG123_OK };

  s.title = UnknownTitleStr;
  s.artist = UnknownArtistStr;
  s.album = UnknownAlbumStr;
  s.albumArtist = UnknownAlbumArtistStr;
  s.year = UnknownYearStr;
  s.genre = GenreUnknownStr;
  s.publisher.clear();
  s.isrc.clear();
  s.custom_tag.clear();
  s.trackNumber = 0;
  s.trackNumberStr = "0";

  if ((mp = mpg123_new(nullptr, &err)) == nullptr) error("Failed to initialise mpg123: %s", mpg123_plain_strerror(err));
  mpg123_param(mp, MPG123_FLAGS, MPG123_QUIET, 0);
  if (mpg123_open(mp, filename) != MPG123_OK)
  {
    error("Cannot open '%s'", filename);
  }
  mpg123_getformat(mp, &rt, &ch, &enc);
  if (rt == 0) {
    log_file << WARNING << "Audio Rate zero! (" << filename << ")" << endl;
    song.push_back(s);
    return;
  }

  mpg123_scan(mp);
  meta = mpg123_meta_check(mp);

  s.length = mpg123_length(mp) / rt;

  if(meta & MPG123_ID3 && mpg123_id3(mp, &v1, &v2) == MPG123_OK)
  {
    if (v1 != nullptr)
    {
      s.title  = v1->title;
      s.artist = v1->artist;
      s.album  = v1->album;
      s.year   = v1->year;

      uint32_t genre {static_cast<uint32_t>(v1->genre)};
      if (genre < NUM_GENRES)
      {
        s.genre = GenreStr.at(genre);
      }
    }

    if (v2 != nullptr)
    {
      for (size_t i {0}; i<v2->texts; ++i)
      {
        if (!strncmp("TALB", v2->text[i].id, 4))      s.album = v2->text[i].text.p;
        else if (!strncmp("TIT2", v2->text[i].id, 4)) s.title = v2->text[i].text.p;
        else if (!strncmp("TRCK", v2->text[i].id, 4)) s.trackNumber = atoi(v2->text[i].text.p);
        else if (!strncmp("TYER", v2->text[i].id, 4)) s.year = v2->text[i].text.p;
        else if (!strncmp("TPE1", v2->text[i].id, 4)) s.artist = v2->text[i].text.p;
        else if (!strncmp("TPE2", v2->text[i].id, 4)) s.albumArtist = v2->text[i].text.p;
        else if (!strncmp("TPUB", v2->text[i].id, 4)) s.publisher = v2->text[i].text.p;
        else if (!strncmp("TSRC", v2->text[i].id, 4)) s.isrc = v2->text[i].text.p;
        else if (!strncmp("TCON", v2->text[i].id, 4))
        {
          // half-hearted effort at parsing tags...
          // Can replace first bracketed number (X) with ID3v1 Genre(X) (as longas it starts at the beginning of the string)
          // If first character is not a '(' then it just copies the tag string into the song's genre string.
          // Can't support multiple (X) ID3v1 tag references.
          // Can't retain other user characters in presence of ID3v1 reference.
          string tag { v2->text[i].text.p };
          if (tag.size())
          {
            s.genre = tag;
            if (tag.at(0) == '(') // ID3v1 reference (NUM)
            {
              if (tag.size() > 1)
              {
                istringstream ss { &tag.at(1) }; // skip first '('
                uint32_t genre { NUM_GENRES };
                ss >> genre;
                if ((ss.fail() == false) && genre < NUM_GENRES)
                {
                  s.genre = GenreStr.at(genre);
                }
              }
            }
          }

        }
        if (Config->general->custom_mp3_tag.size())
        {
          if (!strncmp(Config->general->custom_mp3_tag.c_str(), v2->text[i].id, Config->general->custom_mp3_tag.size())) s.custom_tag = v2->text[i].text.p;
        }
      }
    }

    if ((v1 == nullptr) && (v2 == nullptr))
    {
      error("'%s' has no MP3 ID3v1 or ID3v2 tag information", filename);
    }
  }
  mpg123_close(mp);
  mpg123_delete(mp);
  song.push_back(s);
}


void AudioClass::GetOGVSongInfo
(
  const char *filename,
  vector<song_t> &song
)
{
  // no metadata in OGV files, so make the title the name of the file (without extension)
  // all other tag data will need to be manually added to the database by the user :(
  song_t s {};
  s.type = song_type_e::ogv;
  s.title = UnknownTitleStr;
  s.artist = UnknownArtistStr;
  s.album = UnknownAlbumStr;
  s.albumArtist = UnknownAlbumArtistStr;
  s.year = UnknownYearStr;
  s.genre = GenreUnknownStr;
  s.publisher.clear();
  s.isrc.clear();
  s.custom_tag.clear();
  s.trackNumber = 0;
  s.trackNumberStr = "0";
  s.length = 0; // unknown

  s.title = string(filename);
  s.title.erase(0, s.title.find_last_of("/")+1); // remove path
  s.title.erase(s.title.find_last_of("."), string::npos); // remove extension
  song.push_back(s);
}

void AudioClass::GetPLSSongInfo
(
  const char *filename,
  vector<song_t> &song
)
{
  ifstream plsFile;
  string line;

  plsFile.open(filename, ios::in);

  if (plsFile.is_open())
  {
    song_t s {};
    s.type = song_type_e::url;
    s.title = UnknownTitleStr;
    s.artist = UnknownArtistStr;
    s.album = UnknownAlbumStr;
    s.albumArtist = UnknownAlbumArtistStr;
    s.year = UnknownYearStr;
    s.genre = GenreUnknownStr;
    s.publisher.clear();
    s.isrc.clear();
    s.custom_tag.clear();
    s.trackNumber = 0;
    s.trackNumberStr = "0";
    s.length = 0;

    string current_filename {};
    string current_title {UnknownTitleStr};

    uint32_t current_file_num {1};
    uint32_t current_title_num {1};

    while (getline(plsFile, line))
    {

      if (line.empty()) continue;

      line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
      line.erase(std::remove(line.begin(), line.end(), 13), line.end()); // remove CR (for non-linux text file)
      line.erase(std::remove(line.begin(), line.end(), 10), line.end()); // remove LF (for non-linux text file)

      size_t pos {};
      string str {};

      // find FileX= ...
      str = plsFile_File + to_string(current_file_num) + "=";
      pos = line.find(str);
      if (pos != string::npos) // found "File<current_file_num>"
      {
        try {
          line.erase(0, str.size()); // remove "File<current_file_num>=", to leave data field
        }
        catch (const std::out_of_range &err) {
          continue;
        }
        if (current_filename.size()) // save previous song now we have moved onto the next one...
        {
          s.filename = current_filename;
          s.title = current_title;
          song.push_back(s);
          current_title = UnknownTitleStr;
          current_title_num = current_file_num;
        }
        current_filename = line;
        current_file_num++;
        continue;
      }

      // find TitleX= ...
      str = plsFile_Title + to_string(current_title_num) + "=";
      pos = line.find(str);
      if (pos != string::npos) // found "Title<current_title_num>"
      {
        try {
          line.erase(0, str.size()); // remove "Title<current_title_num>=", to leave data field
        }
        catch (const std::out_of_range &err) {
          continue;
        }
        current_title = line;
        continue;
      }
    }
    if (current_filename.size()) // save last song...
    {
      s.filename = current_filename;
      s.title = current_title;
      song.push_back(s);
    }
    plsFile.close();
  }
}


void AudioClass::GetM3USongInfo
(
  const char *filename,
  vector<song_t> &song
)
{

  ifstream m3uFile;
  string line;

  m3uFile.open(filename, ios::in);

  if (m3uFile.is_open())
  {
    song_t s {};
    s.type = song_type_e::url;
    s.title = UnknownTitleStr;
    s.artist = UnknownArtistStr;
    s.album = UnknownAlbumStr;
    s.albumArtist = UnknownAlbumArtistStr;
    s.year = UnknownYearStr;
    s.genre = GenreUnknownStr;
    s.publisher.clear();
    s.isrc.clear();
    s.custom_tag.clear();
    s.trackNumber = 0;
    s.trackNumberStr = "0";
    s.length = 0;

    while (getline(m3uFile, line))
    {
      if (line.empty()) continue;

      line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
      line.erase(std::remove(line.begin(), line.end(), 13), line.end()); // remove CR (for non-linux text file)
      line.erase(std::remove(line.begin(), line.end(), 10), line.end()); // remove LF (for non-linux text file)

      if (line.find(m3uFile_ExtInf) != string::npos)
      {
        try {
          line.erase(0, line.find_first_of(",") + 1); // remove characters upto first comma, leaving "Artist - Title"
        }
        catch (const std::out_of_range &err) {
          continue;
        }
        // cout << "1 line " << line << endl;
        string title { line };
        size_t pos { title.find(" - ") };
        if (pos != string::npos)
        try {
          title.erase(0, pos+3);
        }
        catch (const std::out_of_range &err) {
          continue;
        }
        // cout << "2 title " << title << endl;
        s.title = title;
        try {
          line.erase(pos); // leaves "Artist"
        }
        catch (const std::out_of_range &err) {
          continue;
        }
        // cout << "3 line " << line << endl;
        s.artist = line;
      }
      else if (line.find(URLPrefix) != string::npos) // string contains "http"
      {
        s.filename = line;
        song.push_back(s);
        s.title = UnknownTitleStr;
        s.artist = UnknownArtistStr;
      }
    }
    m3uFile.close();
  }

// #EXTINF:-1,BBC - Radio 1
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_one.m3u8

// BBC Radio 1Xtra
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_1xtra.m3u8

// BBC Radio 2
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_two.m3u8

// BBC Radio 3
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_three.m3u8

// BBC Radio 4
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_fourfm.m3u8

// BBC Radio 4LW
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_fourlw.m3u8

// BBC Radio 4 Extra
// http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_radio_four_extra.m3u8

/////
// #EXTM3U
// http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio1_mf_p
// #EXTINF:-1,BBC - Radio 2
// http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio2_mf_p
// #EXTINF:-1,BBC - Radio 3
// http://open.live.bbc.co.uk/mediaselector/5/select/version/2.0/mediaset/http-icy-aac-lc-a/format/pls/vpid/bbc_radio_three.pls
// #EXTINF:-1,BBC - Radio 4
// http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio4fm_mf_p
// #EXTINF:-1,BBC - Radio 5 live
// http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio5live_mf_p
// #EXTINF:-1,BBC - Radio 6
// http://bbcmedia.ic.llnwd.net/stream/bbcmedia_6music_mf_p
// #EXTINF:-1,BBC - Radio 1 Extra
// http://www.bbc.co.uk/radio/listen/live/r1x_aaclca.pls
// #EXTINF:-1,BBC - Radio 4 Extra
// http://www.bbc.co.uk/radio/listen/live/r4x_aaclca.pls
// #EXTINF:-1,BBC - Radio 5 Live sports extra
// http://www.bbc.co.uk/radio/listen/live/r5lsp_aaclca.pls
// #EXTINF:-1,BBC - Radio Asian Network
// http://www.bbc.co.uk/radio/listen/live/ran_aaclca.pls
// # GistID: 8705765
}

void AudioClass::Mute(void)
{
  muted = true;
  al_set_mixer_gain(al_get_default_mixer(), 0.0);
}

void AudioClass::UnMute(void)
{
  muted = false;
  SetVolume(Config->sounds->song_volume);
}

void AudioClass::SetVolume
(
  const int32_t vol
)
{
  if (vol < MinSongVolume) Config->sounds->song_volume = MinSongVolume;
  else if (vol > MaxSongVolume) Config->sounds->song_volume = MaxSongVolume;
  else Config->sounds->song_volume = vol;
  al_set_mixer_gain(al_get_default_mixer(), gain_db.at(Config->sounds->song_volume / SongVolumeInc));

  stringstream s {};
  s << Config->sounds->song_volume;
  status.volume_str = s.str();

  Engine->status_event |= StatusEvent_volumeChange;
}

void AudioClass::VolumeUp(void)
{
  Config->sounds->song_volume += SongVolumeInc;
  SetVolume(Config->sounds->song_volume);
}

void AudioClass::VolumeDown(void)
{
  Config->sounds->song_volume -= SongVolumeInc;
  SetVolume(Config->sounds->song_volume);
}

void AudioClass::StopSong(bool skip)
{
  skipped = skip;
  AudioClass::play_song = false;
}

void AudioClass::PauseSong(void)
{
  if (paused)
  {
    paused = false;
  }
  else
  {
    paused = true;
  }
  Engine->status_event |= StatusEvent_songPauseChange;
}
