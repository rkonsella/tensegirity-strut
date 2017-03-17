# Written by James Boggs
# Uses btInteractions.sh and char_translate.py to interact with a Simblee
# RFDuino.
# Eventually this code should allow the user to change the frequency of the
# motor(s) controlled by the RFDuino at will, while consistently gathering data
# from the RFDuino. Currently, it allows the user to set the motor to a certain
# frequency, sort of. More realistically, it allows the user to adjust how fast
# the motor spins on a scale from 0-255, but the actual mapping between that
# scale and the actual frequency of the motor is unknown.

# Usage: sudo python runTens.py speed

import sys
import subprocess
from time import sleep

def int2Hex(val):
    return "0x%0.2X" % val

if __name__ == '__main__':
    speed = sys.argv[1]
    try:
        speed = int(speed)
    except ValueError:
        print("Invalid speed {spd}! Speed must be in [0-255]".format(spd=speed))
        sys.exit()

    if speed < 0 or speed > 255:
        print("Invalid speed {spd}! Speed must be in [0-255]".format(spd=speed))
        sys.exit()

    hexSpeed = int2Hex(speed)
    print hexSpeed
    # subprocess.call(["sudo", "./btInteraction.sh", "E7:50:27:0F:4A:CB", "w", hexSpeed])
