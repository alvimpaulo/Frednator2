#include "fieldDetector2.hpp"


void FieldDetector2::run(cv::Mat imgTop, cv::Mat imgBot, PerceptionData *data)
{
    cv::Mat src_HLS;

    //Color transformations
    cv::cvtColor(imgTop, src_HLS, cv::COLOR_BGR2HLS);
    cv::blur(src_HLS, src_HLS, cv::Size(2,2));
    cv::inRange(src_HLS, cv::Scalar(iLowH, iLowL, iLowS), cv::Scalar(iHighH, iHighL, iHighS), src_HLS);


    #ifdef DEBUG_PERCEPTION

        //Create an image vector, put the desired images inside it and atualize the perception data debugImages with it.
        debugImgVector.assign(1, imgTop); //0
        debugImgVector.push_back(imgBot); // 1
        cv::cvtColor( src_HLS, src_HLS, CV_GRAY2BGR);
        debugImgVector.push_back(src_HLS); //teve que converter //3
        cv::cvtColor( src_HLS, src_HLS, CV_BGR2GRAY);
    #endif

    int whiteCount = cv::countNonZero(src_HLS);

    float fieldpercentage = (float)whiteCount/(src_HLS.rows*src_HLS.cols);

    int y_horizont = fieldpercentage*src_HLS.rows;

   cv::Mat lineOutput;
   cv::cvtColor(src_HLS, lineOutput, CV_GRAY2BGR);

   std::cout <<lineOutput.rows-y_horizont<< std::endl;

   cv::line(lineOutput, cv::Point(0,lineOutput.rows-y_horizont), cv::Point(lineOutput.cols-1, lineOutput.rows-y_horizont), cv::Scalar(0,0,255), 2,8,0);

#ifdef DEBUG_PERCEPTION
    debugImgVector.push_back(lineOutput);

#endif



#ifdef DEBUG_PERCEPTION
    // atualize the perception data debugImages with debugImgVector.
    std::pair<std::map<std::string,std::vector<cv::Mat> >::iterator, bool> debugInsertion;
    debugInsertion = data->debugImages.insert(std::make_pair("fieldDetector2", debugImgVector));
    if(!debugInsertion.second){
        data->debugImages["fieldDetector2"] = debugImgVector;
    }
#endif

}

void FieldDetector2::updateData(PerceptionData *data)
{
}
