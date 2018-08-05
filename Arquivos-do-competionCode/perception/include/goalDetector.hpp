#ifndef GOALDETECTOR_HPP
#define GOALDETECTOR_HPP

#include "featureDetector.hpp"

typedef struct goalCandidate {
    int imgPosX;
    goalCandidate():imgPosX(-1){}
} goalCandidate;

class GoalDetector : public FeatureDetector
{
private:
    goalCandidate bestGoal;
    cv::Mat roiGoal;
    int greenVerticalAvg;
public:
    GoalDetector(){}
    virtual cv::Mat run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data);
    int getGreenVerticalAvg(){return this->greenVerticalAvg;}
    void setGreenVerticalAvg(int newGreenVerticalAvg){this->greenVerticalAvg = newGreenVerticalAvg;}
    virtual void updateData(PerceptionData *data);
};

#endif // GOALDETECTOR_HPP
