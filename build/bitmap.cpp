#include "fruitbox.hpp"

using namespace std;

void BitmapDisplayClass::init
(
  const uints2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(size, emsk, bitmap_name); // use objects size (from reading config file)
  if ((horz_scale == bitmap_scale_e::Volume) || (vert_scale == bitmap_scale_e::Volume))
  {
    event_mask |= StatusEvent_volumeChange;
  }
  if ((horz_scale == bitmap_scale_e::NowPlayingElapsedTime) || (vert_scale == bitmap_scale_e::NowPlayingElapsedTime))
  {
    event_mask |= StatusEvent_oneSecondChange;
  }
}

void BitmapDisplayClass::update
(
  const uint32_t event
)
{
  // if (event_mask && !(event & event_mask)) return; // don't do anything if no incoming events match any of bitmap objects's events
  if ((event_mask & event) == 0) return; // don't do anything if no incoming events match any of bitmap objects's events

  // Display->redraw = true;

  if (event & StatusEvent_volumeChange)
  // change the width and/or height according to the volume - scaled or clipped
  {
    float vol = static_cast<float>(Config->sounds->song_volume) / static_cast<float>(MaxSongVolume - MinSongVolume);
    if (horz_scale == bitmap_scale_e::Volume)
    {
      if (horz_scale_mode == bitmap_scale_mode_e::Scaled)
      {
        h_scale_factor = vol;
      }
      else // clipped
      {
        h_clip = static_cast<uint32_t>(static_cast<float>(size.x) * (1.0 - vol));
      }
    }
    if (vert_scale == bitmap_scale_e::Volume)
    {
      if (vert_scale_mode == bitmap_scale_mode_e::Scaled)
      {
        v_scale_factor = vol;
      }
      else // clipped
      {
        v_clip = static_cast<uint32_t>(static_cast<float>(size.y) * (1.0 - vol));
      }
    }
  }

  if (event & StatusEvent_oneSecondChange)
  // change the width and/or height according to the now playing elapsed time - scaled or clipped
  {
    if (horz_scale == bitmap_scale_e::NowPlayingElapsedTime)
    {
      if (horz_scale_mode == bitmap_scale_mode_e::Scaled)
      {
        h_scale_factor = status.now_playing_time_remaining_scale;
      }
      else // clipped
      {
        h_clip = static_cast<uint32_t>(static_cast<float>(size.x) * (1.0 - status.now_playing_time_remaining_scale));
      }
    }
    if (vert_scale == bitmap_scale_e::NowPlayingElapsedTime)
    {
      if (vert_scale_mode == bitmap_scale_mode_e::Scaled)
      {
        v_scale_factor = status.now_playing_time_remaining_scale;
      }
      else // clipped
      {
        v_clip = static_cast<uint32_t>(static_cast<float>(size.y) * (1.0 - status.now_playing_time_remaining_scale));
      }
    }
  }

}

void BitmapDisplayClass::draw(void) {
  if (bitmap != nullptr) {
    if (reverse_clip)
    {
      if (h_clip || v_clip) al_set_clipping_rectangle(position.x, position.y, size.x - h_clip, size.y - v_clip);
    }
    else
    {
      if (h_clip || v_clip) al_set_clipping_rectangle(position.x + h_clip, position.y + v_clip, size.x, size.y);
    }
    if (angle)
    {
      float ang = static_cast<float>(angle) * (ALLEGRO_PI / 180.0);
      int bw { al_get_bitmap_width(bitmap) };
      int bh { al_get_bitmap_height(bitmap) };
      float cx { static_cast<float>(bw >> 1) };
      float cy { static_cast<float>(bh >> 1) };
      float sx { static_cast<float>(h_scale_factor * size.x) / static_cast<float>(bw) };
      float sy { static_cast<float>(v_scale_factor * size.y) / static_cast<float>(bh) };
      al_draw_scaled_rotated_bitmap(bitmap, cx, cy, position.x + (size.x >> 1), position.y + (size.y >> 1), sx, sy, ang, 0);
    }
    else
    {
      al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), position.x, position.y, h_scale_factor * size.x, v_scale_factor * size.y, 0);
    }
    al_reset_clipping_rectangle();
  }
}


