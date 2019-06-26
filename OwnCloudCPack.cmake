include( InstallRequiredSystemLibraries )

set( CPACK_PACKAGE_CONTACT  "Dominik Schmidt <domme@tomahawk-player.org>" )

if ( DEFINED OEM_THEME_DIR AND EXISTS ${OEM_THEME_DIR}/OEM.cmake )
     include ( "${OEM_THEME_DIR}/OEM.cmake" )
else ()
     include ( "${CMAKE_SOURCE_DIR}/OWNCLOUD.cmake" )
endif()

include( VERSION.cmake )
set( CPACK_PACKAGE_VERSION_MAJOR  ${MIRALL_VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR  ${MIRALL_VERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH  ${MIRALL_VERSION_PATCH} )
set( CPACK_PACKAGE_VERSION_BUILD  ${MIRALL_VERSION_BUILD} )
set( CPACK_PACKAGE_VERSION  ${MIRALL_VERSION_FULL}${MIRALL_VERSION_SUFFIX} )

if(APPLE)
    set( CPACK_GENERATOR "DragNDrop" )
    set( CPACK_SOURCE_GENERATOR "")
    set( CPACK_PACKAGE_FILE_NAME ${APPLICATION_SHORTNAME}-${CPACK_PACKAGE_VERSION} )
    set( CPACK_PACKAGE_ICON ${CMAKE_BINARY_DIR}/src/gui/ownCloud.icns)

    set( CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/admin/osx/DS_Store.in")
#    set( CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/admin/osx/DMGBackground.png" )

    set( CPACK_DMG_FORMAT "UDBZ" )
    set( CPACK_DMG_VOLUME_NAME "${APPLICATION_SHORTNAME}")

    # did not work with cmake 2.8.7, so we override MacOSXBundleInfo.plist.in
    #set( CPACK_BUNDLE_PLIST ${CMAKE_SOURCE_DIR}/admin/osx/Info.plist )

    # do we need these?
    #set( CPACK_SYSTEM_NAME "OSX" )
    #set( CPACK_PACKAGE_NAME "FOO" )
    #set( CPACK_BUNDLE_NAME "BAR" )
endif()




if(WIN32)
    #[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX187F8mfVyttyOZ+h98xv0aeSA6hTWRzwwRpjGjzn2G0wt902jdwf97m
mk8Owh3JcFB7qQgmB1vqtAvc/ekWaovVlOU9yqM1u+Xl8CFoN82QjxKfKrRZlBqq
vQmFNFhxK0yYqPCZbWKm4m7kv0yJPXEJApRoiRVbR8ttk41zvJFGiEtOJom9UwDK
Oyf01ViceQnUjD1apiCkwplU+x62Ot4rpJriJMS7LfXDOn24R0YNhzprQlBpbePG
v4MgsmXWqXme/R4DWoheoU9YvoT8mF1IkqQFHyRLaQc=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]
    set( CPACK_PACKAGE_FILE_NAME  "VirtualSAFE-Installer" )
    # Package file name without extension. Also a directory of installer  cmake-2.5.0-Linux-i686
    # CPACK_GENERATOR   CPack generator to be used  STGZ;TGZ;TZ
    # CPACK_INCLUDE_TOPLEVEL_DIRECTORY    Controls whether CPack adds a top-level directory, usually of the form ProjectName-Version-OS, to the top of package tree.  0 to disable, 1 to enable
    # CPACK_INSTALL_CMAKE_PROJECTS    List of four values: Build directory, Project Name, Project Component, Directory in the package     /home/andy/vtk/CMake-bin;CMake;ALL;/
    set( CPACK_PACKAGE_DESCRIPTION_FILE  "${CMAKE_SOURCE_DIR}/README.md" ) # File used as a description of a project     /path/to/project/ReadMe.txt
    set( CPACK_PACKAGE_DESCRIPTION_SUMMARY  "${APPLICATION_NAME} Syncing Client" ) #  Description summary of a project
    # CPACK_PACKAGE_EXECUTABLES   List of pairs of executables and labels. Used by the NSIS generator to create Start Menu shortcuts.     ccmake;CMake
    #[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19HZ7t2Y9OJ3hzx4cm+sY9lMzN5/BnITvNGZVjIB/IHSP0dZvG5G/Vf
d80iakRswMa/Iit1Ri8uho1EqBmjCcqLp0waaSLFoZzOrbVJPC8jgilG/sY8dLeH
nGCNg1PlHaAwC35RUWZU/TM81m9IA5t7GOQRUBr/cW3xLVEmk8wNJFOGJOkqtszS
kOpkWji3RojLx+TEZO9RP+1djD62ZOYt9PiREYjTVST3chNYRdJGAZmuD21qoS6L
+tgKmeFI2e6LxfAMiQobDjVgBNM8g180j0zoz6aNuL+HWopRupTs5j/krFY8Ci8f
6FNVBbaBGR04MWPnQvfGCjs95dALU8OurP/a5uj4PP8=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]
    set( CPACK_PACKAGE_INSTALL_DIRECTORY  "VirtualSAFE" )
    #[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/iBVetYCQBykLh4kASti/zRzpIdIrKjbiPlGamJekppZH24ypxfGl0
1kYL60OLPSbf9ATp15O7t/o3XjoMIIN1KGy/7MdNqfbxS+NI2HGQ5x/FY+U+hVyp
qFpJithqMse5lpaFUYDfTh2NGATn5EE04n+buEK2oPvryDg0QP345VSHvrFeBBFH
QVtrkDpGpDJyo2gxd/CIfb5XMi088krR5bAv1iTXGBsLJD+BG5Ga+m2966rF0LDj
C1oJMTDenqHPdVR2UJP1AQ==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]
    set( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "VirtualSAFE" )
    #[[ ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+bZj+5+u8ISZCfklnqchdFegwfS5onj1mEkgHTIDrcSySSmUR8yV6E
lAG37NAAFLohKXuz2v8qppZf1cv60WqTe6282avXtqiJHqfxPpdZjFykA13U2G2F
XF0n0uc8rF1Ytenf33WjSAHIuvJ/SYn/g29/vkOLIbbcqMPBTgfKFsdBx/DiY3CL
KxuIySrnyB0KG+r4z10pESteaA7XK1lPk96vKVbO13ik3T/mAEeghAFqsNWieQf4
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### ]]
    set( CPACK_PACKAGE_NAME  "VirtualSAFE" )
    set( CPACK_PACKAGE_VENDOR  "http://${APPLICATION_DOMAIN}" )   # Package vendor name
endif()

# set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt" ) # License file for the project, used by the STGZ, NSIS, and PackageMaker generators.  /home/andy/vtk/CMake/Copyright.txt


set( CPACK_TOPLEVEL_TAG "unused" ) # Directory for the installed files.  - needed to provide anything to avoid an error# CPACK_INSTALL_COMMANDS  Extra commands to install components.


# Set the options file that needs to be included inside CMakeCPackOptions.cmake
configure_file("${CMAKE_SOURCE_DIR}/CPackOptions.cmake.in"
    "${CMAKE_BINARY_DIR}/CPackOptions.cmake" @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CPackOptions.cmake") # File included at cpack time, once per generator after setting CPACK_GENERATOR to the actual generator being used; allows per-generator setting of CPACK_* variables at cpack time.  ${PROJECT_BINARY_DIR}/CPackOptions.cmake
include(CPack)
