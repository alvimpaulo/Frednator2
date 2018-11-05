#ifndef BALLDETECTORRAPHA_H
#define BALLDETECTORRAPHA_H

#include "../../Arquivos-do-competionCode/perception/include/featureDetector.hpp"
#include "./include/houghCirclesContrast.h"
#include "./include/quaternaryMask.h"
#include "./include/pixelCountCheck.hpp"


#define BLACK_L_MAX 50
#define WHITE_L_MIN 200
#define GREEN_H_MEAN 60
#define GREEN_H_VAR 40
#define GREEN_S_MIN 10
#define HOUGH_PARAM_1 20
#define HOUGH_PARAM_2 28
#define PIXEL_PARAM_1 0.55
#define PIXEL_PARAM_2 0.35


class ballDetectorRapha: public FeatureDetector
{
public:
    ballDetectorRapha():
        blackLMax(BLACK_L_MAX),
        whiteLMin(WHITE_L_MIN),
        greenHMean(GREEN_H_MEAN),
        greenHVar(GREEN_H_VAR),
        greenSMin(GREEN_S_MIN),
        hough_param1(HOUGH_PARAM_1),
        hough_param2(HOUGH_PARAM_2),
        pixel_param1(PIXEL_PARAM_1),
        pixel_param2(PIXEL_PARAM_2)
    {}
    virtual void run(cv::Mat src);

    int blackLMax, whiteLMin, greenHMean, greenHVar, greenSMin;
    float hough_param1, hough_param2, pixel_param1, pixel_param2;
private:
    std::vector<cv::Vec3f> circles;
    float resize_factor;



};

#endif // BALLDETECTORRAPHA_H
