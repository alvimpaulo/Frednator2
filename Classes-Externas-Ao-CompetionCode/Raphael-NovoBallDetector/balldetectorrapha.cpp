#include "balldetectorrapha.h"

#define DEBUG_PERCEPTION 1

void ballDetectorRapha::run(cv::Mat src, cv::Mat src2, PerceptionData *data){
    debugImgVector.assign(1,src); //0
    houghCirclesContrast hough(hough_param1, hough_param2, 30, (int)MIN_RADIUS, (int)MAX_RADIUS);
    Mask.setMask(BLACK_L_MAX, WHITE_L_MIN, GREEN_H_MEAN, GREEN_H_VAR, GREEN_S_MIN);
    Mask.generateMask(src);
    debugImgVector.push_back(Mask.blackMask); //1
    debugImgVector.push_back(Mask.whiteMask); //2
    debugImgVector.push_back(Mask.greenMask); //3

    Dilater.setDilation(0, DILATION * RESIZE_FACTOR);

    cv::Mat greenROI = Dilater.runDilation(Mask.greenMask);

    circles = hough.run(src, circles);

    pixelCountCheck pixelChecker(pixel_param1, pixel_param2);
    cv::Point center(-1, -1);
    int radius = -1;

    if(circles.size() > 0){
        for(int i = 0; i < circles.size() && i < 10; i++){
            //std::cout << "achei bola" << std::endl;
            //pixelcount faz a sua mágica
#ifdef DEBUG_PERCEPTION
                cv::circle(src, cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(0,255,255));
#endif
            if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, src)){
                center.x = cvRound(circles[i][0]);
                center.y = cvRound(circles[i][1]);
                radius = cvRound(circles[i][2]);

                //primeiro que aceita o threshold ->break

                break;
            }
        }


    }

#ifdef DEBUG_PERCEPTION
//Create an image vector, put the desired images inside it and atualize the perception data debugImages with it.
    debugImgVector.push_back(src);
    std::pair<std::map<std::string,std::vector<cv::Mat> >::iterator, bool> debugInsertion;
    debugInsertion = data->debugImages.insert(std::make_pair("raphaDetector", debugImgVector));
    if(!debugInsertion.second){
        data->debugImages["raphaDetector"] = debugImgVector;
    }
#endif
}

void ballDetectorRapha::updateData(PerceptionData *){

}
