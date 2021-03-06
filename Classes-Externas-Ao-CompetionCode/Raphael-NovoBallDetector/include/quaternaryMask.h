#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#ifndef QUATERNARYMASK_H
#define QUATERNARYMASK_H


class quaternaryMask
{
public:
    quaternaryMask(){}

    int blackLMax, whiteLMin, greenHMean, greenHVar, greenSMin;

    cv::Mat blackMask, whiteMask, greenMask;

    void setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin);
    void generateMask(cv::Mat image);

};

#endif // QUATERNARYMASK_H
