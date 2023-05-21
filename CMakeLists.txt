cmake_minimum_required(VERSION 3.1)

project(
    Game
    VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")


add_executable(player main.cpp ${SOURCES} )
add_executable(mediator main.cpp ${SOURCES} )

set_target_properties(mediator PROPERTIES COMPILE_FLAGS "-DM" )
set_target_properties(player PROPERTIES COMPILE_FLAGS "-DP" )
