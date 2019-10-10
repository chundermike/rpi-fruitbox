#pragma once

class PlayQueueClass {
public:
  void Load(const string filename);
  void Save(const string filename);
  int FindSong(song_t *song);
  song_t * QuerySong(const int32_t from_top);
  bool Add(song_t *song, play_type_e credit_play);
  void Remove(void);
  void Clear(void);
  uint32_t NumSongsTotal(void);
  uint32_t NumSongsComingUp(void);
  string NumSongsComingUpStr(void);
  string TotalTimeComingUp(void);
  std::mutex mtx;
  void AddToHistory(const int32_t from_top);
  deque<song_t *> song_play_history { };
  deque<song_t*> queue { };
  bool empty {true};
  bool full {false};
private:
  uint32_t total_time { };
  string StrHMS(uint32_t hms) {
    stringstream s;
    s << setfill('0') << setw(2) << SecondsToHours(hms)  << ":"
      << setfill('0') << setw(2) << SecondsToMinutes(hms) << ":"
      << setfill('0') << setw(2) << SecondsToSeconds(hms);
    return s.str();
  }
};
