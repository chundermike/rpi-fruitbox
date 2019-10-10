#include "fruitbox.hpp"
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

// fruitbox database...
//
// The database consists of a sorted vector of song_t structures
// The vector is created if the database doesn't exist, and then written to the database file.

// If the database file exists, it is read into a vector of song_t and then sorted (by whatever
// is specified in the config file).  Alongside the songs vector, a 2d vector of songs is created
// (song_lookup) each time fruitbox is run. The two dimensions correspond to the page number and
// song entry within each page. Each song is represented by a song_t* which points to a song_t in
// the database songs vector.
//
// Songs are retrieved by the GetSong(page, entry) or GetSong() methods

vector<song_t> DatabaseClass::database { };
string DatabaseClass::music_path { };
string DatabaseClass::database_filename { };
ofstream DatabaseClass::dbFile { };
bool DatabaseClass::file_created { false };
bool DatabaseClass::music_path_written { false };
bool DatabaseClass::db_out_of_date { false };
time_t DatabaseClass::db_mtime {};

constexpr int  search_depth     { 16 };
constexpr char dbFile_delimiter { '|' };
constexpr char dbFile_comment   { '#' };

/////////////////////////////////////////////////////////////////////////////////////////////////////

DatabaseClass::DatabaseClass
(
  const string &filename
)
{
  string line;
  ifstream dbFile;
  uint32_t dbFile_line_number { 0 };
  number_of_songs = 0;
  
  struct stat sb;

  if (stat(filename.c_str(), &sb) == 0)
  {
    // log_file << filename << " Last file modification:   " << ctime(&sb.st_mtime) << " " << sb.st_mtime << endl;
    db_mtime = sb.st_mtime;
  }

  for (auto i : Config->general->music_path)
  {
    ftw(i.c_str(), CheckDate, search_depth);
    // if (stat(i.c_str(), &sb) == 0)
    // {
      // if (sb.st_mtime > db_mtime) // music_path has been modified after database file...
      // {
        // db_out_of_date = true;
      // }
    // }
  }

  // delete database file if it's out of date...

  if (db_out_of_date)
  {
    log_file << NOTE << "Database out of date, ";
    if (no_db_update)
    {
      log_file << "but regeneration disabled with " << commandLineArgNoDbUpdate << " command line option" << endl;
    }
    else {
      log_file << "will regenerate it." << endl;
      string cmd { "sudo rm " + filename };
      // log_file << "CMD = " << cmd << endl;
      int s = system(cmd.c_str());
    }
  }

  // check if database file exists...if not, create a default one
  dbFile.open(filename, ios::in);
  if (!dbFile.is_open())
  { // doesn't exist so create it..
    log_file << "Database '" << filename << "' not found, so will create it for you..." << endl;
    Create(filename);
    dbFile.open(filename, ios::in);
    if (!dbFile.is_open())
    { // still doesn't exist so report error
      error("Couldn't open database file '%s' for input", filename.c_str());
    }
  }

  // now read database file...

  log_file << "Loading database '" << filename << "'..." << endl;

  DatabaseClass::database.clear(); // start with an empty database (Create will have filled it)

  // read the songs from the file...as robust as possible
  song_t song;
  while (getline(dbFile, line))
  {
    dbFile_line_number++;
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.at(0) == dbFile_comment) continue; // comment line
    istringstream ss { line };
    if (line.find(dbFile_delimiter) == string::npos)
    { // no delimiter, so probably a new music_path
      getline(ss >> std::ws, DatabaseClass::music_path, dbFile_comment);
      DatabaseClass::music_path.erase(DatabaseClass::music_path.find_last_not_of(" \t")+1);// remove trailing whitespace
      continue;
    }
    // else song entry ...
    string intstr;
    if (!getline(ss >> std::ws, song.filename, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.title, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.artist, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.album, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.albumArtist, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.year, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.trackNumberStr, dbFile_delimiter)) goto bad_line;
    // if (!getline(ss, intstr, dbFile_delimiter)) goto bad_line;
    try { song.trackNumber = static_cast<uint32_t>(stoi(song.trackNumberStr)); }
    catch (const std::invalid_argument &err) { goto bad_line; }
    catch (const std::out_of_range &err) { goto bad_line; }

    if (!getline(ss, intstr, dbFile_delimiter)) goto bad_line;

    try { song.length = static_cast<uint32_t>(stoi(intstr)); }
    catch (const std::invalid_argument &err) { song.length = 0; }
    catch (const std::out_of_range &err) { song.length = 0; }

    song.publisher.clear();
    song.isrc.clear();
    song.custom_tag.clear();

    // publisher, IRSC and custom (V1.4 onwards, so if they don't exist we are probably loading a pre V1.4 database, so don't throw a wobbly)
    if (getline(ss >> std::ws, song.publisher, dbFile_delimiter))
    {
      if (getline(ss >> std::ws, song.isrc, dbFile_delimiter))
      {
        if (getline(ss >> std::ws, song.custom_tag, dbFile_delimiter))
        {
          getline(ss >> std::ws, song.genre, dbFile_delimiter);
        }
      }
    }

    // add the current music_path to the song.filename (if it's not a URL)...
    if (song.filename.find(URLPrefix) == string::npos) // string doesn't contain "http"
    {
      song.filename = DatabaseClass::music_path + song.filename;
    }
    // log_file << song.filename << endl;
    // ...and store the song in database
    DatabaseClass::database.push_back(song);
    continue;

    bad_line:
    log_file << endl << WARNING << "Badly formatted song entry ('" << filename << "', line " << dbFile_line_number << ")" << endl;
  }

  dbFile.close();

  DatabaseClass::database.shrink_to_fit(); // free unused capacity

  number_of_songs = DatabaseClass::database.size();
  log_file << number_of_songs << " songs found" << endl;

  if (number_of_songs == 0) {
    error("database file '%s' contains no songs.  Please delete it and re-run fruitbox, making sure the MusicPath parameter in your configuration file points to a directory which contains some MP3 files", filename.c_str());
  }

  // sort the database...

  for (auto &song_sort : Config->general->sort_songs_by)
  {
    log_file << "Sorting songs by ";
    static bool (*sort_func)(const song_t &song_a, const song_t &song_b);

    // choose sort method...
    // switch (Config->general->sort_songs_by)
    switch (song_sort)
    {
      case sort_songs_by_e::Title :
        sort_func = SortByTitle;
        log_file << "Title..." << endl;
        break;

      case sort_songs_by_e::Artist :
        sort_func = SortByArtist;
        log_file << "Artist..." << endl;
        break;

      case sort_songs_by_e::Album :
        sort_func = SortByAlbum;
        log_file << "Album..." << endl;
        break;

      case sort_songs_by_e::AlbumArtist :
        sort_func = SortByAlbumArtist;
        log_file << "Album Artist..." << endl;
        break;

      case sort_songs_by_e::Year :
        sort_func = SortByYear;
        log_file << "Year..." << endl;
        break;

      case sort_songs_by_e::Genre :
        sort_func = SortByGenre;
        log_file << "Genre..." << endl;
        break;

      case sort_songs_by_e::TrackNumber :
        sort_func = SortByTrackNumber;
        log_file << "Track Number..." << endl;
        break;

      case sort_songs_by_e::Publisher :
        sort_func = SortByPublisher;
        log_file << "Publisher..." << endl;
        break;

      case sort_songs_by_e::ISRC :
        sort_func = SortByISRC;
        log_file << "ISRC..." << endl;
        break;

      case sort_songs_by_e::Custom :
        sort_func = SortByCustom;
        log_file << "Custom MP3 tag..." << endl;
        break;

      case sort_songs_by_e::Random :
        sort_func = nullptr;
        log_file << "Random..." << endl;
        std::random_shuffle(DatabaseClass::database.begin(), DatabaseClass::database.end());
        break;

      case sort_songs_by_e::Unsorted :
        sort_func = nullptr;
        log_file << "database order (Unsorted)" << endl;
        break;

    }

    // do the sort...
    if (sort_func != nullptr) std::stable_sort(DatabaseClass::database.begin(), DatabaseClass::database.end(), sort_func);
  }

  // construct song pages (depends upon Config->songs_per_page and Config->pair_songs)
  BuildPages();
  status.num_songs_str = to_string(number_of_songs);
  status.num_pages_str = to_string(number_of_pages);
}

///////////////////////////////////////////////////////////////////////////////
// use file tree walker to recursively check directory timestamps for database out-of-date check...

int DatabaseClass::CheckDate
(
  const char        *path,
  const struct stat *sptr,
  int               type
)
{
  string p { path };
  if (type == FTW_D)
  { // directory
    struct stat sb;
    if (stat(path, &sb) == 0)
    {
      if (sb.st_mtime > DatabaseClass::db_mtime) // music_path has been modified after database file...
      {
        DatabaseClass::db_out_of_date = true;
      }
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// use file tree walker to search for MP3 files, and store them in the database...

int DatabaseClass::Search
(
  const char        *path,
  const struct stat *sptr,
  int               type
)
{
  string p { path };
  if (type == FTW_F)
  { // normal file
    if (p.size() < 4) return 0;

    vector<song_t> song;

    // extract file extension and convert to lower case...
    string file_ext { p.substr( p.length() - 4 ) };
    transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

    if (file_ext == ".mp3") Audio->GetMP3SongInfo((const char *)path, song);
    if (file_ext == ".ogv") Audio->GetOGVSongInfo((const char *)path, song);
    #ifdef _CURL
    if (file_ext == ".m3u") Audio->GetM3USongInfo((const char *)path, song); // could be more than one song
    if (file_ext == ".pls") Audio->GetPLSSongInfo((const char *)path, song); // could be more than one song
    #endif

    for (auto &s : song)
    {
      if (s.title.size())
      {
        if (s.type != song_type_e::url) // for url files, filename is extracted from inside m3u file (http address)
        {
          try {
            s.filename.assign(p, DatabaseClass::music_path.size(), string::npos);
          }
          catch (const std::out_of_range &err) { // no song
            return 0;
          }
        }

        // add song to database...
        DatabaseClass::database.push_back(s);

        if (DatabaseClass::file_created == false)
        {
          DatabaseClass::OpenNew();
          DatabaseClass::file_created = true;
        }
        
        if (DatabaseClass::music_path_written == false)
        {
          DatabaseClass::dbFile << endl << DatabaseClass::music_path << endl << endl;
          DatabaseClass::music_path_written = true;
        }

        // write song to database file...
        DatabaseClass::dbFile << s.filename << dbFile_delimiter;
        DatabaseClass::dbFile << s.title << dbFile_delimiter;
        DatabaseClass::dbFile << s.artist << dbFile_delimiter;
        DatabaseClass::dbFile << s.album << dbFile_delimiter;
        DatabaseClass::dbFile << s.albumArtist << dbFile_delimiter;
        DatabaseClass::dbFile << s.year << dbFile_delimiter;
        DatabaseClass::dbFile << s.trackNumber << dbFile_delimiter;
        DatabaseClass::dbFile << s.length << dbFile_delimiter;
        DatabaseClass::dbFile << s.publisher << dbFile_delimiter;
        DatabaseClass::dbFile << s.isrc << dbFile_delimiter;
        DatabaseClass::dbFile << s.custom_tag << dbFile_delimiter;
        DatabaseClass::dbFile << s.genre << endl;

        string info1 { s.title + " - " + s.artist };
        string info2 { DatabaseClass::music_path + " ... " + to_string(DatabaseClass::database.size()) + " songs" };
        Display->DrawInfoBox("Creating Database " + DatabaseClass::database_filename, info1, info2, Chooser->screenshot_bm, false, true);
      }
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////

void DatabaseClass::Create
(
  const string filename
)
{
  log_file << "Creating new database '" << filename << "'..." << endl;
  log_file << "This may take some time, but only needs to be done once." << endl;
  log_file << "If your music library changes please delete '" << Config->general->database_filename << "' and re-run fruitbox.\n" << endl;
  log_file << "Alternatively, if you are feeling brave, you can edit the database file directly," << endl;
  log_file << "using a text editor.  This can be useful if you want to add or remove songs manually," << endl;
  log_file << "and/or modify their tag data (song title, artist name, etc.)" << endl << endl;

  DatabaseClass::database_filename = filename;

  for (auto i : Config->general->music_path)
  { // for each music path specified in the config
    log_file << "Searching " << i << " ..." << endl;
    DatabaseClass::music_path_written = false;
    DatabaseClass::music_path = i;
    ftw(i.c_str(), Search, search_depth);
  }
  log_file << endl;

  number_of_songs = DatabaseClass::database.size();

  if (number_of_songs == 0)
  {
    error("Can't find any MP3 songs (are the 'MusicPath' settings in your config correct?)\n");
  }

  DatabaseClass::dbFile.close();
}

void DatabaseClass::OpenNew(void)
{
  DatabaseClass::dbFile.open(DatabaseClass::database_filename.c_str(), ios::out);
  if (!DatabaseClass::dbFile.is_open())
  {
    error("Couldn't create '%s'", DatabaseClass::database_filename.c_str());
  }

  // write database header
  DatabaseClass::dbFile << "# fruitbox " << FRUITBOX_VERSION << " database file" << endl;
  DatabaseClass::dbFile << "# song entry format is Filename" << dbFile_delimiter << "SongTitle" << dbFile_delimiter << "Artist" << dbFile_delimiter << "AlbumTitle" << dbFile_delimiter;
  DatabaseClass::dbFile << "AlbumArtist" << dbFile_delimiter << "Year" << dbFile_delimiter << "TrackNumber" << dbFile_delimiter << "LengthInSeconds" << dbFile_delimiter;
  DatabaseClass::dbFile << "Publisher" << dbFile_delimiter << "ISRC" << dbFile_delimiter << "CustomTag[" << Config->general->custom_mp3_tag << "]" << dbFile_delimiter;
  DatabaseClass::dbFile << "Genre" << endl;
}

bool DatabaseClass::CheckNewSortSectionStart(song_t &song)
{
  if (Config->general->sort_songs_by.size() == 0) return false;

  static char previous_first_char {};
  char first_char;
  sort_songs_by_e song_sort { Config->general->sort_songs_by.back()};
  string *str {};

  switch (song_sort)
  {
    case sort_songs_by_e::Title :
      str = &song.title;
      // log_file << "Title..." << endl;
      break;

    case sort_songs_by_e::Artist :
      str = &song.artist;
      // log_file << "Artist..." << endl;
      break;

    case sort_songs_by_e::Album :
      str = &song.album;
      // log_file << "Album..." << endl;
      break;

    case sort_songs_by_e::AlbumArtist :
      str = &song.albumArtist;
      // log_file << "Album Artist..." << endl;
      break;

    case sort_songs_by_e::Year :
      str = &song.year;
      // log_file << "Year..." << endl;
      break;

    case sort_songs_by_e::Genre :
      str = &song.genre;
      // log_file << "Genre..." << endl;
      break;

    case sort_songs_by_e::TrackNumber :
      str = &song.trackNumberStr;
      // log_file << "Track Number..." << endl;
      break;

    case sort_songs_by_e::Publisher :
      str = &song.publisher;
      // log_file << "Publisher..." << endl;
      break;

    case sort_songs_by_e::ISRC :
      str = &song.isrc;
      // log_file << "ISRC..." << endl;
      break;

    case sort_songs_by_e::Custom :
      str = &song.custom_tag;
      // log_file << "Custom MP3 tag..." << endl;
      break;

    case sort_songs_by_e::Random :
      return false;
      break;

    case sort_songs_by_e::Unsorted :
      return false;
      break;

  }

  // log_file << "String : " << *str << endl;

  if (str->size())
  {
    first_char = tolower(str->at(0));
    if (previous_first_char != first_char)
    {
      previous_first_char = first_char;
      // log_file << "NEW SORT SECTION!!" << endl;
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
// fill the song_lookup 2d vector with pages of song entries
// lower dimension holds entries on each page, upper dimension holds complete pages...

void DatabaseClass::BuildPages(void)
{
  number_of_pages = 0;
  vector<song_t*> page(Config->general->songs_per_page, nullptr);
  uint32_t entry_number_this_page { 0 };
  string previousAlbum {};

  // log_file << "number of song pages..." << Config->general->num_pages << endl;
  log_file << "Building song pages..." << endl;

  for (uint32_t current_song { 0 }; current_song < DatabaseClass::database.size(); ++current_song)
  { // for every song in the database
    if ((Config->general->page_mode == page_mode_e::Albums) && (DatabaseClass::database.at(current_song).album != previousAlbum))
    // albums mode and album name changed, so start a new page...
    {
      if (entry_number_this_page) // don't start new page if last just pushed back
      {
        if (number_of_pages > 0) song_lookup.push_back(page); // don't push anything before very first page
        entry_number_this_page = 0;
      }
    }

    if (entry_number_this_page == 0)
    { // first entry on a page
      // log_file << " number_of_pages % Config->general->num_pages " << number_of_pages << " " << Config->general->num_pages << " " << number_of_pages % Config->general->num_pages << endl;
      if ((number_of_pages % Config->general->num_pages) == 0)
      // check first song every Config->general->num_pages
      {
        if (CheckNewSortSectionStart(DatabaseClass::database.at(current_song)))
        {
          jump_sort_page.push_back(number_of_pages);// / Config->general->num_pages);
          // log_file << "jump_sort_page.push_back(" << number_of_pages << ")" << endl;
        }
      }
      number_of_pages++;
      std:fill(page.begin(), page.end(), nullptr); // all entries default to empty
    }

    // add song from database to page...
    page.at(entry_number_this_page) = &DatabaseClass::database.at(current_song);
    ++entry_number_this_page;
    previousAlbum = DatabaseClass::database.at(current_song).album;
    // check if we have filled the current page up; if so, add it to the song_lookup table
    if ((entry_number_this_page == Config->general->songs_per_page) || (current_song == DatabaseClass::database.size() - 1))
    { // page complete or no more songs
      song_lookup.push_back(page);
      entry_number_this_page = 0;
    }
    else // paired song?...
    {
      if (Config->general->page_mode == page_mode_e::Singles)
      {
        if (Config->general->pair_songs != pair_songs_e::No)
        { // if pairing songs, see if next song in database is by the same artist...
          if (current_song + 1 == DatabaseClass::database.size()) break; // no songs left
          // If in Dual pair_song mode we pair the songs up regardless of if they share the same artist
          // Otherwise (in Yes pair_song mode) we pair the songs up only if they share the same artist
          if ((Config->general->pair_songs == pair_songs_e::Dual) || (DatabaseClass::database.at(current_song).artist == DatabaseClass::database.at(current_song + 1).artist))
          { // yes, so add next song (ptr)
            ++current_song;
            page.at(entry_number_this_page) = &DatabaseClass::database.at(current_song);
          }
          ++entry_number_this_page;
          previousAlbum = DatabaseClass::database.at(current_song).album;
          if ((entry_number_this_page == Config->general->songs_per_page) || (current_song == DatabaseClass::database.size() - 1))
          { // page complete or no more songs
            song_lookup.push_back(page);
            entry_number_this_page = 0;
          }
        }
      }
    }
  }

  song_lookup.shrink_to_fit(); // free unused capacity

  #if 0
  // debug print out of pages...
  for (uint32_t p {} ; p < song_lookup.size(); ++p) {
    log_file << endl << "page " << p << " ..." << endl;

    for (auto e : song_lookup.at(p)) {
      if (e == nullptr) log_file << "------" << endl;
      else log_file << e->title << endl;
    }
  }
  #endif

}

///////////////////////////////////////////////////////////////////////////////
// retrieve a song from the database, by specifying its filename...
// note this will be slow, but is used when loading a playlist at startup

song_t* DatabaseClass::GetSong
(
  const string &filename
)
{
  uint32_t page {};
  uint32_t entry {};
  auto pos = std::find_if(DatabaseClass::database.begin(), DatabaseClass::database.end(), [s = filename](const song_t song) -> bool { return s == song.filename; });

  if (pos == DatabaseClass::database.end()) return nullptr;
  return &DatabaseClass::database.at(pos - DatabaseClass::database.begin());
}

///////////////////////////////////////////////////////////////////////////////
// retrieve a song from the database, by specifying its page number and
// entry position in that page...

song_t* DatabaseClass::GetSong
(
  const uint32_t page,
  const uint32_t entry
)
{
  return song_lookup.at(page).at(entry);
}


///////////////////////////////////////////////////////////////////////////////
// retrieve a random song from the database...

song_t* DatabaseClass::GetSong(void)
{
  uint32_t tries { 100 };
  song_t *song;
  deque<song_t *> *history = &PlayQueue->song_play_history;
  deque<song_t *> *playqueue = &PlayQueue->queue;
  bool duplicate { false };
  PlayQueue->mtx.lock();

  while (tries--)
  // make sure we don't add one from the song_play_history, or also one from the playqueue...
  // if we timeout then just send back one anyway
  {
    song = &DatabaseClass::database.at(rand() % number_of_songs);
    if (find(history->begin(), history->end(), song) == history->end()) // song not in history
    {
      if (find(playqueue->begin(), playqueue->end(), song) == playqueue->end()) break; // and also not in playqueue
    }
  }

  PlayQueue->mtx.unlock();
  return song;
}

///////////////////////////////////////////////////////////////////////////////
// retrieve a random song from the database from a certain genre...

song_t* DatabaseClass::GetGenreSong
(
  const string &genre
)
{
  uint32_t tries { 1000 };
  song_t *song;
  deque<song_t *> *history = &PlayQueue->song_play_history;
  deque<song_t *> *playqueue = &PlayQueue->queue;
  bool duplicate { false };

  if (genre == GenreAnyStr)
  {
    song = GetSong(); // get a random song (genre doesn't matter)
  }
  else // genre does matter
  {
    while (tries--)
    {
      song = GetSong(); // get a random song (which isn't currently in the playqueue or history)

      // check if it's the genre we want...
      if (song->genre == genre) break; // genre exactly matches song genre string
      // if (song->genre.find(genre) != string::npos) break; // genre appears in song genre string
    }
  }

  return song;
}
