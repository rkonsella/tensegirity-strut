## by James Boggs and Riley Konsella
## jboggsy and rkonsella

# Wireless Tensegrity Code
## How to:
`./runTens.sh motorSpeed` runs the motor at motorSpeed, e.g.: `./runTens.sh 0x20`

`motorSpeed=0x00` re-arms the ESC

`motorSpeed>=0x20` starts the motor spinning

`motorSpeed=0xff` is the fastest speed

If the code stops working because it can't connect to the device, and you know you're connected to the RFDuino, look at bluetooth settings and replace the btAddr variable in runTens.sh with the new bluetooth address of the RFDuino.
## Details
This is all the code we have right now for running the wireless tensegrity. It doesn't do much besides communicate with the bluetooth onboard the RFDuino and set certain values, which the RFDuino can interpret. It can also receive data from the RFDuino. The core code is in three files:
* btInteraction.sh is the shell script which directly interacts with the bluetooth stuff. It can be used standalone, if needed.
* char_translate.py is a python script which accepts four arguments of two-character strings and tries to turn them into useful data. It is there because the gatttool output produces four space-separated values, not a single value. It just makes it easier to interpret what the RFDuino is sending.
* runTens.sh is the easy way to activate the motors, since it only needs one parameter. It just wraps btInteraction.sh, though, and uses a static bluetooth address.

The core functionality is encapsulated in btInteraction.sh. Use it through shell as

`sudo ./btInteraction.sh addr mode data`

* addr should be the bluetooth address of the RFDuino, which is subject to change. To find it, open up the bluetooth settings on your computer and find the RFDuino. It is named 'VALTR.' Somewhere on VALTR's settings should be it's address, which looks like E7:50:27:0F:4A:CB.
* mode is whether you want the code to read from the RFDuino ('r'), write to the RFDuino ('w'), or both ('rw').
* data is the value you want to write to the RFDuino, if you are writing. To use the motor through this or runTens.sh, see further below.

runTens.sh wraps this by using a built-in static bluetooth address and mode ('rw'). Use it through the shell as

`./runTens.sh motorSpeed`

* motor speed controls, shockingly enough, the speed of the motor.

## Motor speed control info
Sending data over bluetooth to the RFDuino is very particular. You *MUST* send data as 2-digit hex values, e.g. 0x20, otherwise the RFDUino doesn't know how to interpret it (read: I don't know how to make the RFDuino interpret it). Thus, the motor speed is mapped from the minimum (0x00) to the maximum (0xff) values of this setup to the minimum (1100) to the maximum (2000) pulse values on the RFDUino.

Only a pulse value of 1200 or more will actually spin the motor, everything else is effectively off. The lowest hex value which maps to above 1200 is 0x20, anything less than that will turn the motor off. The value 0x00 has special significance. It re-arms the ESC.
