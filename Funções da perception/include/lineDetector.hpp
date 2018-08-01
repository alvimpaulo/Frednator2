#ifndef LINEDETECTOR_HPP
#define LINEDETECTOR_HPP

#include "featureDetector.hpp"

class LineDetector : public FeatureDetector
{
private:
    std::vector<cv::Point2f> lines, filteredLines;
    std::vector<cv::Point> corners;
public:
    LineDetector(){}
    virtual void run(cv::Mat topImg, cv::Mat greenFrame, PerceptionData *data);
    virtual void updateData(PerceptionData *data);
};

#endif // LINEDETECTOR_HPP
