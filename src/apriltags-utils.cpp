#include "apriltags-utils.h"


unsigned char* detect(unsigned char** img, int width, int height) {
    // Construct a sobel filter
    int sobelFilterXRaw[3][3] = {{-1, 0, 1}, 
                                 {-2, 0, 2}, 
                                 {-1, 0, 1}};
    int** sobelFilterX = new int*[3];
    for (int row = 0; row < 3; row++) {
        sobelFilterX[row] = new int[3];
        for (int col = 0; col < 3; col++) {
            sobelFilterX[row][col] = sobelFilterXRaw[row][col];
        } 
    }

    int** convImg = conv(img, width, height, sobelFilterX, 3, 3);
    unsigned char* fImg = flatten(convImg, width, height, -1020, 1020);

    Mat mImg = Mat(height, width, CV_8U, fImg);
    imshow("Display", mImg);
    int k = waitKey(0);

    return fImg;
    // printImg(convImg, width, height);
}


template<typename T>
void printImg(T** img, int width, int height) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            std::cout << (int)img[row][col] << " ";
        }
        std::cout << std::endl << std::endl;
    }
}


unsigned char* flatten(int** img, int width, int height, int min, int max) {
    unsigned char* flattenedArr = new unsigned char[width * height];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            flattenedArr[(row * width) + col] = map(img[row][col], min, max, 0, 255);
        }
    }

    return flattenedArr;
}


int map(float val, float prevMin, float prevMax, float newMin, float newMax) {
    int tVal = val;
    // Center the value
    val -= prevMin;

    // Scale the value to the new range
    float prevRange = prevMax - prevMin;
    float newRange = newMax - newMin;
    val *= (newRange / prevRange);

    // Recenter the value accordingly
    val += newMin;
    // std::cout << tVal << " from (" << prevMin << ", " << prevMax << ") to (" << newMin << ", " << newMax << ") -> " << val << std::endl;
    return (int)val;
}