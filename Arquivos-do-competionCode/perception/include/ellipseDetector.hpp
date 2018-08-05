#ifndef ELLIPSEDETECTOR_HPP
#define ELLIPSEDETECTOR_HPP

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "featureDetector.hpp"


class EllipseDetector : public FeatureDetector
{
private:
    cv::Point media;
    float media_angle;
public:
    EllipseDetector(){}
    virtual cv::Mat run(cv::Mat topImg, cv::Mat greenFrame, PerceptionData *data);
    virtual void updateData(PerceptionData *data);
};

#endif // YELLOWDETECTOR_HPP
