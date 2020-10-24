cmake_minimum_required(VERSION 3.10)

project(Tut3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})

add_executable(Tut3 src/main.cpp)
target_link_libraries(Tut3 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})