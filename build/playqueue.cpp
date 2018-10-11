#include "fruitbox.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Play Queues...

uint32_t PlayQueueClass::NumSongsTotal(void)
{
  return queue.size();
}

uint32_t PlayQueueClass::NumSongsComingUp(void)
{
  uint32_t n { 0 };
  mtx.lock();
  if (queue.size())
  { // exclude top song (which is playing/about to be played)
    n = queue.size() - 1;
  }
  mtx.unlock();
  return n;
}

string PlayQueueClass::NumSongsComingUpStr(void)
{
  stringstream s {};
  uint32_t n { NumSongsComingUp() };
  s << n;
  return s.str();
}

string PlayQueueClass::TotalTimeComingUp(void)
{
  uint32_t t { total_time };

  mtx.lock();
  if (queue.size())
  {
    song_t *top_song = queue.at(0);
    t -= top_song->length;
  }
  mtx.unlock();
  return StrHMS(t);
}

// QuerySong : return the song information for the entry in the queue "from_top" entries from the top
// i.e. if from_top = 0, this returns the next entry in the queue
// i.e. if from_top = 1, this returns the second entry in the queue

song_t * PlayQueueClass::QuerySong(const int32_t from_top)
{
  song_t *song;
  uint32_t occ { static_cast<uint32_t>(queue.size()) };
  if (occ == 0) return nullptr; // nothing in queue
  if (from_top >= occ) return nullptr; // not enough entries in the queue
  song = queue.at(from_top);

  string file_ext { song->filename.substr( song->filename.length() - 4 ) };
  transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

  song->type = song_type_e::unknown;
  if (file_ext == ".mp3") song->type = song_type_e::mp3;
  if (file_ext == ".ogv") song->type = song_type_e::ogv;
    // cout << "song->filename " << song->filename << endl;
  if (song->filename.find(URLPrefix) != string::npos) // string contains "http"
  {
    // cout << "SONG IS URL!!!" << endl;
    song->type = song_type_e::url;
  }

  // cout << endl << "Query " << from_top << "..." << endl;
  // cout << "title = " << song->title << endl;
  // cout << "artist = " << song->artist << endl;
  // cout << "album artist = " << song->albumArtist << endl;
  // cout << "track = " << song->trackNumberStr << endl << endl;
  return song;
}

void PlayQueueClass::AddToHistory(const int32_t from_top)
{
  if (Config->general->song_history_depth == 0) return;
  
  mtx.lock();
  uint32_t occ { static_cast<uint32_t>(queue.size()) };
  if (occ) 
  {
    song_play_history.push_back(queue.at(from_top));
    if (song_play_history.size() > Config->general->song_history_depth)
    // remove oldest entry if history size exceeds user specified...
    {
      song_play_history.pop_front();
    }
  }
  mtx.unlock();
}

void PlayQueueClass::Add(song_t *song, play_type_e credit_play)
{ // add song(s) to the end of the queue
  mtx.lock();
  if (queue.size() < Config->general->max_playlist_length) // room in play queue
  {
    if ((Config->general->free_play == false) && (static_cast<bool>(credit_play) == true))
    { // credit check...
      if (status.credits == 0) // no money left!
      {
        mtx.unlock();
        return;
      }
      status.credits--;
      Engine->status_event |= StatusEvent_creditsChange;
    }
    queue.push_back(song);
    total_time += song->length;
    empty = false;
    if (queue.size() == Config->general->max_playlist_length) // queue full
    {
      full = true;
    }
    Engine->status_event |= StatusEvent_playqueueChange;
  }
  mtx.unlock();
}

void PlayQueueClass::Remove(void)
{ // remove last song from the beginning of the queue
  mtx.lock(); // can be called by main thread or audio thread
  if (queue.size())
  {
    queue.pop_front();
    total_time -= status.now_playing->length;
    full = false;
    if (queue.size() == 0) empty = true;
    Engine->status_event |= StatusEvent_playqueueChange;
  }
  mtx.unlock();
}

void PlayQueueClass::Clear(void)
{
  song_t *song {};
  mtx.lock();
  if (queue.size())
  {
    song = QuerySong(0); // remember top song (it's the one currently playing)
    queue.clear();
    empty = true;
    total_time = 0;
    mtx.unlock();
    Add(song, play_type_e::free_play); // restore currently playing song
    Engine->status_event |= StatusEvent_playqueueChange;
  }
  else
  {
    mtx.unlock();
  }
}

void PlayQueueClass::Load(const string filename)
{
  if (filename.size())
  {
    song_t *song;
    string line;
    string song_filename;
    ifstream playlistFile;
    playlistFile.open(filename.c_str(), ios::in);
    if (!playlistFile.is_open())
    {
      cout << WARNING << "Couldn't open ''" << filename.c_str() << "'" << endl;
    }
    else
    {
      cout << "Loading playlist '" << filename << "'..." << endl;
      while (getline(playlistFile, line))
      // read line (containing filename)
      {
        if (line.empty()) continue;
        line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
        if (line.at(0) == '#') continue; // comment line
        istringstream ss { line };
        if (!getline(ss >> std::ws, song_filename)) continue;
        song_filename.erase(song_filename.find_last_not_of(" \t")+1);// remove trailing whitespace
        song = Database->GetSong(song_filename);
        // search database for filename
        if (song != nullptr)
        {
          Add(song, play_type_e::free_play); // add song to queue
        }
      }
      playlistFile.close();
      status.coming_up_num_songs_str = NumSongsComingUpStr();
      status.coming_up_total_length_str = TotalTimeComingUp();
    }
  }
}

void PlayQueueClass::Save(const string filename)
{
  if (filename.size())
  {
    ofstream playlistFile;
    playlistFile.open(filename.c_str(), ios::out);
    if (!playlistFile.is_open())
    {
      cout << WARNING << "Couldn't create ''" << filename.c_str() << "'" << endl;
    }
    else
    {
      cout << "Saving playlist '" << filename << "'..." << endl;
      playlistFile << "# fruitbox " << FRUITBOX_VERSION << " playlist file " << endl << endl;
      for (auto i : queue)
      {
        playlistFile << i->filename << endl;
      }
      playlistFile.close();
    }
  }
}

