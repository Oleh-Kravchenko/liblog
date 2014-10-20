CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(liblog)

INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-pedantic -std=gnu99)

# support subdirectory
SET(LIBLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)

# main
SET(LIBLOG_SOURCES
include/tools/list.h
include/liblog/log.h
include/liblog/stderr.h
include/liblog/syslog.h
source/log.c
source/stderr.c
source/syslog.c
)

ADD_LIBRARY(logcore OBJECT ${LIBLOG_SOURCES})
SET_PROPERTY(TARGET logcore PROPERTY COMPILE_FLAGS "-fPIC")

ADD_LIBRARY(log SHARED $<TARGET_OBJECTS:logcore>)

ADD_LIBRARY(log_static STATIC $<TARGET_OBJECTS:logcore>)
SET_TARGET_PROPERTIES(log_static PROPERTIES OUTPUT_NAME "log")

ADD_EXECUTABLE(demo source/main.c)
TARGET_LINK_LIBRARIES(demo log)


# uninstall target
CONFIGURE_FILE(
"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
IMMEDIATE @ONLY
)

ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}"
-P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)


# install
INSTALL(TARGETS log log_static
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
)

INSTALL(FILES
include/tools/list.h
include/liblog/log.h
include/liblog/stderr.h
include/liblog/syslog.h
DESTINATION include/liblog
)
