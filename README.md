# rpi-fruitbox
Raspberry Pi fruitbox

fruitbox is a customisable MP3 player for the Raspberry Pi, allowing the user to create the look and feel of classic jukeboxes.

Installation is as follows:

1. It is recommended to start from a fresh OS install (Raspbian Stretch Lite 2018-03-13 release)
2. Increase GPU memory to (at least) 256 (sudo raspi-config -> Advanced Options -> Memory Split)
3. From a command shell, type : wget https://github.com/chundermike/rpi-fruitbox/raw/master/install.sh
4. From a command shell, type : chmod +x ./install.sh
5. From a command shell, type : source ./install.sh
6. Copy your music MP3 files (either to the SD card or USB memory stick)
7. Point fruitbox to your MP3 files (edit skins/WallJuke/fruitbox.cfg (or any other skin you fancy) and change the MusicPath parameter)
8. Run fruitbox ( ./fruitbox --cfg skins/WallJuke/fruitbox.cfg)

Run with --config-buttons command line argument to map buttons to touch screen, GPIO and/or USB controllers.

For best results, run fruitbox directly from a command line boot, not from a command shell launched from the desktop.

The user guide will give details on how to create your own skins, storing songs on USB memory sticks, and other helpful hints.

fruitbox works on all Raspberry Pi devices except model 4, but runs better on the higher spec (quad core) machines (i.e. Models 2 and 3), especially if playing music videos.

Please feedback to me any bugs which need fixing, or any feature requests you would like to see in future releases.

If you design any skins and would like to share them, please let me know and I can include them in the fruitbox github
repository.

If you wish to encourage fruitbox development, please consider making a donation to the author at https://paypal.me/rpifruitbox

Thanks!
