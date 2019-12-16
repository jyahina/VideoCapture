#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

class ReceivedVideo {
public:
    ReceivedVideo() = default;
    void run();

private:
    const char * myfifo = "/tmp/myfifo";

    void readBuf(int &fd1, cv::Mat &frame);
    void checkFrame(const cv::Mat &frame);
    void showFrame(const cv::Mat &frame) ;
};


