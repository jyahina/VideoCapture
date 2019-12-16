cmake_minimum_required(VERSION 3.15)
project(VideoProducer)

set(CMAKE_CXX_STANDARD 17)
set (OpenCV_DIR /usr/share/OpenCV)

find_package( OpenCV  REQUIRED )
find_package(Threads)

include_directories(video_out)
add_executable(VideoProducer main.cpp UploadedVideo.cpp UploadedVideo.h)

link_libraries(stdc++fs)
target_link_libraries(VideoProducer ${OpenCV_LIBS} pthread)
