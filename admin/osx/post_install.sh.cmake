#!/bin/sh

#osascript << EOF
#tell application "Finder"
#   activate
#   select the last Finder window
#	reveal POSIX file "/Applications/@APPLICATION_EXECUTABLE@.app"
#end tell
#EOF

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19grdovLeaxqbnhN7mPbP+NLUD/DwWvwczlpA3ogQfvaVu3MyK9zDYq
ii3Kso18JZjwXevfxrgzuPj894rjDatWktC1xdi1sM/8Rb5xKuGK2+9aC+HjaVCm
uc7dMAH6ibN6DhiaMQBf0UNilYw0G4hT6ZZNt/DxQWqnrTG6udDROdsy/ax8OHGx
QJa6zaZvXuf+GxShCtxkabQvC4dapvpoTxds9qn+eYziQAbFm/PsDFinpg2Uh9IC
+w7gxC+9zYf1vyVnwCPbhvVSbPCNa4WL77kibEC/o4I=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
PUBKEYFILENAME=$(basename "$PACKAGE_PATH" .pkg).pubkey
PUBKEYFILEPATH=$(dirname "$PACKAGE_PATH")/$PUBKEYFILENAME
if [ -s "$PUBKEYFILEPATH" ]
then
base64 -D -i "$PUBKEYFILEPATH" -o "/tmp/$PUBKEYFILENAME"
unzip -q -o "/tmp/$PUBKEYFILENAME" -d /tmp
if [ ! \( -s "/tmp/CUSTOM_public_key.der" -a -s "/tmp/CUSTOM_single_user_credential" \) ]
then
osascript << EOF
display alert "Corrupted public key file" message "Public key file is invalid. Please contact support."
EOF
rm -f "/tmp/$PUBKEYFILENAME" /tmp/CUSTOM_public_key.der /tmp/CUSTOM_single_user_credential
exit 1
fi
rm -f "/tmp/$PUBKEYFILENAME"
fi

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19aGEBGaJmMKbOWLrD1U1wAxJHrfOTeIPC6LJ2uMgE9hBV7yHuXiOnf
VWA5HlNoA59RoWoCrHNC+8R4kQrcM3o9dEwE9l6CnKTl3BO91n49AMJX6SQLjLMB
FViBBIW3S2tQJ5mQbpsaIDKBrQ9XZtEVstQMqXzCciwTo057fKYxUITj5SB4adJS
kxNcQXVCoCEr3ICbOVndDIQj+CzZrJ6i3oPEGpI388WibQdKHYhwrVBnJ+7PJmOc
HM6ZUiQ1zBdFSjiBsGcwbe09FyLsfQ1nITr+4DDgnWP2yAt0HYB8htX+Sw1XtS9a
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/NiYKLlrMN9kIdhPOGN8UYAsGLL9Hm1tnmFAXVdnfwvNqu4pdg4faR
w1pIrMFHHr2zZYXXiEBNwA==
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
sudo mkdir -p ~${USER}/VSYNC
sudo chown -R $USER ~${USER}/VSYNC

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+wxlf5kB/BCqBWreEntMCoDlm0+QEOEB/opOf6v9F+a6JXDeIyivHW
lrdF6OpHu4UMSQPTpBcmRYnat8F5chv3yLxQ1fN4eM9U7FcX1iG+gnNE8b5ETQsk
YVMuqqqpc9L/w9tAxqF5OuxkJScep6+eI4weMHWA1+CcTwD6Rc9NceSvRJPBIeIf
EW9TYbIXfjWCpq0SboFsJwU21KYIOF4OjunAePT6seU=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
if [ -s "/tmp/CUSTOM_single_user_credential" ]
then
mv /tmp/CUSTOM_single_user_credential ~${USER}/vsync.login
sudo chown $USER ~${USER}/vsync.login
fi
: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/yog08+xfM13S8zJSmgLQN7vhxjUNrUeN0kLJ23PxC0u8/wicVXGu9
DGxIlK6zHprA4/d7n7RVHbTp8D/7yeqKphnyz/hkhVCdyV/folTf6DpNNcYE6hu1
3wR09I4s8wFbMqut6v9V9Ux/kOE189elwVzfiVNcdfK9+jmEyfkYkacHFq5a909y
wZVNIBamXOlIj459y+bkNwKYUs7FzauAHXa7sJZ5B+A=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
if [ -s "/tmp/CUSTOM_public_key.der" ]
then
sudo mkdir -p ~${USER}/.VirtualSAFE
mv /tmp/CUSTOM_public_key.der ~${USER}/.VirtualSAFE/public_key.der
sudo chown -R $USER ~${USER}/.VirtualSAFE
fi

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/uwveiusGaHLPybBi3mfrTOd3BM4PdAfmXnEkLw1JQJNRqUl4WCypZ
53LFJEqWDSoL7VIKOor98Y5P6zC/ySyrxIUPP+Tntk48Bq3kQbtT5bEXS3QNaghT
QUCSyhCOIERm90CL9ZWfKyQoF9r5YqVdtSMP1Z3YrICd3rWtla031228MPD0x02X
C38Ckw715GitMoR2P7REulRaYMYaHvQUu4mDdTa7nyYHKZt7faw5qD35Krh+zyIv
8XoE0gRDRX0T4Rzrjdj9GzcGcMLZcLJOetMwsyqk54GBOzPz2Sfy17f/dHG0i2rN
GvtUSG9XOaguWOdjztDue9SYCryk5Kf9SSXC50qvbBk=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
osascript << EOF
set vsyncApp to "/Applications/VirtualSAFE/VSYNC.app"
tell application vsyncApp to launch
set vsafeApp to "/Applications/VirtualSAFE/VirtualSAFE.app"
tell application vsafeApp to launch
tell application "System Events"
    get the name of every login item
    if login item "VSYNC" exists then
        delete login item "VSYNC"
    end if
    if login item "VirtualSAFE" exists then
        delete login item "VirtualSAFE"
    end if
	make new login item at end of login items with properties {name:"VSYNC", path:"/Applications/VirtualSAFE/VSYNC.app", hidden:false}
	make new login item at end of login items with properties {name:"VirtualSAFE", path:"/Applications/VirtualSAFE/VirtualSAFE.app", hidden:false}
end tell
EOF

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/MRVvdyB5OFdiLxy9BmEe2i8XIjqpi4ol687nvy4QdESKHRb/ojUGT
67NWpEaZ8vBUql/2okSpdG66lU3ggWuCJ/aqHBCABx7rgZSqajtRLl1sJ8MHnCpA
M9k3VjbtZr3D4UYIJ44dbA==
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
# # Always enable the new 10.10 finder plugin if available
# if [ -x "$(command -v pluginkit)" ]; then
#     # add it to DB. This happens automatically too but we try to push it a bit harder for issue #3463
#     pluginkit -a  "/Applications/@APPLICATION_EXECUTABLE@.app/Contents/PlugIns/FinderSyncExt.appex/"
#     # Since El Capitan we need to sleep #4650
#     sleep 10s
#     # enable it
#     pluginkit -e use -i @APPLICATION_REV_DOMAIN@.FinderSyncExt
# fi

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18ZbTIPONXTIkycZQOi8juCWFpEfXMBqgQzwLAdpwEBbS32dTpA17EW
4Dq/+hRxEcsQ9cVPH69ecwDUFVRiM2KTJr1/jiTdKooUFc/SvISuQarJo6QoaCUB
RYbz1MQCWB0bBZgVNr7S04xRREjRD55+OM0LLL2/xYDsOuzAiMp6ZV+CDEfp2cSc
GeYOrIX/JBtPLwmjPeW9XTYVPOMUgKDyfLfxYBzqe7V5hQn4NG08bYSvfheMpenR
6Y45VQvbt4GaucZ7ffUGMBWIeRe8JhQeBPce9SVt5d0Jda0LRPq1HI3i2r924li0
X5hoFbzXYG0nYyN20J9bk/oMtUUSwGcXOJ+g7vhNiOKkEKyKFCvV/V5anz3Y1aup
tKHAlkn/MUR0gN/W4WWsCIWDGybHiC8pXwpoyTWc7NsSxgyXemW3wNrbzzfeVJuG
fMPij6H8NDOrRU0BZ8L1JREW/XlZSxOomOEUcjp0YHYW6U4j99e4Fi7VpZajqYOy
7yg/jVDABWl3FE8s/VUlPQgKIudcLbedybZYa09fTtSt8z8mPVuDXQKa1SWAxNZN
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '
sudo installer -pkg "osxfuse.pkg" -target / -applyChoiceChangesXML "osxfuse.xml"

exit 0
