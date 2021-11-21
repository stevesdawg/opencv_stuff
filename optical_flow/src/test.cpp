#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

double y_center(Mat m, double w, double h) {
    double weighted = 0;
    double sum = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            sum += m.at<double>(i, j);
            weighted += h * m.at<double>(i, j);
        }
    }
    return weighted / sum;
}

int main(int argc, char* argv[]) {
    //    VideoCapture cap("Pen Detection.mp4");
    int id = 0;
    if (argc == 2)
        id = std::atoi(argv[1]);
    VideoCapture cap(id);

    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video camera" << std::endl;
        return -1;
    }

    auto dwidth = cap.get(CAP_PROP_FRAME_WIDTH);
    double dheight = cap.get(CAP_PROP_FRAME_HEIGHT);

    std::cout << "Resolution of the video: " << dwidth << " x " << dheight
              << std::endl;
    std::cout << "Press [Esc] to exit." << std::endl;

    namedWindow("Camera Feed");
    Mat frame;
    Mat prev_frame;
    Mat diff_frame;
    cap.read(frame);
    cap >> frame;
    frame.copyTo(prev_frame);

    while (true) {
        cap >> frame;
        bool bsuccess = cap.read(frame);

        if (!bsuccess) {
            std::cout << "Video camera is disconnected!" << std::endl;
            break;
        }

        absdiff(frame, prev_frame, diff_frame);
        imshow("Camera Feed", diff_frame);
        frame.copyTo(prev_frame);
        std::cout << "Y Center of Mass: "
                  << y_center(diff_frame, dwidth, dheight) << std::endl;

        if (waitKey(1) == 27) {
            std::cout << "Escape key is pressed by user. Stopping the feed."
                      << std::endl;
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
