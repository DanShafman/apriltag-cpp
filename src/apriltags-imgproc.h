#include <iostream>

/*
Convolve base matrix with specified filter.
*/
int** conv(unsigned char** base, int width, int height, int** filter, int filterWidth, int filterHeight);