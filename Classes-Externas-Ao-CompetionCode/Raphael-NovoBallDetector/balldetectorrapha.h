#ifndef BALLDETECTORRAPHA_H
#define BALLDETECTORRAPHA_H

#include "../../Arquivos-do-competionCode/perception/include/featureDetector.hpp"
#include "./include/houghCirclesContrast.h"
#include "./include/quaternaryMask.h"
#include "./include/pixelCountCheck.hpp"
#include "./include/evaluator.hpp"
#include "./include/dilate.hpp"


#define BLACK_L_MAX 40
#define WHITE_L_MIN 200
#define GREEN_H_MEAN 50
#define GREEN_H_VAR 20
#define GREEN_S_MIN 40
#define HOUGH_PARAM_1 20
#define HOUGH_PARAM_2 28
#define PIXEL_PARAM_1 0.55
#define PIXEL_PARAM_2 0.35

#define MIN_RADIUS 10
#define MAX_RADIUS 30

#define DILATION 1

#define N_OF_CANDIDATES 10

#define RESIZE_FACTOR 0.5



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
    virtual void run(cv::Mat src, cv::Mat src2, PerceptionData *data);
    virtual void updateData(PerceptionData *);

#ifdef DEBUG_PERCEPTION
    std::vector<cv::Mat> debugImgVector;
#endif

    int blackLMax, whiteLMin, greenHMean, greenHVar, greenSMin;
    double hough_param1, hough_param2;
    float pixel_param1, pixel_param2;
private:
    std::vector<cv::Vec3f> circles;
    dilate Dilater;
    quaternaryMask Mask;



};

#endif // BALLDETECTORRAPHA_H
