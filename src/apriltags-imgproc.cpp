#include "apriltags-imgproc.h"

int** conv(unsigned char** baseImg, int width, int height, int** filter, int filterWidth, int filterHeight) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << filter[i][j] << " ";
        }
        std::cout << std::endl;
    }



    // Set up output matrix
    int** convImg = new int*[height];
    for (int row = 0; row < height; row++) {
        convImg[row] = new int[width];
    }

    // Loop through each pixel
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int convElem = 0;

            // Apply each element of the filter
            for (int fRow = 0; fRow < filterHeight; fRow++) {
                for (int fCol = 0; fCol < filterWidth; fCol++) {
                    int rowAdj = fRow - (filterHeight / 2);
                    int colAdj = fCol - (filterWidth / 2);

                    // Check that the filter index is still within bounds and perform linear combination
                    if (row + rowAdj >= 0 && col + colAdj >= 0 && row + rowAdj < height && col + colAdj < width) {
                        convElem += (int)baseImg[row + rowAdj][col + colAdj] * filter[fRow][fCol];
                    }
                }
            }

            convImg[row][col] = convElem;
        }
    }
    return convImg;
}