#include "fieldDetector.hpp"
#define DEBUG_PERCEPTION 1

cv::Mat FieldDetector::getGreenRegion()
{
    return this->greenRegion;
}

fieldCandidate FieldDetector::getRoiField()
{
    return this->bestField;
}

cv::Mat FieldDetector::run(cv::Mat imgTop, cv::Mat imgBot, PerceptionData *data)
{
    cv::Mat roi(imgBot, cv::Rect(cv::Point(60,140),cv::Size(200,80)));
    cv::Mat g_TopChromacity(imgTop.rows,imgTop.cols,CV_8UC1), g_BotChromacity(roi.rows,roi.cols,CV_8UC1), hist, dilate_element, erode_element;
    cv::Vec3b color;
    //calculates green chromacity for both top and bottom images
    for (int i = 0; i < roi.rows; i++)
    {
        for (int j = 0; j < roi.cols; j++)
        {
            color = roi.at<cv::Vec3b>(i,j);
            if (color[0] + color[1] + color [2] == 0)
                g_BotChromacity.at<uchar>(i,j) = uchar(0);
            else
                if(color[0]+color[1]+color[2] > 0)  g_BotChromacity.at<uchar>(i,j) = (255*color[1]/(color[0]+color[1]+color[2]));
        }
    }

    for (int i = 0; i < imgTop.rows; i++)
    {
        for (int j = 0; j < imgTop.cols; j++)
        {
            color = imgTop.at<cv::Vec3b>(i,j);
            if (color[0] + color[1] + color [2] == 0)
                g_TopChromacity.at<uchar>(i,j) = uchar(0);
            else
                if(color[0]+color[1]+color[2] > 0)g_TopChromacity.at<uchar>(i,j) = (255*color[1]/(color[0]+color[1]+color[2]));
        }
    }
    //creates the histogram
    float range[] = {0, 256};
    const float* hrange = {range};
    int hsize = 32;
    int max_g = 0, i_max_g = 0, min_g;

    cv::calcHist(&g_BotChromacity, 1, 0, cv::Mat(), hist, 1, &hsize, &hrange);
    for (int i = 0; i < hist.rows; i++)
    {
        hist.at<int>(i,0) > max_g ? max_g = hist.at<int>(i,0), i_max_g = i : 0;
    }
    //std::cout << "i_max_g = " << i_max_g << std::endl;
    // defines both maximum and minimum g chroma desired
    min_g = (i_max_g * 256/(hsize));
    max_g = 255;//min_g + 45;

    // eliminates all non green pixels, green pixels become white
    cv::threshold(g_TopChromacity,g_TopChromacity,max_g,255,CV_THRESH_TOZERO_INV);
    cv::threshold(g_TopChromacity,g_TopChromacity,min_g,255,CV_THRESH_TOZERO);
    cv::threshold(g_TopChromacity,g_TopChromacity,0,255,CV_THRESH_BINARY);

    dilate_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2), cv::Point(-1, -1) );
    cv::dilate(g_TopChromacity, g_TopChromacity, dilate_element);

    erode_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7), cv::Point(-1, -1) );
    cv::erode(g_TopChromacity, g_TopChromacity, erode_element);

#ifdef DEBUG_PERCEPTION
    //std::cout << "i_max_g: " << i_max_g * 256/(hsize) << std::endl;
    //imwrite("top green chromacity.jpg",g_TopChromacity);
#endif


    // Find top green pixels in each checkpoint
    int fieldDistance = 0;
    int fieldAverage = 0;
    std::vector<cv::Point> fieldPixels, fieldBestPixels;
    int checkPoints = 40;

    for (int i = 0; i < checkPoints; i++)
    {
        fieldPixels.push_back(cv::Point((i*imgTop.cols)/checkPoints, imgTop.rows));
        for (int j = 0; j < imgTop.rows; j++)
            if (g_TopChromacity.at<uchar>(j, (i)*(imgTop.cols/checkPoints)) != 0)
            {
                fieldPixels[i].y = j;
                fieldAverage += j;
                j = imgTop.rows;
            }
    }

    // Find green pixel in the right edge of the image
    for (int j = 0; j < imgTop.rows; j++)
        if (g_TopChromacity.at<uchar>(j, imgTop.cols - 1) != 0)
        {
            fieldPixels.push_back(cv::Point(imgTop.cols - 1, j));
            fieldAverage += j;
            j = imgTop.rows;
        }

    fieldAverage = fieldAverage/checkPoints;

    // Eliminate outliers
    if (fieldPixels.size() > 2)
    {
        for (int i = 1; i < fieldPixels.size() - 1; i++)
            if (abs(fieldPixels[i].y - fieldAverage) <= 60)
            {
                fieldBestPixels.push_back(fieldPixels[i]);
                fieldDistance += fieldPixels[i].y;
            }
        fieldDistance = (float)fieldDistance/(float)fieldBestPixels.size();
    }


    this->bestField.horizonHeight = fieldDistance;


    //ROI FIELD AND ROI GOAL DETECTION - generate binary image

    cv::Mat roi_goal, roi_field(imgTop.rows, imgTop.cols, CV_8UC1);
    roi_field = cv::Scalar(0);
    roi_goal = roi_field.clone(); // ROI to find base of the goal
    int a;
    if (fieldBestPixels.size() > 1)
    {
        for (int i = 0; i < fieldBestPixels.size() - 1; i++)
        {
            //if((fieldBestPixels[i+1].x-fieldBestPixels[i].x) > 0)
                 a = (fieldBestPixels[i+1].y-fieldBestPixels[i].y)/(fieldBestPixels[i+1].x-fieldBestPixels[i].x);
            for (int j = fieldBestPixels[i].x; j < fieldBestPixels[i+1].x; j++)
            {
                int y_max = a*(j-fieldBestPixels[i].x)+fieldBestPixels[i].y;
                for (int k = 0; k < imgTop.rows; k++)
                {
                    if (k >= y_max)
                        roi_field.at<uchar>(k,j) = 255;

                    if (k < y_max + 20 && k > y_max - 20)  // Amount of pixels arround the edge of roi_field to look for the base of the goal
                        roi_goal.at<uchar>(k,j) = 255;
                }
            }

        }
        this->bestField.fieldImg = roi_field;
        this->greenRegion = g_TopChromacity;

        updateData(data);
    }

#ifdef DEBUG_PERCEPTION
    //imwrite("roi field.jpg",roi_field);
    //imwrite("roi goal.jpg",roi_goal);
#endif

}

void FieldDetector::updateData(PerceptionData *data)
{
    data->fieldDistance = this->bestField.horizonHeight;
}
