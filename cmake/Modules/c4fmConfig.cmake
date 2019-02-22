INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_C4FM c4fm)

FIND_PATH(
    C4FM_INCLUDE_DIRS
    NAMES c4fm/api.h
    HINTS $ENV{C4FM_DIR}/include
        ${PC_C4FM_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    C4FM_LIBRARIES
    NAMES gnuradio-c4fm
    HINTS $ENV{C4FM_DIR}/lib
        ${PC_C4FM_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(C4FM DEFAULT_MSG C4FM_LIBRARIES C4FM_INCLUDE_DIRS)
MARK_AS_ADVANCED(C4FM_LIBRARIES C4FM_INCLUDE_DIRS)

