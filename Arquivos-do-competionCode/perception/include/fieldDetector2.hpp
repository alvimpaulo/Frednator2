#ifndef FIELDDETECTOR2_HPP
#define FIELDDETECTOR2_HPP

#include <featureDetector.hpp>


class FieldDetector2 : public FeatureDetector
{
private:
    cv::Mat greenRegion;
    int horizont;

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
        iHighS(255),
        factor(1.0)
    {}
    cv::Mat getGreenRegion();
    virtual void run(cv::Mat imgTop, cv::Mat imgBot, PerceptionData *data);
    virtual void updateData(PerceptionData* data);

    //Green HSL values range definitions
    int iLowH, iHighH, iLowS, iHighS, iLowL, iHighL;
    int factor_int;
    float factor;
};

#endif // FIELDDETECTOR2_HPP
