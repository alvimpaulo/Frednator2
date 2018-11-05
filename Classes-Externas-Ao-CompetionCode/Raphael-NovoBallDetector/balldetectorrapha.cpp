#include "balldetectorrapha.h"


void ballDetectorRapha::run(cv::Mat src, cv::Mat src2, PerceptionData *data){
    houghCirclesContrast hough(hough_param1, hough_param2, resize_factor);
    quaternaryMask Mask;
    Mask.generateMask(src);
    circles = hough.run(src);
    pixelCountCheck pixelChecker(pixel_param1, pixel_param2, resize_factor);
    cv::Point center(-1, -1);
    int radius = -1;

    if(circles.size() > 0){
        for(int i = 0; i < circles.size() && i < 10; i++){
            //pixelcount faz a sua mágica
            if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, src)){
                center.x = cvRound(circles[i][0]);
                center.y = cvRound(circles[i][1]);
                radius = cvRound(circles[i][2]);
                //primeiro que aceita o threshold ->break
                break;
            }
        }


    }
}

void ballDetectorRapha::updateData(PerceptionData *){

}
