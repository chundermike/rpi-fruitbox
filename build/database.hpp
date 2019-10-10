#pragma once

#include "fruitbox.hpp"

using namespace std;

class DatabaseClass {
public:
  DatabaseClass(const string &filename);
  song_t* GetSong(const uint32_t page, const uint32_t entry);
  song_t* GetSong(const string &filename);
  song_t* GetSong(void); // get a random song
  song_t* GetGenreSong(const string &genre); // get random song from specified genre
  uint32_t number_of_songs { };
  uint32_t number_of_pages { };
  vector<uint32_t> jump_sort_page {};
private:
  static string database_filename;
  static vector<song_t> database;
  static string music_path;
  static ofstream dbFile;
  vector< vector<song_t*> > song_lookup { };
  void Create(const string filename);
  static int CheckDate(const char *path, const struct stat *sptr, int type);
  static int Search(const char *path, const struct stat *sptr, int type);
  bool CheckNewSortSectionStart(song_t &song);
  static void OpenNew(void);
  void BuildPages(void);
  static bool file_created;
  static bool music_path_written;
  static bool db_out_of_date;
  static time_t db_mtime;


  static bool SortByAlbum(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.album < song_b.album) return true;
    return false;
  }

  static bool SortByTrackNumber(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.trackNumber < song_b.trackNumber) return true;
    return false;
  }

  static bool SortByAlbumArtist(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.albumArtist < song_b.albumArtist) return true;
    return false;
  }

  static bool SortByArtist(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.artist < song_b.artist) return true;
    return false;
  }

  static bool SortByTitle(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.title < song_b.title) return true;
    return false;
  }

  static bool SortByYear(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.year < song_b.year) return true;
    return false;
  }

  static bool SortByGenre(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.genre < song_b.genre) return true;
    return false;
  }

  static bool SortByPublisher(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.publisher < song_b.publisher) return true;
    return false;
  }

  static bool SortByISRC(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.isrc < song_b.isrc) return true;
    return false;
  }

  static bool SortByCustom(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.custom_tag < song_b.custom_tag) return true;
    return false;
  }

};
