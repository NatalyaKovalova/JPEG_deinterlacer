cmake_minimum_required(VERSION 3.10)
project(JPEGDeinterlacer)

find_package(JPEG REQUIRED)

set(SOURCES main.cpp)

include_directories(${JPEG_INCLUDE_DIR})

add_executable(your_executable_name ${SOURCES})
target_link_libraries(your_executable_name ${JPEG_LIBRARY})
