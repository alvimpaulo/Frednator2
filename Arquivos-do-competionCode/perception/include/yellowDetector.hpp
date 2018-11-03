#ifndef YELLOWDETECTOR_HPP
#define YELLOWDETECTOR_HPP

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "featureDetector.hpp"


class YellowDetector : public FeatureDetector
{
private:

    int distance;
    float angle;
#ifdef DEBUG_PERCEPTION
    std::vector<cv::Mat> debugImgVector;
#endif


public:
    YellowDetector():
        iLowH(20),
        iHighH(30),
        iLowS(100),
        iHighS(255),
        iLowV(100),
        iHighV(255)
    {}
    virtual void run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data);
    virtual void updateData(PerceptionData *data);

    virtual int getDistance();

    //Yellow HSL values range definitions
    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;
};

#endif // YELLOWDETECTOR_HPP
