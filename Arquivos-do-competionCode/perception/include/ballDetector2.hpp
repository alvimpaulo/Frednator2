#ifndef BALL_DETECTOR2_HPP
#define BALL_DETECTOR2_HPP

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "featureDetector.hpp"

typedef struct ball2Candidate {
    cv::Point center;
    int radius;
    std::vector<cv::Rect> blackSpots;
    ball2Candidate(cv::Point p, int r) {
        this->center = p;
        this->radius = r;
    }
    ball2Candidate() {
        this->center = cv::Point(-1,-1);
    }
} ball2Candidate;

class BallDetector2 : public FeatureDetector
{
private:
    ball2Candidate bestCandidate;
#ifdef DEBUG_PERCEPTION
    std::vector<cv::Mat> debugImgVector;
#endif
public:

    BallDetector2():
        iLowH(30),
        iHighH(90),
        iLowL(50),
        iHighL(200),
        iLowS(10),
        iHighS(255),
        iLowH2(30),
        iHighH2(90),
        iLowL2(50),
        iHighL2(200),
        iLowS2(10),
        iHighS2(255),
        kernel(3),
        minThreshold(150),
        maxThreshold(250),
        filterByArea(true),
        minArea(500),
        filterByCircularity(true),
        minCircularity(0.2),
        filterByConvexity(true),
        minConvexity(0.001),
        filterByInertia(true),
        minInertiaRatio(0.01)
    {}

    int iLowH, iHighH, iLowS, iHighS, iLowL, iHighL;
    int iLowH2, iHighH2, iLowS2, iHighS2, iLowL2, iHighL2;
    int kernel;
    int minThreshold;
    int maxThreshold;
    bool filterByArea;
    int minArea;
    bool filterByCircularity;
    double minCircularity;
    bool filterByConvexity;
    double minConvexity;
    bool filterByInertia;
    double minInertiaRatio;


    virtual void run(cv::Mat topImg, cv::Mat botImg, PerceptionData *data);
    virtual void updateData(PerceptionData* data);
};

#endif //BALL_DETECTOR_HPP2
