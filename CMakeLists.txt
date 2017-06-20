cmake_minimum_required(VERSION 3.7)
project(SDL_Basics)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

include_directories($(SDL2_INCLUDE_DIR))

set(SOURCE_FILES main.cpp Screen.cpp Screen.h Particle.cpp Particle.h Swarm.cpp Swarm.h)
add_executable(SDL_Basics ${SOURCE_FILES})
target_link_libraries(SDL_Basics ${SDL2_LIBRARY})