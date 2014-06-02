CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(liblog)

INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-pedantic -std=gnu99)

ADD_LIBRARY(log SHARED
source/log.c
source/stderr.c
source/syslog.c
)

ADD_EXECUTABLE(demo source/main.c)

TARGET_LINK_LIBRARIES(demo log)

CONFIGURE_FILE(
"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
IMMEDIATE @ONLY
)

ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}"
-P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
