CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(liblog)

INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-pedantic -std=gnu99)

ADD_EXECUTABLE(demo source/main.c
include/log/syslog.h
include/log/stderr.h
include/log/log.h
source/syslog.c
source/log.c
source/stderr.c
)
