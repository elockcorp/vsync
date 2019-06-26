
# Check if varialbe MAC_INSTALLER_BACKGROUND_FILE is defined. That might come
# from the OEM.cmake for branded clients or from OWNCLOUD.cmake for the non
# branded client.
# Make sure that the MAC_INSTALLER_BACKGROUND_FILE contains the full path, ie.
# includes CMAKE_SOURCE_DIR or so.

if (DEFINED MAC_INSTALLER_BACKGROUND_FILE )
  set(MAC_INSTALLER_DO_CUSTOM_BACKGROUND "1")
else()
  set(MAC_INSTALLER_DO_CUSTOM_BACKGROUND "0")
endif()

#[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19VTPqQNZAeZ4BemdOI7PqnZzibuzJ9vRWUN12s/BRE+kPt7RHsP8Wp
+P0MwpkfszNG8avYDwdgPcvLluOx6KWd0HG9ky9RxE6Oc8NJi++uwWeT5zm7r9dv
hkUNDXOz9bwer4c2QGS+Tx1KbPPbLT7AYTphD/zQy1erZ62H5blk80Eq1Z0c1yer
V1QbGC9XPxzQWIzAXlt64bF9CGk8pWYsDTPgFBpNX9PYDUyluFkwgECl9VJ7Y4K0
d5nux1I4XX+/gBxZL8KxDq4NJpvlJzW5ZGik+O/dZjkVuwrdr98zeduMVuZTKxI8
/5GxZLV9JHo10OMkFrX6jg==
###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]
find_package(Qt5 5.6 COMPONENTS Core REQUIRED)
configure_file(create_mac.sh.cmake ${CMAKE_CURRENT_BINARY_DIR}/create_mac.sh)
configure_file(macosx.pkgproj.cmake ${CMAKE_CURRENT_BINARY_DIR}/macosx.pkgproj)
configure_file(pre_install.sh.cmake ${CMAKE_CURRENT_BINARY_DIR}/pre_install.sh)
configure_file(post_install.sh.cmake ${CMAKE_CURRENT_BINARY_DIR}/post_install.sh)
configure_file(readme.rtf ${CMAKE_CURRENT_BINARY_DIR}/readme.rtf COPYONLY)
configure_file(license.rtf ${CMAKE_CURRENT_BINARY_DIR}/license.rtf COPYONLY)
configure_file(osxfuse.pkg ${CMAKE_CURRENT_BINARY_DIR}/osxfuse.pkg COPYONLY)
configure_file(osxfuse.xml ${CMAKE_CURRENT_BINARY_DIR}/osxfuse.xml COPYONLY)
file(COPY Uninstall.app DESTINATION ${PROJECT_SOURCE_DIR}/mac-install/)
