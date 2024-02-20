cmake_minimum_required(VERSION 3.10)

project(JPEGDeinterlacer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(JPEGDeinterlacer main.cpp Core/File.cpp)
target_include_directories(JPEGDeinterlacer PRIVATE Core)

find_package(JPEG REQUIRED)
target_include_directories(JPEGDeinterlacer PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(JPEGDeinterlacer PRIVATE ${JPEG_LIBRARIES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
