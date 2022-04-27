find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_C4FM gnuradio-c4fm)

FIND_PATH(
    GR_C4FM_INCLUDE_DIRS
    NAMES gnuradio/c4fm/api.h
    HINTS $ENV{C4FM_DIR}/include
        ${PC_C4FM_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_C4FM_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-c4fmTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_C4FM DEFAULT_MSG GR_C4FM_LIBRARIES GR_C4FM_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_C4FM_LIBRARIES GR_C4FM_INCLUDE_DIRS)
