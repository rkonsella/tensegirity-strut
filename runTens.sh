# Wrapper for btInteraction.sh so that the only value you need to enter is
# the speed. Note that the bluetooth address is hard-coded in, so you may need
# to change this.
btAddr="E7:50:27:0F:4A:CB"
mode="rw"
sudo ./btInteraction.sh $btAddr $mode $1
