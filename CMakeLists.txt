cmake_minimum_required(VERSION 2.8.9)

project(crap_engine)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.0/lib/cmake/SFML")

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
add_executable(crap_engine main.cpp)
target_link_libraries(crap_engine sfml-graphics sfml-audio)