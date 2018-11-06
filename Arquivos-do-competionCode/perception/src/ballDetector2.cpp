#include "ballDetector2.hpp"

void BallDetector2::run(cv::Mat imgTop, cv::Mat imgBot,PerceptionData* data)
{
    std::cout<<"1"<<std::endl;
    cv::Mat src_HLS_green, src_HLS_white;

    //Color transformations
    cv::cvtColor(imgTop, src_HLS_green, cv::COLOR_BGR2HLS);
    src_HLS_white = src_HLS_green.clone();

    cv::blur(src_HLS_green, src_HLS_green, cv::Size(3,3));
    cv::inRange(src_HLS_green, cv::Scalar(iLowH, iLowL, iLowS), cv::Scalar(iHighH, iHighL, iHighS), src_HLS_green);
    cv::inRange(src_HLS_white, cv::Scalar(iLowH2, iLowL2, iLowS2), cv::Scalar(iHighH2, iHighL2, iHighS2), src_HLS_white);


#ifdef DEBUG_PERCEPTION
    //Create an image vector, put the desired images inside it and atualize the perception data debugImages with it.
    debugImgVector.assign(1, imgTop); //0
    debugImgVector.push_back(imgBot); // 1

    cv::cvtColor( src_HLS_green, src_HLS_green, CV_GRAY2BGR);
    debugImgVector.push_back(src_HLS_green); //2
    cv::cvtColor( src_HLS_green, src_HLS_green, CV_BGR2GRAY);

    cv::cvtColor( src_HLS_white, src_HLS_white, CV_GRAY2BGR);
    debugImgVector.push_back(src_HLS_white); //3
    cv::cvtColor( src_HLS_white, src_HLS_white, CV_BGR2GRAY);

#endif


    cv::Mat element = cv::getStructuringElement( cv::MORPH_RECT, cv::Size(3,3), cv::Point(-1,-1));
    cv::Mat erodeOutput_green, dilateOutput_green, dilateOutput_white;

    if(kernel>0){
        element = cv::getStructuringElement( cv::MORPH_RECT, cv::Size(kernel,kernel), cv::Point(-1,-1));
    }

    cv::erode(src_HLS_green, erodeOutput_green, element, cv::Point(-1,-1),1, cv::BORDER_CONSTANT);
    cv::dilate(erodeOutput_green, dilateOutput_green, element, cv::Point(-1,-1),1, cv::BORDER_CONSTANT);

    cv::dilate(src_HLS_white, dilateOutput_white, element, cv::Point(-1,-1),1, cv::BORDER_CONSTANT);

    cv::Mat ballMask;
    cv::bitwise_xor(dilateOutput_green, dilateOutput_white, ballMask);



    /*



    cv::Mat ballOutput = imgTop.clone();

    std::vector<cv::Vec3f> circles;

    cv::HoughCircles(dilateOutput, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);

    for( int i = 0; i < circles.size(); i++ )
    {
       cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
       int radius = cvRound(circles[i][2]);
       cv::circle( ballOutput, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
       // circle outline
       circle( ballOutput, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
     }


    cv::SimpleBlobDetector::Params params;
    cv::SimpleBlobDetector detector(params);
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat im_with_keypoints;
    cv::drawKeypoints(im, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
*/


    //updateData(data);

#ifdef DEBUG_PERCEPTION
//Create an image vector, put the desired images inside it and atualize the perception data debugImages with it.
    cv::cvtColor( ballMask, ballMask, CV_GRAY2BGR);
    debugImgVector.push_back(ballMask); //3
    cv::cvtColor( ballMask, ballMask, CV_BGR2GRAY);

    std::pair<std::map<std::string,std::vector<cv::Mat> >::iterator, bool> debugInsertion;
    debugInsertion = data->debugImages.insert(std::make_pair("ballDetector2", debugImgVector));
    if(!debugInsertion.second){
        data->debugImages["ballDetector2"] = debugImgVector;
    }
#endif
}

void BallDetector2::updateData(PerceptionData *data)
{
    data->ballX = this->bestCandidate.center.x;
    data->ballY = this->bestCandidate.center.y;
}
