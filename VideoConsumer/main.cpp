#include <iostream>
#include "ReceivedVideo.h"

int main() {

    try {
        auto video = ReceivedVideo();
        video.run();
    } catch (const std::exception &e) {
        std::cout << "\n Error: " << e.what() << std::endl;
    }

    return 0;
}
