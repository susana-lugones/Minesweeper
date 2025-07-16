cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper)

## To link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache (adjust accordingly)
set(SFML_DIR "C:/Users/17863/OneDrive - University of Florida/Desktop/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(minesweeper main.cpp slay.h ScreenGenerator.h Game.h)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)
