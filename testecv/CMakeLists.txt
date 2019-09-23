cmake_minimum_required(VERSION 3.14)
project(testecv)

set(CMAKE_CXX_STANDARD 17)

add_executable(testecv main.cpp Labirynth.h Menu.h Fases.h)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# linking
target_link_libraries(testecv ${OpenCV_LIBS})