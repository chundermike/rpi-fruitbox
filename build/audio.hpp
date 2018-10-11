#pragma once

#include "fruitbox.hpp"
#ifdef _CURL
#include <curl/curl.h>
#endif

constexpr int32_t MinSongVolume { 0 };
constexpr int32_t MaxSongVolume { 100 };
constexpr int32_t SongVolumeInc { 10 };

using namespace std;

enum class song_play_state_e {
  loading,
  playing,
  unloading,
  stopped
};

class AudioClass
{
public:
  AudioClass(void);
  ~AudioClass();
  void Run(void);
  void GetMP3SongInfo(const char *filename, vector<song_t> &song );
  void GetOGVSongInfo(const char *filename, vector<song_t> &song );
  void GetM3USongInfo(const char *filename, vector<song_t> &song );
  void GetPLSSongInfo(const char *filename, vector<song_t> &song );
  void GetSongCoverArt(song_t *song);
  void RemoveSong(bool skipped);
  void PlaySongThread(void);
  void LoadAlbumArtwork(const song_t *song, bitmap_t *bitmap);
  void LoadArtworkThread(void);
  void PlaySound(sound_t sound);
  void StopSong(bool skip);
  void PauseSong(void);
  void SetVolume(const int32_t vol);
  void VolumeUp(void);
  void VolumeDown(void);
  void Mute(void);
  void UnMute(void);

  string song_filename {};
  string song_artist {};
  string song_album_artist {};
  string song_album {};
  string song_title {};
  mpg123_picture *song_picture {};
  int32_t song_number {};
  string song_year {};
  static atomic<bool>play_song;
  atomic<bool>skipped {};
  song_play_state_e song_play_state { song_play_state_e::stopped };
  static ALLEGRO_AUDIO_STREAM *mp3_stream;
  atomic<int32_t>SongPlayThread_status_event {};
  atomic<int32_t>LoadArtworkThread_status_event {};
  bool stereo {};
  bool paused { false };

private:
  static size_t CurlGetFormat(void *buffer, size_t size, size_t nmemb, void *userp);
  static size_t CurlGetMP3(void *buffer, size_t size, size_t nmemb, void *userp);
  bool AttachMP3ToMixer(const string &filename);
  time_t start_time, current_time;
  static mpg123_handle *mp3;
  static unsigned char *mp3_buffer;
  static size_t mp3_buffer_size;
  static size_t bytes_remaining;
  int32_t channels {}, encoding {};
  long rate {};
  uint32_t samples {};
  song_t no_song {};
  mutex artwork_mtx {};
  condition_variable get_artwork {};
  song_t *artwork_song {};
  bool muted { false };
  static bool url_get_format;
  // static bool url_format_valid;
  vector<double> gain_db {};
#ifdef _CURL
  CURL *curl {};
#endif
};

#define NUM_GENRES 192

const array<string, NUM_GENRES + 3> GenreStr {
 "Blues",
 "Classic Rock",
 "Country",
 "Dance",
 "Disco",
 "Funk",
 "Grunge",
 "Hip-Hop",
 "Jazz",
 "Metal",
 "New Age",
 "Oldies",
 "Other",
 "Pop",
 "R&B",
 "Rap",
 "Reggae",
 "Rock",
 "Techno",
 "Industrial",
 "Alternative",
 "Ska",
 "Death Metal",
 "Pranks",
 "Soundtrack",
 "Euro-Techno",
 "Ambient",
 "Trip-Hop",
 "Vocal",
 "Jazz+Funk",
 "Fusion",
 "Trance",
 "Classical",
 "Instrumental",
 "Acid",
 "House",
 "Game",
 "Sound Clip",
 "Gospel",
 "Noise",
 "AlternRock",
 "Bass",
 "Soul",
 "Punk",
 "Space",
 "Meditative",
 "Instrumental Pop",
 "Instrumental Rock",
 "Ethnic",
 "Gothic",
 "Darkwave",
 "Techno-Industrial",
 "Electronic",
 "Pop-Folk",
 "Eurodance",
 "Dream",
 "Southern Rock",
 "Comedy",
 "Cult",
 "Gangsta Rap",
 "Top 40",
 "Christian Rap",
 "Pop / Funk",
 "Jungle",
 "Native American",
 "Cabaret",
 "New Wave",
 "Psychedelic",
 "Rave",
 "Showtunes",
 "Trailer",
 "Lo-Fi",
 "Tribal",
 "Acid Punk",
 "Acid Jazz",
 "Polka",
 "Retro",
 "Musical",
 "Rock & Roll",
 "Hard Rock",
 "Folk",
 "Folk-Rock",
 "National Folk",
 "Swing",
 "Fast Fusion",
 "Bebob",
 "Latin",
 "Revival",
 "Celtic",
 "Bluegrass",
 "Avantgarde",
 "Gothic Rock",
 "Progressive Rock",
 "Psychedelic Rock",
 "Symphonic Rock",
 "Slow Rock",
 "Big Band",
 "Chorus",
 "Easy Listening",
 "Acoustic",
 "Humour",
 "Speech",
 "Chanson",
 "Opera",
 "Chamber Music",
 "Sonata",
 "Symphony",
 "Booty Bass",
 "Primus",
 "Porn Groove",
 "Satire",
 "Slow Jam",
 "Club",
 "Tango",
 "Samba",
 "Folklore",
 "Ballad",
 "Power Ballad",
 "Rhythmic Soul",
 "Freestyle",
 "Duet",
 "Punk Rock",
 "Drum Solo",
 "A Cappella",
 "Euro-House",
 "Dance Hall",
 "Goa",
 "Drum & Bass",
 "Club-House",
 "Hardcore",
 "Terror",
 "Indie",
 "BritPop",
 "Negerpunk",
 "Polsk Punk",
 "Beat",
 "Christian Gangsta Rap",
 "Heavy Metal",
 "Black Metal",
 "Crossover",
 "Contemporary Christian",
 "Christian Rock",
 "Merengue",
 "Salsa",
 "Thrash Metal",
 "Anime",
 "JPop",
 "Synthpop",
 "Abstract",
 "Art Rock",
 "Baroque",
 "Bhangra",
 "Big Beat",
 "Breakbeat",
 "Chillout",
 "Downtempo",
 "Dub",
 "EBM",
 "Eclectic",
 "Electro",
 "Electroclash",
 "Emo",
 "Experimental",
 "Garage",
 "Global",
 "IDM",
 "Illbient",
 "Industro-Goth",
 "Jam Band",
 "Krautrock",
 "Leftfield",
 "Lounge",
 "Math Rock",
 "New Romantic",
 "Nu-Breakz",
 "Post-Punk",
 "Post-Rock",
 "Psytrance",
 "Shoegaze",
 "Space Rock",
 "Trop Rock",
 "World Music",
 "Neoclassical",
 "Audiobook",
 "Audio Theatre",
 "Neue Deutsche Welle",
 "Podcast",
 "Indie Rock",
 "G-Funk",
 "Dubstep",
 "Garage Rock",
 "Psybient",
  GenreUnknownStr, // fruitbox specific
  GenreAnyStr, // fruitbox specific
  GenreOffStr // fruitbox specific
};
