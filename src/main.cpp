/*
Program to test functionality of the Apriltags C++ library; simply captures video stream, converts
to grayscale, and attempts to detect the apriltag in it. Depends on opencv.
*/

// g++ $(pkg-config --cflags --libs opencv4) -std=c++11  main.cpp

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "apriltags-utils.h"

using namespace std;
using namespace cv;

int main() {
    Mat frame, grayFrame;
    VideoCapture cap;
    int width, height;
    unsigned char** rawImg;

    // Start video stream capture
    cap.open(0, CAP_ANY);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
    height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);

    // Initialize raw image matrix
    rawImg = new unsigned char*[height];

    // Handle frame
    while (true)
    {
        // Read in frame 
        cap.read(frame);
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        // Convert frame to grayscale and store in byte array
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        for (int row = 0; row < height; row++) {
            rawImg[row] = grayFrame.ptr(row);
        }

        // Display frame
        imshow("Display", grayFrame);
        if (waitKey(5) >= 0)
            break;
    }

    unsigned char* fImg = detect(rawImg, width, height);

    // std::cout << map(12, -1020, 1020, 0, 255) << std::endl;
    std::cout << "\nend\n";

    return 0;
}