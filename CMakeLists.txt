cmake_minimum_required(VERSION 3.21)
project(alcode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
find_package(FLTK REQUIRED)

include_directories(${FLTK_INCLUDE_DIRS})

add_executable(alcode main.cpp)
target_link_libraries(alcode fltk)