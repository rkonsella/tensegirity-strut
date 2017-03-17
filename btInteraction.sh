#!/bin/bash
# Script usage:
# sudo btInteraction.sh addr mode data
# The addr parameter is always necessary, and tells the code which bluetooth
# device its aimed at. This parameter mainly exists since the buetooth address
# of the arduino is subject to change. the mode parameter tells the code whether
# it should read from (r), write to (w) or write to and then read from (rw) the
# arduino. Finally, the data parameter takes a hex number to write to the
# arduino if mode = w or rw.

btAddr=${1}  # get the bluetooth address
mode=${2:-"r"}  # get the mode, default to read
writeData=${3:-0x00}  # get the data to write, default to 0
readHandle=0x11  # the bluetooth handle which we read from is 0x11
writeHandle=0x14  # the bluetooth handle we write to is 0x14

if [ "$mode" = "w" ]  # if the mode is write only
then
  echo "writing" #DEBUG CODE
  # use gatttool to write to the proper handle. We throw the output out
  gatttool --device=$btAddr --char-write-req --value $writeData --handle $writeHandle -t random #>/dev/null
  sleep 1
elif [ "$mode" = "rw" ]  # if the mode is write, then read
then
  echo "writing then reading" #DEBUG CODE
  # first, write to the arduino and squelch the output
  gatttool --device=$btAddr --char-write-req --value $writeData --handle $writeHandle -t random #>/dev/null
  # then read from the arduino and give the output to a python script to clean and display
  gatttool --device=$btAddr --char-read --handle $readHandle -t random | xargs python char_translate.py
  sleep 1
else
  # echo "reading"
  # read from the arduino and use a python script to make the output useful
  gatttool --device=$btAddr --char-read --handle $readHandle -t random | xargs python char_translate.py
  sleep 1
fi
