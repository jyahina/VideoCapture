cmake_minimum_required(VERSION 3.15)
project(VideoConsumer)

set(CMAKE_CXX_STANDARD 17)
set (OpenCV_DIR /usr/share/OpenCV)

find_package( OpenCV  REQUIRED )
add_executable(VideoConsumer main.cpp ReceivedVideo.cpp ReceivedVideo.h)

link_libraries(stdc++fs)
target_link_libraries(VideoConsumer ${OpenCV_LIBS})