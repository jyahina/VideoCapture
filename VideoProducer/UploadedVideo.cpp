#include "UploadedVideo.h"

using namespace cv;

void UploadedVideo::send(const char* fileName)
{
    std::future<void> readThread;
    std::vector<std::future<void>> thread(2);

    VideoCapture capture(fileName);
    checkOpeningVideo(capture);

    int fd_even, fd_uneven;
    mkfifo(myfifo, 0666);

    int count = 1;

    while (1)
    {
        Mat frame;

        readThread = std::async([&capture, &frame]{capture >> frame;});
        readThread.wait();

        checkFrame(capture, frame);

        if (count%2 == 0) {
           thread[0] = std::async(std::launch::async, &UploadedVideo::sendFrame, this, std::ref(fd_even), std::ref(frame));
           thread[0].get();
        }
        else {

           thread[1] = std::async(std::launch::async, &UploadedVideo::sendFrame, this, std::ref(fd_uneven), std::ref(frame));
           thread[1].get();
        }

        count++;
        auto stopFrame = static_cast<char>(cvWaitKey(frameInterval));
        if (stopFrame == 27) { break; }
    }

    unlink (myfifo);
    capture.release();
    destroyAllWindows();
}

void UploadedVideo::sendFrame(int &fd, const  Mat& frame)
{
    std::lock_guard<std::mutex> guard(m);

    fd = open(myfifo, O_WRONLY);// Open FIFO for write only
    write(fd,&frame.rows,sizeof(int));
    write(fd,&frame.cols,sizeof(int));
    write(fd, frame.data, 3 * frame.rows * frame.cols);// Write the input arr2ing on FIFO and close it
    close(fd);
}

void UploadedVideo::checkOpeningVideo(const VideoCapture& video)
{
    if (!video.isOpened())
    {
        throw std::runtime_error("Cannot open the video file.");
    }
}

void UploadedVideo::checkFrame(VideoCapture& video, const Mat& frame)
{
    if (!video.read(frame))
    {
        throw std::runtime_error("Cannot read the video file. ");
    }

    if (frame.empty())
    {
        throw std::runtime_error("Cannot read the frame. ");
    }
}