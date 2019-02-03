#include "fruitbox.hpp"
#include "fruitbox_logo.hpp"
#include "info_bkgnd.hpp"
#include "info_font.hpp"
#include "chooser_arrow.hpp"

using namespace std;

constexpr int32_t SpinOffsetX   { -16 * 512 / 800 }; /*  svg centre offset * png width / svg width  */
constexpr int32_t SpinOffsetY   { -70 * 512 / 800 }; /*  svg centre offset * png height / svg height */

DisplayClass::DisplayClass(void)
{
  cout << "Detecting display...";
  if (al_get_display_mode(0, &display_size) == nullptr) error("Failed to get display mode");
  cout << display_size.width << " x " << display_size.height << " (" << display_size.refresh_rate << "Hz)" << endl;

  display = al_create_display(display_size.width, display_size.height);
  if (display == nullptr) error("Failed to create %d x %d display", display_size.width, display_size.height);

  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);// | ALLEGRO_MIPMAP);

  ALLEGRO_FILE *fruitbox_logo_f { al_open_memfile(fruitbox_logo_data, FRUITBOX_LOGO_LEN, "rb") };
  if (fruitbox_logo_f == nullptr) error( "Failed to load fruitbox logo mem file");
  fruitbox_logo_bm = al_load_bitmap_f(fruitbox_logo_f, ".png");
  if (fruitbox_logo_bm == nullptr) error( "Failed to load embedded logo");
  al_fclose(fruitbox_logo_f);

  ALLEGRO_FILE *info_bkgnd_f { al_open_memfile(info_bkgnd_data, INFO_BKGND_LEN, "rb") };
  if (info_bkgnd_f == nullptr) error( "Failed to load info bkgnd mem file");
  info_bkgnd_bm = al_load_bitmap_f(info_bkgnd_f, ".png");
  if (info_bkgnd_bm == nullptr) error( "Failed to load info background");
  al_fclose(info_bkgnd_f);

  ALLEGRO_FILE *chooser_arrow_f { al_open_memfile(chooser_arrow_data, CHOOSER_ARROW_LEN, "rb") };
  if (chooser_arrow_f == nullptr) error( "Failed to load chooser arrow mem file");
  chooser_arrow_bm = al_load_bitmap_f(chooser_arrow_f, ".png");
  if (chooser_arrow_bm == nullptr) error( "Failed to load chooser arrow");
  al_fclose(chooser_arrow_f);

  // position info box in bottom centre of screen...
  info_box_pos.x = (display_size.width - InfoBoxWidth) / 2;
  info_box_pos.y = (display_size.height - InfoBoxHeight);

  info_font_f = al_open_memfile(info_font_data, INFO_FONT_LEN, "rb");
  if (info_font_f == nullptr) error( "Failed to load info font file");
  info_font = al_load_ttf_font_f(info_font_f, nullptr, -InfoBoxTextHeight, 0);
  if (info_font == nullptr) error( "Failed to load info font");

  SetText(info_title_text  , -1, 0,0,0,0xff,   ALLEGRO_ALIGN_CENTRE, false,  true, false, -6, 44, 540);
  SetText(info_status1_text, -1, 200,0,0,0xff, ALLEGRO_ALIGN_CENTRE, false, true, false,  -6, (InfoBoxHeight / 3) + 18, 470);
  SetText(info_status2_text, -1, 0,0,0,0xff,   ALLEGRO_ALIGN_CENTRE, false,  true, false, -6, (2 * (InfoBoxHeight / 3)) - 7, 540);

  splash_state.bk = al_map_rgb(255, 255, 255);
  splash_state.dw = display_size.width;
  splash_state.dh = display_size.height;
  splash_state.lw = al_get_bitmap_width(fruitbox_logo_bm);
  splash_state.lh = al_get_bitmap_width(fruitbox_logo_bm);
  splash_state.s = splash_state.dw > splash_state.dh ? splash_state.dh : splash_state.dw;
  splash_state.w = splash_state.s / (2.0 * static_cast<float>(splash_state.lw)); /* make logo roughly half the smallest screen dimension */
  splash_state.h = splash_state.s / (2.0 * static_cast<float>(splash_state.lw)); /* make logo roughly half the smallest screen dimension */
}

DisplayClass::~DisplayClass()
{
  // if (chooser_font)
  // {
    // al_destroy_font(chooser_font);
    // al_fclose(chooser_font_f);
  // }
  al_destroy_font(info_font);
  al_fclose(info_font_f);
  al_destroy_bitmap(chooser_arrow_bm);
  al_destroy_bitmap(info_bkgnd_bm);
  al_destroy_bitmap(fruitbox_logo_bm);
  al_destroy_bitmap(jukebox);
  al_destroy_display(display);
}

void DisplayClass::SetText
(
  text_t &text, 
  const int32_t font_number,
  const uint32_t colour_r,
  const uint32_t colour_g,
  const uint32_t colour_b,
  const uint32_t colour_a,
  const int32_t alignment,
  const bool capitalise,
  const bool condense,
  const bool quoted,
  const int32_t offset_x,
  const int32_t offset_y,
  const uint32_t max_width
)
{
  text.font_number = font_number;
  text.colour.r = colour_r;
  text.colour.g = colour_g;
  text.colour.b = colour_b;
  text.colour.a = colour_a;
  text.alignment = alignment;
  text.capitalise = capitalise;
  text.condense = condense;
  text.quoted = quoted;
  text.offset.x = offset_x;
  text.offset.y = offset_y;
  text.max_width = max_width;
}
  
void DisplayClass::CapitaliseAndQuote
(
  string     &str,
  const bool cap_en,
  const bool quo_en
)
{
  if (cap_en) transform(str.begin(), str.end(),str.begin(), ::toupper);
  if (quo_en) str = "\"" + str + "\"";
}

void DisplayClass::DrawText
(
  ALLEGRO_BITMAP *bitmap,
  const text_t   &text,
  const int32_t  x,
  const int32_t  y,
  const string   &str
)
{
  if (!str.size()) return;
  if ((text.font_number != -1) && text.font_number >= Config->fonts.size()) return;
  string s { str };
  int32_t tx, ty;
  int32_t bm_w { al_get_bitmap_width(bitmap) };
  int32_t bm_h { al_get_bitmap_height(bitmap) };
  int32_t alignment = text.alignment;
  ALLEGRO_COLOR colour = al_map_rgba(text.colour.r, text.colour.g, text.colour.b, text.colour.a);
  ALLEGRO_FONT *font = (text.font_number == -1) ? info_font : Config->fonts.at(text.font_number)->font.handle;
  if (font == nullptr) return; // font not defined
  CapitaliseAndQuote(s, text.capitalise, text.quoted);
  uint32_t text_width = al_get_text_width(font, s.c_str());
  if ((text_width < text.max_width) || !text.condense)
  { // text fits within width of bitmap or squash not wanted
    int32_t tc { static_cast<uint32_t>(ALLEGRO_ALIGN_LEFT) };

    if (alignment == ALLEGRO_ALIGN_CENTRE) tc = bm_w / 2;
    if (alignment == ALLEGRO_ALIGN_RIGHT) tc = bm_w;
    tx = tc + x + text.offset.x;
    ty = y + text.offset.y;
    if (tx > bm_w) return; // don't bother drawing text out of region
    if (ty > bm_h) return; // don't bother drawing text out of region
    al_draw_text(font, colour, tx, ty, alignment, s.c_str());
  }
  else
  { // text too wide, so draw to wider bitmap and scale it to fit into target bitmap...
    uint32_t sw { text_width };
    int32_t sh { (text.font_number == -1) ? InfoBoxTextHeight : Config->fonts.at(text.font_number)->font.size };
    int32_t tc { };

    if (alignment == ALLEGRO_ALIGN_CENTRE) tc = (bm_w - text.max_width) / 2;
    if (alignment == ALLEGRO_ALIGN_RIGHT) tc = (bm_w - text.max_width);
    tx = x + text.offset.x;
    ty = y + text.offset.y;
    if (tx > bm_w) return; // don't bother drawing text out of region
    if (ty > bm_h) return; // don't bother drawing text out of region

    ALLEGRO_BITMAP *squashed_text_bm = al_create_bitmap(sw, sh);
    if (squashed_text_bm)
    {
      al_set_target_bitmap(squashed_text_bm);
      al_clear_to_color(al_map_rgba(0,0,0,0));
      al_draw_text(font, colour, 0.0, 0.0, ALLEGRO_ALIGN_LEFT, s.c_str());
      al_set_target_bitmap(bitmap);
      al_draw_scaled_bitmap(squashed_text_bm, 0.0, 0.0, sw, sh, tx + tc, ty, text.max_width, sh, 0);
      al_destroy_bitmap(squashed_text_bm);
    }
  }
}

void DisplayClass::DrawJukebox
(
  const bool flip_display
)
{
  // draw jukebox to jukebox bitmap...
  al_set_target_bitmap(jukebox);
  al_clear_to_color(al_map_rgb(0,0,0));
// static uint32_t draw_cnt {};
// cout << "draw " << draw_cnt++ << endl;
  for (auto &i : Config->display_object) i->draw();

  // now copy jukebox bitmap to display backbuffer (which will scale it...)

  al_set_target_bitmap(al_get_backbuffer(display));
  if (Config->no_scale)
  {
    double dx {(static_cast<double>(display_size.width) - static_cast<double>(al_get_bitmap_width(jukebox))) / 2.0};
    double dy {(static_cast<double>(display_size.height) - static_cast<double>(al_get_bitmap_height(jukebox))) / 2.0};
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(jukebox,  dx, dy, 0);
  }
  else
  {
    al_draw_scaled_bitmap(jukebox, 0, 0, al_get_bitmap_width(jukebox), al_get_bitmap_height(jukebox), 0, 0, display_size.width, display_size.height, 0);
  }
  if (flip_display) al_flip_display();
}

void DisplayClass::DrawChooseMenu
(
  const bool selected
)
{
  uint32_t c {Chooser->current_cfg};

  al_set_target_bitmap(al_get_backbuffer(display));
  al_clear_to_color(al_map_rgb(0,0,0));

  if (choose_arrow_pos_inc)
  {
    if (++choose_arrow_pos == 40)
    {
      choose_arrow_pos_inc = false;
    }
  }
  else
  {
    if (--choose_arrow_pos == 0)
    {
      choose_arrow_pos_inc = true;
    }
  }
  
  al_draw_scaled_rotated_bitmap(fruitbox_logo_bm, SpinOffsetX + splash_state.lw/2, SpinOffsetY + splash_state.lh/2, splash_state.dw/2, splash_state.dh/2, splash_state.w, splash_state.h, splash_state.ang, 0);

  if (selected)
  {
    DrawInfoBox("Loading...Let's Rock!", Chooser->name.at(c), Chooser->desc.at(c), Chooser->screenshot_bm, false, true);
  }
  else
  {
    DrawInfoBox(Chooser->help_text, Chooser->name.at(c), Chooser->desc.at(c), Chooser->screenshot_bm, true, true);
  }
}

void DisplayClass::DrawTouchTarget
(
  uint32_t x,
  uint32_t y
)
{
  al_set_target_bitmap(al_get_backbuffer(display));
  al_draw_line(x,      y - 48, x,      y + 48, al_map_rgb(0, 0, 0), 8);
  al_draw_line(x - 48, y,      x + 48, y,      al_map_rgb(0, 0, 0), 8);
  al_draw_circle(x,y, 32, al_map_rgb(0,0,0), 8);
}

void DisplayClass::DrawInfoBox
// draw info box with no arrows, default background, and flip display after draw...
(
  const string &title,
  const string &info1,
  const string &info2
)
{
  DrawInfoBox(title, info1, info2, nullptr, false, true);
}

void DisplayClass::DrawInfoBox
// info box with specified background and arrows...
(
  const string &title,
  const string &info1,
  const string &info2,
  ALLEGRO_BITMAP *background,
  bool draw_arrows,
  bool flip
)
{
  al_set_target_bitmap(al_get_backbuffer(display));

  if (background)
  {
    al_clear_to_color(al_map_rgb(0,0,0));
    if (Config->no_scale)
    {
      double dx {(static_cast<double>(display_size.width) - static_cast<double>(al_get_bitmap_width(background))) / 2.0};
      double dy {(static_cast<double>(display_size.height) - static_cast<double>(al_get_bitmap_height(background))) / 2.0};
      al_draw_bitmap(background,  dx, dy, 0);
    }
    else
    {
      al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, display_size.width, display_size.height, 0);
    }
  }
  else
  {
    al_clear_to_color(splash_state.bk);
  }

  al_draw_scaled_bitmap(info_bkgnd_bm, 0, 0, al_get_bitmap_width(info_bkgnd_bm), al_get_bitmap_height(info_bkgnd_bm), info_box_pos.x, info_box_pos.y, InfoBoxWidth, InfoBoxHeight, 0);
  DrawText(al_get_backbuffer(display), info_title_text, 0, info_box_pos.y, title);
  DrawText(al_get_backbuffer(display), info_status1_text, 0, info_box_pos.y, info1);
  DrawText(al_get_backbuffer(display), info_status2_text, 0, info_box_pos.y, info2);

  if (draw_arrows)
  {
    al_draw_bitmap(chooser_arrow_bm, static_cast<int32_t>(info_box_pos.x - al_get_bitmap_width(chooser_arrow_bm) + 20 - (choose_arrow_pos / 2)), info_box_pos.y + 32, 0);
    al_draw_bitmap(chooser_arrow_bm, info_box_pos.x + al_get_bitmap_width(info_bkgnd_bm) - 50 + (choose_arrow_pos / 2), info_box_pos.y + 32, ALLEGRO_FLIP_HORIZONTAL);
  }

  al_draw_scaled_rotated_bitmap(fruitbox_logo_bm, SpinOffsetX + splash_state.lw/2, SpinOffsetY + splash_state.lh/2, splash_state.dw/2, splash_state.dh/2, splash_state.w, splash_state.h, splash_state.ang, 0);

  if (flip) al_flip_display();
}

void DisplayClass::LogoSpinUp(void)
{
  al_set_target_bitmap(al_get_backbuffer(display));

  for (size_t fade {200}; fade > 0; --fade)
  {
    float ang_vel { static_cast<float>(fade) / 400 };
    float f { static_cast<float>(fade) / 100 };
    splash_state.ang += ang_vel;
    al_clear_to_color(splash_state.bk);
    splash_state.fcol = al_map_rgba_f(0,0,0, f/2);

    al_draw_scaled_rotated_bitmap(fruitbox_logo_bm, SpinOffsetX + splash_state.lw/2, SpinOffsetY + splash_state.lh/2, splash_state.dw/2, splash_state.dh/2, splash_state.w, splash_state.h, splash_state.ang, 0);
    al_draw_filled_rectangle(0, 0, splash_state.dw, splash_state.dh, splash_state.fcol);
    
    al_draw_text(info_font, al_map_rgb(0,0,0),
      display_size.width - 8, 
      display_size.height - InfoBoxTextHeight - 8, 
      ALLEGRO_ALIGN_RIGHT, FRUITBOX_VERSION);

    al_flip_display();
  }
}

void DisplayClass::JukeboxFadeIn(void)
{
  al_set_target_bitmap(al_get_backbuffer(display));

  for (size_t fade {200}; fade > 0; --fade)
  {
    float f { static_cast<float>(fade)/200 };
    splash_state.fcol = al_map_rgba_f(f, f, f, f);

    for (auto i : Config->display_object)
    {
      i->update(StatusEvent_timerChange);
    }
    DrawJukebox(false);
    al_draw_filled_rectangle(0, 0, splash_state.dw, splash_state.dh, splash_state.fcol);
    al_draw_scaled_rotated_bitmap(fruitbox_logo_bm, SpinOffsetX + splash_state.lw/2, SpinOffsetY + splash_state.lh/2, splash_state.dw/2, splash_state.dh/2, splash_state.w, splash_state.h, splash_state.ang, 0);
    // FB_VER;
    al_flip_display();
  }

}

void DisplayClass::LogoFadeOut(void)
{
  al_set_target_bitmap(al_get_backbuffer(display));

  for (size_t fade {100}; fade > 0; fade-=2)
  {
    float f { static_cast<float>(fade) / 100 };
    splash_state.fcol = al_map_rgba_f(f, f, f, f);

    for (auto i : Config->display_object)
    {
      i->update(StatusEvent_timerChange);
    }

    DrawJukebox(false);
    al_draw_tinted_scaled_rotated_bitmap(fruitbox_logo_bm, splash_state.fcol, SpinOffsetX + splash_state.lw/2, SpinOffsetY + splash_state.lh/2, splash_state.dw/2, splash_state.dh/2, splash_state.w, splash_state.h, splash_state.ang, 0);
    // FB_VER;
    al_flip_display();
  }

}

