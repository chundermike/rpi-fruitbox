#include "fruitbox.hpp"
#include "status.hpp"
#include <ftw.h>

#include <vector>

using namespace std;

int32_t StatusDisplayClass::if_song_coming_ups;
int32_t StatusDisplayClass::coming_up_song_title;
int32_t StatusDisplayClass::coming_up_song_artist;
int32_t StatusDisplayClass::coming_up_song_album;
int32_t StatusDisplayClass::coming_up_song_album_artist;
int32_t StatusDisplayClass::coming_up_song_track_number;
int32_t StatusDisplayClass::coming_up_song_year;
int32_t StatusDisplayClass::coming_up_song_genre;
int32_t StatusDisplayClass::coming_up_song_publisher;
int32_t StatusDisplayClass::coming_up_song_isrc;
int32_t StatusDisplayClass::coming_up_song_custom_tag;
int32_t StatusDisplayClass::coming_up_song_length;
uint32_t StatusDisplayClass::num_sound_channels;

vector<string> StatusDisplayClass::static_bitmap_name;

///////////////////////////////////////////////////////////////////////////////

bool StatusDisplayClass::funcNowPlayingTitle(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->title;
  return false;
}

bool StatusDisplayClass::funcNowPlayingArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->artist;
  return false;
}

bool StatusDisplayClass::funcNowPlayingAlbum(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->album;
  return false;
}

bool StatusDisplayClass::funcNowPlayingAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->albumArtist;
  return false;
}

bool StatusDisplayClass::funcNowPlayingTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->trackNumberStr;
  return false;
}

bool StatusDisplayClass::funcNowPlayingYear(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->year;
  return false;
}

bool StatusDisplayClass::funcNowPlayingGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->genre;
  return false;
}

bool StatusDisplayClass::funcNowPlayingPublisher(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->publisher;
  return false;
}

bool StatusDisplayClass::funcNowPlayingISRC(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->isrc;
  return false;
}

bool StatusDisplayClass::funcNowPlayingCustomTag(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->custom_tag;
  return false;
}

bool StatusDisplayClass::funcNowPlayinglength(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_length_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingElapsedTime(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_elapsed_time_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingTimeRemaining(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_time_remaining_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingArtwork(StatusDisplayClass *s, unsigned char param)
{
  s->artwork_bitmap.handle = status.now_playing->artwork.handle;
  return false;
}

bool StatusDisplayClass::funcComingUpNumSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.coming_up_num_songs_str;
  return false;
}

bool StatusDisplayClass::funcComingUpTotalTime(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.coming_up_total_length_str;
  return false;
}

bool StatusDisplayClass::funcComingUpTitle(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_title + 1) }; // +1 since first song in play list is currently playing song
  if (song != nullptr)
  {
    s->var_str = &song->title;
    StatusDisplayClass::coming_up_song_title++; // next time the variable is used it should return the coming up song title after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpArtist(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_artist + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->artist;
    StatusDisplayClass::coming_up_song_artist++; // next time the variable is used it should return the coming up song artist after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpAlbum(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_album + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->album;
    StatusDisplayClass::coming_up_song_album++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_album_artist + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->albumArtist;
    StatusDisplayClass::coming_up_song_album_artist++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_track_number + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->trackNumberStr;
    StatusDisplayClass::coming_up_song_track_number++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpYear(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_year + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->year;
    StatusDisplayClass::coming_up_song_year++; // next time the variable is used it should return the coming up song year after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpGenre(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_genre + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->genre;
    StatusDisplayClass::coming_up_song_genre++; // next time the variable is used it should return the coming up song year after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpPublisher(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_publisher + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->publisher;
    StatusDisplayClass::coming_up_song_publisher++; // next time the variable is used it should return the coming up song publisher after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpISRC(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_isrc + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->isrc;
    StatusDisplayClass::coming_up_song_isrc++; // next time the variable is used it should return the coming up song ISRC after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpCustomTag(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_custom_tag + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->custom_tag;
    StatusDisplayClass::coming_up_song_custom_tag++; // next time the variable is used it should return the coming up song ISRC after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpLength(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_length + 1) };
  if (song != nullptr)
  {
    if (song->length)
    {
      s->coming_up_song_length_str = s->StrMS(song->length);
    }
    else
    {
      s->coming_up_song_length_str = invalidTimeMS;
    }
    s->var_str = &s->coming_up_song_length_str;
    StatusDisplayClass::coming_up_song_length++; // next time the variable is used it should return the coming up song title after this one
  }
  return false;
}

bool StatusDisplayClass::funcLastPlayedTitle(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->title;
  return false;
}

bool StatusDisplayClass::funcLastPlayedArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->artist;
  return false;
}

bool StatusDisplayClass::funcLastPlayedAlbum(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->album;
  return false;
}

bool StatusDisplayClass::funcLastPlayedAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->albumArtist;
  return false;
}

bool StatusDisplayClass::funcLastPlayedTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->trackNumberStr;
  return false;
}

bool StatusDisplayClass::funcLastPlayedYear(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->year;
  return false;
}

bool StatusDisplayClass::funcLastPlayedGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->genre;
  return false;
}

bool StatusDisplayClass::funcLastPlayedPublisher(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->publisher;
  return false;
}

bool StatusDisplayClass::funcLastPlayedISRC(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->isrc;
  return false;
}

bool StatusDisplayClass::funcLastPlayedCustomTag(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->custom_tag;
  return false;
}

bool StatusDisplayClass::funcLastPlayedlength(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played_length_str;
  return false;
}

bool StatusDisplayClass::funcCredits(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.credits_str;
  return false;
}

bool StatusDisplayClass::funcAutoGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &Config->general->auto_genre.at(Config->auto_genre_select);
  return false;
}

bool StatusDisplayClass::funcPlaysPerCoin(StatusDisplayClass *s, unsigned char param)
{
  uint32_t coin { static_cast<uint32_t>(param) };
  s->var_str = &Config->general->plays_per_coin_str.at(coin);
  return false;
}

bool StatusDisplayClass::funcVolume(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.volume_str;
  return false;
}

bool StatusDisplayClass::funcSelectCode(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.select_code_str;
  return false;
}

bool StatusDisplayClass::funcNumSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_songs_str;
  return false;
}

bool StatusDisplayClass::funcNumPages(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_pages_str;
  return false;
}

bool StatusDisplayClass::funcFirstVisiblePage(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.first_visible_page_str;
  return false;
}

bool StatusDisplayClass::funcLastVisiblePage(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_visible_page_str;
  return false;
}

bool StatusDisplayClass::funcGPIOSetPinHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t pin { static_cast<uint32_t>(param) };

  // we check if it is unused to prevent setting as an output if it is being used as button input
  // if not, we set the direction to output for subsequent calls...
  if (Config->general->gpio.at(pin) == gpio_e::Unused)
  {
    Gpio->ConfigurePinAsOutput(pin);
  }

  if (Config->general->gpio.at(pin) == gpio_e::Output)
  {
    Gpio->SetPin(pin);
  }

  return false;
}

bool StatusDisplayClass::funcGPIOSetPinLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t pin { static_cast<uint32_t>(param) };

  // we check if it is unused to prevent setting as an output if it is being used as button input
  // if not, we set the direction to output for subsequent calls...
  if (Config->general->gpio.at(pin) == gpio_e::Unused)
  {
    Gpio->ConfigurePinAsOutput(pin);
  }

  if (Config->general->gpio.at(pin) == gpio_e::Output)
  {
    Gpio->ClrPin(pin);
  }

  return false;
}

bool StatusDisplayClass::funcSetFlagLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };

  if (Config->status_flag.at(flag)) Engine->next_status_event |= StatusEvent_flagChange;

  Config->status_flag.at(flag) = false;

  return false;
}

bool StatusDisplayClass::funcSetFlagHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };

  if (Config->status_flag.at(flag) == false) Engine->next_status_event |= StatusEvent_flagChange;

  Config->status_flag.at(flag) = true;

  return false;
}

bool StatusDisplayClass::funcDrawBitmap(StatusDisplayClass *s, unsigned char param)
{
  if (s->bitmap_name.size())
  // bitmap directory specified and has bitmaps in it, so use these instead
  {
    s->draw_bitmap = true;
    if (++s->bitmap_idx == s->bitmap_name.size()) s->bitmap_idx = 0; // move to next bitmap
    return false;
  }

  if (s->bitmap_list.size())
  {
    s->draw_bitmap = true;
    if (++s->bitmap_idx == s->bitmap_list.size()) s->bitmap_idx = 0; // move to next bitmap
  }
  return false;
}

bool StatusDisplayClass::funcDrawRandomBitmap(StatusDisplayClass *s, unsigned char param)
{
  if (s->bitmap_name.size())
  {
    size_t size { s->bitmap_name.size() };
    if (size)
    {
      s->draw_bitmap = true;
      s->bitmap_idx = rand() % size;
    }
    return false;
  }

  size_t size { s->bitmap_list.size() };
  if (size)
  {
    s->draw_bitmap = true;
    s->bitmap_idx = rand() % size;
  }
  return false;
}

bool StatusDisplayClass::funcUndrawBitmap(StatusDisplayClass *s, unsigned char param)
{
  s->draw_bitmap = false;
  return false;
}

bool StatusDisplayClass::funcDrawVideo(StatusDisplayClass *s, unsigned char param)
{
  s->draw_video = true;
  return false;
}

bool StatusDisplayClass::funcUndrawVideo(StatusDisplayClass *s, unsigned char param)
{
  s->draw_video = false;
  return false;
}

bool StatusDisplayClass::funcStartVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle == nullptr)
  {
    s->video.handle = al_open_video(s->video.filename.c_str());
    if (s->video.handle)
    {
      al_start_video(s->video.handle, al_get_default_mixer());
      s->video.playing = true;
    }
  }
  return false;
}

bool StatusDisplayClass::funcStopVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, false);
    s->video.playing = false;
    al_close_video(s->video.handle);
    s->video.handle = nullptr;
  }
  return false;
}

bool StatusDisplayClass::funcPauseVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, false);
  }
  return false;
}

bool StatusDisplayClass::funcUnPauseVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, true);
  }
  return false;
}

bool StatusDisplayClass::funcStopTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_enable = false;
  return false;
}

bool StatusDisplayClass::funcStartTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_enable = true;
  return false;
}

bool StatusDisplayClass::funcResetTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_count = 0;
  return false;
}

bool StatusDisplayClass::funcIfFreeplay(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->general->free_play)
  { // if not free play then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotFreeplay(StatusDisplayClass *s, unsigned char param)
{
  if (Config->general->free_play)
  { // if in free play then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNoCredits(StatusDisplayClass *s, unsigned char param)
{
  if (status.credits)
  { // if credits left then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfAnyCredits(StatusDisplayClass *s, unsigned char param)
{
  if (status.credits == 0)
  { // if no credits left then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::playing)
  { // if no song currently playing then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  // if ((Audio->song_play_state == song_play_state_e::playing) || PlayQueue->NumSongsTotal())
  if ((Audio->song_play_state == song_play_state_e::playing))
  { // if song currently playing (or one about to) then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfVideoSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (status.now_playing->type != song_type_e::ogv)
  { // if song currently playing isn't video then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotVideoSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (status.now_playing->type == song_type_e::ogv)
  { // if song currently playing is video then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfRadioSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (status.now_playing->type != song_type_e::url)
  { // if song currently playing isn't from a url link then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotRadioSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (status.now_playing->type == song_type_e::url)
  { // if song currently playing is from a url link then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongLoading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::loading)
  { // if no song currently loading then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongLoading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state == song_play_state_e::loading)
  { // if song currently loading then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongUnloading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::unloading)
  { // if no song currently unloading then don't print rest of line...
    s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongUnloading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state == song_play_state_e::unloading)
  { // if no song currently loading then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfAnyComingUp(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->NumSongsComingUp())
  { // if no songs coming up then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNoneComingUp(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->NumSongsComingUp())
  { // if songs coming up then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongComingUp(StatusDisplayClass *s, unsigned char param)
{
  bool ret { false };
  if ((PlayQueue->NumSongsComingUp()) <= StatusDisplayClass::if_song_coming_ups)
  { // if no songs (left to display) coming up then don't print rest of line...
    ret = s->SkipToEndIf();
  }
  StatusDisplayClass::if_song_coming_ups++;
  return ret;
}

bool StatusDisplayClass::funcIfAutoPlayMode(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->general->auto_play)
  { // if not in random play (auto play mode) then...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotAutoPlayMode(StatusDisplayClass *s, unsigned char param)
{
  if (Config->general->auto_play )
  { // if in random play (auto play mode) then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfLoopMode(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->general->loop_playlist)
  { // if not in loop mode then...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotLoopMode(StatusDisplayClass *s, unsigned char param)
{
  if (Config->general->loop_playlist)
  { // if loop mode then don't print rest of line...
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerHi(StatusDisplayClass *s, unsigned char param)
{
  if (!s->timer_hi)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerLo(StatusDisplayClass *s, unsigned char param)
{
  if (s->timer_hi)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerTick(StatusDisplayClass *s, unsigned char param)
{
  if (!s->timer_tick)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPageMoving(StatusDisplayClass *s, unsigned char param)
{
  if (status.pages_idle)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPageNotMoving(StatusDisplayClass *s, unsigned char param)
{
  if (!status.pages_idle)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPlayQueueEmpty(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->empty)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPlayQueueEmpty(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->empty)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPlayQueueFull(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->full)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPlayQueueFull(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->full)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfStereo(StatusDisplayClass *s, unsigned char param)
{
  if (!Audio->stereo)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotStereo(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->stereo)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPaused(StatusDisplayClass *s, unsigned char param)
{
  if (!Audio->paused)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPaused(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->paused)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfInvalidChoice(StatusDisplayClass *s, unsigned char param)
{
  if (!Engine->invalid_choice)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotInvalidChoice(StatusDisplayClass *s, unsigned char param)
{
  if (Engine->invalid_choice)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfDuplicateChoice(StatusDisplayClass *s, unsigned char param)
{
  if (!Engine->duplicate_choice)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotDuplicateChoice(StatusDisplayClass *s, unsigned char param)
{
  if (Engine->duplicate_choice)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfFlagHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };

  if (Config->status_flag.at(flag) == false)
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfFlagLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };
  if (Config->status_flag.at(flag))
  {
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfMute(StatusDisplayClass *s, unsigned char param)
{
  if (!Engine->mute)
  { // if not mute then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotMute(StatusDisplayClass *s, unsigned char param)
{
  if (Engine->mute)
  { // if mute then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfButtonPressed(StatusDisplayClass *s, unsigned char param)
{
  uint64_t button = (1 << static_cast<uint64_t>(param));
  if (param == BUTTON_ANY)
  // make the button we're looking for the same as the actual button pressed...
  {
    button = Engine->button_pressed_mask;
  }
  if (!(Engine->button_pressed_mask & button))
  { // if button not pressed then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotButtonPressed(StatusDisplayClass *s, unsigned char param)
{
  uint64_t button = (1 << static_cast<uint64_t>(param));
  if (param == BUTTON_ANY)
  // make the button we're looking for the same as the actual button pressed...
  {
    button = Engine->button_pressed_mask;
  }
  if (Engine->button_pressed_mask & button)
  { // if button pressed then we skip the text section (to $END_IF or end of line)
    return s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcEndIf(StatusDisplayClass *s, unsigned char param)
{
  return false;
}

bool StatusDisplayClass::funcNoDraw(StatusDisplayClass *s, unsigned char param)
{
  s->no_draw = true;
  return false;
}


///////////////////////////////////////////////////////////////////////////////

int StatusDisplayClass::BitmapSearch
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

    bool found { };
    // extract file extension and convert to lower case...
    string file_ext { p.substr( p.length() - 4 ) };
    transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

    if (file_ext == ".bmp") found = true;
    if (file_ext == ".jpg") found = true;
    if (file_ext == ".png") found = true;

    if (found)
    {
      StatusDisplayClass::static_bitmap_name.push_back(p);
    }
  }

  return 0;
}

void StatusDisplayClass::init(const uints2_t sze, const uint32_t emsk)
/*
  read the text file and replace any $VAR keyword strings with a 3-character
  shortcut code for last lookup later (STATUS_VAR_START, code, code_param).
  Also set apprpriate bits in the event_mask
  depending upon which $VAR keywords are found.  Store each modified line from the text
  file into the internal "lines" vector array, for use by the real-time update function
*/
{
  ifstream inFile;
  string line;
  if (bitmap_directory.size())
  {
    // ftw bitmap_directory and save each image filename in the bitmap_name vector...
    // we have to push into the staticbitmap_name vector, then copy this vector to our bitmap_name
    // vector unique to this status object instance...
    ftw(bitmap_directory.c_str(), BitmapSearch, 16);
  }

  StatusDisplayClass::static_bitmap_name.shrink_to_fit();
  bitmap_name = StatusDisplayClass::static_bitmap_name;
  StatusDisplayClass::static_bitmap_name.clear();

  if (desc_name.size() == 0)
  {
    event_mask = 0;
    return;
  }

  if (text.max_width == 0) text.max_width = size.x;

  inFile.open(desc_name, ios::in);
  if (!inFile.is_open())
  {
    error("Couldn't open status file '%s' for input", desc_name.c_str());
  }

  // replace any status variables ($...) with their 2-character code...
  while (getline(inFile, line))
  {
    line.erase(std::remove(line.begin(), line.end(), 13), line.end()); // remove CR (for non-linux text file)
    line.erase(std::remove(line.begin(), line.end(), 10), line.end()); // remove LF (for non-linux text file)
    for (auto &s : status_vars)
    {
      string c { static_cast<char>(STATUS_VAR_START) };
      c += static_cast<char>(s.code);
      c += static_cast<char>(s.code_param);
      size_t pos;
      while ((pos = line.find(s.name)) != string::npos)
      {
        line.replace(pos, s.name.length(), c);
        event_mask |= s.event_bit;
        if ((s.code >= STATUS_VAR_SET_GPIO_00_HI) && (s.code <= STATUS_VAR_SET_GPIO_27_LO))
        {
          Gpio->ConfigurePinAsOutput((s.code - STATUS_VAR_SET_GPIO_00_HI) / 2);
        }
      }
    }
    lines.push_back(line);
  }

  inFile.close();

  DisplayBaseClass::init(size, event_mask); // use size picked up from config file, and event_mask derived here in init()
  update(StatusEvent_init);
  event_mask &= ~StatusEvent_initEmpty; // no longer need the init event mask bit
}

bool StatusDisplayClass::SkipToEndIf(void)
/*
  skip to the position in the line where the enclosing $END_IF is from the start point
  Returns true if the end of the line is reached, otherwise it returns false and updates
  the position in the line after the $END_IF corresponding to the start point (it will ignore
  earlier $END_IFs if it sees any $IF vars within the search)
*/
{
  uint32_t end_level { 1 };
  do
  { // jump to the next $END_IF or end of line
    if (line_pos == line->size()) return true; // end of line
    uint8_t c1 = static_cast<uint8_t>(line->at(line_pos++));
    if (c1 == STATUS_VAR_START) // start of VAR code sequence
    {
      c1 = static_cast<uint8_t>(line->at(line_pos++)); // VAR code
      line_pos++; // skip second control character (code_param)
      if (c1 != STATUS_VAR_END_IF)
      { // if not an $END_IF then we increase the nested end_if level
        if (status_vars.at(c1 - STATUS_VAR_OFFSET).is_if) end_level++;
      }
      else
      { // it is an $END_IF, but we only terminate if it corresponds to our level (0)
        end_level--;
        if (end_level == 0) break;
      }
    }
    if (line_pos == line->size()) return true; // end of line
  } while (1);
  return false;
}

void StatusDisplayClass::update
/*
  Parse each line in the lines array...normal characters get printed
  out, but embedded $VAR characters get their associated function called
  to do their specific task...
*/
(
  const uint32_t event
)
{

  if (!(event_mask && (event & event_mask))) return; // don't do anything if no incoming events match any of status box's events

  ALLEGRO_BITMAP *bm {};
  uint32_t y { };
  bool status_file_output { false };
  ofstream outFile;

  // Display->redraw = true;

  al_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  no_draw = false;

  if (event & StatusEvent_timerChange)
  {
    timer_tick = false;
    if (timer_enable)
    {
      if (++timer_count == timer_tick_period)
      {
        timer_tick = true;
        timer_count = 0;
        timer_hi = 1 - timer_hi;
        if (timer_oneshot)
        {
          timer_enable = false;
        }
      }
    }
  }

  if (output_filename.size())
  {
    outFile.open(output_filename, ios::out | ios::trunc);
    if (outFile.is_open())
    {
      status_file_output = true;
    }
    // else
    // {
      // log_file << WARNING << "Couldn't open file '" << output_filename << "' for output" << endl;
    // }
  }

  for (auto & l: lines)
  { // each status line...
    bool line_done { false };
    string dst {};
    line = &l;
    line_pos = 0;

    dst.reserve(256);

    while (line_done == false)
    { // search control codes...
      if (line_pos == line->size()) break;
      if (static_cast<uint8_t>(line->at(line_pos)) == STATUS_VAR_START)
      { // VAR control code
        var_str = nullptr;
        line_pos++;
        uint8_t var_code = static_cast<uint8_t>(line->at(line_pos++));
        uint8_t var_code_param = static_cast<uint8_t>(line->at(line_pos++));

        const status_vars_t *var { &status_vars.at(static_cast<uint32_t>(var_code - STATUS_VAR_OFFSET)) };

        var->func(this, var_code_param);

        if (var_str != nullptr)
        {
          dst += *var_str;
        }
      }
      else
      { // normal character
        dst += line->at(line_pos);
        if (++line_pos == line->size()) line_done = true;
      }
    }

    Display->DrawText(bitmap, text, 0, y, dst);

    if (status_file_output)
    {
      outFile << dst << endl;
    }

    if(text.font_number < Config->fonts.size())
    {
      y += Config->fonts.at(text.font_number)->font.size + line_spacing;
    }
  }

  if (artwork_bitmap.handle)
  {
    al_draw_scaled_bitmap(artwork_bitmap.handle, 0, 0, al_get_bitmap_width(artwork_bitmap.handle), al_get_bitmap_height(artwork_bitmap.handle), 0, 0, size.x, size.y, 0);
  }

  if (draw_bitmap)
  {
    if (bitmap_name.size())
    // bitmap directory specified and has bitmaps in it, so use these instead
    {
      if (bm) al_destroy_bitmap(bm);
      bm = al_load_bitmap(bitmap_name.at(bitmap_idx).c_str());
      if (bm)
      {
        al_draw_scaled_bitmap(bm, 0, 0, al_get_bitmap_width(bm), al_get_bitmap_height(bm), 0, 0, size.x, size.y, 0);
      }
    }
    else
    {
      bm = bitmap_list.at(bitmap_idx);
      if (bm)
      {
        al_draw_scaled_bitmap(bm, 0, 0, al_get_bitmap_width(bm), al_get_bitmap_height(bm), 0, 0, size.x, size.y, 0);
      }
    }
  }

  if (draw_video)
  {

    video_t *status_video;
    bool loop {};

    // If a Video has been defined in the status object, then use it, otherwise use the song video...

    if (video.filename.size())
    {
      status_video = &video;
      loop = loop_video;
    }
    else
    {
      status_video = &Engine->song_video;
    }

    if (loop)
    {
      if (al_is_video_playing(status_video->handle) == false) // restart (loop) video
      {
        al_seek_video(status_video->handle, 0);
        al_set_video_playing(status_video->handle, true);
      }
    }

    if (status_video->playing)
    {
      if (status_video->handle != nullptr)
      {
        status_video->bm_handle = al_get_video_frame(status_video->handle);
        if (status_video->bm_handle != nullptr)
        {
          al_draw_scaled_bitmap(status_video->bm_handle, 0, 0, al_get_bitmap_width(status_video->bm_handle), al_get_bitmap_height(status_video->bm_handle), 0, 0, size.x, size.y, 0);
        }
      }
    }
  }

  if (status_file_output)
  {
    outFile.close();
  }

}
