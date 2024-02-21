cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JPEGDeinterlacer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(JPEGDeinterlacer main.cpp 
Core/BaseImageProcessingCommandCollection.cpp 
Core/DeinterlacerJPEGProcessingCommand.cpp 
Core/File.cpp 
Core/ImageProcessingCommandCollectionsHolder.cpp 
Core/ImageProcessor.cpp 
Core/JPEGImage.cpp 
Core/JPEGImageProcessingCommandCollection.cpp 
)

target_include_directories(JPEGDeinterlacer PRIVATE Core)

find_package(JPEG REQUIRED)
target_include_directories(JPEGDeinterlacer PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(JPEGDeinterlacer PRIVATE ${JPEG_LIBRARIES})


