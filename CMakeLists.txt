cmake_minimum_required(VERSION 3.20)

project(moba-routing VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.h.in config.h)

add_executable(
    moba-routing 

    src/main.cpp
    src/msgloop.cpp
    src/layoutparser.cpp
)

install(TARGETS moba-routing)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

target_include_directories(moba-routing PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(moba-routing mobacommon)

target_link_libraries(moba-routing ${CMAKE_SOURCE_DIR}/modules/lib-msghandling/src/moba/libmsghandling.a)

include_directories(${CMAKE_SOURCE_DIR}/modules/lib-msghandling/src)

#AM_CPPFLAGS = \
#    $(GTKMM_CFLAGS) \
#    -I$(srcdir)/../modules/lib-msghandling/src \
#    -I$(srcdir)/../modules/lib-tracklayout/src \
#    -g3 -g -ggdb  -Wall
#
### Process this file with automake to generate Makefile.in
#SUBDIRS = \
#    modules/lib-msghandling/src/moba \
#    modules/lib-tracklayout/src/moba \
#    src
#