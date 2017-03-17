import datetime as dt
import sys

# Reading from the arduino produces a series of 2 digit hex values which, as far
# as I have seen, come in sets of four (e.g. a0 b0 c0 d0). The first line below
# captures all of these and puts them into a list 'gattOutStrs'. However, the
# arduino (or the gatttool code) outputs them in reverse order, so that the
# least significant 2 hex digits are first, and the most significant digits are
# last. The second line of code below puts the pairs of digits into a list
# 'gattOutOrdered' in the right order. I keep the unordered list around just in
# case.
gattOutStrs = [str(i) for i in sys.argv[3:7]]
gattOutOrdered = [str(i) for i in sys.argv[6:2:-1]]

# This portion just turns the list of strs in gattOutStrs into a single string.
# This is just so that we don't lose the information given by gatttool. It also
# does some error-checking to ensure that we HAVE output.
gattOutput = " ".join(gattOutStrs)
if gattOutput == "":
    print("No BT output!")
    sys.exit()

# This is the code that takes the gatttool output gotten from the arduino and
# turns it into useful information. It concatenates the ordered digit pairs into
# a single string, then uses int() to conert the 8 digit hex string into a
# decimal integer.
sentInfo = "".join(gattOutOrdered)
intValue = int(sentInfo, base=16)

# Finally, we output all the pertinent information, namely the gatttool output,
# the hex number the arduino is sending, and the decimal representation of that
# number.
print("gatt Output: " + gattOutput)
print("BT Output: " + sentInfo)
print("Int: " + str(intValue))
