#pragma once

#include "fruitbox.hpp"

#define STATUS_VAR_START                      255
#define STATUS_VAR_OFFSET                     1  /* prevents null (0) character as STATUS_VAR code) */


#define STATUS_VAR_NOW_PLAYING_TITLE                (STATUS_VAR_OFFSET + 0)
#define STATUS_VAR_NOW_PLAYING_ARTIST               (STATUS_VAR_OFFSET + 1)
#define STATUS_VAR_NOW_PLAYING_ALBUM                (STATUS_VAR_OFFSET + 2)
#define STATUS_VAR_NOW_PLAYING_ALBUM_ARTIST         (STATUS_VAR_OFFSET + 3)
#define STATUS_VAR_NOW_PLAYING_TRACK_NUMBER         (STATUS_VAR_OFFSET + 4)
#define STATUS_VAR_NOW_PLAYING_YEAR                 (STATUS_VAR_OFFSET + 5)
#define STATUS_VAR_NOW_PLAYING_GENRE                (STATUS_VAR_OFFSET + 6)
#define STATUS_VAR_NOW_PLAYING_PUBLISHER            (STATUS_VAR_OFFSET + 7)
#define STATUS_VAR_NOW_PLAYING_ISRC                 (STATUS_VAR_OFFSET + 8)
#define STATUS_VAR_NOW_PLAYING_CUSTOM_TAG           (STATUS_VAR_OFFSET + 9)
#define STATUS_VAR_NOW_PLAYING_LENGTH               (STATUS_VAR_OFFSET + 10)
#define STATUS_VAR_NOW_PLAYING_ELAPSED_TIME         (STATUS_VAR_OFFSET + 11)
#define STATUS_VAR_NOW_PLAYING_TIME_REMAINING       (STATUS_VAR_OFFSET + 12)
#define STATUS_VAR_NOW_PLAYING_ARTWORK              (STATUS_VAR_OFFSET + 13)
#define STATUS_VAR_COMING_UP_NUM_SONGS              (STATUS_VAR_OFFSET + 14)
#define STATUS_VAR_COMING_UP_TOTAL_TIME             (STATUS_VAR_OFFSET + 15)
#define STATUS_VAR_COMING_UP_TITLE                  (STATUS_VAR_OFFSET + 16)
#define STATUS_VAR_COMING_UP_ARTIST                 (STATUS_VAR_OFFSET + 17)
#define STATUS_VAR_COMING_UP_ALBUM                  (STATUS_VAR_OFFSET + 18)
#define STATUS_VAR_COMING_UP_ALBUM_ARTIST           (STATUS_VAR_OFFSET + 19)
#define STATUS_VAR_COMING_UP_TRACK_NUMBER           (STATUS_VAR_OFFSET + 20)
#define STATUS_VAR_COMING_UP_YEAR                   (STATUS_VAR_OFFSET + 21)
#define STATUS_VAR_COMING_UP_GENRE                  (STATUS_VAR_OFFSET + 22)
#define STATUS_VAR_COMING_UP_PUBLISHER              (STATUS_VAR_OFFSET + 23)
#define STATUS_VAR_COMING_UP_ISRC                   (STATUS_VAR_OFFSET + 24)
#define STATUS_VAR_COMING_UP_CUSTOM_TAG             (STATUS_VAR_OFFSET + 25)
#define STATUS_VAR_COMING_UP_LENGTH                 (STATUS_VAR_OFFSET + 26)
#define STATUS_VAR_LAST_PLAYED_TITLE                (STATUS_VAR_OFFSET + 27)
#define STATUS_VAR_LAST_PLAYED_ARTIST               (STATUS_VAR_OFFSET + 28)
#define STATUS_VAR_LAST_PLAYED_ALBUM                (STATUS_VAR_OFFSET + 29)
#define STATUS_VAR_LAST_PLAYED_ALBUM_ARTIST         (STATUS_VAR_OFFSET + 30)
#define STATUS_VAR_LAST_PLAYED_TRACK_NUMBER         (STATUS_VAR_OFFSET + 31)
#define STATUS_VAR_LAST_PLAYED_YEAR                 (STATUS_VAR_OFFSET + 32)
#define STATUS_VAR_LAST_PLAYED_GENRE                (STATUS_VAR_OFFSET + 33)
#define STATUS_VAR_LAST_PLAYED_PUBLISHER            (STATUS_VAR_OFFSET + 34)
#define STATUS_VAR_LAST_PLAYED_ISRC                 (STATUS_VAR_OFFSET + 35)
#define STATUS_VAR_LAST_PLAYED_CUSTOM_TAG           (STATUS_VAR_OFFSET + 36)
#define STATUS_VAR_LAST_PLAYED_LENGTH               (STATUS_VAR_OFFSET + 37)
#define STATUS_VAR_CREDITS                          (STATUS_VAR_OFFSET + 38)
#define STATUS_VAR_AUTO_GENRE                       (STATUS_VAR_OFFSET + 39)
#define STATUS_VAR_PLAYS_PER_COIN1                  (STATUS_VAR_OFFSET + 40)
#define STATUS_VAR_PLAYS_PER_COIN2                  (STATUS_VAR_OFFSET + 41)
#define STATUS_VAR_PLAYS_PER_COIN3                  (STATUS_VAR_OFFSET + 42)
#define STATUS_VAR_PLAYS_PER_COIN4                  (STATUS_VAR_OFFSET + 43)
#define STATUS_VAR_VOLUME                           (STATUS_VAR_OFFSET + 44)
#define STATUS_VAR_SELECT_CODE                      (STATUS_VAR_OFFSET + 45)
#define STATUS_VAR_NUM_SONGS                        (STATUS_VAR_OFFSET + 46)
#define STATUS_VAR_NUM_PAGES                        (STATUS_VAR_OFFSET + 47)
#define STATUS_VAR_FIRST_VISIBLE_PAGE               (STATUS_VAR_OFFSET + 48)
#define STATUS_VAR_LAST_VISIBLE_PAGE                (STATUS_VAR_OFFSET + 49)
#define STATUS_VAR_SET_GPIO_00_HI                   (STATUS_VAR_OFFSET + 50)
#define STATUS_VAR_SET_GPIO_00_LO                   (STATUS_VAR_OFFSET + 51)
#define STATUS_VAR_SET_GPIO_01_HI                   (STATUS_VAR_OFFSET + 52)
#define STATUS_VAR_SET_GPIO_01_LO                   (STATUS_VAR_OFFSET + 53)
#define STATUS_VAR_SET_GPIO_02_HI                   (STATUS_VAR_OFFSET + 54)
#define STATUS_VAR_SET_GPIO_02_LO                   (STATUS_VAR_OFFSET + 55)
#define STATUS_VAR_SET_GPIO_03_HI                   (STATUS_VAR_OFFSET + 56)
#define STATUS_VAR_SET_GPIO_03_LO                   (STATUS_VAR_OFFSET + 57)
#define STATUS_VAR_SET_GPIO_04_HI                   (STATUS_VAR_OFFSET + 58)
#define STATUS_VAR_SET_GPIO_04_LO                   (STATUS_VAR_OFFSET + 59)
#define STATUS_VAR_SET_GPIO_05_HI                   (STATUS_VAR_OFFSET + 60)
#define STATUS_VAR_SET_GPIO_05_LO                   (STATUS_VAR_OFFSET + 61)
#define STATUS_VAR_SET_GPIO_06_HI                   (STATUS_VAR_OFFSET + 62)
#define STATUS_VAR_SET_GPIO_06_LO                   (STATUS_VAR_OFFSET + 63)
#define STATUS_VAR_SET_GPIO_07_HI                   (STATUS_VAR_OFFSET + 64)
#define STATUS_VAR_SET_GPIO_07_LO                   (STATUS_VAR_OFFSET + 65)
#define STATUS_VAR_SET_GPIO_08_HI                   (STATUS_VAR_OFFSET + 66)
#define STATUS_VAR_SET_GPIO_08_LO                   (STATUS_VAR_OFFSET + 67)
#define STATUS_VAR_SET_GPIO_09_HI                   (STATUS_VAR_OFFSET + 68)
#define STATUS_VAR_SET_GPIO_09_LO                   (STATUS_VAR_OFFSET + 69)
#define STATUS_VAR_SET_GPIO_10_HI                   (STATUS_VAR_OFFSET + 70)
#define STATUS_VAR_SET_GPIO_10_LO                   (STATUS_VAR_OFFSET + 71)
#define STATUS_VAR_SET_GPIO_11_HI                   (STATUS_VAR_OFFSET + 72)
#define STATUS_VAR_SET_GPIO_11_LO                   (STATUS_VAR_OFFSET + 73)
#define STATUS_VAR_SET_GPIO_12_HI                   (STATUS_VAR_OFFSET + 74)
#define STATUS_VAR_SET_GPIO_12_LO                   (STATUS_VAR_OFFSET + 75)
#define STATUS_VAR_SET_GPIO_13_HI                   (STATUS_VAR_OFFSET + 76)
#define STATUS_VAR_SET_GPIO_13_LO                   (STATUS_VAR_OFFSET + 77)
#define STATUS_VAR_SET_GPIO_14_HI                   (STATUS_VAR_OFFSET + 78)
#define STATUS_VAR_SET_GPIO_14_LO                   (STATUS_VAR_OFFSET + 79)
#define STATUS_VAR_SET_GPIO_15_HI                   (STATUS_VAR_OFFSET + 80)
#define STATUS_VAR_SET_GPIO_15_LO                   (STATUS_VAR_OFFSET + 81)
#define STATUS_VAR_SET_GPIO_16_HI                   (STATUS_VAR_OFFSET + 82)
#define STATUS_VAR_SET_GPIO_16_LO                   (STATUS_VAR_OFFSET + 83)
#define STATUS_VAR_SET_GPIO_17_HI                   (STATUS_VAR_OFFSET + 84)
#define STATUS_VAR_SET_GPIO_17_LO                   (STATUS_VAR_OFFSET + 85)
#define STATUS_VAR_SET_GPIO_18_HI                   (STATUS_VAR_OFFSET + 86)
#define STATUS_VAR_SET_GPIO_18_LO                   (STATUS_VAR_OFFSET + 87)
#define STATUS_VAR_SET_GPIO_19_HI                   (STATUS_VAR_OFFSET + 88)
#define STATUS_VAR_SET_GPIO_19_LO                   (STATUS_VAR_OFFSET + 89)
#define STATUS_VAR_SET_GPIO_20_HI                   (STATUS_VAR_OFFSET + 90)
#define STATUS_VAR_SET_GPIO_20_LO                   (STATUS_VAR_OFFSET + 91)
#define STATUS_VAR_SET_GPIO_21_HI                   (STATUS_VAR_OFFSET + 92)
#define STATUS_VAR_SET_GPIO_21_LO                   (STATUS_VAR_OFFSET + 93)
#define STATUS_VAR_SET_GPIO_22_HI                   (STATUS_VAR_OFFSET + 94)
#define STATUS_VAR_SET_GPIO_22_LO                   (STATUS_VAR_OFFSET + 95)
#define STATUS_VAR_SET_GPIO_23_HI                   (STATUS_VAR_OFFSET + 96)
#define STATUS_VAR_SET_GPIO_23_LO                   (STATUS_VAR_OFFSET + 97)
#define STATUS_VAR_SET_GPIO_24_HI                   (STATUS_VAR_OFFSET + 98)
#define STATUS_VAR_SET_GPIO_24_LO                   (STATUS_VAR_OFFSET + 99)
#define STATUS_VAR_SET_GPIO_25_HI                   (STATUS_VAR_OFFSET + 100)
#define STATUS_VAR_SET_GPIO_25_LO                   (STATUS_VAR_OFFSET + 101)
#define STATUS_VAR_SET_GPIO_26_HI                   (STATUS_VAR_OFFSET + 102)
#define STATUS_VAR_SET_GPIO_26_LO                   (STATUS_VAR_OFFSET + 103)
#define STATUS_VAR_SET_GPIO_27_HI                   (STATUS_VAR_OFFSET + 104)
#define STATUS_VAR_SET_GPIO_27_LO                   (STATUS_VAR_OFFSET + 105)
#define STATUS_VAR_SET_FLAG_1_HI                    (STATUS_VAR_OFFSET + 106)
#define STATUS_VAR_SET_FLAG_1_LO                    (STATUS_VAR_OFFSET + 107)
#define STATUS_VAR_SET_FLAG_2_HI                    (STATUS_VAR_OFFSET + 108)
#define STATUS_VAR_SET_FLAG_2_LO                    (STATUS_VAR_OFFSET + 109)
#define STATUS_VAR_SET_FLAG_3_HI                    (STATUS_VAR_OFFSET + 110)
#define STATUS_VAR_SET_FLAG_3_LO                    (STATUS_VAR_OFFSET + 111)
#define STATUS_VAR_SET_FLAG_4_HI                    (STATUS_VAR_OFFSET + 112)
#define STATUS_VAR_SET_FLAG_4_LO                    (STATUS_VAR_OFFSET + 113)
#define STATUS_VAR_DRAW_BITMAP                      (STATUS_VAR_OFFSET + 114)
#define STATUS_VAR_DRAW_RANDOM_BITMAP               (STATUS_VAR_OFFSET + 115)
#define STATUS_VAR_UNDRAW_BITMAP                    (STATUS_VAR_OFFSET + 116)
#define STATUS_VAR_DRAW_VIDEO                       (STATUS_VAR_OFFSET + 117)
#define STATUS_VAR_UNDRAW_VIDEO                     (STATUS_VAR_OFFSET + 118)
#define STATUS_VAR_START_VIDEO                      (STATUS_VAR_OFFSET + 119)
#define STATUS_VAR_STOP_VIDEO                       (STATUS_VAR_OFFSET + 120)
#define STATUS_VAR_PAUSE_VIDEO                      (STATUS_VAR_OFFSET + 121)
#define STATUS_VAR_UNPAUSE_VIDEO                    (STATUS_VAR_OFFSET + 122)
#define STATUS_VAR_IF_FREE_PLAY                     (STATUS_VAR_OFFSET + 123)
#define STATUS_VAR_IF_NOT_FREE_PLAY                 (STATUS_VAR_OFFSET + 124)
#define STATUS_VAR_IF_NO_CREDITS                    (STATUS_VAR_OFFSET + 125)
#define STATUS_VAR_IF_ANY_CREDITS                   (STATUS_VAR_OFFSET + 126)
#define STATUS_VAR_IF_SONG_PLAYING                  (STATUS_VAR_OFFSET + 127)
#define STATUS_VAR_IF_NOT_SONG_PLAYING              (STATUS_VAR_OFFSET + 128)
#define STATUS_VAR_IF_VIDEO_SONG_PLAYING            (STATUS_VAR_OFFSET + 129)
#define STATUS_VAR_IF_NOT_VIDEO_SONG_PLAYING        (STATUS_VAR_OFFSET + 130)
// #define STATUS_VAR_IF_RADIO_PLAYING                 (STATUS_VAR_OFFSET + 131)
// #define STATUS_VAR_IF_NOT_RADIO_PLAYING             (STATUS_VAR_OFFSET + 132)
#define STATUS_VAR_IF_SONG_LOADING                  (STATUS_VAR_OFFSET + 133 - 2)
#define STATUS_VAR_IF_NOT_SONG_LOADING              (STATUS_VAR_OFFSET + 134 - 2)
#define STATUS_VAR_IF_SONG_UNLOADING                (STATUS_VAR_OFFSET + 135 - 2)
#define STATUS_VAR_IF_NOT_SONG_UNLOADING            (STATUS_VAR_OFFSET + 136 - 2)
#define STATUS_VAR_IF_ANY_COMING_UP                 (STATUS_VAR_OFFSET + 137 - 2)
#define STATUS_VAR_IF_NONE_COMING_UP                (STATUS_VAR_OFFSET + 138 - 2)
#define STATUS_VAR_IF_SONG_COMING_UP                (STATUS_VAR_OFFSET + 139 - 2)
#define STATUS_VAR_IF_AUTO_PLAY_MODE                (STATUS_VAR_OFFSET + 140 - 2)
#define STATUS_VAR_IF_NOT_AUTO_PLAY_MODE            (STATUS_VAR_OFFSET + 141 - 2)
#define STATUS_VAR_IF_LOOP_MODE                     (STATUS_VAR_OFFSET + 142 - 2)
#define STATUS_VAR_IF_NOT_LOOP_MODE                 (STATUS_VAR_OFFSET + 143 - 2)
#define STATUS_VAR_IF_TIMER_HI                      (STATUS_VAR_OFFSET + 144 - 2)
#define STATUS_VAR_IF_TIMER_LO                      (STATUS_VAR_OFFSET + 145 - 2)
#define STATUS_VAR_IF_TIMER_TICK                    (STATUS_VAR_OFFSET + 146 - 2)
#define STATUS_VAR_IF_MUTE                          (STATUS_VAR_OFFSET + 147 - 2)
#define STATUS_VAR_IF_NOT_MUTE                      (STATUS_VAR_OFFSET + 148 - 2)
#define STATUS_VAR_IF_PAGE_MOVING                   (STATUS_VAR_OFFSET + 149 - 2)
#define STATUS_VAR_IF_NOT_PAGE_MOVING               (STATUS_VAR_OFFSET + 150 - 2)
#define STATUS_VAR_IF_PLAYQUEUE_EMPTY               (STATUS_VAR_OFFSET + 151 - 2)
#define STATUS_VAR_IF_NOT_PLAYQUEUE_EMPTY           (STATUS_VAR_OFFSET + 152 - 2)
#define STATUS_VAR_IF_PLAYQUEUE_FULL                (STATUS_VAR_OFFSET + 153 - 2)
#define STATUS_VAR_IF_NOT_PLAYQUEUE_FULL            (STATUS_VAR_OFFSET + 154 - 2)
#define STATUS_VAR_IF_STEREO                        (STATUS_VAR_OFFSET + 155 - 2)
#define STATUS_VAR_IF_NOT_STEREO                    (STATUS_VAR_OFFSET + 156 - 2)
#define STATUS_VAR_IF_PAUSED                        (STATUS_VAR_OFFSET + 157 - 2)
#define STATUS_VAR_IF_NOT_PAUSED                    (STATUS_VAR_OFFSET + 158 - 2)
#define STATUS_VAR_IF_INVALID_CHOICE                (STATUS_VAR_OFFSET + 159 - 2)
#define STATUS_VAR_IF_NOT_INVALID_CHOICE            (STATUS_VAR_OFFSET + 160 - 2)
#define STATUS_VAR_IF_FLAG_HI                       (STATUS_VAR_OFFSET + 161 - 2)
#define STATUS_VAR_IF_FLAG_LO                       (STATUS_VAR_OFFSET + 162 - 2)
//                                                                       163 - 2 // placemarkers for FLAGS 2..4
//                                                                       164 - 2
//                                                                       165 - 2
//                                                                       166 - 2
//                                                                       167 - 2
//                                                                       168 - 2
#define STATUS_VAR_IF_BUTTON_PRESSED                (STATUS_VAR_OFFSET + 169 - 2)
#define STATUS_VAR_IF_NOT_BUTTON_PRESSED            (STATUS_VAR_OFFSET + 170 - 2)
#define STATUS_VAR_NO_DRAW                          (STATUS_VAR_OFFSET + 171 - 2)
#define STATUS_VAR_END_IF                           (STATUS_VAR_OFFSET + 172 - 2)

const char STAT_DESC_NULL[] = {""};
const char STAT_DESC_NPTI[] = {"The name of the song which is currently playing"};
const char STAT_DESC_NPAR[] = {"The name of the artist of the song which is currently playing"};
const char STAT_DESC_NPAL[] = {"The name of the album of the song which is currently playing"};
const char STAT_DESC_NPAA[] = {"The name of the album artist of the song which is currently playing"};
const char STAT_DESC_NPTN[] = {"The track number of the song which is currently playing"};
const char STAT_DESC_NPYR[] = {"The year of the song which is currently playing"};
const char STAT_DESC_NPGN[] = {"The genre of the song which is currently playing"};
const char STAT_DESC_NPPU[] = {"The publisher of the song which is currently playing"};
const char STAT_DESC_NPIS[] = {"The ISRC of the song which is currently playing"};
const char STAT_DESC_NPCT[] = {"The custom MP3 tag of the song which is currently playing"};
const char STAT_DESC_NPLE[] = {"The length in mm:ss of the currently playing song"};
const char STAT_DESC_NPET[] = {"The elapsed time in mm:ss of the currently playing song"};
const char STAT_DESC_NPRT[] = {"The remaining time in mm:ss of the currently playing song"};
const char STAT_DESC_NPAT[] = {"The cover artwork of the currently playing song.  "
                              "The artwork will occupy the entire status box, and is drawn before any text.  " \
                              "The actual artwork displayed will depend upon the value of the [general] 'ArtworkMode' configuration setting."};
const char STAT_DESC_CUNS[] = {"The number of songs coming up in the play queue"};
const char STAT_DESC_CUTT[] = {"The total play time in hh:mm:ss of the songs in the play queue"};
const char STAT_DESC_CUTI[] = {"The title of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAL[] = {"The album name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAR[] = {"The artist name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAA[] = {"The album artist name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUTN[] = {"The track number a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUYR[] = {"The year of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUGN[] = {"The genre of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUPU[] = {"The publisher of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUIS[] = {"The ISRC of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUCT[] = {"The custom MP3 tag of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CULE[] = {"The length in mm:ss of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};

const char STAT_DESC_LPTI[] = {"The name of the song which was last played"};
const char STAT_DESC_LPAR[] = {"The name of the artist of the song which was last played"};
const char STAT_DESC_LPAL[] = {"The name of the album of the song which was last played"};
const char STAT_DESC_LPAA[] = {"The name of the album artist of the song which was last played"};
const char STAT_DESC_LPTN[] = {"The track number of the song which was last played"};
const char STAT_DESC_LPYR[] = {"The year of the song which was last played"};
const char STAT_DESC_LPGN[] = {"The genre of the song which was last played"};
const char STAT_DESC_LPPU[] = {"The publisher of the song which was last played"};
const char STAT_DESC_LPIS[] = {"The ISRC of the song which was last played"};
const char STAT_DESC_LPCT[] = {"The custom MP3 tag of the song which was last played"};
const char STAT_DESC_LPLE[] = {"The length in mm:ss of the song which was last played"};

const char STAT_DESC_CRED[] = {"The number of credits"};
const char STAT_DESC_AUTG[] = {"The name of the current AutoGenre that AutoPlay will select a random song from"};
const char STAT_DESC_PPCR[] = {"The number of plays per coin"};
const char STAT_DESC_VOLU[] = {"The song volume"};
const char STAT_DESC_SELC[] = {"The select code"};
const char STAT_DESC_NSON[] = {"The total number of songs in the database"};
const char STAT_DESC_NPAG[] = {"The total number of pages in the jukebox"};
const char STAT_DESC_FVPA[] = {"The number of the first page visible on the display"};
const char STAT_DESC_LVPA[] = {"The number of the last page visible on the display"};
const char STAT_DESC_GPHI[] = {"Sets the specified GPIO output high"};
const char STAT_DESC_GPLO[] = {"Sets the specified GPIO output low"};
const char STAT_DESC_FGHI[] = {"Sets the specified status flag high"};
const char STAT_DESC_FGLO[] = {"Sets the specified status flag low"};
const char STAT_DESC_BMPX[] = {"Draw user defined bitmaps, as specified by the Bitmap parameter.  " \
                               "The bitmap will occupy the entire status box, and is drawn after any text.  " \
                               "If multiple bitmaps are defined, they will be drawn in turn, each time the " \
                               "$DRAW_BITMAP keyword is executed.  Bitmaps remain visible until " \
                               "a $UNDRAW_BITMAP command is executed."};
const char STAT_DESC_BMPR[] = {"Draw a random user defined bitmap, chosen from the specified Bitmap parameters."};
const char STAT_DESC_BMPU[] = {"Undraw the bitmap"};
const char STAT_DESC_VIDX[] = {"Draw the video"};
const char STAT_DESC_VIDU[] = {"Undraw the video"};
const char STAT_DESC_STRV[] = {"Start video playing"};
const char STAT_DESC_STPV[] = {"Stop video playing"};
const char STAT_DESC_PAUV[] = {"Pause video playing"};
const char STAT_DESC_UNPV[] = {"Un-pause video playing"};
const char STAT_DESC_IFSM[] = {"Activates the text following it if the secret menu enabled"};
const char STAT_DESC_INSM[] = {"Activates the text following it if the secret menu disabled"};
const char STAT_DESC_IFFP[] = {"Activates the text following it if Free Play mode is enabled"};
const char STAT_DESC_INFP[] = {"Activates the text following it if Free Play mode is disabled"};
const char STAT_DESC_IFNC[] = {"Activates the text following it if no credits are available"};
const char STAT_DESC_IFCA[] = {"Activates the text following it if credits are available"};
const char STAT_DESC_IFPL[] = {"Activates the text following it if a song is currently playing"};
const char STAT_DESC_IFNP[] = {"Activates the text following it if no song is currently playing"};
const char STAT_DESC_IFSV[] = {"Activates the text following it if the song is currently playing is a video"};
const char STAT_DESC_IFNV[] = {"Activates the text following it if the song is currently playing is not a video"};
const char STAT_DESC_IFSR[] = {"Activates the text following it if the song is currently playing is a radio (http streaming) song"};
const char STAT_DESC_IFNR[] = {"Activates the text following it if the song is currently playing is not a radio (http streaming) song"};
const char STAT_DESC_IFLO[] = {"Activates the text following it if a song is currently loading"};
const char STAT_DESC_IFNL[] = {"Activates the text following it if no song is currently loading"};
const char STAT_DESC_IFUL[] = {"Activates the text following it if a song is currently unloading"};
const char STAT_DESC_IFNU[] = {"Activates the text following it if no song is currently unloading"};
const char STAT_DESC_IFAC[] = {"Activates the text following it if any songs are coming up"};
const char STAT_DESC_INCU[] = {"Activates the text following it if no songs are coming up"};
const char STAT_DESC_ISCU[] = {"Activates the text following it if there is another song in the play queue.  This is different to the $IF_ANY_COMING_UP " \
                               "keyword because it refers to the next coming up entry rather than the complete play queue"};
const char STAT_DESC_IFRM[] = {"Activates the text following it if Auto Play mode is enabled"};
const char STAT_DESC_INRM[] = {"Activates the text following it if Auto Play mode is disabled"};
const char STAT_DESC_IFLM[] = {"Activates the text following it if Loop mode is enabled"};
const char STAT_DESC_INLM[] = {"Activates the text following it if Loop mode is disabled"};
const char STAT_DESC_IFTY[] = {"Activates the text following it if the status timer is high.  " \
                               "The value of 'TimerTickPeriod' for the status object in the configuration file determines the rate at which the timer toggles between high and low.  " \
                               "i.e. TimerTickPeriod = 30 means the timer will be high for 30 video frames, then low for 30 video frames, repeating indefinitely"};
const char STAT_DESC_IFTN[] = {"Activates the text following it if the status timer is low"};
const char STAT_DESC_IFTT[] = {"Activates the text following it when the status timer ticks (each tick occurs every TimerTickPeriod video frames"};
const char STAT_DESC_IFPM[] = {"Activates the text following it when the song pages are moving"};
const char STAT_DESC_IFPN[] = {"Activates the text following it when the song pages are not moving"};
const char STAT_DESC_IFPE[] = {"Activates the text following it if the play queue is empty\n (includes currently playing song)"};
const char STAT_DESC_INPE[] = {"Activates the text following it if the play queue is not empty\n (includes currently playing song)"};
const char STAT_DESC_IFPF[] = {"Activates the text following it if the play queue is full\n (includes currently playing song)"};
const char STAT_DESC_INPF[] = {"Activates the text following it if the play queue is not full\n (includes currently playing song)"};
const char STAT_DESC_IFST[] = {"Activates the text following it if the current song is stereo"};
const char STAT_DESC_INST[] = {"Activates the text following it if the current song is not stereo"};
const char STAT_DESC_IFPA[] = {"Activates the text following it if the current song is paused"};
const char STAT_DESC_INPA[] = {"Activates the text following it if the current song is not paused"};
const char STAT_DESC_IFIC[] = {"Activates the text following it if the last song selection was invalid"};
const char STAT_DESC_INIC[] = {"Activates the text following it if the last song selection was not invalid"};
const char STAT_DESC_IFLH[] = {"Activates the text following it if the specified status flag is high"};
const char STAT_DESC_IFLL[] = {"Activates the text following it if the specified status flag is low"};
const char STAT_DESC_IFMU[] = {"Activates the text following it when the song volume is muted"};
const char STAT_DESC_IFNM[] = {"Activates the text following it when the song volume is not muted"};
const char STAT_DESC_ENIF[] = {"Marks the end of a text section playing by the preceding $IF_"};
const char STAT_DESC_ENND[] = {"Supresses drawing of the status object"};
const char STAT_DESC_IFBP[] = {"Activates the text following it if the specified button is pressed"};
const char STAT_DESC_INBP[] = {"Activates the text following it if the specified button is not pressed"};


class StatusDisplayClass : public DisplayBaseClass {
public:

  void init(const uints2_t sze, const uint32_t emsk);

  void update(const uint32_t event) override;

  void cfgRead(string line) {
    string str {};
    bitmap_t bm {};
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Contents,        desc_name)) return;
    if (GetParam(line, cfgKeyword_Output,          output_filename)) return;
    if (GetParam(line, cfgKeyword_Text,            text)) return;
    if (GetParam(line, cfgKeyword_LineSpacing,     line_spacing)) return;
    if (GetParam(line, cfgKeyword_LoopVideo,       loop_video)) return;
    if (GetParam(line, cfgKeyword_TimerTickPeriod, timer_tick_period)) return;
    if (GetParam(line, cfgKeyword_BitmapDirectory, bitmap_directory)) return;
    if (GetParam(line, cfgKeyword_Bitmap,          bm)) {
      bitmap_list.push_back(bm.handle);
      return;
    }
    if (GetParam(line, cfgKeyword_Video, video))
    {
      num_sound_channels++;
      return;
    }
    return;
  }

  void cfgShow(const char *indent) {
    DisplayBaseClass::cfgShow(indent);
    cfgShowEntry(indent, cfgKeyword_Contents        , cfgKeywordDesc_Contents          , false);
    cfgShowEntry(indent, cfgKeyword_Output          , cfgKeywordDesc_Output            , false);
    cfgShowEntry(indent, cfgKeyword_Text            , cfgKeywordDesc_Text              , false);
    cfgShowEntry(indent, cfgKeyword_LineSpacing     , cfgKeywordDesc_StatusLineSpacing , false);
    cfgShowEntry(indent, cfgKeyword_LoopVideo       , cfgKeywordDesc_LoopVideo         , false);
    cfgShowEntry(indent, cfgKeyword_TimerTickPeriod , cfgKeywordDesc_TimerTickPeriod   , false);
    cfgShowEntry(indent, cfgKeyword_BitmapDirectory , cfgKeywordDesc_BitmapDirectory   , false);
    cfgShowEntry(indent, cfgKeyword_Bitmap          , cfgKeywordDesc_Bitmap            , true);
    cfgShowEntry(indent, cfgKeyword_Video           , cfgKeywordDesc_Video            , true);
  }

  StatusDisplayClass* clone() const { return new StatusDisplayClass(*this); }

  void renew(void) {
    size.x = size.y = 0;
    bitmap_list.clear(); // ensure no bitmaps from a previous status object are included in the next status objects
    output_filename.clear(); // ensure no output_filename from a previous status object is defined in the next status objects
    video.handle = nullptr;
    bitmap_directory.clear();
  };

  static int BitmapSearch(const char *path, const struct stat *sptr, int type);

  static int32_t if_song_coming_ups;
  static int32_t coming_up_song_title;
  static int32_t coming_up_song_artist;
  static int32_t coming_up_song_album;
  static int32_t coming_up_song_album_artist;
  static int32_t coming_up_song_track_number;
  static int32_t coming_up_song_year;
  static int32_t coming_up_song_genre;
  static int32_t coming_up_song_publisher;
  static int32_t coming_up_song_isrc;
  static int32_t coming_up_song_custom_tag;
  static int32_t coming_up_song_length;
  static uint32_t num_sound_channels;

  static bool funcNowPlayingTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingYear(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayinglength(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingElapsedTime(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingTimeRemaining(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingArtwork(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpNumSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTotalTime(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpYear(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpLength(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedYear(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedlength(StatusDisplayClass *s, unsigned char param);
  static bool funcCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcAutoGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcPlaysPerCoin(StatusDisplayClass *s, unsigned char param);
  static bool funcVolume(StatusDisplayClass *s, unsigned char param);
  static bool funcSelectCode(StatusDisplayClass *s, unsigned char param);
  static bool funcNumSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcNumPages(StatusDisplayClass *s, unsigned char param);
  static bool funcFirstVisiblePage(StatusDisplayClass *s, unsigned char param);
  static bool funcLastVisiblePage(StatusDisplayClass *s, unsigned char param);
  static bool funcGPIOSetPinHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcGPIOSetPinLow(StatusDisplayClass *s, unsigned char param);
  static bool funcSetFlagLow(StatusDisplayClass *s, unsigned char param);
  static bool funcSetFlagHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawRandomBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcUndrawBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcUndrawVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcStartVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcStopVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcPauseVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcUnPauseVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFreeplay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotFreeplay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNoCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAnyCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfVideoSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotVideoSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfRadioSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotRadioSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongLoading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongLoading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongUnloading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongUnloading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAnyComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNoneComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAutoPlayMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotAutoPlayMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfLoopMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotLoopMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerHi(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerLo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerTick(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPageMoving(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPageNotMoving(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPlayQueueEmpty(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPlayQueueEmpty(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPlayQueueFull(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPlayQueueFull(StatusDisplayClass *s, unsigned char param);
  static bool funcIfStereo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotStereo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPaused(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPaused(StatusDisplayClass *s, unsigned char param);
  static bool funcIfInvalidChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotInvalidChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFlagHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFlagLow(StatusDisplayClass *s, unsigned char param);
  static bool funcIfMute(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotMute(StatusDisplayClass *s, unsigned char param);
  static bool funcIfButtonPressed(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotButtonPressed(StatusDisplayClass *s, unsigned char param);
  static bool funcEndIf(StatusDisplayClass *s, unsigned char param);
  static bool funcNoDraw(StatusDisplayClass *s, unsigned char param);

  bool SkipToEndIf(void);
  string *var_str {};
  bitmap_t artwork_bitmap {};

  string StrMS(uint32_t ms) {
    stringstream s;
    s << setfill('0') << setw(2) << SecondsToMinutes(ms) << ":"
      << setfill('0') << setw(2) << SecondsToSeconds(ms);
    return s.str();
  }
  uint32_t timer_hi {};
  uint32_t timer_ticks {};
  string coming_up_song_length_str {};
  vector<ALLEGRO_BITMAP*> bitmap_list {};
  int32_t bitmap_idx {};

  private:
  bool draw_bitmap { false };
  bool draw_video { false };
  bool loop_video { false };
  string output_filename {};
  string desc_name {};
  text_t text {};
  uint32_t line_spacing {};
  uint32_t timer_tick_period { 1 };
  string bitmap_directory {};
  static vector<string> static_bitmap_name;
  vector<string> bitmap_name;
  vector<string> lines {};

  string *line {};
  uint32_t line_pos {};
  video_t video {};
};

struct status_vars_t {
  const string name;
  const string desc;
  unsigned char code;
  unsigned char code_param;
  bool is_if;
  bool (*func)(StatusDisplayClass *s, unsigned char param);
  int32_t event_bit;
};



///////////////////////////////////////////////////////////////////////////////

const vector <status_vars_t> (status_vars) {
  {"$NOW_PLAYING_TITLE",                  STAT_DESC_NPTI, STATUS_VAR_NOW_PLAYING_TITLE,                0xff,                       false, &StatusDisplayClass::funcNowPlayingTitle,         StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_ARTIST",                 STAT_DESC_NPAR, STATUS_VAR_NOW_PLAYING_ARTIST,               0xff,                       false, &StatusDisplayClass::funcNowPlayingArtist,        StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_ALBUM",                  STAT_DESC_NPAL, STATUS_VAR_NOW_PLAYING_ALBUM,                0xff,                       false, &StatusDisplayClass::funcNowPlayingAlbum,         StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_ALB_ARTIST",             STAT_DESC_NPAA, STATUS_VAR_NOW_PLAYING_ALBUM_ARTIST,         0xff,                       false, &StatusDisplayClass::funcNowPlayingAlbumArtist,   StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_TRACK_NUMBER",           STAT_DESC_NPTN, STATUS_VAR_NOW_PLAYING_TRACK_NUMBER,         0xff,                       false, &StatusDisplayClass::funcNowPlayingTrackNumber,   StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_YEAR",                   STAT_DESC_NPYR, STATUS_VAR_NOW_PLAYING_YEAR,                 0xff,                       false, &StatusDisplayClass::funcNowPlayingYear,          StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_GENRE",                  STAT_DESC_NPGN, STATUS_VAR_NOW_PLAYING_GENRE,                0xff,                       false, &StatusDisplayClass::funcNowPlayingGenre,         StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_PUBLISHER",              STAT_DESC_NPPU, STATUS_VAR_NOW_PLAYING_PUBLISHER,            0xff,                       false, &StatusDisplayClass::funcNowPlayingPublisher,     StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_ISRC",                   STAT_DESC_NPIS, STATUS_VAR_NOW_PLAYING_ISRC,                 0xff,                       false, &StatusDisplayClass::funcNowPlayingISRC,          StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_CUSTOM_TAG",             STAT_DESC_NPCT, STATUS_VAR_NOW_PLAYING_CUSTOM_TAG,           0xff,                       false, &StatusDisplayClass::funcNowPlayingCustomTag,     StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_LENGTH",                 STAT_DESC_NPLE, STATUS_VAR_NOW_PLAYING_LENGTH,               0xff,                       false, &StatusDisplayClass::funcNowPlayinglength,        StatusEvent_songStart | StatusEvent_songStop},
  {"$NOW_PLAYING_ELAPSED_TIME",           STAT_DESC_NPET, STATUS_VAR_NOW_PLAYING_ELAPSED_TIME,         0xff,                       false, &StatusDisplayClass::funcNowPlayingElapsedTime,   StatusEvent_oneSecondChange},
  {"$NOW_PLAYING_TIME_REMAINING",         STAT_DESC_NPRT, STATUS_VAR_NOW_PLAYING_TIME_REMAINING,       0xff,                       false, &StatusDisplayClass::funcNowPlayingTimeRemaining, StatusEvent_oneSecondChange},
  {"$NOW_PLAYING_ARTWORK",                STAT_DESC_NPAT, STATUS_VAR_NOW_PLAYING_ARTWORK,              0xff,                       false, &StatusDisplayClass::funcNowPlayingArtwork,       StatusEvent_newArtwork | StatusEvent_playqueueChange},
  {"$COMING_UP_NUM_SONGS",                STAT_DESC_CUNS, STATUS_VAR_COMING_UP_NUM_SONGS,              0xff,                       false, &StatusDisplayClass::funcComingUpNumSongs,        StatusEvent_playqueueChange},
  {"$COMING_UP_TOTAL_TIME",               STAT_DESC_CUTT, STATUS_VAR_COMING_UP_TOTAL_TIME,             0xff,                       false, &StatusDisplayClass::funcComingUpTotalTime,       StatusEvent_playqueueChange},
  {"$COMING_UP_TITLE",                    STAT_DESC_CUTI, STATUS_VAR_COMING_UP_TITLE,                  0xff,                       false, &StatusDisplayClass::funcComingUpTitle,           StatusEvent_playqueueChange},
  {"$COMING_UP_ARTIST",                   STAT_DESC_CUAR, STATUS_VAR_COMING_UP_ARTIST,                 0xff,                       false, &StatusDisplayClass::funcComingUpArtist,          StatusEvent_playqueueChange},
  {"$COMING_UP_ALBUM",                    STAT_DESC_CUAL, STATUS_VAR_COMING_UP_ALBUM,                  0xff,                       false, &StatusDisplayClass::funcComingUpAlbum,           StatusEvent_playqueueChange},
  {"$COMING_UP_ALB_ARTIST",               STAT_DESC_CUAA, STATUS_VAR_COMING_UP_ALBUM_ARTIST,           0xff,                       false, &StatusDisplayClass::funcComingUpAlbumArtist,     StatusEvent_playqueueChange},
  {"$COMING_UP_TRACK_NUMBER",             STAT_DESC_CUTN, STATUS_VAR_COMING_UP_TRACK_NUMBER,           0xff,                       false, &StatusDisplayClass::funcComingUpTrackNumber,     StatusEvent_playqueueChange},
  {"$COMING_UP_YEAR",                     STAT_DESC_CUYR, STATUS_VAR_COMING_UP_YEAR,                   0xff,                       false, &StatusDisplayClass::funcComingUpYear,            StatusEvent_playqueueChange},
  {"$COMING_UP_GENRE",                    STAT_DESC_CUGN, STATUS_VAR_COMING_UP_GENRE,                  0xff,                       false, &StatusDisplayClass::funcComingUpGenre,           StatusEvent_playqueueChange},
  {"$COMING_UP_PUBLISHER",                STAT_DESC_CUPU, STATUS_VAR_COMING_UP_PUBLISHER,              0xff,                       false, &StatusDisplayClass::funcComingUpPublisher,       StatusEvent_playqueueChange},
  {"$COMING_UP_ISRC",                     STAT_DESC_CUIS, STATUS_VAR_COMING_UP_ISRC,                   0xff,                       false, &StatusDisplayClass::funcComingUpISRC,            StatusEvent_playqueueChange},
  {"$COMING_UP_CUSTOM_TAG",               STAT_DESC_CUCT, STATUS_VAR_COMING_UP_CUSTOM_TAG,             0xff,                       false, &StatusDisplayClass::funcComingUpCustomTag,       StatusEvent_playqueueChange},
  {"$COMING_UP_LENGTH",                   STAT_DESC_CULE, STATUS_VAR_COMING_UP_LENGTH,                 0xff,                       false, &StatusDisplayClass::funcComingUpLength,          StatusEvent_playqueueChange},
  {"$LAST_PLAYED_TITLE",                  STAT_DESC_LPTI, STATUS_VAR_LAST_PLAYED_TITLE,                0xff,                       false, &StatusDisplayClass::funcLastPlayedTitle,         StatusEvent_playqueueChange},
  {"$LAST_PLAYED_ARTIST",                 STAT_DESC_LPAR, STATUS_VAR_LAST_PLAYED_ARTIST,               0xff,                       false, &StatusDisplayClass::funcLastPlayedArtist,        StatusEvent_playqueueChange},
  {"$LAST_PLAYED_ALBUM",                  STAT_DESC_LPAL, STATUS_VAR_LAST_PLAYED_ALBUM,                0xff,                       false, &StatusDisplayClass::funcLastPlayedAlbum,         StatusEvent_playqueueChange},
  {"$LAST_PLAYED_ALB_ARTIST",             STAT_DESC_LPAA, STATUS_VAR_LAST_PLAYED_ALBUM_ARTIST,         0xff,                       false, &StatusDisplayClass::funcLastPlayedAlbumArtist,   StatusEvent_playqueueChange},
  {"$LAST_PLAYED_TRACK_NUMBER",           STAT_DESC_LPTN, STATUS_VAR_LAST_PLAYED_TRACK_NUMBER,         0xff,                       false, &StatusDisplayClass::funcLastPlayedTrackNumber,   StatusEvent_playqueueChange},
  {"$LAST_PLAYED_YEAR",                   STAT_DESC_LPYR, STATUS_VAR_LAST_PLAYED_YEAR,                 0xff,                       false, &StatusDisplayClass::funcLastPlayedYear,          StatusEvent_playqueueChange},
  {"$LAST_PLAYED_GENRE",                  STAT_DESC_LPGN, STATUS_VAR_LAST_PLAYED_GENRE,                0xff,                       false, &StatusDisplayClass::funcLastPlayedGenre,         StatusEvent_playqueueChange},
  {"$LAST_PLAYED_PUBLISHER",              STAT_DESC_LPPU, STATUS_VAR_LAST_PLAYED_PUBLISHER,            0xff,                       false, &StatusDisplayClass::funcLastPlayedPublisher,     StatusEvent_playqueueChange},
  {"$LAST_PLAYED_ISRC",                   STAT_DESC_LPIS, STATUS_VAR_LAST_PLAYED_ISRC,                 0xff,                       false, &StatusDisplayClass::funcLastPlayedISRC,          StatusEvent_playqueueChange},
  {"$LAST_PLAYED_CUSTOM_TAG",             STAT_DESC_LPCT, STATUS_VAR_LAST_PLAYED_CUSTOM_TAG,           0xff,                       false, &StatusDisplayClass::funcLastPlayedCustomTag,     StatusEvent_playqueueChange},
  {"$LAST_PLAYED_LENGTH",                 STAT_DESC_LPLE, STATUS_VAR_LAST_PLAYED_LENGTH,               0xff,                       false, &StatusDisplayClass::funcLastPlayedlength,        StatusEvent_playqueueChange},
  {"$CREDITS",                            STAT_DESC_CRED, STATUS_VAR_CREDITS,                          0xff,                       false, &StatusDisplayClass::funcCredits,                 StatusEvent_creditsChange},
  {"$AUTO_GENRE",                         STAT_DESC_AUTG, STATUS_VAR_AUTO_GENRE,                       0xff,                       false, &StatusDisplayClass::funcAutoGenre,               StatusEvent_autoPlayModeChange},
  {"$PLAYS_PER_COIN1",                    STAT_DESC_PPCR, STATUS_VAR_PLAYS_PER_COIN1,                  0x00,                       false, &StatusDisplayClass::funcPlaysPerCoin,            StatusEvent_freeplayModeChange},
  {"$PLAYS_PER_COIN2",                    STAT_DESC_PPCR, STATUS_VAR_PLAYS_PER_COIN2,                  0x01,                       false, &StatusDisplayClass::funcPlaysPerCoin,            StatusEvent_freeplayModeChange},
  {"$PLAYS_PER_COIN3",                    STAT_DESC_PPCR, STATUS_VAR_PLAYS_PER_COIN3,                  0x02,                       false, &StatusDisplayClass::funcPlaysPerCoin,            StatusEvent_freeplayModeChange},
  {"$PLAYS_PER_COIN4",                    STAT_DESC_PPCR, STATUS_VAR_PLAYS_PER_COIN4,                  0x03,                       false, &StatusDisplayClass::funcPlaysPerCoin,            StatusEvent_freeplayModeChange},
  {"$VOLUME",                             STAT_DESC_VOLU, STATUS_VAR_VOLUME,                           0xff,                       false, &StatusDisplayClass::funcVolume,                  StatusEvent_volumeChange},
  {"$SELECT_CODE",                        STAT_DESC_SELC, STATUS_VAR_SELECT_CODE,                      0xff,                       false, &StatusDisplayClass::funcSelectCode,              StatusEvent_selCodeChange},
  {"$NUM_SONGS",                          STAT_DESC_NSON, STATUS_VAR_NUM_SONGS,                        0xff,                       false, &StatusDisplayClass::funcNumSongs,                StatusEvent_none},
  {"$NUM_PAGES",                          STAT_DESC_NPAG, STATUS_VAR_NUM_PAGES,                        0xff,                       false, &StatusDisplayClass::funcNumPages,                StatusEvent_none},
  {"$FIRST_VISIBLE_PAGE",                 STAT_DESC_FVPA, STATUS_VAR_FIRST_VISIBLE_PAGE,               0xff,                       false, &StatusDisplayClass::funcFirstVisiblePage,        StatusEvent_pageMoveLeftInit | StatusEvent_pageMoveRightInit},
  {"$LAST_VISIBLE_PAGE",                  STAT_DESC_LVPA, STATUS_VAR_LAST_VISIBLE_PAGE,                0xff,                       false, &StatusDisplayClass::funcLastVisiblePage,         StatusEvent_pageMoveLeftInit | StatusEvent_pageMoveRightInit},
  {"$SET_GPIO_00_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_00_HI,                   0x00,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_00_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_00_LO,                   0x00,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_01_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_01_HI,                   0x01,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_01_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_01_LO,                   0x01,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_02_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_02_HI,                   0x02,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_02_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_02_LO,                   0x02,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_03_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_03_HI,                   0x03,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_03_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_03_LO,                   0x03,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_04_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_04_HI,                   0x04,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_04_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_04_LO,                   0x04,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_05_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_05_HI,                   0x05,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_05_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_05_LO,                   0x05,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_06_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_06_HI,                   0x06,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_06_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_06_LO,                   0x06,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_07_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_07_HI,                   0x07,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_07_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_07_LO,                   0x07,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_08_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_08_HI,                   0x08,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_08_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_08_LO,                   0x08,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_09_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_09_HI,                   0x09,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_09_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_09_LO,                   0x09,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_10_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_10_HI,                   0x0a,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_10_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_10_LO,                   0x0a,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_11_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_11_HI,                   0x0b,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_11_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_11_LO,                   0x0b,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_12_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_12_HI,                   0x0c,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_12_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_12_LO,                   0x0c,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_13_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_13_HI,                   0x0d,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_13_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_13_LO,                   0x0d,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_14_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_14_HI,                   0x0e,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_14_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_14_LO,                   0x0e,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_15_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_15_HI,                   0x0f,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_15_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_15_LO,                   0x0f,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_16_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_16_HI,                   0x10,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_16_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_16_LO,                   0x10,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_17_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_17_HI,                   0x11,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_17_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_17_LO,                   0x11,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_18_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_18_HI,                   0x12,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_18_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_18_LO,                   0x12,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_19_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_19_HI,                   0x13,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_19_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_19_LO,                   0x13,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_20_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_20_HI,                   0x14,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_20_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_20_LO,                   0x14,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_21_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_21_HI,                   0x15,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_21_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_21_LO,                   0x15,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_22_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_22_HI,                   0x16,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_22_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_22_LO,                   0x16,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_23_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_23_HI,                   0x17,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_23_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_23_LO,                   0x17,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_24_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_24_HI,                   0x18,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_24_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_24_LO,                   0x18,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_25_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_25_HI,                   0x19,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_25_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_25_LO,                   0x19,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_26_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_26_HI,                   0x1a,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_26_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_26_LO,                   0x1a,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_GPIO_27_HI",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_27_HI,                   0x1b,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_none},
  {"$SET_GPIO_27_LO",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_27_LO,                   0x1b,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_none},
  {"$SET_FLAG_1_HI",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_1_HI,                    0x00,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_none},
  {"$SET_FLAG_1_LO",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_1_LO,                    0x00,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_none},
  {"$SET_FLAG_2_HI",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_2_HI,                    0x01,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_none},
  {"$SET_FLAG_2_LO",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_2_LO,                    0x01,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_none},
  {"$SET_FLAG_3_HI",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_3_HI,                    0x02,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_none},
  {"$SET_FLAG_3_LO",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_3_LO,                    0x02,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_none},
  {"$SET_FLAG_4_HI",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_4_HI,                    0x03,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_none},
  {"$SET_FLAG_4_LO",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_4_LO,                    0x03,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_none},
  {"$DRAW_BITMAP",                        STAT_DESC_BMPX, STATUS_VAR_DRAW_BITMAP,                      0xff,                       false, &StatusDisplayClass::funcDrawBitmap,              StatusEvent_none},
  {"$DRAW_RANDOM_BITMAP",                 STAT_DESC_BMPR, STATUS_VAR_DRAW_RANDOM_BITMAP,               0xff,                       false, &StatusDisplayClass::funcDrawRandomBitmap,        StatusEvent_none},
  {"$UNDRAW_BITMAP",                      STAT_DESC_BMPU, STATUS_VAR_UNDRAW_BITMAP,                    0xff,                       false, &StatusDisplayClass::funcUndrawBitmap,            StatusEvent_none},
  {"$DRAW_VIDEO",                         STAT_DESC_VIDX, STATUS_VAR_DRAW_VIDEO,                       0xff,                       false, &StatusDisplayClass::funcDrawVideo,               StatusEvent_none},
  {"$UNDRAW_VIDEO",                       STAT_DESC_VIDU, STATUS_VAR_UNDRAW_VIDEO,                     0xff,                       false, &StatusDisplayClass::funcUndrawVideo,             StatusEvent_none},
  {"$START_VIDEO",                        STAT_DESC_STRV, STATUS_VAR_START_VIDEO,                      0xff,                       false, &StatusDisplayClass::funcStartVideo,              StatusEvent_none},
  {"$STOP_VIDEO",                         STAT_DESC_STPV, STATUS_VAR_STOP_VIDEO,                       0xff,                       false, &StatusDisplayClass::funcStopVideo,               StatusEvent_none},
  {"$PAUSE_VIDEO",                        STAT_DESC_PAUV, STATUS_VAR_PAUSE_VIDEO,                      0xff,                       false, &StatusDisplayClass::funcPauseVideo,              StatusEvent_none},
  {"$UNPAUSE_VIDEO",                      STAT_DESC_UNPV, STATUS_VAR_UNPAUSE_VIDEO,                    0xff,                       false, &StatusDisplayClass::funcUnPauseVideo,            StatusEvent_none},
  {"$IF_FREE_PLAY",                       STAT_DESC_IFFP, STATUS_VAR_IF_FREE_PLAY,                     0xff,                       true,  &StatusDisplayClass::funcIfFreeplay,              StatusEvent_freeplayModeChange},
  {"$IF_NOT_FREE_PLAY",                   STAT_DESC_INFP, STATUS_VAR_IF_NOT_FREE_PLAY,                 0xff,                       true,  &StatusDisplayClass::funcIfNotFreeplay,           StatusEvent_freeplayModeChange},
  {"$IF_NO_CREDITS",                      STAT_DESC_IFNC, STATUS_VAR_IF_NO_CREDITS,                    0xff,                       true,  &StatusDisplayClass::funcIfNoCredits,             StatusEvent_creditsChange},
  {"$IF_ANY_CREDITS",                     STAT_DESC_IFCA, STATUS_VAR_IF_ANY_CREDITS,                   0xff,                       true,  &StatusDisplayClass::funcIfAnyCredits,            StatusEvent_creditsChange},
  {"$IF_SONG_PLAYING",                    STAT_DESC_IFPL, STATUS_VAR_IF_SONG_PLAYING,                  0xff,                       true,  &StatusDisplayClass::funcIfSongPlaying,           StatusEvent_songStart | StatusEvent_songStop},
  {"$IF_NOT_SONG_PLAYING",                STAT_DESC_IFNP, STATUS_VAR_IF_NOT_SONG_PLAYING,              0xff,                       true,  &StatusDisplayClass::funcIfNotSongPlaying,        StatusEvent_songStart | StatusEvent_songStop},
  {"$IF_VIDEO_SONG_PLAYING",              STAT_DESC_IFSV, STATUS_VAR_IF_VIDEO_SONG_PLAYING,            0xff,                       true,  &StatusDisplayClass::funcIfVideoSongPlaying,      StatusEvent_songVideoShow},
  {"$IF_NOT_VIDEO_SONG_PLAYING",          STAT_DESC_IFNV, STATUS_VAR_IF_NOT_VIDEO_SONG_PLAYING,        0xff,                       true,  &StatusDisplayClass::funcIfNotVideoSongPlaying,   StatusEvent_songStart},
  // {"$IF_RADIO_PLAYING",                   STAT_DESC_IFSR, STATUS_VAR_IF_RADIO_PLAYING,                 0xff,                       true,  &StatusDisplayClass::funcIfRadioSongPlaying,      StatusEvent_songStart | StatusEvent_songStop},
  // {"$IF_NOT_RADIO_PLAYING",               STAT_DESC_IFNR, STATUS_VAR_IF_NOT_RADIO_PLAYING,             0xff,                       true,  &StatusDisplayClass::funcIfNotRadioSongPlaying,   StatusEvent_songStart | StatusEvent_songStop},
  {"$IF_SONG_LOADING",                    STAT_DESC_IFLO, STATUS_VAR_IF_SONG_LOADING,                  0xff,                       true,  &StatusDisplayClass::funcIfSongLoading,           StatusEvent_songStart | StatusEvent_songLoad},
  {"$IF_NOT_SONG_LOADING",                STAT_DESC_IFNL, STATUS_VAR_IF_NOT_SONG_LOADING,              0xff,                       true,  &StatusDisplayClass::funcIfNotSongLoading,        StatusEvent_songStart | StatusEvent_songLoad},
  {"$IF_SONG_UNLOADING",                  STAT_DESC_IFUL, STATUS_VAR_IF_SONG_UNLOADING,                0xff,                       true,  &StatusDisplayClass::funcIfSongUnloading,         StatusEvent_songStop | StatusEvent_songUnload},
  {"$IF_NOT_SONG_UNLOADING",              STAT_DESC_IFNU, STATUS_VAR_IF_NOT_SONG_UNLOADING,            0xff,                       true,  &StatusDisplayClass::funcIfNotSongUnloading,      StatusEvent_songStop | StatusEvent_songUnload},
  {"$IF_ANY_COMING_UP",                   STAT_DESC_IFAC, STATUS_VAR_IF_ANY_COMING_UP,                 0xff,                       true,  &StatusDisplayClass::funcIfAnyComingUp,           StatusEvent_playqueueChange},
  {"$IF_NONE_COMING_UP",                  STAT_DESC_INCU, STATUS_VAR_IF_NONE_COMING_UP,                0xff,                       true,  &StatusDisplayClass::funcIfNoneComingUp,          StatusEvent_playqueueChange},
  {"$IF_SONG_COMING_UP",                  STAT_DESC_ISCU, STATUS_VAR_IF_SONG_COMING_UP,                0xff,                       true,  &StatusDisplayClass::funcIfSongComingUp,          StatusEvent_playqueueChange},
  {"$IF_AUTO_PLAY_MODE",                  STAT_DESC_IFRM, STATUS_VAR_IF_AUTO_PLAY_MODE,                0xff,                       true,  &StatusDisplayClass::funcIfAutoPlayMode,          StatusEvent_autoPlayModeChange},
  {"$IF_NOT_AUTO_PLAY_MODE",              STAT_DESC_INRM, STATUS_VAR_IF_NOT_AUTO_PLAY_MODE,            0xff,                       true,  &StatusDisplayClass::funcIfNotAutoPlayMode,       StatusEvent_autoPlayModeChange},
  {"$IF_LOOP_MODE",                       STAT_DESC_IFLM, STATUS_VAR_IF_LOOP_MODE,                     0xff,                       true,  &StatusDisplayClass::funcIfLoopMode,              StatusEvent_loopModeChange},
  {"$IF_NOT_LOOP_MODE",                   STAT_DESC_INLM, STATUS_VAR_IF_NOT_LOOP_MODE,                 0xff,                       true,  &StatusDisplayClass::funcIfNotLoopMode,           StatusEvent_loopModeChange},
  {"$IF_TIMER_HI",                        STAT_DESC_IFTY, STATUS_VAR_IF_TIMER_HI,                      0xff,                       true,  &StatusDisplayClass::funcIfTimerHi,               StatusEvent_timerChange},
  {"$IF_TIMER_LO",                        STAT_DESC_IFTN, STATUS_VAR_IF_TIMER_LO,                      0xff,                       true,  &StatusDisplayClass::funcIfTimerLo,               StatusEvent_timerChange},
  {"$IF_TIMER_TICK",                      STAT_DESC_IFTT, STATUS_VAR_IF_TIMER_TICK,                    0xff,                       true,  &StatusDisplayClass::funcIfTimerTick,             StatusEvent_timerChange},
  {"$IF_MUTE",                            STAT_DESC_IFMU, STATUS_VAR_IF_MUTE,                          0xff,                       true,  &StatusDisplayClass::funcIfMute,                  StatusEvent_muteChange},
  {"$IF_NOT_MUTE",                        STAT_DESC_IFNM, STATUS_VAR_IF_NOT_MUTE,                      0xff,                       true,  &StatusDisplayClass::funcIfNotMute,               StatusEvent_muteChange},
  {"$IF_PAGE_MOVING",                     STAT_DESC_IFPM, STATUS_VAR_IF_PAGE_MOVING,                   0xff,                       true,  &StatusDisplayClass::funcIfPageMoving,            StatusEvent_timerChange},
  {"$IF_NOT_PAGE_MOVING",                 STAT_DESC_IFPN, STATUS_VAR_IF_NOT_PAGE_MOVING,               0xff,                       true,  &StatusDisplayClass::funcIfPageNotMoving,         StatusEvent_timerChange},
  {"$IF_PLAYQUEUE_EMPTY",                 STAT_DESC_IFPE, STATUS_VAR_IF_PLAYQUEUE_EMPTY,               0xff,                       true,  &StatusDisplayClass::funcIfPlayQueueEmpty,        StatusEvent_playqueueChange},
  {"$IF_NOT_PLAYQUEUE_EMPTY",             STAT_DESC_INPE, STATUS_VAR_IF_NOT_PLAYQUEUE_EMPTY,           0xff,                       true,  &StatusDisplayClass::funcIfNotPlayQueueEmpty,     StatusEvent_playqueueChange},
  {"$IF_PLAYQUEUE_FULL",                  STAT_DESC_IFPF, STATUS_VAR_IF_PLAYQUEUE_FULL,                0xff,                       true,  &StatusDisplayClass::funcIfPlayQueueFull,         StatusEvent_playqueueChange},
  {"$IF_NOT_PLAYQUEUE_FULL",              STAT_DESC_INPF, STATUS_VAR_IF_NOT_PLAYQUEUE_FULL,            0xff,                       true,  &StatusDisplayClass::funcIfNotPlayQueueFull,      StatusEvent_playqueueChange},
  {"$IF_STEREO",                          STAT_DESC_IFST, STATUS_VAR_IF_STEREO,                        0xff,                       true,  &StatusDisplayClass::funcIfStereo,                StatusEvent_songStart},
  {"$IF_NOT_STEREO",                      STAT_DESC_INST, STATUS_VAR_IF_NOT_STEREO,                    0xff,                       true,  &StatusDisplayClass::funcIfNotStereo,             StatusEvent_songStart},
  {"$IF_PAUSED",                          STAT_DESC_IFPA, STATUS_VAR_IF_PAUSED,                        0xff,                       true,  &StatusDisplayClass::funcIfPaused,                StatusEvent_songPauseChange},
  {"$IF_NOT_PAUSED",                      STAT_DESC_INPA, STATUS_VAR_IF_NOT_PAUSED,                    0xff,                       true,  &StatusDisplayClass::funcIfNotPaused,             StatusEvent_songPauseChange},
  {"$IF_INVALID_CHOICE",                  STAT_DESC_IFIC, STATUS_VAR_IF_INVALID_CHOICE,                0xff,                       true,  &StatusDisplayClass::funcIfInvalidChoice,         StatusEvent_chooseSong},
  {"$IF_NOT_INVALID_CHOICE",              STAT_DESC_INIC, STATUS_VAR_IF_NOT_INVALID_CHOICE,            0xff,                       true,  &StatusDisplayClass::funcIfNotInvalidChoice,      StatusEvent_chooseSong},
  {"$IF_FLAG_1_HI",                       STAT_DESC_IFLH, STATUS_VAR_IF_FLAG_HI,                       0x00,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_flagChange},
  {"$IF_FLAG_1_LO",                       STAT_DESC_IFLL, STATUS_VAR_IF_FLAG_LO,                       0x00,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_flagChange},
  {"$IF_FLAG_2_HI",                       STAT_DESC_IFLH, STATUS_VAR_IF_FLAG_HI,                       0x01,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_flagChange},
  {"$IF_FLAG_2_LO",                       STAT_DESC_IFLL, STATUS_VAR_IF_FLAG_LO,                       0x01,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_flagChange},
  {"$IF_FLAG_3_HI",                       STAT_DESC_IFLH, STATUS_VAR_IF_FLAG_HI,                       0x02,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_flagChange},
  {"$IF_FLAG_3_LO",                       STAT_DESC_IFLL, STATUS_VAR_IF_FLAG_LO,                       0x02,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_flagChange},
  {"$IF_FLAG_4_HI",                       STAT_DESC_IFLH, STATUS_VAR_IF_FLAG_HI,                       0x03,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_flagChange},
  {"$IF_FLAG_4_LO",                       STAT_DESC_IFLL, STATUS_VAR_IF_FLAG_LO,                       0x03,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_flagChange},
  {"$IF_BUTTON_QUIT_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_QUIT,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_QUIT_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_QUIT,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_COIN1_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN1,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_COIN1_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN1,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_COIN2_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN2,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_COIN2_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN2,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_COIN3_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN3,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_COIN3_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN3,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_COIN4_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN4,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_COIN4_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN4,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_VOLUP_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_VOL_UP,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_VOLUP_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_VOL_UP,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_VOLDOWN_PRESSED",          STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_VOL_DOWN,            true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_VOLDOWN_PRESSED",      STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_VOL_DOWN,            true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_RANDOM_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_ADD_RANDOM,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_RANDOM_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_ADD_RANDOM,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_SELECT_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_SELECT,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_SELECT_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_SELECT,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_SKIP_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_SKIP,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_SKIP_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_SKIP,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_PAUSE_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_PAUSE,               true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_PAUSE_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_PAUSE,               true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_UP_PRESSED",               STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_UP,                  true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_UP_PRESSED",           STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_UP,                  true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_DOWN_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_DOWN,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_DOWN_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_DOWN,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_LEFT_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_LEFT_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_RIGHT_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT,               true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_RIGHT_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT,               true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_LEFT_JUMP_PRESSED",        STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT_JUMP,           true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_LEFT_JUMP_PRESSED",    STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT_JUMP,           true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_RIGHT_JUMP_PRESSED",       STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT_JUMP,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_RIGHT_JUMP_PRESSED",   STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT_JUMP,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_LEFT_ALPHA_PRESSED",       STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT_ALPHA,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_LEFT_ALPHA_PRESSED",   STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT_ALPHA,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_RIGHT_ALPHA_PRESSED",      STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT_ALPHA,         true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_RIGHT_ALPHA_PRESSED",  STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT_ALPHA,         true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_AUTO_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_AUTO_PLAY_TOG,       true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_AUTO_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_AUTO_PLAY_TOG,       true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_LOOP_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LOOP_TOG,            true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_LOOP_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LOOP_TOG,            true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_FREE_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FREEPLAY_TOG,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_FREE_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FREEPLAY_TOG,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_CLEAR_PRESSED",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_CLEAR_QUEUE,         true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_CLEAR_PRESSED",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_CLEAR_QUEUE,         true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_MUTE_PRESSED",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_MUTE,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_MUTE_PRESSED",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_MUTE,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_0_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_0,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_0_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_0,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_1_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_1,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_1_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_1,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_2_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_2,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_2_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_2,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_3_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_3,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_3_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_3,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_4_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_4,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_4_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_4,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_5_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_5,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_5_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_5,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_6_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_6,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_6_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_6,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_7_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_7,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_7_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_7,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_8_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_8,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_8_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_8,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_9_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_9,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_9_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_9,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_A_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_A,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_A_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_A,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_B_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_B,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_B_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_B,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_C_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_C,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_C_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_C,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_D_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_D,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_D_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_D,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_E_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_E,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_E_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_E,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_F_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_F,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_F_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_F,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_G_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_G,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_G_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_G,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_H_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_H,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_H_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_H,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_I_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_I,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_I_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_I,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_J_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_J,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_J_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_J,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_K_PRESSED",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_K,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_K_PRESSED",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_K,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_POWER_OFF_PRESSED",        STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_POWER_OFF,           true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_POWER_OFF_PRESSED",    STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_POWER_OFF,           true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_FLAG_1_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_1,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_FLAG_1_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_1,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_FLAG_2_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_2,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_FLAG_2_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_2,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_FLAG_3_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_3,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_FLAG_3_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_3,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$IF_BUTTON_FLAG_4_PRESSED",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_4,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_buttonChanged},
  {"$IF_NOT_BUTTON_FLAG_4_PRESSED",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_4,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_buttonChanged},
  {"$NO_DRAW",                            STAT_DESC_ENND, STATUS_VAR_NO_DRAW,                          0xff,                       false, &StatusDisplayClass::funcNoDraw,                  StatusEvent_none},
  {"$END_IF",                             STAT_DESC_ENIF, STATUS_VAR_END_IF,                           0xff,                       false, &StatusDisplayClass::funcEndIf,                   StatusEvent_none}

};

