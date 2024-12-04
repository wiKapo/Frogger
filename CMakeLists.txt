cmake_minimum_required(VERSION 3.29)
project(Frogger C)

set(CMAKE_C_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Frogger
        main.c window.c)
target_link_libraries(nazwaprojektu ${CURSES_LIBRARIES})