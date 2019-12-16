#include <iostream>
#include <exception>
#include <experimental/filesystem>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/videoio.hpp>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <future>
#include<mutex>

class UploadedVideo {
public:
    UploadedVideo() = default;
    void send(const char* fileName);

private:
    const int frameInterval = 33;
    const char * myfifo = "/tmp//myfifo"; // FIFO file path
    std::mutex m;

    void checkOpeningVideo(const cv::VideoCapture& video);
    void checkFrame(cv::VideoCapture& video, const cv::Mat& frame);
    void sendFrame(int &fd, const cv::Mat& frame);
};

