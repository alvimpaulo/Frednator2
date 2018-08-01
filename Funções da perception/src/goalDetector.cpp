#include "goalDetector.hpp"
#define DEBUG_PERCEPTION 1

//void GoalDetector::run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data)
void GoalDetector::run(cv::Mat topImg, cv::Mat goalImg, PerceptionData *data)
{

    // Goal detection on roi_field
    cv::Mat goal = topImg.clone();
    cv::Mat src_gray,src;
    //treshold for binary image
    int t = 240;
    cv::Mat campo = cv::Mat::zeros(goal.rows,goal.cols, CV_8UC1);
    cv::cvtColor( goal, src_gray, CV_BGR2GRAY );
    //Field roi mask creation
    for (int w = 0; w < campo.rows; w++) {
        for (int q = 0; q < campo.cols ; q ++) {
            if(w < this->greenVerticalAvg /*&& w > (140 - 0.5*greenVerticalAvg)*/ ){
                campo.at<uchar>(w,q) = 255;
            }
        }}
    //Get goal ROI
    cv::bitwise_and(src_gray,campo,src);
    cv::GaussianBlur( src, src, cv::Size( 3,3 ), 0, 0 );

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    cv::Mat grad;
    //Get contour
    cv::Sobel( src, grad, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );

    cv::convertScaleAbs( grad, grad);

    //cv::addWeighted( abs_grad_x, 1, cv::Mat::zeros(abs_grad_x.rows,abs_grad_x.cols,CV_8UC1)  , 0.5, 0, grad );
    cv::threshold( grad, grad, t, 255,0 );
    //Noise canceling
    cv::dilate(grad,grad,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,3)),cv::Point(-1,-1)); //3
    cv::erode(grad,grad,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,9)),cv::Point(-1,-1)); //7
    //Get line in image
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(grad,lines,1,CV_PI/180,10,10);

    float gol_x = 0.0, nLines = 0.0;

    for(size_t i = 0; i < lines.size(); i++){
    // If lines close to field its likely a goal
        cv::Vec4i aLine = lines[i];
        if(aLine[1] > this->greenVerticalAvg - 50 /*&& aLine[3] < (160 - 0.5*media)*/){
            gol_x = gol_x + (float)((float)aLine[0]/(fabs((float)aLine[1] - (float)this->greenVerticalAvg)));
            nLines = nLines + (float)(1/(fabs((float)aLine[1] - (float)this->greenVerticalAvg)));
#ifdef DEBUG_PERCEPTION
            //std::cout << "linha_x:" << std::dec << aLine[0] << std::endl;
            cv::line(goal,cv::Point(aLine[0],aLine[1]),cv::Point(aLine[2],aLine[3]),cv::Scalar(0,0,255),3,CV_AA);
#endif
        }
    }
    std::cout << "Perception: nlines " << nLines << std::endl;
    if(nLines){
        gol_x = gol_x/nLines;
    }
    else{
        gol_x = -1;
    }


#ifdef DEBUG_PERCEPTION
    cv::circle(goal,cv::Point(gol_x,this->greenVerticalAvg),4,cv::Scalar(255,0,0),2);
    cv::imwrite("gol.jpg",goal);
    cv::imwrite("gol_gradiente.jpg",grad);
    //std::cout << "gol_x = " << std::dec << gol_x << " " << this->greenVerticalAvg << std::endl;
#endif

    this->bestGoal.imgPosX = gol_x;

    updateData(data);
}

void GoalDetector::updateData(PerceptionData *data)
{
    data->goalCenter = this->bestGoal.imgPosX;
}
