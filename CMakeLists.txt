cmake_minimum_required(VERSION 3.25)
project(Game01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Game01 main.cpp src/enums/AsciiChar.h src/Game.h src/Player.h config.h src/LabirinthGenetator.h src/utils.h src/Enemy.h)
