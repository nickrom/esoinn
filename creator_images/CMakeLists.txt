cmake_minimum_required(VERSION 3.4)

project(opencv_my_example)

set(OpenCV_DIR /usr/local/share/OpenCV)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/usr/include/)

add_executable(opencv_my_example main.cpp)

target_link_libraries(opencv_my_example ${OpenCV_LIBS})