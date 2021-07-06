#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
    //    cv::VideoCapture cap("Pen Detection.mp4");
    int id = 0;
    if (argc == 2)
        id = std::atoi(argv[1]);
    cv::VideoCapture cap(id);

    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video camera" << std::endl;
        return -1;
    }

    double dwidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double dheight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Resolution of the video: " << dwidth << " x " << dheight
              << std::endl;
    std::cout << "Press [Esc] to exit." << std::endl;

    cv::namedWindow("Camera Feed");
    cv::Mat frame;
    cap.read(frame);

    while (true) {
        cap.retrieve(frame);
        bool bsuccess = cap.read(frame);

        if (!bsuccess) {
            std::cout << "Video camera is disconnected!" << std::endl;
            break;
        }

        cv::imshow("Camera Feed", frame);

        if (cv::waitKey(1) == 27) {
            std::cout << "Escape key is pressed by user. Stopping the feed."
                      << std::endl;
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
