cmake_minimum_required(VERSION 3.1)

project(
    Game
    VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(game main.cpp ${SOURCES} )
