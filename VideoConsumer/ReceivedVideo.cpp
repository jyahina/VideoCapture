#include "ReceivedVideo.h"

using namespace cv;

void ReceivedVideo::run()
{
    int fd1;
    unsigned char* buf;

    Mat frame;
    mkfifo(myfifo, 0666);

    while (1)
    {
        readBuf(fd1, frame);
        checkFrame(frame);
        showFrame(frame);

        auto stopFrame =  static_cast<char>(cvWaitKey(33));
        if (stopFrame == 27) { break; }
    }
}

void ReceivedVideo::showFrame(const Mat &frame)
{
    namedWindow("Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", frame );
}

void ReceivedVideo::readBuf(int &fd1, cv::Mat &frame)
{
    fd1 = open(myfifo, O_RDONLY);
    int row,column;

    read(fd1,&row,sizeof(int));
    read(fd1,&column,sizeof(int));

    const int size = row*column*3;

    frame = Mat(row, column, CV_8UC3);
    read(fd1, frame.data, size);

    close(fd1);
}

void ReceivedVideo::checkFrame(const cv::Mat &frame)
{
    if (frame.empty()) {
        throw std::runtime_error("Cannot read a frame.");
    }
}
