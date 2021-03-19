#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

int main() {
    cv::Mat image;
    image = cv::imread("sample.jpg", cv::IMREAD_COLOR);

    if(image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Display Window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Window", image);

    cv::waitKey(0);
    return 0;
}
