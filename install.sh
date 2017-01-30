#!/bin/bash
#detect zenity
sudo apt-get update
zenity --help &> /dev/null

if [ $? -ne 0 ] ; then
	echo "You need zenity to run driver LogiLed"
	sudo apt-get install zenity -y
fi

git --help &> /dev/null

if [ $? -ne 0 ] ; then
        echo "You need git to run driver LogiLed"
        sudo apt-get install git -y
fi

g++ --help &> /dev/null

if [ $? -ne 0 ] ; then
        echo "You need g++ to run driver LogiLed"
        sudo apt-get install g++ -y
fi

make --help &> /dev/null

if [ $? -ne 0 ] ; then
        echo "You need make to run driver LogiLed"
        sudo apt-get make git -y
fi

sudo apt-get install linux-headers-$(uname -r) -y
sudo apt-get install libusb-1.0-0 -y
sudo apt-get install libusb-1.0-0-dev -y

make
sudo make install

sudo cp logiled /usr/bin/logiled
sudo chmod +x /usr/bin/logiled
