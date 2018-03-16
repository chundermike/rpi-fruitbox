# rpi-fruitbox
Raspberry Pi fruitbox

fruitbox is a customisable MP3 player for the Raspberry Pi, allowing the user to create the look and feel of classic jukeboxes.

Installation is as follows:

1. It is recommended to start from a fresh OS install (Raspbian Stretch Lite 2017-09-07 release)
2. Increase GPU memory to (at least) 256 (sudo raspi-config -> Advanced Options -> Memory Split)
3. Install fruitbox dependencies and download fruitbox and the example skins...
  
  sudo apt-get install libsm-dev libxcursor-dev libxi-dev libxinerama-dev libxrandr-dev
  
  wget https://codeload.github.com/chundermike/rpi-fruitbox/zip/master
  
  unzip master
  
  cd rpi-fruitbox-master
  
  chmod +x ./fruitbox                  (if you are using Raspbian Stretch)

  chmod +x ./fruitbox-jessie           (if you are using Raspbian Jessie)

NB: in the following instructions, if you are using Raspbian Jessie, substitute './fruitbox' for './fruitbox-jessie'...

4. Copy your music MP3 files (either to the SD card or USB memory stick)
5. Point fruitbox to your MP3 files (edit skins/WallJuke/fruitbox.cfg and/or skins/NumberOne/fruitbox.cfg and change the MusicPath parameter)
6. Run fruitbox ( ./fruitbox --cfg skins/WallJuke/fruitbox.cfg)

For best results, run fruitbox directly from a command line boot, not from a command shell launched from the desktop.

For help, type './fruitbox --help' from the fruitbox installation directory.  The user guide will give details on how to create your own skins, storing songs on USB memory sticks, and other helpful hints.  You can generate the user-guide with the command ./fruitbox --user-guide > user-guide.txt

I have tested it using a Raspberry Pi A+ with a HifiBerry Amp+, and also a Raspberry Pi zero, using the Raspbian Stretch Lite 2017-09-07 release.

Please feedback to me any bugs which need fixing, or any feature requests you would like to see in future releases.

If you design any skins and would like to share them, please let me know and I can include them in the fruitbox github
repository.
