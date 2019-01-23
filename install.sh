#!/bin/bash
echo "----------------------"
echo "Installing fruitbox..."
echo "----------------------"
rm master*
rm -Rf rpi-fruitbox-master
sudo apt-get -y install libsm-dev libxcursor-dev libxi-dev libxinerama-dev libxrandr-dev libxpm-dev libvorbis-dev libtheora-dev
wget https://codeload.github.com/chundermike/rpi-fruitbox/zip/master
unzip master
cd rpi-fruitbox-master
chmod +x ./fruitbox
echo
echo "Quick Start Guide"
echo "-----------------"
echo "1. Choose a skin (see skins directory); lets call it MYSKIN."
echo "2. Edit (using nano for example) the skins/MYSKIN/fruitbox.cfg file"
echo "   and change the MusicPath value to point to where your mp3 files are kept."
echo "3. run fruitbox..."
echo "   sudo ./fruitbox --cfg skins/MYSKIN/fruitbox.cfg"
echo ""
echo "For help, run fruitbox with no arguments (i.e. ./fruitbox)"
