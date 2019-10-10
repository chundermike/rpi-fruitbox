#pragma once

#include "fruitbox.hpp"

extern void error(const char *fmt, ...);

using namespace std;

constexpr uint32_t maxCfgKeywordWidth                    { 30 };

constexpr char cfgFile_section_start                     { '[' };
constexpr char cfgFile_section_end                       { ']' };
constexpr char cfgFile_comment                           { '#' };
constexpr char cfgFile_keyword_param_separator[]         { "\t :=" };

constexpr char cfgSection_general[]                      { "[general]" };
constexpr char cfgSection_touch_areas[]                  { "[touch areas]" };
constexpr char cfgSection_touch_song[]                   { "[touch song]" };
constexpr char cfgSection_sounds[]                       { "[sounds]" };
constexpr char cfgSection_font[]                         { "[font]" };
constexpr char cfgSection_page[]                         { "[page]" };
constexpr char cfgSection_status[]                       { "[status]" };
constexpr char cfgSection_bitmap[]                       { "[bitmap]" };
constexpr char cfgSection_joystick[]                     { "[joystick]" };

constexpr char cfgKeyword_SkinSize[]                     { "SkinSize" };
constexpr char cfgKeywordDesc_SkinSize[]                 { "Size of the skin (width and height in pixels).\n" \
                                                           "                                    The skin is scaled to match the full screen size of the display" };
constexpr char cfgKeyword_SkinName[]                     { "SkinName" };
constexpr char cfgKeywordDesc_SkinName[]                 { "Name of the skin" };

constexpr char cfgKeyword_SkinDescription[]              { "SkinDescription" };
constexpr char cfgKeywordDesc_SkinDescription[]          { "Description of the skin" };

constexpr char cfgKeyword_Screenshot[]                   { "Screenshot" };
constexpr char cfgKeywordDesc_Screenshot[]               { "Filename of screenshot capture" };

constexpr char cfgKeyword_Database[]                     { "Database" };
constexpr char cfgKeywordDesc_Database[]                 { "File name of Database file" };

constexpr char cfgKeyword_MusicPath[]                    { "MusicPath" };
constexpr char cfgKeywordDesc_MusicPath[]                { "File name of path to mp3 music files.  Can contain sub-directories.\n" \
                                                           "                                    Ignored if the 'Database' file already exists" };

constexpr char cfgKeyword_SortSongsBy[]                  { "SortSongsBy" };
constexpr char cfgKeywordDesc_SortSongsBy[]              { "'Title', 'Artist', 'Album', 'AlbumArtist', 'Year', 'Genre', 'TrackNumber', 'Publisher', 'ISRC', 'Custom', 'Random', 'Unsorted'" };

constexpr char cfgKeyword_NoDuplicates[]                 { "NoDuplicates" };
constexpr char cfgKeywordDesc_NoDuplicates[]             { "Prevent songs being added to the playqueue if they are already in the playqueue" };
                                                       
constexpr char cfgKeyword_DuplicatesUseCredits[]         { "DuplicatesUseCredits" };
constexpr char cfgKeywordDesc_DuplicatesUseCredits[]     { "Determines of a selected song which is already playing or in the queue (duplicate song)\n" \
                                                           "                                    uses up a credit" };

constexpr char cfgKeyword_SelectButtons[]                { "SelectButtons" };
constexpr char cfgKeywordDesc_SelectButtons[]            { "List of characters for the select code for the button presses" };
                                                       
constexpr char cfgKeyword_SelectButtonsSequence[]        { "SelectButtonsSequence" };
constexpr char cfgKeywordDesc_SelectButtonsSequence[]    { "'RowCol', 'ColRow'\n" \
                                                           "                                    Specifies if the first select buttons are cycled before the second\n" \
                                                           "                                    select code buttons (ColRow) or the after the second buttons (RowCol)" };
// constexpr char cfgKeyword_TouchDevice[]                  { "TouchDevice" };
// constexpr char cfgKeywordDesc_TouchDevice[]              { "Name of touch device (defaults to 'FT5406' - the official Raspberry Pi 7\" display)" };

constexpr char cfgKeyword_TouchMin[]                     { "TouchMin" };
constexpr char cfgKeywordDesc_TouchMin[]                 { "x y (the touch co-ordinatesfor top left of touch display)" };

constexpr char cfgKeyword_TouchMax[]                     { "TouchMax" };
constexpr char cfgKeywordDesc_TouchMax[]                 { "x y (the touch co-ordinatesfor bottom right of touch display)" };

// constexpr char cfgKeyword_InputDevice[]                  { "InputDevice" };
// constexpr char cfgKeywordDesc_InputDevice[]              { "Name of an input device.  Can be the full device name or part of the device name\n" \
                                                          // "                                    ('evtest' gives you this information) *Can be defined multiple times" };

constexpr char cfgKeyword_CustomMP3Tag[]                 { "CustomMP3Tag" };
constexpr char cfgKeywordDesc_CustomMP3Tag[]             { "Name of an MP3 ID3v2 tag the user wishes to extract to a song's 'Custom' field (i.e. \"TCON\" is content type)\n" \
                                                          "                                    Note: this is only used during database file *creation*" };

constexpr char cfgKeyword_AutoSelect[]                   { "AutoSelect" };
constexpr char cfgKeywordDesc_AutoSelect[]               { "'No' = ButtonSelect needs to be pressed to select song (after the select code is entered)\n" \
                                                           "                                    'Yes' = song selected immediately select code is entered" };

constexpr char cfgKeyword_PageJump[]                     { "PageJump" };
constexpr char cfgKeywordDesc_PageJump[]                 { "The number of screens of pages moved in one go when 'ButtonLeftJump' or 'ButtonRightJump' is pressed" };

constexpr char cfgKeyword_SelectTimeout[]                { "SelectTimeout" };
constexpr char cfgKeywordDesc_SelectTimeout[]            { "Timeout for select code to return to '--' after not detecting all the selection digits" };

constexpr char cfgKeyword_SelectHoldTimeout[]            { "SelectHoldTimeout" };
constexpr char cfgKeywordDesc_SelectHoldTimeout[]        { "Timeout for select code to return to '--' after song selected" };

constexpr char cfgKeyword_AutoPageTurnTime[]             { "AutoPageTurnTime" };
constexpr char cfgKeywordDesc_AutoPageTurnTime[]         { "Time between pages automatically turning (0 = no automatic page turn)" };

constexpr char cfgKeyword_MaxPlaylistLength[]            { "MaxPlaylistLength" };
constexpr char cfgKeywordDesc_MaxPlaylistLength[]        { "Maximum number of songs which can be stored in the coming up queue" };

constexpr char cfgKeyword_LoopPlaylist[]                 { "LoopPlaylist" };
constexpr char cfgKeywordDesc_LoopPlaylist[]             { "'Yes' = a song is added to the back of the play queue when it has finished playing (credits permitting)" };

constexpr char cfgKeyword_AutoPlay[]                     { "AutoPlay" };
constexpr char cfgKeywordDesc_AutoPlay[]                 { "'Yes' = a random song is played if the play queue is empty and no songs are playing" };

constexpr char cfgKeyword_AutoGenre[]                    { "AutoGenre" };
constexpr char cfgKeywordDesc_AutoGenre[]                { "Name of Genre.  Pressing ButtonAuto will cycle through all AutoGenre definitions (and 'Off'\n" \
                                                           "                                    and 'Any') and only select a random song from that Genre **" };

constexpr char cfgKeyword_AutoPlayGap[]                  { "AutoPlayGap" };
constexpr char cfgKeywordDesc_AutoPlayGap[]              { "The time between a random song being selected and played after the last song has finished playing" };

constexpr char cfgKeyword_PlaysPerCoin1[]                { "PlaysPerCoin1" };
constexpr char cfgKeyword_PlaysPerCoin2[]                { "PlaysPerCoin2" };
constexpr char cfgKeyword_PlaysPerCoin3[]                { "PlaysPerCoin3" };
constexpr char cfgKeyword_PlaysPerCoin4[]                { "PlaysPerCoin4" };
constexpr char cfgKeywordDesc_PlaysPerCoin[]             { "The number of song credits added when a coin is inserted (if all PlaysPerCoin = 0; freeplay mode)" };

constexpr char cfgKeyword_SongsPerPage[]                 { "SongsPerPage" };
constexpr char cfgKeywordDesc_SongsPerPage[]             { "The number of song entries on each song page" };

constexpr char cfgKeyword_PageSize[]                     { "PageSize" };
constexpr char cfgKeywordDesc_PageSize[]                 { "The size (width and height in pixels) of each song page" };

constexpr char cfgKeyword_PageMode[]                     { "PageMode" };
constexpr char cfgKeywordDesc_PageMode[]                 { "'Singles' or 'Albums'." };

constexpr char cfgKeyword_PairSongs[]                    { "PairSongs" };
constexpr char cfgKeywordDesc_PairSongs[]                { "'No' = each song in a page is listed with its artist line\n" \
                                                           "                                    'Yes' = two songs are displayed (above and below) the artist line only if they are by the same artist\n" \
                                                           "                                    'Dual' = two songs are displayed (above and below) the artist line regardless of artist" };

constexpr char cfgKeyword_PageMoveStyle[]                { "PageMoveStyle" };
constexpr char cfgKeywordDesc_PageMoveStyle[]            { "effect speed fading.  See section 'Pages'" };

constexpr char cfgKeyword_SongDescription[]              { "SongDescription" };
constexpr char cfgKeywordDesc_SongDescription[]          { "Defines (part of) the song description for the song entry (first in a pair) in the pages...\n" \
                                                           "                                    'SongTitle', 'Artist', 'AlbumTitle', 'AlbumArtist', 'Year', 'Genre', 'TrackNumber',\n" \
                                                           "                                    'Publisher', 'ISRC', 'Custom', 'PairedSongTitle', 'PairedArtist',\n" \
                                                           "                                    'PairedAlbumTitle', 'PairedAlbumArtist', 'PairedYear', 'PairedGenre',\n" \
                                                           "                                    'PairedTrackNumber', 'PairedPublisher', 'PairedISRC', 'PairedCustom'" };

constexpr char cfgKeyword_PairedSongDescription[]        { "PairedSongDescription" };
constexpr char cfgKeywordDesc_PairedSongDescription[]    { "Defines (part of) the song description for the second song in a pair\n" \
                                                           "                                    NOTE: In Albums mode (PageMode = Albums) this determines the Album Title line" };

constexpr char cfgKeyword_ArtistDescription[]            { "ArtistDescription" };
constexpr char cfgKeywordDesc_ArtistDescription[]        { "Defines (part of) the artist description in the pages (same values as 'SongDescription')" };

constexpr char cfgKeyword_MatchedArtistDescription[]     { "MatchedArtistDescription" };
constexpr char cfgKeywordDesc_MatchedArtistDescription[] { "Used instead of 'ArtistDescription' if the artists of the songs in a pair are the same\n" \
                                                           "                                    (or the second song in a pair is absent)" };

constexpr char cfgKeyword_ExtraDescription[]             { "ExtraDescription" };
constexpr char cfgKeywordDesc_ExtraDescription[]         { "Defines (part of) the extra description in the pages (same values as 'SongDescription')" };

constexpr char cfgKeyword_SongHistoryDepth[]             { "SongHistoryDepth" };
constexpr char cfgKeywordDesc_SongHistoryDepth[]         { "Determines the search range of number of previously played songs to ensure\n" \
                                                           "                                    no repeated songs are chosen in Auto play or Random selection.\n" \
                                                           "                                    If not specified or set to zero, fruitbox will only check for\n" \
                                                           "                                    repeated songs from within the play queue" };

constexpr char cfgKeyword_SongLoadTime[]                 { "SongLoadTime" };
constexpr char cfgKeywordDesc_SongLoadTime[]             { "The time the song takes to load (from removing from the coming up queue to starting to play)" };

constexpr char cfgKeyword_SongUnloadTime[]               { "SongUnloadTime" };
constexpr char cfgKeywordDesc_SongUnloadTime[]           { "The time the song takes to unload (from finishing playing to the next song in the queue loading)" };

constexpr char cfgKeyword_SongText[]                     { "SongText" };
constexpr char cfgKeywordDesc_SongText[]                 { "Text style for Song title in song page. See section 'Fonts and Text'" };

constexpr char cfgKeyword_PairedSongText[]               { "PairedSongText" };
constexpr char cfgKeywordDesc_PairedSongText[]           { "Text style for the paired Song title in song page. See section 'Fonts and Text'" };

constexpr char cfgKeyword_ArtistText[]                   { "ArtistText" };
constexpr char cfgKeywordDesc_ArtistText[]               { "Text style for Artist name in song page. See section 'Fonts and Text'" };

constexpr char cfgKeyword_AlbumText[]                    { "AlbumText" };
constexpr char cfgKeywordDesc_AlbumText[]                { "Text style for Album name in song page. See section 'Fonts and Text'" };

constexpr char cfgKeyword_ExtraText[]                    { "ExtraText" };
constexpr char cfgKeywordDesc_ExtraText[]                { "Text style for the extra text field in song page. See section 'Fonts and Text'" };

constexpr char cfgKeyword_AlbumArtSize[]                 { "AlbumArtSize" };
constexpr char cfgKeywordDesc_AlbumArtSize[]             { "width height (in pixels)" };

constexpr char cfgKeyword_AlbumArtOffset[]               { "AlbumArtOffset" };
constexpr char cfgKeywordDesc_AlbumArtOffset[]           { "Offset from top left hand corner of songs page (x y in pixels)" };

constexpr char cfgKeyword_AlbumArtAngle[]                { "AlbumArtAngle" };
constexpr char cfgKeywordDesc_AlbumArtAngle[]            { "Angle of Album artwork in degrees (0..359)" };

constexpr char cfgKeyword_NowPlayingMissingArtwork[]     { "NowPlayingMissingArtwork" };
constexpr char cfgKeywordDesc_NowPlayingMissingArtwork[] { "Filename of graphic image (bmp, png, tga, jpg, pcx) to be used if NowPlayingArtworkMode = 'Specified',\n" \
                                                            "                                    or no song artwork is found and NowPlayingArtworkMode = 'Auto'" };

constexpr char cfgKeyword_AlbumPageMissingArtwork[]      { "AlbumPageMissingArtwork" };
constexpr char cfgKeywordDesc_AlbumPageMissingArtwork[]  { "Filename of graphic image (bmp, png, tga, jpg, pcx) to be used if AlbumPageArtworkMode = 'Specified',\n" \
                                                           "                                    or no song artwork is found and AlbumPageArtworkMode = 'Auto'" };

constexpr char cfgKeyword_NowPlayingArtworkMode[]        { "NowPlayingArtworkMode" };
constexpr char cfgKeywordDesc_NowPlayingArtworkMode[]    { "'None' don't show artwork,\n" \
                                                           "                                    'Embedded' use image in MP3 file,\n" \
                                                           "                                    'Folder' use 'folder.jpg' in song directory,\n" \
                                                           "                                    'Specified' use MissingArtwork image,\n" \
                                                           "                                    'Logo' use fruitbox logo,\n" \
                                                           "                                    'Auto' use embedded/folder/missing/logo if available" };

constexpr char cfgKeyword_AlbumPageArtworkMode[]         { "AlbumPageArtworkMode" };
constexpr char cfgKeywordDesc_AlbumPageArtworkMode[]     { "'None' don't show artwork,\n" \
                                                           "                                    'Folder' use 'folder.jpg' in song directory,\n" \
                                                           "                                    'Specified' use MissingArtwork image,\n"
                                                           "                                    'Logo' use fruitbox logo,\n" \
                                                           "                                    'Auto' use folder/missing/logo if available" };
                                                           
constexpr char cfgKeyword_InsertCoin[]                   { "InsertCoin" };
constexpr char cfgKeywordDesc_InsertCoin[]               { "Volume (0..100), Filename of sound effect when a coin is inserted (wav, flac, ogg)" };

constexpr char cfgKeyword_LoadSong[]                     { "LoadSong" };
constexpr char cfgKeywordDesc_LoadSong[]                 { "Volume (0..100), Filename of sound effect when a song is loading (wav, flac, ogg)" };

constexpr char cfgKeyword_UnloadSong[]                   { "UnloadSong" };
constexpr char cfgKeywordDesc_UnloadSong[]               { "Volume (0..100), Filename of sound effect when a song is unloading (wav, flac, ogg)" };

constexpr char cfgKeyword_PageMove[]                     { "PageMove" };
constexpr char cfgKeywordDesc_PageMove[]                 { "Volume (0..100), Filename of sound effect when pages are moving (wav, flac, ogg)" };

constexpr char cfgKeyword_InvalidSong[]                  { "InvalidSong" };
constexpr char cfgKeywordDesc_InvalidSong[]              { "Volume (0..100), Filename of sound effect when an invalid song choice is selected (wav, flac, ogg)" };

constexpr char cfgKeyword_SongVolume[]                   { "SongVolume" };
constexpr char cfgKeywordDesc_SongVolume[]               { "Initial song volume (0..100)" };

constexpr char cfgKeyword_Size[]                         { "Size" };
constexpr char cfgKeywordDesc_Size[]                     { "width height (in pixels)" };
constexpr char cfgKeywordDesc_JoystickSize[]             { "width height (in pixels).  If not specified the size will be set to cover the song title exactly" };

constexpr char cfgKeyword_Position[]                     { "Position" };
constexpr char cfgKeywordDesc_Position[]                 { "x y (in pixels)" };

constexpr char cfgKeyword_Angle[]                        { "Angle" };
constexpr char cfgKeywordDesc_Angle[]                    { "Angle of object in degrees (0..359)" };

constexpr char cfgKeyword_Offset[]                       { "Offset" };
constexpr char cfgKeywordDesc_JoystickOffset[]           { "x, y (offset in pixels from top left corner of joystick highlight in song title region)" };
constexpr char cfgKeywordDesc_TouchSongOffset[]          { "x, y (offset in pixels from top left corner of song touch highlight in song title region)" };

constexpr char cfgKeyword_Contents[]                     { "Contents" };
constexpr char cfgKeywordDesc_Contents[]                 { "Filename of text file describing status box contents" };

constexpr char cfgKeyword_Output[]                       { "Output" };
constexpr char cfgKeywordDesc_Output[]                   { "Filename of output text file containing status" };

constexpr char cfgKeyword_LineSpacing[]                  { "LineSpacing" };
constexpr char cfgKeywordDesc_StatusLineSpacing[]        { "Gap (in pixels) between text lines in the status box" };

constexpr char cfgKeyword_LoopVideo[]                    { "LoopVideo" };
constexpr char cfgKeywordDesc_LoopVideo[]                { "'Yes' - start video from beginning after it finishes" };

constexpr char cfgKeyword_AlbumPageLineSpacing[]         { "AlbumPageLineSpacing" };
constexpr char cfgKeywordDesc_AlbumPageLineSpacing[]     { "Gap (in pixels) between song titles in the albums song pages" };

constexpr char cfgKeyword_BitmapDirectory[]              { "BitmapDirectory" };
constexpr char cfgKeywordDesc_BitmapDirectory[]          { "Location of image files (bmp, jpg, png)" };

constexpr char cfgKeyword_TimerTickPeriod[]              { "TimerTickPeriod" };
constexpr char cfgKeywordDesc_TimerTickPeriod[]          { "Time (in video frame ticks) of status box timer period" };

constexpr char cfgKeyword_TimerOneShot[]                 { "TimerOneShot" };
constexpr char cfgKeywordDesc_TimerOneShot[]             { "'Yes' - timer stops after one tick, 'No' - timer runs indefinitely (default)" };

constexpr char cfgKeyword_TimerEnable[]                  { "TimerEnable" };
constexpr char cfgKeywordDesc_TimerEnable[]              { "'Yes' - timer initially enabled (default), 'No' - timer initially disabled" };

constexpr char cfgKeyword_Text[]                         { "Text" };
constexpr char cfgKeywordDesc_Text[]                     { "Status box text style.  See section 'Fonts and Text'" };

constexpr char cfgKeyword_Bitmap[]                       { "Bitmap" };
constexpr char cfgKeywordDesc_Bitmap[]                   { "Filename of graphic image (bmp, png, tga, jpg, pcx)" };

constexpr char cfgKeyword_Video[]                        { "Video" };
constexpr char cfgKeywordDesc_Video[]                    { "Filename of video clip (ogv)" };

constexpr char cfgKeyword_Title[]                        { "Title" };

constexpr char cfgKeyword_File[]                         { "File" };
constexpr char cfgKeywordDesc_BitmapFile[]               { "Filename of graphic image (bmp, png, tga, jpg, pcx)" };

constexpr char cfgKeyword_Font[]                         { "Font" };
constexpr char cfgKeywordDesc_Font[]                     { "See section 'Fonts and Text'" };

constexpr char cfgKeyword_FontHeight[]                   { "Height" };
constexpr char cfgKeywordDesc_FontHeight[]               { "The height of the font in pixels" };

constexpr char cfgKeywordDesc_FontFile[]                 { "Filename of a font to add to the font pool (ttf, opentype, type1, CID, CFF, fon, fnt, x11, pcf)" };

constexpr char cfgKeyword_Background[]                   { "Background" };
constexpr char cfgKeywordDesc_Background[]               { "Filename of graphic image (bmp, png, tga, jpg, pcx) to be used as the page background" };

constexpr char cfgKeyword_MoveDelay[]                    { "MoveDelay" };
constexpr char cfgKeywordDesc_MoveDelay[]                { "Delay (in video frame ticks) between left/right button press and page moving" };

constexpr char cfgKeyword_HorzScale[]                    { "HorzScale" };
constexpr char cfgKeywordDesc_HorzScale[]                { "Set the bitmap horizontal size according to 'Volume' or 'NowPlayingElapsedTime'" };

constexpr char cfgKeyword_HorzScaleMode[]                { "HorzScaleMode" };
constexpr char cfgKeywordDesc_HorzScaleMode[]            { "'Scaled' - bitmap is scaled to size, 'Clipped' - bitmap is clipped not scaled" };

constexpr char cfgKeyword_VertScale[]                    { "VertScale" };
constexpr char cfgKeywordDesc_VertScale[]                { "Set the bitmap vertical size according to 'Volume' or 'NowPlayingElapsedTime'" };

constexpr char cfgKeyword_VertScaleMode[]                { "VertScaleMode" };
constexpr char cfgKeywordDesc_VertScaleMode[]            { "'Scaled' - bitmap is scaled to size, 'Clipped' - bitmap is clipped not scaled" };

constexpr char cfgKeyword_ReverseClip[]                  { "ReverseClip" };
constexpr char cfgKeywordDesc_ReverseClip[]              { "'No' - bitmap is clipped bottom->top and/or right->left\n" \
                                                           "                                    'Yes' - bitmap is clipped top->bottom and/or left->right" };

constexpr char cfgKeyword_AudioOnlyClip[]                { "AudioOnlyClip" };
constexpr char cfgKeywordDesc_AudioOnlyClip[]            { "Filename of video (ogv) to be played for audio only music files" };
constexpr char cfgKeyword_IdleClip[]                     { "IdleClip" };
constexpr char cfgKeywordDesc_IdleClip[]                 { "Filename of video (ogv) to be played when no music playing" };

constexpr char cfgKeyword_ButtonQuit[]                   { "ButtonQuit" };
constexpr char cfgKeyword_ButtonCoin1[]                  { "ButtonCoin1" };
constexpr char cfgKeyword_ButtonCoin2[]                  { "ButtonCoin2" };
constexpr char cfgKeyword_ButtonCoin3[]                  { "ButtonCoin3" };
constexpr char cfgKeyword_ButtonCoin4[]                  { "ButtonCoin4" };
constexpr char cfgKeyword_ButtonVolUp[]                  { "ButtonVol+" };
constexpr char cfgKeyword_ButtonVolDown[]                { "ButtonVol-" };
constexpr char cfgKeyword_ButtonRandom[]                 { "ButtonRandom" };
constexpr char cfgKeyword_ButtonSelect[]                 { "ButtonSelect" };
constexpr char cfgKeyword_ButtonSkip[]                   { "ButtonSkip" };
constexpr char cfgKeyword_ButtonPause[]                  { "ButtonPause" };
constexpr char cfgKeyword_ButtonUp[]                     { "ButtonUp" };
constexpr char cfgKeyword_ButtonDown[]                   { "ButtonDown" };
constexpr char cfgKeyword_ButtonLeft[]                   { "ButtonLeft" };
constexpr char cfgKeyword_ButtonRight[]                  { "ButtonRight" };
constexpr char cfgKeyword_ButtonLeftJump[]               { "ButtonLeftJump" };
constexpr char cfgKeyword_ButtonRightJump[]              { "ButtonRightJump" };
constexpr char cfgKeyword_ButtonLeftAlpha[]              { "ButtonLeftAlpha" };
constexpr char cfgKeyword_ButtonRightAlpha[]             { "ButtonRightAlpha" };
constexpr char cfgKeyword_ButtonAuto[]                   { "ButtonAuto" };
constexpr char cfgKeyword_ButtonLoop[]                   { "ButtonLoop" };
constexpr char cfgKeyword_ButtonFree[]                   { "ButtonFree" };
constexpr char cfgKeyword_ButtonClear[]                  { "ButtonClear" };
constexpr char cfgKeyword_ButtonMute[]                   { "ButtonMute" };
constexpr char cfgKeyword_ButtonPowerOff[]               { "ButtonPowerOff" };
constexpr char cfgKeyword_Button0[]                      { "Button0" };
constexpr char cfgKeyword_Button1[]                      { "Button1" };
constexpr char cfgKeyword_Button2[]                      { "Button2" };
constexpr char cfgKeyword_Button3[]                      { "Button3" };
constexpr char cfgKeyword_Button4[]                      { "Button4" };
constexpr char cfgKeyword_Button5[]                      { "Button5" };
constexpr char cfgKeyword_Button6[]                      { "Button6" };
constexpr char cfgKeyword_Button7[]                      { "Button7" };
constexpr char cfgKeyword_Button8[]                      { "Button8" };
constexpr char cfgKeyword_Button9[]                      { "Button9" };
constexpr char cfgKeyword_ButtonA[]                      { "ButtonA" };
constexpr char cfgKeyword_ButtonB[]                      { "ButtonB" };
constexpr char cfgKeyword_ButtonC[]                      { "ButtonC" };
constexpr char cfgKeyword_ButtonD[]                      { "ButtonD" };
constexpr char cfgKeyword_ButtonE[]                      { "ButtonE" };
constexpr char cfgKeyword_ButtonF[]                      { "ButtonF" };
constexpr char cfgKeyword_ButtonG[]                      { "ButtonG" };
constexpr char cfgKeyword_ButtonH[]                      { "ButtonH" };
constexpr char cfgKeyword_ButtonI[]                      { "ButtonI" };
constexpr char cfgKeyword_ButtonJ[]                      { "ButtonJ" };
constexpr char cfgKeyword_ButtonK[]                      { "ButtonK" };
constexpr char cfgKeyword_ButtonFlag1[]                  { "ButtonFlag1" };
constexpr char cfgKeyword_ButtonFlag2[]                  { "ButtonFlag2" };
constexpr char cfgKeyword_ButtonFlag3[]                  { "ButtonFlag3" };
constexpr char cfgKeyword_ButtonFlag4[]                  { "ButtonFlag4" };
constexpr char cfgKeyword_ButtonMenu[]                   { "ButtonMenu" };
constexpr char cfgKeywordDesc_ButtonQuit[]               { "Name of button (quit fruitbox)" };
constexpr char cfgKeywordDesc_ButtonInsertCoin[]         { "Name of button (insert coin)" };
constexpr char cfgKeywordDesc_ButtonVolume[]             { "Name of button (change volume)" };
constexpr char cfgKeywordDesc_ButtonRandom[]             { "Name of button (select random song)" };
constexpr char cfgKeywordDesc_ButtonSelect[]             { "Name of button (play selected song)" };
constexpr char cfgKeywordDesc_ButtonSkip[]               { "Name of button (stop current song)" };
constexpr char cfgKeywordDesc_ButtonPause[]              { "Name of button (pause/unpause currently playing song)" };
constexpr char cfgKeywordDesc_ButtonDirections[]         { "Name of button (move pages/joystick selector)" };
constexpr char cfgKeywordDesc_ButtonJumpDirections[]     { "Name of button (move pages by 'PageJump' amount)" };
constexpr char cfgKeywordDesc_ButtonSortDirections[]     { "Name of button (move pages by last 'SortSongsBy' value)" };
constexpr char cfgKeywordDesc_ButtonDirectionsJoy[]      { "Name of button (joystick selector)" };
constexpr char cfgKeywordDesc_ButtonAuto[]               { "Name of button (toggle Auto (aka Attract) mode)" };
constexpr char cfgKeywordDesc_ButtonLoop[]               { "Name of button (toggle Loop mode)" };
constexpr char cfgKeywordDesc_ButtonFree[]               { "Name of button (toggle Freeplay mode)" };
constexpr char cfgKeywordDesc_ButtonClear[]              { "Name of button (empty play queue)" };
constexpr char cfgKeywordDesc_ButtonMute[]               { "Name of button (volume mute)" };
constexpr char cfgKeywordDesc_ButtonSongSelect[]         { "Name of button (song selection)" };
constexpr char cfgKeywordDesc_ButtonFlag[]               { "Name of button (toggle status flag)" };
constexpr char cfgKeywordDesc_ButtonMenu[]               { "Name of button (toggle menu)" };
constexpr char cfgKeywordDesc_ButtonPowerOff[]           { "Name of button (power off)" };

constexpr char cfgKeyword_ButtonTouchArea[]              { "x y width height  (touch area of button, where x y = top left corner)" };

struct default_button_t
{
  uint32_t num;
  const char *name;
  const char *desc;
  int32_t key;
};

// const array<default_button_t, 2> default_button
const default_button_t default_button[NUM_BUTTONS] = 
{
  {BUTTON_QUIT          , cfgKeyword_ButtonQuit        , cfgKeywordDesc_ButtonQuit           , KEY_ESC         },
  {BUTTON_INSERT_COIN1  , cfgKeyword_ButtonCoin1       , cfgKeywordDesc_ButtonInsertCoin     , KEY_F1          },
  {BUTTON_INSERT_COIN2  , cfgKeyword_ButtonCoin2       , cfgKeywordDesc_ButtonInsertCoin     , KEY_F2          },
  {BUTTON_INSERT_COIN3  , cfgKeyword_ButtonCoin3       , cfgKeywordDesc_ButtonInsertCoin     , KEY_F3          },
  {BUTTON_INSERT_COIN4  , cfgKeyword_ButtonCoin4       , cfgKeywordDesc_ButtonInsertCoin     , KEY_F4          },
  {BUTTON_VOL_UP        , cfgKeyword_ButtonVolUp       , cfgKeywordDesc_ButtonVolume         , KEY_EQUAL       },
  {BUTTON_VOL_DOWN      , cfgKeyword_ButtonVolDown     , cfgKeywordDesc_ButtonVolume         , KEY_MINUS       },
  {BUTTON_ADD_RANDOM    , cfgKeyword_ButtonRandom      , cfgKeywordDesc_ButtonRandom         , KEY_SPACE       },
  {BUTTON_SELECT        , cfgKeyword_ButtonSelect      , cfgKeywordDesc_ButtonSelect         , KEY_ENTER       },
  {BUTTON_SKIP          , cfgKeyword_ButtonSkip        , cfgKeywordDesc_ButtonSkip           , KEY_BACKSPACE   },
  {BUTTON_PAUSE         , cfgKeyword_ButtonPause       , cfgKeywordDesc_ButtonPause          , KEY_Z           },
  {BUTTON_UP            , cfgKeyword_ButtonUp          , cfgKeywordDesc_ButtonDirectionsJoy  , KEY_UP          },
  {BUTTON_DOWN          , cfgKeyword_ButtonDown        , cfgKeywordDesc_ButtonDirectionsJoy  , KEY_DOWN        },
  {BUTTON_LEFT          , cfgKeyword_ButtonLeft        , cfgKeywordDesc_ButtonDirections     , KEY_LEFT        },
  {BUTTON_RIGHT         , cfgKeyword_ButtonRight       , cfgKeywordDesc_ButtonDirections     , KEY_RIGHT       },
  {BUTTON_LEFT_JUMP     , cfgKeyword_ButtonLeftJump    , cfgKeywordDesc_ButtonJumpDirections , KEY_LEFTBRACE   },
  {BUTTON_RIGHT_JUMP    , cfgKeyword_ButtonRightJump   , cfgKeywordDesc_ButtonJumpDirections , KEY_RIGHTBRACE  },
  {BUTTON_LEFT_ALPHA    , cfgKeyword_ButtonLeftAlpha   , cfgKeywordDesc_ButtonSortDirections , KEY_COMMA       },
  {BUTTON_RIGHT_ALPHA   , cfgKeyword_ButtonRightAlpha  , cfgKeywordDesc_ButtonSortDirections , KEY_DOT         },
  {BUTTON_AUTO_PLAY_TOG , cfgKeyword_ButtonAuto        , cfgKeywordDesc_ButtonAuto           , KEY_R           },
  {BUTTON_LOOP_TOG      , cfgKeyword_ButtonLoop        , cfgKeywordDesc_ButtonLoop           , KEY_L           },
  {BUTTON_FREEPLAY_TOG  , cfgKeyword_ButtonFree        , cfgKeywordDesc_ButtonFree           , KEY_P           },
  {BUTTON_CLEAR_QUEUE   , cfgKeyword_ButtonClear       , cfgKeywordDesc_ButtonClear          , KEY_X           },
  {BUTTON_MUTE          , cfgKeyword_ButtonMute        , cfgKeywordDesc_ButtonMute           , KEY_M           },
  {BUTTON_POWER_OFF     , cfgKeyword_ButtonPowerOff    , cfgKeywordDesc_ButtonPowerOff       , KEY_F12         },
  {BUTTON_0             , cfgKeyword_Button0           , cfgKeywordDesc_ButtonSongSelect     , KEY_0           },
  {BUTTON_1             , cfgKeyword_Button1           , cfgKeywordDesc_ButtonSongSelect     , KEY_1           },
  {BUTTON_2             , cfgKeyword_Button2           , cfgKeywordDesc_ButtonSongSelect     , KEY_2           },
  {BUTTON_3             , cfgKeyword_Button3           , cfgKeywordDesc_ButtonSongSelect     , KEY_3           },
  {BUTTON_4             , cfgKeyword_Button4           , cfgKeywordDesc_ButtonSongSelect     , KEY_4           },
  {BUTTON_5             , cfgKeyword_Button5           , cfgKeywordDesc_ButtonSongSelect     , KEY_5           },
  {BUTTON_6             , cfgKeyword_Button6           , cfgKeywordDesc_ButtonSongSelect     , KEY_6           },
  {BUTTON_7             , cfgKeyword_Button7           , cfgKeywordDesc_ButtonSongSelect     , KEY_7           },
  {BUTTON_8             , cfgKeyword_Button8           , cfgKeywordDesc_ButtonSongSelect     , KEY_8           },
  {BUTTON_9             , cfgKeyword_Button9           , cfgKeywordDesc_ButtonSongSelect     , KEY_9           },
  {BUTTON_A             , cfgKeyword_ButtonA           , cfgKeywordDesc_ButtonSongSelect     , KEY_A           },
  {BUTTON_B             , cfgKeyword_ButtonB           , cfgKeywordDesc_ButtonSongSelect     , KEY_B           },
  {BUTTON_C             , cfgKeyword_ButtonC           , cfgKeywordDesc_ButtonSongSelect     , KEY_C           },
  {BUTTON_D             , cfgKeyword_ButtonD           , cfgKeywordDesc_ButtonSongSelect     , KEY_D           },
  {BUTTON_E             , cfgKeyword_ButtonE           , cfgKeywordDesc_ButtonSongSelect     , KEY_E           },
  {BUTTON_F             , cfgKeyword_ButtonF           , cfgKeywordDesc_ButtonSongSelect     , KEY_F           },
  {BUTTON_G             , cfgKeyword_ButtonG           , cfgKeywordDesc_ButtonSongSelect     , KEY_G           },
  {BUTTON_H             , cfgKeyword_ButtonH           , cfgKeywordDesc_ButtonSongSelect     , KEY_H           },
  {BUTTON_I             , cfgKeyword_ButtonI           , cfgKeywordDesc_ButtonSongSelect     , KEY_I           },
  {BUTTON_J             , cfgKeyword_ButtonJ           , cfgKeywordDesc_ButtonSongSelect     , KEY_J           },
  {BUTTON_K             , cfgKeyword_ButtonK           , cfgKeywordDesc_ButtonSongSelect     , KEY_K           },
  {BUTTON_FLAG_1        , cfgKeyword_ButtonFlag1       , cfgKeywordDesc_ButtonFlag           , KEY_F5          },
  {BUTTON_FLAG_2        , cfgKeyword_ButtonFlag2       , cfgKeywordDesc_ButtonFlag           , KEY_F6          },
  {BUTTON_FLAG_3        , cfgKeyword_ButtonFlag3       , cfgKeywordDesc_ButtonFlag           , KEY_F7          },
  {BUTTON_FLAG_4        , cfgKeyword_ButtonFlag4       , cfgKeywordDesc_ButtonFlag           , KEY_F8          }
};

class ReadBool
{
public:
  ReadBool(bool& v) : v_(v) {}
  void Parse(istringstream& is) const
  {
    string s;
    is >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    v_ = (s == "1" || s == "yes" || s == "on" || s == "enable" || s == "true");
  }
private:
  bool& v_;
};

static istringstream& operator>>(istringstream& is, const ReadBool& rb)
{
  rb.Parse(is);
  return is;
}

class ConfigBaseClass {
public:
  static string filepath;
  virtual void cfgRead(string line) = 0;
  virtual void cfgShow(const char *indent) = 0;
  ints2_t touch_min { };
  ints2_t touch_max { };

  void cfgShowEntry(const string & indent, const string &keyword, const string &description, const bool multi_param)
  {
    if (multi_param)
    {
      log_file << indent << keyword << setw(maxCfgKeywordWidth - keyword.size()) << left << multiCfgParameter << description << endl;
    }
    else
    {
      log_file << indent << setw(maxCfgKeywordWidth) << left << keyword << description << endl;
    }
  }

private:

  bool ExtractParameterValues(string &line, const char *keyword)
  {
    // remove any CRLF characters...
    line.erase(std::remove(line.begin(), line.end(), 10), line.end());
    line.erase(std::remove(line.begin(), line.end(), 13), line.end());

    // remove everything after any comment...
    size_t eolc { line.find_first_of(cfgFile_comment) };
    if (eolc != string::npos) line.erase(eolc);

    if (line.size() == 0) return false; // no characters left!

    string lowercase_keyword {keyword};
    transform(lowercase_keyword.begin(), lowercase_keyword.end(), lowercase_keyword.begin(), ::tolower);

    string lowercase_line { line };
    transform(lowercase_line.begin(), lowercase_line.end(), lowercase_line.begin(), ::tolower);

    // search for keyword...
    // cout << "lowercase_keyword : " << lowercase_keyword << endl;
    size_t p { lowercase_line.find(lowercase_keyword) };
    if (p == string::npos) return false; // keyword not found

    if (p > 0) // there are some characters before the keyword so could be a different keyword...
    {
      char c { lowercase_line.at(p-1) };
      if ((c != ' ')  && (c != '\t')) return false; // not a whitespace, so probably a different keyword
    }

    // see if there are any non separator characters immediately after the keyword - if so, it could be another keyword...
    size_t q { lowercase_line.find_first_not_of(cfgFile_keyword_param_separator, p + lowercase_keyword.size()) };
    if (q == lowercase_keyword.size()) return false;

    line.erase(0, line.find_first_not_of(cfgFile_keyword_param_separator, p + lowercase_keyword.size())); // remove keyword + parameter separators

    // replace certain characters with spaces...
    // constexpr char invalidParameterSeparators[] { ",{}[]()" };
    // size_t found = line.find_first_of(invalidParameterSeparators);
    // while (found!=std::string::npos)
    // {
      // line[found]=' ';
      // found=line.find_first_of(invalidParameterSeparators,found+1);
    // }

    // remove trailing whitespace...
    size_t eolw { line.find_last_not_of(" \t") };
    if (eolw != string::npos) line.erase(eolw + 1);
    return true;
  }

protected:

  bool GetParam(string line, const char *keyword, pair<title_desc_e, string> &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string str {};
    if (!getline(ss >> std::ws, str)) return false;
    log_file << "  " << keyword << " = " << str << endl;
    if (str.size() == 0) return false;
    var.first = title_desc_e::String;

    if (str.at(0) == '\"')
    {
      str.erase(remove(str.begin(), str.end(), '\"' ), str.end()); // remove double quotes
    }
    else if (str == "SongTitle") var.first = title_desc_e::SongTitle;
    else if (str == "Artist") var.first = title_desc_e::Artist;
    else if (str == "AlbumTitle") var.first = title_desc_e::AlbumTitle;
    else if (str == "AlbumArtist") var.first = title_desc_e::AlbumArtist;
    else if (str == "Year") var.first = title_desc_e::Year;
    else if (str == "Genre") var.first = title_desc_e::Genre;
    else if (str == "TrackNumber") var.first = title_desc_e::TrackNumber;
    else if (str == "Publisher") var.first = title_desc_e::Publisher;
    else if (str == "ISRC") var.first = title_desc_e::ISRC;
    else if (str == "Custom") var.first = title_desc_e::Custom;
    else if (str == "PairedSongTitle") var.first = title_desc_e::PairedSongTitle;
    else if (str == "PairedArtist") var.first = title_desc_e::PairedArtist;
    else if (str == "PairedAlbumTitle") var.first = title_desc_e::PairedAlbumTitle;
    else if (str == "PairedAlbumArtist") var.first = title_desc_e::PairedAlbumArtist;
    else if (str == "PairedYear") var.first = title_desc_e::PairedYear;
    else if (str == "PairedGenre") var.first = title_desc_e::PairedGenre;
    else if (str == "PairedTrackNumber") var.first = title_desc_e::PairedTrackNumber;
    else if (str == "PairedPublisher") var.first = title_desc_e::PairedPublisher;
    else if (str == "PairedISRC") var.first = title_desc_e::PairedISRC;
    else if (str == "PairedCustom") var.first = title_desc_e::PairedCustom;
    var.second = str;
    return true;
  }

  bool GetParam(string line, const char *keyword, string &var, bool no_filepath_prefix)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    log_file << "  " << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, string &var, bool no_filepath_prefix, bool supress_message)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    if (supress_message == false) log_file << "  " << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, string &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    var = ConfigBaseClass::filepath + '/' + var;
    log_file << "  " << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, bool &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> ReadBool(var);
    log_file << "  " << boolalpha << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, uint32_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var;
    log_file << "  " << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, int32_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var;
    log_file << "  " << keyword << " = " << var << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, uints2_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y;
    log_file << "  " << keyword << " = " << var.x << " " << var.y << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, ints2_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y;
    log_file << "  " << keyword << " = " << var.x << " " << var.y << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, pair_songs_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 'n')
    {
      var = pair_songs_e::No;
      log_file << "  " << keyword << " = No" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'y')
    {
      var = pair_songs_e::Yes;
      log_file << "  " << keyword << " = Yes" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'd')
    {
      var = pair_songs_e::Dual;
      log_file << "  " << keyword << " = Dual" << endl;
      return true;
    }

    return false;
  }

  bool GetParam(string line, const char *keyword, page_mode_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 's')
    {
      var = page_mode_e::Singles;
      log_file << "  " << keyword << " = Singles" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'a')
    {
      var = page_mode_e::Albums;
      log_file << "  " << keyword << " = Albums" << endl;
      return true;
    }

    return false;
  }

  bool GetParam(string line, const char *keyword, select_buttons_sequence_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 'r')
    {
      var = select_buttons_sequence_e::RowCol;
      log_file << "  " << keyword << " = RowCol" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'c')
    {
      var = select_buttons_sequence_e::ColRow;
      log_file << "  " << keyword << " = ColRow" << endl;
      return true;
    }

    return false;
  }

  bool GetParam(string line, const char *keyword, artwork_mode_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 'a')
    {
      var = artwork_mode_e::Auto;
      log_file << "  " << keyword << " = Auto" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'n')
    {
      var = artwork_mode_e::None;
      log_file << "  " << keyword << " = None" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'e')
    {
      var = artwork_mode_e::Embedded;
      log_file << "  " << keyword << " = Embedded" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 's')
    {
      var = artwork_mode_e::Specified;
      log_file << "  " << keyword << " = Specified" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'f')
    {
      var = artwork_mode_e::Folder;
      log_file << "  " << keyword << " = Folder" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'l')
    {
      var = artwork_mode_e::Logo;
      log_file << "  " << keyword << " = Logo" << endl;
      return true;
    }

    return false;
  }

  bool GetParam(string line, const char *keyword, sort_songs_by_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    char c;
    if (s.size() < 2) return false;

    if (tolower(s.at(0)) == 't')
    {
      if (tolower(s.at(1)) == 'i')
      {
        var = sort_songs_by_e::Title;
        log_file << "  " << keyword << " = Title" << endl;
        return true;
      }
      else
      {
        var = sort_songs_by_e::TrackNumber;
        log_file << "  " << keyword << " = TrackNumber" << endl;
        return true;
      }
    }

    if (tolower(s.at(0)) == 'a')
    {
      if (tolower(s.at(1)) == 'r')
      {
        var = sort_songs_by_e::Artist;
        log_file << "  " << keyword << " = Artist" << endl;
        return true;
      }
      else if (tolower(s.at(1)) == 'l')
      {
        if (s.size() > 5)
        {
          var = sort_songs_by_e::AlbumArtist;
          log_file << "  " << keyword << " = AlbumArtist" << endl;
          return true;
        }
        else
        {
          var = sort_songs_by_e::Album;
          log_file << "  " << keyword << " = Album" << endl;
          return true;
        }
      }
    }

    if (tolower(s.at(0)) == 'y')
    {
      var = sort_songs_by_e::Year;
      log_file << "  " << keyword << " = Year" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'g')
    {
      var = sort_songs_by_e::Genre;
      log_file << "  " << keyword << " = Genre" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'r')
    {
      var = sort_songs_by_e::Random;
      log_file << "  " << keyword << " = Random" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'u')
    {
      var = sort_songs_by_e::Unsorted;
      log_file << "  " << keyword << " = Unsorted" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'p')
    {
      var = sort_songs_by_e::Publisher;
      log_file << "  " << keyword << " = Publisher" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'i')
    {
      var = sort_songs_by_e::ISRC;
      log_file << "  " << keyword << " = ISRC" << endl;
      return true;
    }

    if (tolower(s.at(0)) == 'c')
    {
      var = sort_songs_by_e::Custom;
      log_file << "  " << keyword << " = Custom MP3 tag" << endl;
      return true;
    }

    return false;
  }

  bool GetParam(string line, const char *keyword, bitmap_scale_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    var = bitmap_scale_e::None;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 'v')
    {
      var = bitmap_scale_e::Volume;
      log_file << "  " << keyword << " = Volume" << endl;
      return true;
    }
    if (tolower(s.at(0)) == 'n')
    {
      var = bitmap_scale_e::NowPlayingElapsedTime;
      log_file << "  " << keyword << " = NowPlayingElapsedTime" << endl;
      return true;
    }
    return false;
  }

  bool GetParam(string line, const char *keyword, bitmap_scale_mode_e &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    if (tolower(s.at(0)) == 's')
    {
      var = bitmap_scale_mode_e::Scaled;
      log_file << "  " << keyword << " = Scaled" << endl;
      return true;
    }
    if (tolower(s.at(0)) == 'c')
    {
      var = bitmap_scale_mode_e::Clipped;
      log_file << "  " << keyword << " = Clipped" << endl;
      return true;
    }
    return false;
  }

  bool GetParam(string line, const char *keyword, text_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string align;
    ss >> var.font_number;
    ss >> setbase(0) >> var.colour.r >> var.colour.g >> var.colour.b >> var.colour.a;
    ss >> align;
    var.alignment = ALLEGRO_ALIGN_LEFT;
    if (align.size())
    {
      if ((align.at(0) == 'c') || (align.at(0) == 'C')) var.alignment = ALLEGRO_ALIGN_CENTRE;
      if ((align.at(0) == 'r') || (align.at(0) == 'R')) var.alignment = ALLEGRO_ALIGN_RIGHT;
    }
    ss >> ReadBool(var.capitalise) >> ReadBool(var.condense) >> ReadBool(var.quoted);
    ss >> var.offset.x >> var.offset.y;
    log_file << "  " << keyword << " = " << var.font_number << " " << var.colour.r <<  " " << var.colour.g <<  " " << var.colour.b <<  " " << var.colour.a;
    switch (var.alignment)
    {
      case ALLEGRO_ALIGN_CENTRE :
        log_file << " centre";
        break;

      case ALLEGRO_ALIGN_RIGHT :
        log_file << " right";
        break;

      default :
        log_file << " left";
        break;
    }
    ss >> var.max_width;
    log_file << boolalpha << " " << var.capitalise << " " << var.condense << " " << var.quoted;
    log_file << " " << var.offset.x << " " << var.offset.y << " " << var.max_width << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, bitmap_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.filename;
    var.filename = ConfigBaseClass::filepath + '/' + var.filename;
    if (var.handle == nullptr) // not already defined
    {
      if ((var.handle = al_load_bitmap(var.filename.c_str())) == nullptr) error("Couldn't load bitmap '%s'", var.filename.c_str());
      log_file << "  " << keyword << " = " << var.filename << endl;
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, video_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.filename;
    var.filename = ConfigBaseClass::filepath + '/' + var.filename;
    if (var.handle == nullptr) // not already defined
    {
      // if ((var.handle = al_open_video(var.filename.c_str())) == nullptr) error("Couldn't load video '%s'", var.filename.c_str());
      log_file << "  " << keyword << " = " << var.filename << endl;
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, sound_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    uint32_t vol {100};
    istringstream ss { line };
    ss >> vol;
    if (vol > 100) vol = 100;
    var.volume = static_cast<float>(vol)/100.0;
    if (!getline(ss >> std::ws, var.filename)) return false;
    var.filename = ConfigBaseClass::filepath + '/' + var.filename;
    if (var.handle == nullptr) // not already defined
    {
      if ((var.handle = al_load_sample(var.filename.c_str())) == nullptr) error("Couldn't load sound '%s'", var.filename.c_str());
      al_play_sample(var.handle, 0.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &var.id);
      var.length = 10 * al_get_sample_length(var.handle) / al_get_sample_frequency(var.handle); // in hundreds of msec
      log_file << "  " << keyword << " = " << vol << " " << var.filename << endl;
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, page_style_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.speed >> var.effect;
    ss >> ReadBool(var.fading);
    log_file << boolalpha << "  " << keyword << " = " << var.speed << " " << var.effect << " " << var.fading << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, touch_area_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y >> var.w >> var.h;
    log_file << "  " << keyword << " = " << var.x << " " << var.y << " " << var.w << " " << var.h << endl;
    return true;
  }

  bool GetParam(string line, const char *keyword, button_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string type_str;

    ss >> type_str;
    var.param = { 0, 0, 0, 0 };

    if (type_str.size() < 3) return false;

    if (tolower(type_str.at(0)) == tolower(ButtonTypeKeyStr[0]))
    {
      var.type = input_type_e::Key;
      ss >> setbase(0) >> var.param.at(EVENT_PARAM_VAL1);
      // log_file << "  " << keyword << " = " << ButtonTypeKeyStr << " " << var.param.at(EVENT_PARAM_VAL1) << endl; // keycode
      return true;
    }

    if (tolower(type_str.at(0)) == tolower(ButtonTypeMouseButtonStr[0]))
    {
      var.type = input_type_e::MouseButton;
      ss >> setbase(0) >> var.param.at(EVENT_PARAM_ID) >> var.param.at(EVENT_PARAM_VAL1);
      // log_file << "  " << keyword << " = " << ButtonTypeMouseButtonStr << " " << var.param.at(EVENT_PARAM_ID) << var.param.at(EVENT_PARAM_VAL1) << endl; // handler_num, keycode
      return true;
    }

    if (tolower(type_str.at(0)) == tolower(ButtonTypeGPIOStr[0]))
    {
      var.type = input_type_e::GPIO;
      ss >> setbase(0) >> var.param.at(EVENT_PARAM_VAL1);
      // log_file << "  " << keyword << " = " << ButtonTypeGPIOStr << " " << var.param.at(EVENT_PARAM_VAL1) << endl; // GPIO pin
      return true;
    } 

    if (tolower(type_str.at(0)) == tolower(ButtonTypeTouchStr[0]))
    {
      var.type = input_type_e::Touch;
      // log_file << "  " << keyword << " = " << ButtonTypeTouchStr << endl;
      return true;
    }

    if (tolower(type_str.at(0)) == tolower(ButtonTypeJoyStickStr[0])) // 'J'
    {
      if (tolower(type_str.at(3)) == tolower(ButtonTypeJoyStickStr[3])) // 'S'
      {
        var.type = input_type_e::JoyStick;
        ss >> setbase(0) >> var.param.at(EVENT_PARAM_ID) >> var.param.at(EVENT_PARAM_VAL1) >> var.param.at(EVENT_PARAM_VAL2); // handler_num, axis, position
        return true;
      }
      else // JoyButton ('B')
      {
        var.type = input_type_e::JoyButton;
        ss >> setbase(0) >> var.param.at(EVENT_PARAM_ID) >> var.param.at(EVENT_PARAM_VAL1); // handler_num, button code
        return true;
      }
    }

    return false;
  }
  
};

class GeneralConfigClass : public ConfigBaseClass
{
public:
  void cfgRead(string line)
  {
    string str {};
    uint32_t uint { 0 };
    pair<title_desc_e, string> desc;
    sort_songs_by_e song_sort {};
    if (GetParam(line, cfgKeyword_SkinSize, skin_size)) return;
    if (GetParam(line, cfgKeyword_SkinName, skin_name, false)) return;
    if (GetParam(line, cfgKeyword_SkinDescription, skin_desc, false)) return;
    if (GetParam(line, cfgKeyword_Screenshot, screenshot, false)) return;
    if (database_filename.size() == 0) // not defined on command line, so get from cfg file...
    {
      if (GetParam(line, cfgKeyword_Database, database_filename, false)) return;
    }
    if (command_line_music_path == false)
    {
      if (GetParam(line, cfgKeyword_MusicPath, str, false))
      {
        music_path.push_back(str);
        return;
      }
    }
    if (GetParam(line, cfgKeyword_SortSongsBy, song_sort))
    {
      sort_songs_by.push_back(song_sort);
      return;
    }

    if (GetParam(line, cfgKeyword_SelectButtons, str, false))
    {
      select_buttons.push_back(str);
      return;
    }
    if (GetParam(line, cfgKeyword_SelectButtonsSequence,    select_buttons_sequence)) return;
    if (GetParam(line, cfgKeyword_CustomMP3Tag,             custom_mp3_tag, false)) return;
    if (GetParam(line, cfgKeyword_AutoSelect,               auto_select)) return;
    if (GetParam(line, cfgKeyword_PageJump,                 page_jump)) return;
    if (GetParam(line, cfgKeyword_SelectTimeout,            select_timeout)) return;
    if (GetParam(line, cfgKeyword_SelectHoldTimeout,        select_hold_timeout)) return;
    if (GetParam(line, cfgKeyword_AutoPageTurnTime,         auto_page_turn_time)) return;
    if (GetParam(line, cfgKeyword_MaxPlaylistLength,        max_playlist_length)) return;
    if (GetParam(line, cfgKeyword_NoDuplicates,             no_duplicates)) return;
    if (GetParam(line, cfgKeyword_DuplicatesUseCredits,     duplicates_use_credits)) return;
    if (GetParam(line, cfgKeyword_LoopPlaylist,             loop_playlist)) return;
    if (GetParam(line, cfgKeyword_AutoPlay,                 auto_play)) return;
    if (GetParam(line, cfgKeyword_AutoPlayGap,              auto_play_gap)) return;
    if (GetParam(line, cfgKeyword_AutoGenre,                str, true))
    {
      auto_genre.push_back(str);
      return;
    }
    if (GetParam(line, cfgKeyword_PlaysPerCoin1, uint))
    {
      plays_per_coin.at(0) = uint;
      plays_per_coin_str.at(0) = to_string(plays_per_coin.at(0));
      return;
    }
    if (GetParam(line, cfgKeyword_PlaysPerCoin2, uint))
    {
      plays_per_coin.at(1) = uint;
      plays_per_coin_str.at(1) = to_string(plays_per_coin.at(1));
      return;
    }
    if (GetParam(line, cfgKeyword_PlaysPerCoin3, uint))
    {
      plays_per_coin.at(2) = uint;
      plays_per_coin_str.at(2) = to_string(plays_per_coin.at(2));
      return;
    }
    if (GetParam(line, cfgKeyword_PlaysPerCoin4, uint))
    {
      plays_per_coin.at(3) = uint;
      plays_per_coin_str.at(3) = to_string(plays_per_coin.at(3));
      return;
    }
    if (GetParam(line, cfgKeyword_SongsPerPage,             songs_per_page)) return;
    if (GetParam(line, cfgKeyword_PageSize,                 page_size)) return;
    if (GetParam(line, cfgKeyword_PageMode,                 page_mode)) return;
    if (GetParam(line, cfgKeyword_PairSongs,                pair_songs)) return;
    if (GetParam(line, cfgKeyword_PageMoveStyle,            page_move_style)) return;
    if (GetParam(line, cfgKeyword_SongDescription, desc))
    {
      if (song_description_use_default)
      {
        song_description.clear(); // remove default entry as user is defining the fields...
        song_description_use_default = false;
      }
      song_description.push_back(desc);
      return;
    }
    if (GetParam(line, cfgKeyword_PairedSongDescription, desc))
    {
      if (paired_song_description_use_default)
      {
        paired_song_description.clear(); // remove default entry as user is defining the fields...
        paired_song_description_use_default = false;
      }
      paired_song_description.push_back(desc);
      return;
    }
    if (GetParam(line, cfgKeyword_ArtistDescription, desc))
    {
      if (artist_description_use_default)
      {
        artist_description.clear(); // remove default entry as user is defining the fields...
        artist_description_use_default = false;
      }
      artist_description.push_back(desc);
      return;
    }
    if (GetParam(line, cfgKeyword_MatchedArtistDescription, desc))
    {
      if (matched_artist_description_use_default)
      {
        matched_artist_description.clear(); // remove default entry as user is defining the fields...
        matched_artist_description_use_default = false;
      }
      matched_artist_description.push_back(desc);
      return;
    }
    if (GetParam(line, cfgKeyword_ExtraDescription, desc))
    {
      extra_description.push_back(desc);
      return;
    }
    if (GetParam(line, cfgKeyword_SongHistoryDepth,         song_history_depth)) return;
    if (GetParam(line, cfgKeyword_SongLoadTime,             song_load_time)) return;
    if (GetParam(line, cfgKeyword_SongUnloadTime,           song_unload_time)) return;
    if (GetParam(line, cfgKeyword_SongText,                 song_text)) return;
    if (GetParam(line, cfgKeyword_PairedSongText,           paired_song_text)) return;
    if (GetParam(line, cfgKeyword_ArtistText,               artist_text)) return;
    if (GetParam(line, cfgKeyword_AlbumText,                album_text)) return;
    if (GetParam(line, cfgKeyword_ExtraText,                extra_text)) return;
    if (GetParam(line, cfgKeyword_AlbumArtSize,             album_art_size)) return;
    if (GetParam(line, cfgKeyword_AlbumArtOffset,           album_art_offset)) return;
    if (GetParam(line, cfgKeyword_AlbumArtAngle,            album_art_angle)) return;
    if (GetParam(line, cfgKeyword_AlbumPageLineSpacing,     album_song_title_line_spacing)) return;
    if (GetParam(line, cfgKeyword_NowPlayingMissingArtwork, now_playing_missing_artwork)) return;
    if (GetParam(line, cfgKeyword_AlbumPageMissingArtwork,  album_page_missing_artwork)) return;
    if (GetParam(line, cfgKeyword_NowPlayingArtworkMode,    now_playing_artwork_mode)) return;
    if (GetParam(line, cfgKeyword_AlbumPageArtworkMode,     album_page_artwork_mode)) return;
  }

  void cfgShow(const char *indent)
  {
    cfgShowEntry(indent, cfgKeyword_SkinSize                 , cfgKeywordDesc_SkinSize                 , false);
    cfgShowEntry(indent, cfgKeyword_SkinName                 , cfgKeywordDesc_SkinName                 , false);
    cfgShowEntry(indent, cfgKeyword_SkinDescription          , cfgKeywordDesc_SkinDescription          , false);
    cfgShowEntry(indent, cfgKeyword_Screenshot               , cfgKeywordDesc_Screenshot               , false);
    cfgShowEntry(indent, cfgKeyword_Database                 , cfgKeywordDesc_Database                 , false);
    cfgShowEntry(indent, cfgKeyword_MusicPath                , cfgKeywordDesc_MusicPath                , true);
    cfgShowEntry(indent, cfgKeyword_SortSongsBy              , cfgKeywordDesc_SortSongsBy              , true);
    cfgShowEntry(indent, cfgKeyword_NoDuplicates             , cfgKeywordDesc_NoDuplicates             , false);
    cfgShowEntry(indent, cfgKeyword_DuplicatesUseCredits     , cfgKeywordDesc_DuplicatesUseCredits     , false);
    cfgShowEntry(indent, cfgKeyword_SelectButtons            , cfgKeywordDesc_SelectButtons            , true);
    cfgShowEntry(indent, cfgKeyword_SelectButtonsSequence    , cfgKeywordDesc_SelectButtonsSequence    , false);
    cfgShowEntry(indent, cfgKeyword_CustomMP3Tag             , cfgKeywordDesc_CustomMP3Tag             , false);
    cfgShowEntry(indent, cfgKeyword_AutoSelect               , cfgKeywordDesc_AutoSelect               , false);
    cfgShowEntry(indent, cfgKeyword_PageJump                 , cfgKeywordDesc_PageJump                 , false);
    cfgShowEntry(indent, cfgKeyword_SelectTimeout            , cfgKeywordDesc_SelectTimeout            , false);
    cfgShowEntry(indent, cfgKeyword_SelectHoldTimeout        , cfgKeywordDesc_SelectHoldTimeout        , false);
    cfgShowEntry(indent, cfgKeyword_AutoPageTurnTime         , cfgKeywordDesc_AutoPageTurnTime         , false);
    cfgShowEntry(indent, cfgKeyword_MaxPlaylistLength        , cfgKeywordDesc_MaxPlaylistLength        , false);
    cfgShowEntry(indent, cfgKeyword_LoopPlaylist             , cfgKeywordDesc_LoopPlaylist             , false);
    cfgShowEntry(indent, cfgKeyword_AutoPlay                 , cfgKeywordDesc_AutoPlay                 , false);
    cfgShowEntry(indent, cfgKeyword_AutoPlayGap              , cfgKeywordDesc_AutoPlayGap              , false);
    cfgShowEntry(indent, cfgKeyword_AutoGenre                , cfgKeywordDesc_AutoGenre                , true);
    cfgShowEntry(indent, cfgKeyword_PlaysPerCoin1            , cfgKeywordDesc_PlaysPerCoin             , false);
    cfgShowEntry(indent, cfgKeyword_PlaysPerCoin2            , cfgKeywordDesc_PlaysPerCoin             , false);
    cfgShowEntry(indent, cfgKeyword_PlaysPerCoin3            , cfgKeywordDesc_PlaysPerCoin             , false);
    cfgShowEntry(indent, cfgKeyword_PlaysPerCoin4            , cfgKeywordDesc_PlaysPerCoin             , false);
    cfgShowEntry(indent, cfgKeyword_SongsPerPage             , cfgKeywordDesc_SongsPerPage             , false);
    cfgShowEntry(indent, cfgKeyword_PageMode                 , cfgKeywordDesc_PageMode                 , false);
    cfgShowEntry(indent, cfgKeyword_PageSize                 , cfgKeywordDesc_PageSize                 , false);
    cfgShowEntry(indent, cfgKeyword_PairSongs                , cfgKeywordDesc_PairSongs                , false);
    cfgShowEntry(indent, cfgKeyword_PageMoveStyle            , cfgKeywordDesc_PageMoveStyle            , false);
    cfgShowEntry(indent, cfgKeyword_SongDescription          , cfgKeywordDesc_SongDescription          , true);
    cfgShowEntry(indent, cfgKeyword_PairedSongDescription    , cfgKeywordDesc_PairedSongDescription    , true);
    cfgShowEntry(indent, cfgKeyword_ArtistDescription        , cfgKeywordDesc_ArtistDescription        , true);
    cfgShowEntry(indent, cfgKeyword_MatchedArtistDescription , cfgKeywordDesc_MatchedArtistDescription , true);
    cfgShowEntry(indent, cfgKeyword_ExtraDescription         , cfgKeywordDesc_ExtraDescription         , true);
    cfgShowEntry(indent, cfgKeyword_SongHistoryDepth         , cfgKeywordDesc_SongHistoryDepth         , false);
    cfgShowEntry(indent, cfgKeyword_SongLoadTime             , cfgKeywordDesc_SongLoadTime             , false);
    cfgShowEntry(indent, cfgKeyword_SongUnloadTime           , cfgKeywordDesc_SongUnloadTime           , false);
    cfgShowEntry(indent, cfgKeyword_SongText                 , cfgKeywordDesc_SongText                 , false);
    cfgShowEntry(indent, cfgKeyword_PairedSongText           , cfgKeywordDesc_PairedSongText           , false);
    cfgShowEntry(indent, cfgKeyword_ArtistText               , cfgKeywordDesc_ArtistText               , false);
    cfgShowEntry(indent, cfgKeyword_AlbumText                , cfgKeywordDesc_AlbumText                , false);
    cfgShowEntry(indent, cfgKeyword_ExtraText                , cfgKeywordDesc_ExtraText                , false);
    cfgShowEntry(indent, cfgKeyword_AlbumArtSize             , cfgKeywordDesc_AlbumArtSize             , false);
    cfgShowEntry(indent, cfgKeyword_AlbumArtOffset           , cfgKeywordDesc_AlbumArtOffset           , false);
    cfgShowEntry(indent, cfgKeyword_AlbumArtAngle            , cfgKeywordDesc_AlbumArtAngle            , false);
    cfgShowEntry(indent, cfgKeyword_AlbumPageLineSpacing     , cfgKeywordDesc_AlbumPageLineSpacing     , false);
    cfgShowEntry(indent, cfgKeyword_NowPlayingMissingArtwork , cfgKeywordDesc_NowPlayingMissingArtwork , false);
    cfgShowEntry(indent, cfgKeyword_AlbumPageMissingArtwork  , cfgKeywordDesc_AlbumPageMissingArtwork  , false);
    cfgShowEntry(indent, cfgKeyword_NowPlayingArtworkMode    , cfgKeywordDesc_NowPlayingArtworkMode    , false);
    cfgShowEntry(indent, cfgKeyword_AlbumPageArtworkMode     , cfgKeywordDesc_AlbumPageArtworkMode     , false);
  }

  bool command_line_music_path { false };
  string skin_name {};
  string skin_desc {};
  string screenshot {defaultScreenshotFilename};
  string database_filename {};
  uint32_t max_playlist_length { 100 };
  array<uint32_t, 4> plays_per_coin { {0, 0, 0, 0} };
  array<string, 4> plays_per_coin_str { {"0", "0", "0", "0" } };
  vector<string> music_path {};
  uint32_t songs_per_page { 10 };
  uints2_t skin_size {};
  uints2_t page_size {};
  page_mode_e page_mode { page_mode_e::Singles };
  pair_songs_e pair_songs { pair_songs_e::Yes };
  select_mode_e select_mode { select_mode_e::SelectCode };
  uint32_t num_pages { 0 };
  uint32_t page_jump { 5 };
  bool auto_select { false };
  bool auto_play { false };
  uint32_t auto_play_gap { 50 };
  bool no_duplicates { false };
  bool duplicates_use_credits { false };
  bool loop_playlist { false };
  bool free_play { true };
  uint32_t auto_page_turn_time { 0 };
  vector<string> select_buttons { };
  select_buttons_sequence_e select_buttons_sequence { select_buttons_sequence_e::RowCol };
  string custom_mp3_tag {  };
  vector<string> auto_genre { GenreOffStr, GenreAnyStr };
  vector<sort_songs_by_e> sort_songs_by { };
  uint32_t select_timeout { 150 };
  uint32_t select_hold_timeout { 100 };
  page_style_t page_move_style {};
  vector<pair<title_desc_e, string>> song_description {make_pair(title_desc_e::SongTitle, "")};
  vector<pair<title_desc_e, string>> paired_song_description {make_pair(title_desc_e::PairedSongTitle, "")};
  vector<pair<title_desc_e, string>> artist_description {make_pair(title_desc_e::Artist, "")};
  vector<pair<title_desc_e, string>> matched_artist_description {make_pair(title_desc_e::Artist, "")};
  vector<pair<title_desc_e, string>> extra_description {};
  uint32_t song_history_depth {};
  uint32_t song_load_time {};
  uint32_t song_unload_time {};
  text_t artist_text {};
  text_t album_text {};
  text_t extra_text {};
  text_t song_text {};
  text_t paired_song_text {};
  uints2_t album_art_size {};
  uints2_t album_art_offset {};
  uint32_t album_art_angle {};
  uint32_t album_song_title_line_spacing {};
  bitmap_t now_playing_missing_artwork {};
  bitmap_t album_page_missing_artwork {};
  artwork_mode_e now_playing_artwork_mode {artwork_mode_e::Auto};
  artwork_mode_e album_page_artwork_mode {artwork_mode_e::Auto};
  array<gpio_e, NUM_GPIO> gpio {};

private:
  bool song_description_use_default {true};
  bool paired_song_description_use_default {true};
  bool artist_description_use_default {true};
  bool matched_artist_description_use_default {true};
};

class ButtonsConfigClass : public ConfigBaseClass {

public:

  void cfgRead(string line)
  {
    if (GetParam(line, cfgKeyword_TouchMin, ConfigBaseClass::touch_min)) return;
    if (GetParam(line, cfgKeyword_TouchMax, ConfigBaseClass::touch_max)) return;

    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      if (GetParam(line, default_button[b].name , button[default_button[b].num])) return;
    }
  }

  void cfgShow(const char *indent)
  {
    cfgShowEntry(indent, cfgKeyword_TouchMin   , cfgKeywordDesc_TouchMin, false);
    cfgShowEntry(indent, cfgKeyword_TouchMax   , cfgKeywordDesc_TouchMax, false);
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      cfgShowEntry(indent, default_button[b].name, default_button[b].desc, false);
    }
    
  }

  array<button_t, NUM_BUTTONS> button {};

  ButtonsConfigClass(void)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    // set all keys to keyboard defaults...
    {
      button.at(default_button[b].num).name = default_button[b].name;
      button.at(default_button[b].num).type = input_type_e::Key;
      button.at(default_button[b].num).param.at(EVENT_PARAM_ID) = 0;
      button.at(default_button[b].num).param.at(EVENT_PARAM_VAL1) = default_button[b].key;
      button.at(default_button[b].num).param.at(EVENT_PARAM_VAL2) = 0;
      button.at(default_button[b].num).param.at(EVENT_PARAM_PRESSED) = 0;
    }
  };

};

class TouchAreasConfigClass : public ConfigBaseClass {
public:
  void cfgRead(string line)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      if (GetParam(line, default_button[b].name , touch_area[default_button[b].num])) return;
    }
  }

  void cfgShow(const char *indent)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      cfgShowEntry(indent, default_button[b].name, cfgKeyword_ButtonTouchArea, false);
    }
  }

  array<touch_area_t, NUM_BUTTONS> touch_area;

  private:
};

class FontConfigClass : public ConfigBaseClass {
public:
  void cfgRead(string line)
  {
    GetParam(line, cfgKeyword_File, font.filename);
    GetParam(line, cfgKeyword_FontHeight, font.size);
  };

  void cfgShow(const char *indent)
  {
    cfgShowEntry(indent, cfgKeyword_File, cfgKeywordDesc_FontFile, false);
    cfgShowEntry(indent, cfgKeyword_FontHeight, cfgKeywordDesc_FontHeight, false);
  }

  FontConfigClass* clone() const { return new FontConfigClass(*this); }

  font_t font {};

private:
};

class SoundConfigClass : public ConfigBaseClass {
public:
  void cfgRead(string line)
  {
    if (GetParam(line, cfgKeyword_InsertCoin,    insert_coin)) return;
    if (GetParam(line, cfgKeyword_LoadSong,      load_song)) return;
    if (GetParam(line, cfgKeyword_UnloadSong,    unload_song)) return;
    if (GetParam(line, cfgKeyword_PageMove,      page_move)) return;
    if (GetParam(line, cfgKeyword_InvalidSong,   invalid_song)) return;
    if (GetParam(line, cfgKeyword_SongVolume,    song_volume)) return;
  }
  void cfgShow(const char *indent)
  {
    cfgShowEntry(indent, cfgKeyword_InsertCoin   , cfgKeywordDesc_InsertCoin   , false);
    cfgShowEntry(indent, cfgKeyword_LoadSong     , cfgKeywordDesc_LoadSong     , false);
    cfgShowEntry(indent, cfgKeyword_UnloadSong   , cfgKeywordDesc_UnloadSong   , false);
    cfgShowEntry(indent, cfgKeyword_PageMove     , cfgKeywordDesc_PageMove     , false);
    cfgShowEntry(indent, cfgKeyword_InvalidSong  , cfgKeywordDesc_InvalidSong  , false);
    cfgShowEntry(indent, cfgKeyword_SongVolume   , cfgKeywordDesc_SongVolume   , false);
  }

  int32_t song_volume { 100 };
  sound_t insert_coin {};
  sound_t load_song {};
  sound_t unload_song {};
  sound_t page_move {};
  sound_t invalid_song {};

private:
};

class ChooserConfigClass : public ConfigBaseClass {
public:
  void cfgRead(string line)
  {
    string str;
    if (GetParam(line, cfgKeyword_Title, help_text, false)) return;
    if (GetParam(line, cfgKeyword_File, str, false))
    {
      cfg_file.push_back(str);
      if (readCfgFile() == false) // couldn't open skin file, so remove it from the list...
      {
        cfg_file.pop_back();
      }
      return;
    }
  }

  bool readCfgFile(void)
  // for the selected skin, read its cfg file to extract the skin name from it
  {
    ifstream cfgFile;
    string line;

    cfgFile.open(cfg_file.at(current_cfg), ios::in);

    if (!cfgFile.is_open())
    {
      log_file << WARNING << "Couldn't open '" << cfg_file.at(current_cfg) << "' for input" << endl;
      return false;
    }
    else
    {
      name.push_back(cfg_file.at(current_cfg));
      desc.push_back("");
      screenshot.push_back(defaultScreenshotFilename);
      
      while (getline(cfgFile, line))
      {
        if (line.empty()) continue;
        line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
        if (line.empty()) continue;
        if (line.at(0) == cfgFile_comment) continue; // comment line
        if (GetParam(line, cfgKeyword_SkinName, name.at(current_cfg), false)) continue;
        if (GetParam(line, cfgKeyword_SkinDescription, desc.at(current_cfg), false)) continue;
        if (GetParam(line, cfgKeyword_Screenshot, screenshot.at(current_cfg), false)) continue;
      }
      cfgFile.close();
      current_cfg++;
      return true;
    }
  }

  void cfgShow(const char *indent)
  {
  }

  void LoadScreenshot(void)
  {
    if (screenshot_bm)
    {
      al_destroy_bitmap(screenshot_bm);
      screenshot_bm = nullptr;
    }
    uint32_t c {current_cfg};
    string cfg_filename { cfg_file.at(c) };
    string screenshot_filename { cfg_filename.substr(0, cfg_filename.find_last_of("/")) + "/" + screenshot.at(c) };
    screenshot_bm = al_load_bitmap(screenshot_filename.c_str());
  }

  string help_text {"...choose skin with left/right, any other button to select..."};
  vector<string> cfg_file {};
  vector<string> name {};
  vector<string> desc {};
  vector<string> screenshot {};
  uint32_t current_cfg {};
  ALLEGRO_BITMAP *screenshot_bm {};
private:
};
