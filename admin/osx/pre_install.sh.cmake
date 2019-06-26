#!/bin/sh

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18SIbHlxfb656jokWBj3y3VgUS/ysjzEExJYZKIdRQjVQ4pd6ryhJcp
L2Ur8sL3f/W5etPF7Nc+NQW86U5wEeZbfo+4pdUqKHD5dcApekF8FtG7zjZDQNOC
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
security find-generic-password -s VSYNC
if [ $? -ne 0 ]
then

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19KyJA6ylrhrRc4xsj/60SP/iOj7KZ6KRQZzdA/DoMEgpjqjGsET7+y
m4gnXTlhEpmbj1Iz8nWf0fNBfXC0cgjVIAojbo6K2Va2WtdA35+hRfT2KO+J4Ea/
nPeNtoLybApj0eHZnAfvyuhLZ+hpd+JF/gpxFY+5rHx/dH2hgERA8Jfc1svtlcF+
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
PUBKEYFILENAME=$(basename "$PACKAGE_PATH" .pkg).pubkey
PUBKEYFILEPATH=$(dirname "$PACKAGE_PATH")/$PUBKEYFILENAME
if [ ! -s "$PUBKEYFILEPATH" ]
then
# existing installation not found, assume new installation.
osascript << EOF
display alert "Missing public key file" message "$PUBKEYFILENAME file not found. Please contact support."
EOF
exit 1
fi
else
# existing installation detected.
while [ -d /Volumes/VirtualSAFE ]; do
ANSWER="$(osascript -e 'display dialog "Your vault is currently unlocked. Please lock vault to prevent data corruption. Click Retry when you have done so." buttons {"Retry", "Cancel"} default button "Retry"')"
if [ ! "$ANSWER" = "button returned:Retry" ]; then
exit 1
fi
done
osascript << EOF
display dialog "When update has completed, you will be prompted for keychain password. Please enter your login password and click 'Always Allow'." buttons {"OK"} default button "OK"
EOF
fi

# kill the old version. see issue #2044
: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19lgHt3DCtu+VheLtCb7qB29t/L3K5KgdlO5A7YEm8ANBYaybfXdDLg
N9fxkKyZr2zN6ixTH7d706tVX6w0Gh5qkWMzAyloZ8AW6yMHDoAgY20OgYw/r/xO
BRWfHlE8UpWeDgoMEEPngf7CXfe7hbCzZcxso6K8T262hgqBxYACG5DEJM6fi0V7
guKnqOPHNADdVmrp6jOBJGsvp+0RzhVa/pH544qBwIN1uWlDc43YaUyXpK7+5JON
h3khpGLvdj73UQUlQNZ5Lu8SbCOGCESXpOExe/q0QPQBtgrb0hxj6iZFlJakauGp
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
umount /Volumes/VirtualSAFE
umount -f /Volumes/VirtualSAFE
killall @APPLICATION_EXECUTABLE@ VirtualSAFE

exit 0
