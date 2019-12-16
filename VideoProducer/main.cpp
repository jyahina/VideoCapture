#include <iostream>
#include "UploadedVideo.h"

int main() {
    const char* defaultFile = "../../video.mp4";

    try {
        auto video = UploadedVideo();
        video.send(defaultFile);
    } catch (const std::exception &e) {
        std::cout << "\nError: " << e.what() << std::endl;
    }

    return 0;
}
