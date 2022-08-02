cmake_minimum_required(VERSION 3.15)
project(TP3 C)

set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} src/main.c src/pile.c src/World.c src/struct.h)

include_directories(include)
include_directories(lib)

find_library(CURSES_LIBRARY pdcurses lib)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${CURSES_LIBRARY})
