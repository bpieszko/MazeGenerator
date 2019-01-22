cmake_minimum_required(VERSION 3.5.1)
project(MazeGenerator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( OpenCV REQUIRED )

include_directories(include)

file(GLOB SOURCES source/*.cpp)

add_executable(MazeGenerator ${SOURCES})
target_link_libraries(MazeGenerator ${OpenCV_LIBS})