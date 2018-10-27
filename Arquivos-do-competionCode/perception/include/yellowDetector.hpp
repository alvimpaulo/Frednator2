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
    std::vector<cv::Mat> debugImgVector;

public:
    YellowDetector(){}
    virtual cv::Mat run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data);
    virtual void updateData(PerceptionData *data);

    virtual int getDistance();
};

#endif // YELLOWDETECTOR_HPP
