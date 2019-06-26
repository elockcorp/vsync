#set( APPLICATION_NAME       "ownCloud" )
#set( APPLICATION_SHORTNAME  "ownCloud" )
#set( APPLICATION_EXECUTABLE "owncloud" )
#set( APPLICATION_DOMAIN     "owncloud.com" )
#set( APPLICATION_VENDOR     "ownCloud" )
#set( APPLICATION_UPDATE_URL "https://updates.owncloud.com/client/" CACHE string "URL for updater" )
#set( APPLICATION_ICON_NAME  "owncloud" )
#set( APPLICATION_VIRTUALFILE_SUFFIX "owncloud" CACHE STRING "Virtual file suffix (not including the .)")

#set( LINUX_PACKAGE_SHORTNAME "owncloud" )

#set( THEME_CLASS            "ownCloudTheme" )
#set( APPLICATION_REV_DOMAIN "com.owncloud.desktopclient" )
#set( WIN_SETUP_BITMAP_PATH  "${CMAKE_SOURCE_DIR}/admin/win/nsi" )

#set( MAC_INSTALLER_BACKGROUND_FILE "${CMAKE_SOURCE_DIR}/admin/osx/installer-background.png" CACHE STRING "The MacOSX installer background image")

## set( THEME_INCLUDE          "${OEM_THEME_DIR}/mytheme.h" )
## set( APPLICATION_LICENSE    "${OEM_THEME_DIR}/license.txt )

#option( WITH_CRASHREPORTER "Build crashreporter" OFF )
#set( CRASHREPORTER_SUBMIT_URL "https://crash-reports.owncloud.com/submit" CACHE string "URL for crash reporter" )

########################################################################

#[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19g+amyXQKBd7inOv7NoJimRALaQBeELQJzk4IO0K5qjELmlwVXptiC
TSSPgz2AmPM7j6XhB50ASoEDhYDXXPPd4XA+moeV9ixS/3swD3L/j6wgr3Tot5cL
qC5xcXtHLAZokDkIDPPn8QuE8/5s7WVF/8QXMICLQww=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]

set( APPLICATION_NAME       "VSYNC" )
set( APPLICATION_SHORTNAME  "VSYNC" )
set( APPLICATION_EXECUTABLE "VSYNC" )
set( APPLICATION_DOMAIN     "www.elock.com.my" )
set( APPLICATION_VENDOR     "e-Lock Corporation" )
set( APPLICATION_UPDATE_URL "https://s3-ap-southeast-1.amazonaws.com/updates-ap-southeast-1.virtualsafe.cloud/" CACHE string "URL for updater" )
set( APPLICATION_ICON_NAME  "VSYNC" )
set( APPLICATION_VIRTUALFILE_SUFFIX "vsync" CACHE STRING "Virtual file suffix (not including the .)")

set( LINUX_PACKAGE_SHORTNAME "VSYNC" )

set( THEME_CLASS            "ownCloudTheme" )
set( APPLICATION_REV_DOMAIN "my.com.elock.vsync" )
set( WIN_SETUP_BITMAP_PATH  "${CMAKE_SOURCE_DIR}/admin/win/nsi" )

set( MAC_INSTALLER_BACKGROUND_FILE "${CMAKE_SOURCE_DIR}/admin/osx/installer-background.png" CACHE STRING "The MacOSX installer background image")

set( APPLICATION_LICENSE    "${CMAKE_SOURCE_DIR}/license.rtf" )

option( WITH_CRASHREPORTER "Build crashreporter" OFF )
set( CRASHREPORTER_SUBMIT_URL "" CACHE string "URL for crash reporter" )

#[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18xERTfXcEJTq2yCL5rhfva0dyzQV1Wm46eU7tqBUUqUB8jEWKyamAD
dssC2p4rBA/Xmsl4+8ff1uWqN0mCpvT2yB+868cE8KoPaUrNEJf0C9uAfscV4lcQ
gfV8ds4HtScH9VEEqSOK52rNY48yRhj3MCX087m1gf0yAEVa5eQqZlOeglrqc0W0
###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]

set ( CMAKE_OSX_DEPLOYMENT_TARGET   "10.11" )
set ( MACOSX_DEPLOYMENT_TARGET      "10.11" )
