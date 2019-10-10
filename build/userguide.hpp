#pragma once

const char introduction_str[] = { \
  "Welcome to fruitbox, a customisable, Retro MP3 Jukebox for the Raspberry Pi."
};

const char starting_up_str[] = { \
  "fruitbox is intended to be run directly from the command line for maximum performance.\n\n" \
  "See section 'Command Line Options' for startup options."
};

const char operation_str[] = { \
  "To run fruitbox, from the command line goto the installation directory and type 'sudo ./fruitbox --cfg <file>'.  " \
  "fruitbox will then look for the configuration (skin) <file>.  See section 'Configuration (Skin) " \
  "Files' for more detail.  After the configuration file has been read, fruitbox will load the song " \
  "database file (specified in the configuration file).  If the file doesn't exist, a new one will " \
  "be created (see section 'Database Creation').  When the database has been read, fruitbox will start!\n\n" \
  "Song pages are moved using the ButtonLeft and ButtonRight keys, and songs are selected using the select keys or " \
  "cursor keys if in joystick mode.  Once a song is selected, it is added to the play queue.  If no song is " \
  "playing, the song at the top of the play queue is 'loaded', played, and then 'unloaded'."
  "\n\nControl inputs (buttons) can be re-defined...fruitbox will look for a 'fruitbox.btn' file in the same " \
  "directory as it is run from (unless an alternative button mapping file is defined using the '--button-map' command line option." \
  "  If it finds one, it will read the file and re-map one or more of the input " \
  "control buttons as specified in the mapping file."
};

const char command_line_options_str[] = { \
  "fruitbox takes the following command line parameters."
};

const char cfg_file_str[] = { \
  "Configuration files (skins) define the look and feel of fruitbox.  " \
  "A configuration file is a human-readable text file containing a list of " \
  "parameters and their values.  Parameters are grouped into sections, where " \
  "each section is defined by its name enclosed in square brackets, followed " \
  "by the parameter list for that section.  The order of sections is not important " \
  "except when the section refers to a display object, in which case the order of the " \
  "sections determines the render order on the display.\n\n" \
  "A parameter is defined by specifying its name, followed by its parameter value(s).  " \
  "The parameter name and values can be separated by whitespace, = or :.  " \
  "Parameter values can be strings, numeric decimal values, or boolean values (true, false, " \
  "enable, disable, on, off, yes, no, 0, 1).  Comments can be included in the configuration " \
  "file by prefixing any comment text with the '#' character.\n\n" \
  "The following list shows all the possible parameters for each section.  If a parameter is " \
  "not specified in the configuration file, fruitbox will use a default value.\n\nNote that entries marked " \
  "with a '*' means that these groups / parameters can be defined multiple times.\n" \
  "Note: filenames for 'Database' and 'MusicPath' parameters have file paths relative to the directory fruitbox " \
  "was run from, whereas filenames for all other parameters (sound files, bitmap files, status text files, font files) " \
  "have paths which are relative to the directory the configuration file itself is in.  This allows configuration files " \
  "and their associated content files to be kept together, but easily share common MusicPath(s) and Database files with other skins."
};

const char buttons_def_str[] = { \
  "The fruitbox input controls can be modified using the a button mapping file ('fruitbox.btn' by default).  " \
  "If this file exists in the same directory as fruitbox, it will be read by fruitbox " \
  "to determine one or more button mappings.  See section 'Button Mapping File'.\n\n" \
  "By default, the buttons are mapped to keyboard keys (see section 'Default Buttons'), " \
  "but each key can be re-mapped to any of the following...\n\n" \
  "1. Keyboard key\n" \
  "2. GPIO input pin\n" \
  "3. USB joystick stick / button\n" \
  "4. Region on touch screen\n" \
  "\nThe fruitbox command line parameter '--config-buttons' can be used to interactively assign buttons, "\
  "and generate the button map file.  The btn file can be manually edited later if minor adjustments " \
  "are required.  The '--test-buttons' command line parameter can be used to check what codes are generated " \
  "without creating a button mapping file.\n\n" \
  "For touch screen buttons, the touch areas are defined in the skin file itself, using the [touch areas] " \
  "section, because these are skin-related.  However, the button assignment to touch input is done in the " \
  "btn file because this is hardware and not skin related.  Button assignments " \
  "are not specified in the skin to ensure skins remain compatible with different button hardware setups."
};

const char font_text_def_str[] = { \
  "The configuration file [font] section(s) allow multiple fonts of different sizes " \
  "to be loaded and used by different display elements.  This removes the need for each text " \
  "definition to load it's own font, instead referencing a specific font type and size from " \
  "the 'font pool'.\n\n" \
  "Text definitions ([general] ArtistText, [general] SongText, [general] PairedSongText, [general] ExtraText and [status] Text) " \
  "parameters have the following arguments...\n\n" \
  "<font> <colour> <alignment> <capitalise> <condense> <quoted> <offset> <max_width>\n\n" \
  "       font : number of font from 'font pool' (0..)\n"
  "              note that the fonts in the pool are numbered in\n" \
  "              the order in which they are defined in the\n" \
  "              configuration file\n" \
  "     colour : red green blue alpha (0..255)\n" \
  "              (alpha : 0 completely transparent\n" \
  "              through to 255 completely opaque)\n" \
  "  alignment : 'Left', 'Centre' or 'Right'\n" \
  " capitalise : 'Yes' or 'No'\n" \
  "   condense : 'Yes' (wide text is horizontally squashed to fit\n" \
  "              within max_width),\n" \
  "              'No' no squashing is done\n" \
  "     quoted : 'Yes' (text is wrapped within double-quotes),\n" \
  "              'No' text is unmodified\n" \
  "     offset : x y (text position is shifted by these amounts\n" \
  "              in pixels)\n" \
  "  max_width : The maximum width of the text.  If the text is\n" \
  "              wider than this, then it will be shrunk to the\n" \
  "              maximum width (if the 'condense' option is 'Yes')"
};

const char command_line_help_option_str[] = { \
  "Show basic help and version information."
};

const char command_line_user_guide_option_str[] = { \
  "Create this user-guide to file \"userguide.txt\" (but I guess you already worked that one out...)"
};

const char command_line_database_option_str[] = { \
  "Use the specified database instead of the one specified in the skin"
};

const char command_line_musicpath_option_str[] = { \
  "Use the specified music path instead of the one specified in the skin.  Only used when the database " \
  "file doesn't exist (as specified on the command line or skin config file).  Note that the --music-path " \
  "option can be specified multiple times if the user wishes to construct the database from multiple sources."
};

const char command_line_load_playlist_str[] = { \
  "Loads a playlist file and populates the play queue with the songs in it; fruitbox will begin playing the songs after it has " \
  "playing up."
};

const char command_line_save_playlist_str[] = { \
  "When fruitbox exits (by the user pressing the 'Quit' button), this option saves the contents of the play queue (and currently playing " \
  "song) to the specified file.  This can subsequently be loaded back into fruitbox using the '--load-playlist' command line " \
  "argument.  The playlist file contains a list of song filenames which can easily be edited by hand to modify the playlist as required."
};

const char command_line_choose_cfg_str[] = { \
  "This option allows the user to choose a configuration file (skin) from a menu when fruitbox starts up, rather than specifying it using " \
  "the '--cfg' command line option.  The <file> parameter, should contain a list of cfg files to choose from.  Each entry takes the form " \
  "'File = <file>' (path and name of a skin's cfg file).\n\n" \
  "fruitbox will allow the user to cycle through the list of files using the ButtonLeft and ButtonRight keys.  Any other button will select the " \
  "skin.  The 'SkinName' and 'SkinDescription' values in the skin cfg files will be used to display information about each skin. A preview of the skin is shown if " \
  "a screenshot file exists (by default, 'screenshot.jpg' in the same directory as the cfg file, or the name of the 'Screenshot' parameter value " \
  "in the skin configuration file).  Note that screenshot files can be generated with the '--screenshot' command line option."
};

const char command_line_no_scale_str[] = { \
  "Normally fruitbox will scale (resize) the skin to the display, so no matter what it's size, it will always fit exactly.  " \
  "This option turns off the scaling so the skin will be shown at its original size (useful for debugging skin designs).  The skin " \
  "will be centered on the display.  If the skin is smaller than the display then the skin will be surrounded by a black border, but " \
  "if the skin is larger than the display, the outer edges of the skin will not be visible."
};

// const char command_line_touch_min_str[] = { \
  // "These values can be used to define the co-ordinates of the top left corner of the touch screen (usually 0 0, but some touchscreens have a different value).  " \
  // "If not specified, will default to 0 0."
// };

// const char command_line_touch_max_str[] = { \
  // "These values can be used to define the co-ordinates of the bottom right corner of the touch screen (usually the size of the touch screen, " \
  // "but some touchscreens have a different value).  If not specified, will default to the size of the detected display."
// };

const char command_line_button_map_str[] = { \
  "Name of button mapping file (defaults to 'fruitbox.btn' if not specified)"
};
// const char command_line_gpio_scan_row_str[] = { \
  // "These values define the GPIo pin numbers used to form the rows of the GPIO button matrix."
// };

// const char command_line_gpio_scan_col_str[] = { \
  // "These values define the GPIo pin numbers used to form the columns of the GPIO button matrix.\n\n" \
  // "Together with the rows, the columns form a matrix; the matrix is used to allow more buttons than GPIO pins to be " \
  // "defined.  Each row/column intersection on the matrix can be used to connect a button; an example is shown below.  Note " \
  // "that the size and shapre of the matrix is user defined, according to how many ros and columns are defined..." \
  // "***PICTURE OF MATRIX HERE ********"
// };

const char command_line_screenshot_str[] = { \
  "Save a screenshot of the skin, then quit without running.  The screenshot will be written to 'screenshot.jpg' in the skin directory " \
  "by default or the value of the 'Screenshot' parameter in the skin configuration file.  " \
  "This option should be used in conjunction with the '--cfg' or '--choose-cfg' command line options."
};

const char command_line_debug_song_nums_option_str[] = { \
  "Show select code alongside song entries"
};

const char command_line_no_db_update_option_str[] = { \
  "Normally fruitbox will update the database if it has a modification time earler than the contents of any of the MusicPath directories." \
  "This option disables this check, so it is up to the user to delete the database file in order for it to be regenerated."
};

const char command_line_test_buttons_option_str[] = { \
  "This option allows button codes to be checked without creating a button mapping file."
};

const char command_line_gen_button_file_option_str[] = { \
  "This option allows the user to interactively change the input control button mappings, and creates the button " \
  "mapping file specified by the --button-map command line option (or 'fruitbox.btn' if not specified)"
};

const char command_line_calibrate_touch_option_str[] = { \
  "Used in conjunction with '--config-buttons' , this allows the user to interactively specify the " \
  "touch-min and touch-max values rather than through the command line options.  It will also write " \
  "these values to the button mapping file for future use."
};

const char command_line_cfg_option_str[] = { \
  "This option determines which configuration file (skin) is used."
};

const char database_creation_str[] = { \
  "Once fruitbox has read the skin file and found no problems, it will try to load the music database " \
  "as specified in the skin file.  The database contains details of your music; tagged and pre-formatted to allow " \
  "fruitbox to use it efficiently.  If the database file doesn't exist, then fruitbox will automatically generate it for you, using " \
  "one or more 'MusicPath'(s) as specified in the skin file.  Each MusicPath parameter must point to an accessible file directory " \
  "(for example a directory on the SD card itself or a USB memory drive), which contains MP3 songs (which can be in sub-directories).\n\n" \
  "Building the database file may take some considerable time if your music library is large, but " \
  "it only needs to be done once, and subsequent start-ups of fruitbox will be very fast.  If you add or remove music from your library, " \
  "fruitbox will regenerate it automatically, providing the changes are in the same MusicPath directory.  If not, you will have to manually " \
  "delete the database filefor frtuibox to re-generate it correctly.  Alternatively, the database file " \
  "can be edited by hand in a standard text editor if you have small changes to make or are feeling brave!.  This can be useful " \
  "if you wish to add or remove particular songs, or tweak the song details, without having to re-generate the database from scratch.  " \
  "Note that the song order in the database file is irrelevant; after fruitbox has read the songs from the database file it will sort them " \
  "according to the 'SortSongsBy' configuration parameter.\n\n" \
  "If the database file already exists, then fruitbox will ignore the MusicPath parameter(s) in the skin file."
};

const char timers_str[] = { \
  "Several skin parameters are specified in terms of time.  The time value refers to the number of " \
  "video frame ticks.  So for example at 60Hz, a time value of 120 equals 2 seconds.  When starting up, " \
  "fruitbox will detect the video display and print out the frame rate (along with the resolution)."
};

const char status_bitmaps_str[] = { \
  "There are two ways of specifying bitmaps in status objects...\n\n" \
  "Using one or more 'Bitmap' parameters.  This preloads the bitmaps on startup, so the number is limited " \
  "by the GPU memory, but allows for fast switching for full-frame rate animation.\n\n"
  "Alternatively, the 'BitmapDirectory' can be used.  This specifies a location on the file system in " \
  "which image files are stored (.bmp, .jpg, .png).  fruitbox only loads these into GPU memory when needed, " \
  "so is slower, but there is no limit on the number of image files.  This is more suitable for use in slide-show " \
  "displays for example."
};

const char display_str[] = { \
  "The skin file contains a SkinSize parameter; this indicates the intended size of the skin.  fruitbox " \
  "will scale the skin size to the actual video screen size as necessary."
};

const char coin_str[] = { \
  "fruitbox can support upto four coin buttons.  Each coin button has it's own 'PlaysPerCoin' value, so that fruitbox can " \
  "mimic jukeboxes which have multiple coin slots, for different coin denominations.  If all four 'PlaysPerCoin' parameters " \
  "are zero (or not specified) then fruitbox will operate in free play mode."
};

const char joystick_str[] = { \
  "If a [joystick] object is specified in the skin file, then joystick mode is activated.  " \
  "This allows a song to be chosen using the ButtonUp, ButtonDown, ButtonLeft and ButtonRight buttons " \
  "instead of entering the select code.  Pressing ButtonSelect will then add that song to the play queue (AutoSelect mode " \
  "is disabled when joystick mode is active).\n\n" \
  "The joystick image specified is positioned in the same place as the song title being selected, and its size " \
  "is calculated to fit exactly into the region containing the song title.  Specifying the 'Size' parameter in the " \
  "configuration file allows the size to be set manually, for example if the highlighted bitmap needs to overlap the song " \
  "title region.  The 'Offset' parameter can then be used to adjust the position of the highlighter precisely around the song " \
  "title region."
};

const char touch_song_str[] = { \
  "If a [touch song] object is specified in the skin file, then touch song mode is activated " \
  "(only if a touch screen has been detected).  This option over-rides joystick mode if that " \
  "has also been defined (using the [joystick] object).\n\n" \
  "In touch song mode, the user can touch the song title areas themselves to select a song, rather " \
  "than using select buttons.  Note that the song touch areas default to the page area holding the song name, " \
  "but their size and position can be adjusted by using the 'Size' and 'Offset' [touch song] parameters.  " \
  "The 'Bitmap' parameter defines an image file which is displayed over the song area when being touched." \
};

const char random_songs_str[] = { \
  "fruitbox can play random songs in one of two ways...\n" \
  "  1. The user pressing the 'Random' button\n" \
  "  2. fruitbox selecting a random song in AutoPlay mode\n\n" \
  "In either case, fruitbox will attempt to prevent songs being repeatedly " \
  "played by only picking a song if it doesn't appear in it's song play history and current playqueue. " \
  "The size of the history list can be changed with the 'SongHistoryDepth' configuration " \
  "parameter.  If this is large and the number of songs in the database is relatively " \
  "small, then fruitbox may not be able to quickly choose a random song which has not previously " \
  "been played within the history and current play queue, so will just play a random song anyway even if it already been " \
  "played recently." \
};

const char screen_layout_str[] = { \
  "The display is built using a combination of the following objects, as defined in the skin file:\n" \
  "\n" \
  "1.       [page] object : a region which contains songs.\n" \
  "                         See pages section for more details.\n" \
  "2.     [bitmap] object : a region which contains a static bitmap.\n" \
  "                         This can be used for background and\n" \
  "                         foregrounds for example.\n" \
  "3.     [status] object : a region containing status information.\n" \
  "                         See status box section for more details.\n" \
  "4.   [joystick] object : a region containing a bitmap controlled\n" \
  "                         by the four cursor keys.\n" \
  "                         See joystick section for more details.\n" \
  "5. [touch song] object : a region containing a bitmap highlighting\n" \
  "                         a song name when touched.\n" \
  "                         See touch song section for more details.\n" \
  "\n" \
  "Note that there is no limit on the number of objects which can be defined.  They are rendered to the " \
  "display in the order that they are defined in the skin file."
};

const char albums_singles_mode_str[] = { \
  "Fruitbox has two distinct modes - Albums and Singles, specified by the 'PageMode' parameter.\n\n" \
  "In Singles mode, each song is individually selectable, and each page displays a number of songs (or pairs of songs), each along " \
  "with the artist name.  'ArtistText', 'SongText', 'PairedSongText', 'PairSongs' and 'SongsPerPage' configuration parameters can be used adjust the appearance of " \
  "the song details on the pages.\n\n" \
  "In Albums mode, each page shows the album title, album artist, album cover art, and list of songs in the album (upto the " \
  "SongsPerPage value).  One selection will add all the songs in the album to the play queue in one go (assuming, in non-freeplay " \
  "mode, there are sufficient credits).  'AlbumText', 'ArtistText', 'SongText', 'PairedSongText', 'AlbumArtSize', 'AlbumArtOffset' and 'SongsPerPage' " \
  "configuration parameters can be used adjust the appearance of the album details on the pages.  Also note that 'PairedSongDescription' " \
  "is used to define the contents of the line which is associated with the 'AlbumText' parameter, and all of the " \
  "'Paired*' Description values are ignored (as these are only relevant for singles mode song pairs)."
};

const char pages_str[] = { \
  "Pages are the regions in the display which contain the songs.  In Singles mode, song titles** are listed vertically, and shown along with the artist name.  " \
  "If 'PairSongs' is enabled, then the songs are arranged in pairs with the artist name*** shown in between them (i.e. side A/B).  In Albums mode, "\
  "the page contains details about the album in addition to the song list (see section 'Albums / Singles Mode' for more details).\n\n" \
  "Songs are sorted in the order according to the 'SortSongsBy' configuration parameter.  " \
  "Songs in each page (in Singles mode), or pages themselves (in Albums mode) are assigned their own unique select code.  The " \
  "command line option '--debug-song-nums' can be used to make these codes visible; useful when developing skins.\n\n" \
  "Pages automatically move and update their contents when the ButtonLeft or ButtonRight keys are pressed.  The look and movement of the pages is " \
  "determined by 'PageMoveStyle' parameter in the skin file, as follows:\n\n" \
  "  PageMoveStyle <speed> <effect> <fade>\n\n" \
  "       <speed>\n" \
  "         1..x = higher number = faster page turn (0 = instant)\n" \
  "       <effect> ...\n" \
  "            0 = swipe horizontally\n" \
  "            1 = swipe vertically\n" \
  "            2 = reveal horizontally\n" \
  "            3 = reveal vertically\n" \
  "            4 = turn horizontally\n" \
  "            5 = turn vertically\n" \
  "            6 = dissolve\n" \
  "        <fade>\n" \
  "          no  = pages don't fade\n" \
  "          yes = pages fade to black" \
  "\n\nNotes:\n\n" \
  " ** The 'SongDescription' and 'PairedSongDescription' configuration parameters can be used to modify the text displayed on the song lines of the page(s) " \
  " ('PairedSongDescription' is only used if 'PairSongs' is not set to false) " \
  "by setting it to 'SongTitle', 'Artist', 'AlbumTitle', 'AlbumArtist', 'Year', 'Genre', 'TrackNumber', 'Publisher', 'ISRC', 'Custom', " \
  "'PairedSongTitle', 'PairedArtist', 'PairedAlbumTitle', 'PairedAlbumArtist', 'PairedYear', 'PairedGenre', 'PairedTrackNumber', 'PairedPublisher', 'PairedISRC', 'PairedCustom' " \
  " or any user string enclosed in double quotes.  "  \
  "Also, if multiple 'SongDescription' parameters are specified, then they are joined together to make a single text line.  " \
  "For example...\n" \
  "  SongDescription = SongTitle\n" \
  "  SongDescription = \" [\"\n" \
  "  SongDescription = Year\n" \
  "  SongDescription = \"]\"\n" \
  "...will display the text 'Pinball Wizard [1969]' (for example) for the song entries on each page.\n\n" \
  "*** The 'ArtistDescription' configuration parameter works in the same way as the 'SongDescription' parameter, but affects the " \
  "artist name text in the page(s) rather than the song title text."
};

const char status_flags_str[] = { \
  "Four status flags allow for inter-status communication and user triggered status events.  " \
  "Each status flag can be set high or low from button presses (toggle) and/or status $variables.  The values " \
  "of the flags can be read in status objects, allowing support for functionality such as...\n\n" \
  "1. Inter status communication:\n" \
  "for example one status object could toggle a flag with a certain timer tick period " \
  "which could then be detected in a different status object with a different timer tick period. This would " \
  "allow status to \"time-out\" after being started from a different timer period (or a button press)\n" \
  "2. Button invoked status display:\n" \
  "The flag buttons can be used to turn on and off status information."
};

const char gpio_str[] = { \
  "fruitbox can use the GPIO pins for both input and output:\n\nWhen a button is defined which uses a GPIO pin, the GPIO " \
  "pin is automatically configured as an input, with an internal pullup resistor.  You then just have to ensure that the " \
  "hardware button is connected between this GPIO pin and GND.\n\nWhen a $SET_GPIO* variable is encountered in a status object " \
  "Contents file, the specified GPIO pin is automatically configured as an output.\n\n" \
  "Note that if the same pin is defined in both the button mapping file and a status object, then input will take precedence over the " \
  "output, hence the status output will not work.\n\nThe fruitbox developer assumes no responsibility for any damage caused to the " \
  "Raspberry Pi or connected hardware due to the use of the GPIO pins from fruitbox, so please make sure you choose your GPIO pin " \
  "assignments carefully ;)"
};

const char status_boxes_pre_var_str[] = { \
  "Status Boxes provide a very flexible way of displaying real-time text-based information, and fixed and animated bitmaps.  " \
  "Using the 'Output' parameter also allows the status information to be written to an external file to be parsed by external applications*.  " \
  "Examples of status include 'Now Playing' information, 'Coming Up' song list, Select Code, Credits, etc.  Each status box defined should have a 'Contents' " \
  "file associated with it.  This is a file that contains human readable text which indicates what is drawn in the status box.\n\n" \
  "As well as fixed text, the user can also specify the following predefined variables, which represent song details and jukebox " \
  "status, and also enable text and bitmaps to be conditionally drawn under many different circumstances.  The GPIO related predefined " \
  "variables allow GPIO pins to be driven with high or low values under different fruitbox conditions.\n\n" \
  "* Note: outputting status to a text file can be done as well as displaying the status on the display, or instead of " \
  "(to supress the status being rendered to the display, do not define the 'Size' parameter (or set width and/or height to zero)."
};

const char status_videos_str[] = { \
  "Status boxes can be used to display either video clips or music videos.  " \
  "If the Video parameter is specified in the [status] object, any reference to VIDEO in the status Contents file variables (i.e. $DRAW_VIDEO) " \
  "will refer to the video clip specified by the Video parameter.  If the Video parameter is not specified, any VIDEO $variables will refer to " \
  "the currently playing song (if it's a video file).\n\n" \
  "The only supported format is .ogv (Vorbis + Theora). " \
  "Any video format can be converted to this format using for example ffmpeg with the following options for specifying the video bitrate and " \
  "video picture size for better quality...\n\n" \
  "  ffmpeg -i MyVideo.mp4 -b:v 2M -vf scale=640x480 MyVideo.ogv\n\n" \
  "Since the video decoding process is quite CPU intensive, it is recommended that a Quad core Pi is used (Model 2 or 3) with a good PSU (at least 2 Amps) when running fruitbox " \
  "and skins with video content, and the display resolution is kept low (less than 1024x768)." 
};

const char status_boxes_post_var_str[] = { \
  "The variables beginning $IF_ and $IF_NOT_ are used to conditionally execute or ignore the text in the config file which follows it, " \
  "upto the next $END_IF (or end of the line).  Note that IF conditions cannot span lines in the text file.  Variables which do not " \
  "begin with $IF specify dedicated jukebox status such as song names, etc.  " \
  "Each status box can also include images for cover art for the currently playing song, and other user defined bitmaps.  " \
  "Any image will be scaled to cover the entire status box.\n\n" \
  "Hint: For best performance, it is advisable to limit the number of $ variables in a status box.  " \
  "It is better to group status variables together depending upon when they change; for example try " \
  "not to mix status which changes regularly (like now playing elapsed time) with status that " \
  "doesn't change regularly (such as 'coming up' status) in one status box.  This is because the entire " \
  "contents of a status box is re-drawn if just one element changes."
};

const char button_control_summary_str[] = { \
  "The button controls are mapped to the following keyboard keys by default, but can be re-mapped to " \
  "other keyboard keys, GPIO inputs, USB joysticks or touch screen inputs defined in the button mapping file.\n\n" \
  "            LEFT : ButtonLeft ........ Move pages left\n" \
  "           RIGHT : ButtonRight ....... Move pages right\n" \
  "               [ : ButtonLeftJump .... Move 'PageJump' pages\n" \
  "               ] : ButtonRightJump ... Move 'PageJump' pages\n" \
  "               , : ButtonLeftAlpha ... Move to prev sort section*\n" \
  "               . : ButtonRightAlpha .. Move to next sort section*\n" \
  "              UP : ButtonUp .......... Move song selection up\n" \
  "                                       (joystick mode only)\n" \
  "            DOWN : ButtonDown ........ Move song selection down\n" \
  "                                       (joystick mode only)\n" \
  " 0 to 9 / A to K : Button0..ButtonK .. Song selection\n" \
  "           ENTER : ButtonSelect ...... Select song\n" \
  "              F1 : ButtonCoin1 ....... Insert coin\n" \
  "              F2 : ButtonCoin2 ....... Insert coin\n" \
  "              F3 : ButtonCoin3 ....... Insert coin\n" \
  "              F4 : ButtonCoin4 ....... Insert coin\n" \
  "              F5 : ButtonFlag1 ....... Toggle status flag 1\n" \
  "              F6 : ButtonFlag2 ....... Toggle status flag 2\n" \
  "              F7 : ButtonFlag3 ....... Toggle status flag 3\n" \
  "              F8 : ButtonFlag4 ....... Toggle status flag 4\n" \
  "           SPACE : ButtonRandom ...... Select random song\n" \
  "       BACKSPACE : ButtonSkip ........ Skip (stops currently\n" \
  "               Z : ButtonPause ....... pause (pauses/unpauses\n" \
  "                                       currently playing song)\n" \
  "               R : ButtonAuto ........ Toggle Auto Play mode\n" \
  "               L : ButtonLoop ........ Toggle Loop mode\n" \
  "               P : ButtonFree ........ Toggle Free Play mode\n" \
  "               X : ButtonClear ....... Clear all songs in\n" \
  "                                       play queue\n" \
  "               = : ButtonVol+ ........ Song volume up\n" \
  "               - : ButtonVol- ........ Song volume down\n" \
  "               M : ButtonMute ........ Mute / Unmute song and\n" \
  "                                       sound effects volume\n" \
  "             ESC : ButtonQuit ........ Quit fruitbox\n" \
  "             F12 : ButtonPowerOff .... Power off Raspberry Pi\n\n" \
  " * The sort sections start with a new letter of the alphabet corresponding to " \
  "the last SortSongsBy value.  For example, if the last SortSongsBy = Artist, " \
  "and the currently displayed artists begin with 'B', then pressing ButtonLeftAlpha " \
  "will move to page which contains the first Artist beginning with the letter 'A'."
  
};

const char button_mapping_file_str[] = { \
  "The button mapping file ('fruitbox.btn' by default, or specified by the --button-map command line option) " \
  "contains data in the same format as the skin configuration files.  " \
  "Each entry specifies a button and its source and parameters.  This file can be automatically " \
  "generated by the '--config-buttons' command line parameter, and then edited later if adjustments " \
  "are needed.\n\nIf the button file does not exist in the same directory as fruitbox, then all buttons will " \
  "adopt their default mappings.  Any buttons not defined in the button file will adopt their default mapping.\n\n" \
  "The following entries in the button file are recognised:"
};

const char button_mapping_file_post_str[] = { \
  "\nEach of the above Button* parameters can be assigned one of the following values...\n\n" \
  "  = Keyboard <code>\n" \
  "  = GPIO <number>\n" \
  "  = Touch <id>\n" \
  "  = Joystick <id> <axis> <position>\n" \
  "The above <code>, <number>, <id>, <axis> and <position> values can be determined by fruitbox using the " \
  "'--config-buttons' or '--test-buttons' command line options."
};


const char troubleshooting_str[] = { \
  "Poor graphics performance is usually caused by not allocating enough memory to the GPU.  " \
  "If the display is very sluggish, or is corrupted / flashing white, quit fruitbox and check " \
  "for any 'GetError_0x505' messages.  These messages mean the GPU hasn't got enough memory to " \
  "create the graphics in video memory, so has to use (slower) CPU memory instead.  To fix this, " \
  "change the Raspberry Pi memory split using the Advanced Options in the raspi-config (type " \
  "'sudo raspi-config' from the command line).  256M is recommended for the GPU, but more may be " \
  "needed if the skin contains lots of large graphics objects."
};

const char hints_and_tips_str[] = { \
  "Automatically run fruitbox on power up\n" \
  "--------------------------------------\n\n" \
  "To run fruitbox automatically on power up, add the following lines to ~/.bashrc :\n\n" \
  "  cd <directory where fruitbox is installed>\n" \
  "  sudo ./fruitbox --cfg <your cfg file>\n\n\n" \
  "Automatically mount USB memory stick on power up\n" \
  "------------------------------------------------\n\n" \
  "If your music is stored on a USB memory stick, you can automatically mount the USB memory " \
  "stick at boot time by typing the following commands:\n\n" \
  "  sudo mkdir -p /mnt/usb\n" \
  "  sudo nano /etc/fstab\n\n" \
  "When inside the nano editor, add the following line at the end of the table...\n\n" \
  "/dev/sda1     /mnt/usb       vfat    defaults    0       0\n\n" \
  "Save (Ctrl-O), then Quit nano (Ctrl-X).  Then in your fruitbox configuration file, set the 'MusicPath' parameter to '/mnt/usb/'\n\n\n" \
  "Animated GIF support\n" \
  "--------------------\n\n" \
  "Animated GIF files can be supported by splitting the GIF file into individual files (by using 'ffmpeg -i file.gif file%02d.jpg' for example), " \
  "including them in a [status] section with multiple 'Bitmap' entries, and specifying the animation speed with 'TimerTickPeriod'.  Then " \
  "in your status Contents text file include the text\n'$IF_TIMER_TICK$DRAW_BITMAP'.\n\n\n" \
  "Animated Touchscreen Buttons\n" \
  "----------------------------\n\n" \
  "Configuring buttons for touch input will only cause a button event to be generated if the touch screen is touched " \
  "in the area of the button defined in the skin file [touch areas]; it won't produce any visual effects.  In order to produce an effect of " \
  "the button being pressed visually, you can define a status object which displays an image of the " \
  "depressed button if the button press event has occurred i.e. in the status Contents file you will " \
  "need the text:\n  $IF_BUTTON_LEFT_PRESSED$DRAW_BITMAP$END_IF\n  $IF_NOT_BUTTON_LEFT_PRESSED$UNDRAW_BITMAP$END_IF\n" \
  "for example when pressing ButtonLeft.  If the status object is placed over a image of an unpressed button (i.e. in the background) " \
  "then this will have the desired effect.\n\n\n" \
  "Quick fruitbox style change using USB memory sticks\n" \
  "---------------------------------------------------\n\n" \
  "As a general tip, you can store the configuration file and database file on a USB memory " \
  "stick along with the music, and run fruitbox using the command 'sudo ./fruitbox --cfg /mnt/usb/fruitbox.cfg'.  " \
  "That way, you could have a complete jukebox look and feel with specific music all self-contained on " \
  "the USB stick, so then all you need to do to change jukebox styles and music collections is to swap USB sticks..." \
  "\n\nLet's Rock!"
};

void UserGuide(void);
