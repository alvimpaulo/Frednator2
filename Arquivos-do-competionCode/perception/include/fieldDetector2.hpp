#ifndef FIELDDETECTOR2_HPP
#define FIELDDETECTOR2_HPP

#include <featureDetector.hpp>


class FieldDetector2 : public FeatureDetector
{
private:
    cv::Mat greenRegion;

#ifdef DEBUG_PERCEPTION
    std::vector<cv::Mat> debugImgVector;
#endif

public:
    FieldDetector2():
        iLowH(30),
        iHighH(90),
        iLowL(50),
        iHighL(200),
        iLowS(10),
        iHighS(255)
    {}
    cv::Mat getGreenRegion();
    virtual void run(cv::Mat imgTop, cv::Mat imgBot, PerceptionData *data);
    virtual void updateData(PerceptionData* data);

    //Green HSL values range definitions
    int iLowH, iHighH, iLowS, iHighS, iLowL, iHighL;
};

#endif // FIELDDETECTOR2_HPP
