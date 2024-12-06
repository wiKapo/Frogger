cmake_minimum_required(VERSION 3.29)
project(Frogger C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Frogger main.c window.h window.c file.c
        colors.c
        time.c
        time.h
        game.c
        game.h)

target_link_libraries(Frogger ${CURSES_LIBRARIES})