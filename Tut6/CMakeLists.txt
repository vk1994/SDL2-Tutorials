cmake_minimum_required(VERSION 3.10)

project(Tut6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})

add_executable(Tut6 src/main.cpp)

target_link_libraries(Tut6 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})