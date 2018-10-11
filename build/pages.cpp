#include "fruitbox.hpp"
#include "engine.hpp"
#include "pages.hpp"

using namespace std;

uint32_t PageDisplayClass::page_offset { 0 };
uint32_t PageDisplayClass::start_page { 0 };
bool     PageDisplayClass::idle { false };

const animate_t LeftAnimation[num_page_move_effects][animation_pages] =
{
//    ------------------ Current Page -------------------       ------------------- Next Page --------------------
//    ix,  iy,  iw,  ih,  ia,     dx,  dy,  dw,  dh,  da, fd, tl  h      ix,  iy,  iw,  ih,  ia,     dx,  dy,  dw,  dh,  da,  fd, tl h
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}, {{ -1 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}},  // swipe left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}, {{  0 ,  1 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}},  // swipe up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 1, 0, 1}},  // reveal left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 1, 0, 0}},  // reveal up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 , -1 ,  0 , -1 }, 1, 0, 1}, {{  0 ,  0 ,  0 ,  1 ,  0 }, {  0 ,  0 ,  1 ,  0 ,  1 }, 1, 0, 1}},  // squash left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 , -1 , -1 }, 1, 0, 0}, {{  0 ,  0 ,  1 ,  0 ,  0 }, {  0 ,  0 ,  0 ,  1 ,  1 }, 1, 0, 0}},  // squash up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 ,  0 }, 2, 1, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 2, 1, 0}}   // dissolve up
};

const animate_t RightAnimation[num_page_move_effects][animation_pages] =
{
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 0, 1, 1}, {{  1 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 0, 1, 1}},  // swipe right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 0, 1, 0}, {{  0 , -1 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 0, 1, 0}},  // swipe down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 , -1 }, 1, 1, 1}, {{  1 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 1, 1, 1}},  // reveal right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 , -1 }, 1, 1, 0}, {{  0 , -1 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 1, 1, 0}},  // reveal down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 , -1 ,  0 , -1 }, 1, 1, 1}, {{  1 ,  0 ,  0 ,  1 ,  0 }, { -1 ,  0 ,  1 ,  0 ,  1 }, 1, 1, 1}},  // squash right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 , -1 , -1 }, 1, 1, 0}, {{  0 ,  1 ,  1 ,  0 ,  0 }, {  0 , -1 ,  0 ,  1 ,  1 }, 1, 1, 0}},  // squash down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 ,  0 }, 2, 1, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 2, 1, 0}}   // dissolve up
};

void PageDisplayClass::init
(
  const uints2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(sze, emsk);
  for (auto &b : page_bitmap) {
    b = al_create_bitmap(size.x, size.y);
    if (b == nullptr) error("Couldn't create %d x %d page_bitmap", size.x, size.y);
  }
  update(StatusEvent_init);
}

void PageDisplayClass::update
(
  const uint32_t event
)
{
  if (state != page_state_t::idle) PageDisplayClass::idle = false; // common idle for all pages

  switch (state)
  {
    case page_state_t::idle :
      PageDisplayClass::idle = true;
      if (event & StatusEvent_pageMoveLeftInit)
      {
        move_delay_timer = 0;
        animate_direction = animate_direction_e::animate_left;
        state = page_state_t::wait_move_delay;
      }
      if (event & StatusEvent_pageMoveRightInit)
      {
        move_delay_timer = 0;
        animate_direction = animate_direction_e::animate_right;
        state = page_state_t::wait_move_delay;
      }
      break;

    case page_state_t::wait_move_delay :
      if (move_delay_timer++ == move_delay)
      {
        ConstructPage();
        if (Config->general->page_move_style.speed)
        {
          animation_steps = animateInit(Config->general->page_move_style.effect);
          state = page_state_t::moving;
        }
        else
        { // zero speed is instant redraw
          // Display->redraw = true;
          al_set_target_bitmap(bitmap);
          al_draw_bitmap(page_bitmap.at(1 - page_toggle), 0, 0, 0);
          state = page_state_t::idle;
        }
      }
      break;

    case page_state_t::moving :
      // Display->redraw = true;
      if (animatePage() == false)
      { // finished moving, so draw visible page at final place
        al_clear_to_color(al_map_rgba(0,0,0,0));
        al_draw_bitmap(page_bitmap.at(1 - page_toggle), 0, 0, 0);
        state = page_state_t::idle;
      }
      break;

    case page_state_t::init :
      ConstructPage();
      // Display->redraw = true;
      al_set_target_bitmap(bitmap);
      al_draw_bitmap(page_bitmap.at(1 - page_toggle), 0, 0, 0);
      state = page_state_t::idle;
      break;
  }
  page_offset++;
}

void PageDisplayClass::ConstructDescription(const vector<pair<title_desc_e, string>> &var, string &desc, const song_t *song, const song_t *paired_song)
{
  for (auto &s : var)
  {
    switch (s.first)
    {
      case title_desc_e::SongTitle :
        if (song) desc.append(song->title);
        break;
      case title_desc_e::Artist :
        if (song) desc.append(song->artist);
        break;
      case title_desc_e::AlbumTitle :
        if (song) desc.append(song->album);
        break;
      case title_desc_e::AlbumArtist :
        if (song) desc.append(song->albumArtist);
        break;
      case title_desc_e::Year :
        if (song) desc.append(song->year);
        break;
      case title_desc_e::Genre :
        if (song) desc.append(song->genre);
        break;
      case title_desc_e::TrackNumber :
        if (song) desc.append(song->trackNumberStr);
        break;
      case title_desc_e::Publisher :
        if (song) desc.append(song->publisher);
        break;
      case title_desc_e::ISRC :
        if (song) desc.append(song->isrc);
        break;
      case title_desc_e::Custom :
        if (song) desc.append(song->custom_tag);
        break;
      case title_desc_e::PairedSongTitle :
        if (paired_song) desc.append(paired_song->title);
        break;
      case title_desc_e::PairedArtist :
        if (paired_song) desc.append(paired_song->artist);
        break;
      case title_desc_e::PairedAlbumTitle :
        if (paired_song) desc.append(paired_song->album);
        break;
      case title_desc_e::PairedAlbumArtist :
        if (paired_song) desc.append(paired_song->albumArtist);
        break;
      case title_desc_e::PairedYear :
        if (paired_song) desc.append(paired_song->year);
        break;
      case title_desc_e::PairedGenre :
        if (paired_song) desc.append(paired_song->genre);
        break;
      case title_desc_e::PairedTrackNumber :
        if (paired_song) desc.append(paired_song->trackNumberStr);
        break;
      case title_desc_e::PairedPublisher :
        if (paired_song) desc.append(paired_song->publisher);
        break;
      case title_desc_e::PairedISRC :
        if (paired_song) desc.append(paired_song->isrc);
        break;
      case title_desc_e::PairedCustom :
        if (paired_song) desc.append(paired_song->custom_tag);
        break;
      default : // String
        desc.append(s.second);
        break;
    }
  }
}

void PageDisplayClass::ConstructSinglesPage(void)
{
  ALLEGRO_BITMAP *page_bm = page_bitmap.at(page_toggle);

  page_toggle = 1 - page_toggle;

  uint32_t pair_songs { static_cast<uint32_t>(Config->general->pair_songs == pair_songs_e::No ? 0 : 1) };
  al_set_target_bitmap(page_bm);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  if (background_bitmap.handle != nullptr)
  {
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(background_bitmap.handle)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(background_bitmap.handle)) };
    al_draw_scaled_bitmap(background_bitmap.handle,  0 ,  0 , sw, sh,  0 ,  0 , size.x, size.y, 0);
  }

  uint32_t sinc { size.y / Config->general->songs_per_page };
  uint32_t yinc { 2 * sinc / (4 - pair_songs) };

  for (uint32_t entry = 0; entry < Config->general->songs_per_page; entry++)
  {
    song_t *song {};
    song_t *paired_song {};
    uint32_t y { entry * sinc };
    uint32_t second_entry { entry + 1 };

    uint32_t page { PageDisplayClass::page_offset + PageDisplayClass::start_page };

    if (page >= Database->number_of_pages) return;

    if (y > size.y) break; // don't bother drawing text off page

    song = Database->GetSong(page, entry);
    if (second_entry < Config->general->songs_per_page) {
      paired_song = Database->GetSong(page, second_entry);
    }

    if (song)
    {
      string desc { };

      // draw "song" line
      ConstructDescription(Config->general->song_description, desc, song, paired_song);
      if (debug_song_nums)
      {
        uint32_t sel_num { entry + (Config->general->songs_per_page * PageDisplayClass::page_offset) };
        desc = "<" + Engine->IntToSel(sel_num) + "> " + desc;
      }
      Display->DrawText(page_bm, Config->general->song_text, 0, y, desc);
      
      // draw "artist" line
      y += yinc;
      desc.clear();
      vector<pair<title_desc_e, string>> *artist_desc { &Config->general->matched_artist_description };

      // if song artists in song pair are the not the same (or second song is missing) we use the artist_description...
      if (paired_song) { // second (paired) song is present...
        if (song->artist != paired_song->artist) // ...but has a different artist to the first
        {
          artist_desc = &Config->general->artist_description;
        }
      }

      ConstructDescription(*artist_desc, desc, song, paired_song);
      Display->DrawText(page_bm, Config->general->artist_text, 0, y, desc);

      if (pair_songs && paired_song)
      { // draw second "song" line (in pair)
        if (++entry < Config->general->songs_per_page)
        {
          y += yinc;
          desc.clear();
          ConstructDescription(Config->general->paired_song_description, desc, song, paired_song);
          if (debug_song_nums)
          {
            uint32_t sel_num { entry + (Config->general->songs_per_page * PageDisplayClass::page_offset) };
            desc = "<" + Engine->IntToSel(sel_num) + "> " + desc;
          }
          Display->DrawText(page_bm, Config->general->paired_song_text, 0, y, desc);
        }
      }
      
      // Draw "extra" line
      y = entry * sinc; // extra text starts from top of song / pair
      desc.clear();
      ConstructDescription(Config->general->extra_description, desc, song, paired_song);
      Display->DrawText(page_bm, Config->general->extra_text, 0, y, desc);
    }
  }
}

void PageDisplayClass::ConstructAlbumsPage(void)
{
  ALLEGRO_BITMAP *page_bm   { page_bitmap.at(page_toggle) };
  bitmap_t *coverart_bitmap { &album_coverart_bitmap.at(page_toggle) };
  uint32_t page { PageDisplayClass::page_offset + PageDisplayClass::start_page };

  page_toggle = 1 - page_toggle;

  al_set_target_bitmap(page_bm);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  // draw background...
  if (background_bitmap.handle != nullptr)
  {
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(background_bitmap.handle)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(background_bitmap.handle)) };
    al_draw_scaled_bitmap(background_bitmap.handle,  0 ,  0 , sw, sh,  0 ,  0 , size.x, size.y, 0);
  }

  if (page >= Database->number_of_pages) return;
  song_t *song { Database->GetSong(page, 0) };

  // draw artwork...
  Audio->LoadAlbumArtwork(song, coverart_bitmap);

  if (coverart_bitmap->handle != nullptr)
  {
    uint32_t sx { Config->general->album_art_size.x };
    uint32_t sy { Config->general->album_art_size.y };
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(coverart_bitmap->handle)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(coverart_bitmap->handle)) };
    uint32_t dx { Config->general->album_art_offset.x };
    uint32_t dy { Config->general->album_art_offset.y };
    if (Config->general->album_art_angle)
    {
      float ang = static_cast<float>(Config->general->album_art_angle) * (ALLEGRO_PI / 180.0);
      float cx { static_cast<float>(sw >> 1) };
      float cy { static_cast<float>(sh >> 1) };
      float ssx { static_cast<float>(sx) / static_cast<float>(sw) };
      float ssy { static_cast<float>(sy) / static_cast<float>(sh) };
      al_draw_scaled_rotated_bitmap(coverart_bitmap->handle, cx, cy, dx+(sx>>1), dy+(sy>>1), ssx, ssy, ang, 0);
    }
    else
    {
      al_draw_scaled_bitmap(coverart_bitmap->handle, 0, 0, sw, sh, dx, dy, sx, sy, 0);
    }
  }

  string desc { };

  // draw "album" line...
  ConstructDescription(Config->general->paired_song_description, desc, song, nullptr);
  if (debug_song_nums)
  {
    uint32_t sel_num { PageDisplayClass::page_offset };
    desc = "<" + Engine->IntToSel(sel_num) + "> " + desc;
  }
  Display->DrawText(page_bm, Config->general->album_text, 0, 0, desc);
  
  // draw "artist" line
  desc.clear();
  ConstructDescription(Config->general->artist_description, desc, song, nullptr);
  Display->DrawText(page_bm, Config->general->artist_text, 0, 0, desc);
  
  // draw album songs...
  uint32_t line_spacing { Config->general->album_song_title_line_spacing};

  if (Config->general->song_text.font_number >= Config->fonts.size()) return; // invalid song title font number

  for (uint32_t entry = 0; entry < Config->general->songs_per_page; entry++)
  {
    uint32_t text_height {static_cast<uint32_t>(Config->fonts.at(Config->general->song_text.font_number)->font.size)};
    uint32_t y { entry * (line_spacing + text_height) };

    if (page >= Database->number_of_pages) return;

    if (y > size.y) break; // don't bother drawing text off page

    song = Database->GetSong(page, entry);
    if (song) // draw song title
    {
      desc.clear();
      ConstructDescription(Config->general->song_description, desc, song, nullptr);
      Display->DrawText(page_bm, Config->general->song_text, 0, y, desc);
    }
  }
  
  // Draw "extra" line
  desc.clear();
  ConstructDescription(Config->general->extra_description, desc, song, nullptr);
  Display->DrawText(page_bm, Config->general->extra_text, 0, 0, desc);
}

void PageDisplayClass::ConstructPage(void)
{
  if (Config->general->page_mode == page_mode_e::Singles)
  {
    ConstructSinglesPage();
  }
  else
  {
    ConstructAlbumsPage();
  }
}


uint32_t PageDisplayClass::animateInit
(
  const uint32_t ani_num
)
{
  int32_t steps;
  const animate_t *ani;
  ani_t *m;
  const animate_t *a;
  uint32_t sizex { Config->general->page_size.x };
  uint32_t sizey { Config->general->page_size.y };
  uint32_t speed { Config->general->page_move_style.speed };

  if (animate_direction == animate_direction_e::animate_left)
  {
    ani = LeftAnimation[ani_num];
  }
  else
  {
    ani = RightAnimation[ani_num];
  }

  Animate[page_toggle]     = &ani[0];
  Animate[1 - page_toggle] = &ani[1];

  if (ani[0].horz)
  {
    steps = sizex / speed;
  }
  else
  {
    steps = sizey / speed;
  }
// cout << steps << " " << size << " " << speed << endl;
  for (uint32_t i = 0; i < animation_pages; ++i)
  {
    m = &move[i];
    a = Animate[i];
    m->x = a->init.x * sizex;
    m->y = a->init.y * sizey;
    m->w = a->init.w * sizex;
    m->h = a->init.h * sizey;
    m->a = a->init.a * 255;

    move_delta[i].x = a->delta.x * speed;
    move_delta[i].y = a->delta.y * speed;
    move_delta[i].w = a->delta.w * speed;
    move_delta[i].h = a->delta.h * speed;
    move_delta[i].a = a->delta.a * 255 / steps;
  }
  return steps;
}

bool PageDisplayClass::animatePage(void)
{
  uint32_t first_page;
  uint32_t last_page;
  uint32_t page_dir;
  ani_t *m, *d;
  animate_t *a;
  uint32_t sizex { Config->general->page_size.x };
  uint32_t sizey { Config->general->page_size.y };

  for (uint32_t i = 0; i < animation_pages; ++i) // change page positions/sizes...
  {
    m = &move[i];
    d = &move_delta[i];

    m->x += d->x;
    m->y += d->y;
    m->w += d->w;
    m->h += d->h;
    m->a += d->a;
  }

  if (page_toggle ^ Animate[0]->top_layer)
  {
    first_page = 0;
    last_page = animation_pages;
    page_dir = 1;
  }
  else
  {
    first_page = animation_pages  -1;
    last_page = first_page - animation_pages;
    page_dir = -1;
  }

  al_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  for (uint32_t page = first_page; page != last_page; page += page_dir) // draw page and its animation pair...
  {
    m = &move[page];
    uint8_t a = static_cast<uint8_t>(m->a);
    ALLEGRO_BITMAP *bm = page_bitmap.at(page);

    if (Animate[page]->fade == 2) // alpha fade
    {
      al_draw_tinted_scaled_bitmap(bm, al_map_rgba(a,a,a,a), 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
    else if ((Animate[page]->fade == 1) && Config->general->page_move_style.fading) // fade to/from black
    {
      al_draw_tinted_scaled_bitmap(bm, al_map_rgb(a,a,a), 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
    else
    {
      al_draw_scaled_bitmap(bm, 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
  }
  animation_steps--;

  return (animation_steps ? true : false);
}


