/*
TODO:
- Make class for different filters (Sobel, etc.)
- Optimize everything (float arithmetic, runtime)
*/

#include "apriltags-imgproc.h"

/*
Detect a 36h11 tag in the provided image.
*/
unsigned char* detect(unsigned char** img, int width, int height);

/*
Prints the contents of an image as a 2D matrix in plaintext to the console.
*/
template<typename T>
void printImg(T** img, int width, int height);

/*
Flattens a 2D image matrix into a 1D array. This is useful for displaying images in OpenCV imshow.
*/
unsigned char* flatten(int** img, int width, int height, int min, int max);

/*
Map a value from one range onto another.
*/
int map(float val, float prevMin, float prevMax, float newMin, float newMax);