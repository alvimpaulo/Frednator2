#include "yellowDetector.hpp"

#define DEBUG_PERCEPTION 1

//Finds contours of yellow bodies (robot jersey) and calculates distance based on jersey boundaries size
cv::Mat YellowDetector::run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data)
{
    cv::Mat src  =  topImg.clone();

    //Yellow HSL values range definitions
    int iLowH = 20;
    int iHighH = 30;
    int iLowS = 100; 
    int iHighS = 255;
    int iLowV = 100;
    int iHighV = 255;

    //Variables initialization
    cv::Mat src_HSV;
    std::vector<std::vector<cv::Point> > contours;
    int thresh=100;
    std::vector<cv::Vec4i> hierarchy;

    //Color transformations
    cv::cvtColor(src, src_HSV, cv::COLOR_BGR2HSV); 
    cv::blur(src_HSV, src_HSV, cv::Size(2,2));
    cv::inRange(src_HSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), src_HSV);

    //Morphological transformations
    cv::Mat element = cv::getStructuringElement( 0, cv::Size( 3, 3 ), cv::Point( 1, 1 ) );
    cv::erode(src_HSV, src_HSV, element);
    cv::dilate( src_HSV, src_HSV, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 
    cv::erode(src_HSV, src_HSV, element);

    //Edge and Contours detections
    cv::Canny( src_HSV, src_HSV, thresh, thresh*2, 3 );
    cv::findContours( src_HSV, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    //Variables initialization
    cv::vector<cv::vector<cv::Point> > contours_poly( contours.size() );
    cv::Rect boundRect;
    this->distance = -1;
    int n_bound = 0;

    #ifdef DEBUG_PERCEPTION
        //Auxiliar variables for drawing initialization
        cv::RNG rng(12345);
        cv::Mat drawing = cv::Mat::zeros( src_HSV.size(), CV_8UC3 );
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    #endif


    for( std::size_t i = 0; i < contours.size(); i++ )
    {
        //Creates bounding rectangle for each contour
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
        boundRect = cv::boundingRect( cv::Mat(contours_poly[i]) );

        //Excludes too small, big, narrow and wide candidates
        if (boundRect.y < 100)
            continue;
        if (boundRect.height < 12)
            continue;
        if ( boundRect.height > 2*boundRect.width )
            continue;
        if (2*boundRect.height < boundRect.width)
            continue;

        #ifdef DEBUG_PERCEPTION
            //Draws valid bounding rectangle
            cv::drawContours( drawing, contours_poly, i, color, 1, 8, cv::vector<cv::Vec4i>(), 0, cv::Point() );
            //std::cout << "teste " << "height " << boundRect.height << std::endl;
        #endif   

        //Calculates distance based on the boundary height
        this->distance += 948 - 47.2 * boundRect.height + 0.642 * boundRect.height * boundRect.height;  
        //this->distance += 58.8 -0.165 * boundRect.height + 0.000128 * boundRect.height * boundRect.height; 

        n_bound++;
    }
    if(n_bound)
            this->distance=this->distance/n_bound;

    #ifdef DEBUG_PERCEPTION
        //std::cout << "teste "<<"distance: " << this->distance <<std::endl ;
        cv::imwrite("Contornos.jpg", drawing);
        return drawing;
    #endif    

    //updateData(data);
}

void YellowDetector::updateData(PerceptionData *data)
{
    //data->yellowCenter = this->mc;
    data->approxDistance = this->distance;
}

int YellowDetector::getDistance()
{
    return this->distance;
}
