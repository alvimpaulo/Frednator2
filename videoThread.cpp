// Opencv includes.
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// Aldebaran includes.
#include <alvision/alimage.h>
#include <alcommon/alproxy.h>

#include <alvision/alvisiondefinitions.h>
#include <alproxies/altexttospeechproxy.h>
#include <alvalue/alvalue.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alsonarproxy.h>

// Math includes
#include <almath/types/alpose2d.h>
#include <almath/tools/aldubinscurve.h>
#include <almath/tools/almathio.h>
#include <almath/tools/altrigonometry.h>

//File
#include <sys/stat.h>
#include <cstdio>

#include <sstream>

#include "videoThread.hpp"

#include <QMutex>
#include <QDateTime>
#include <QString>

volatile int quit_signal=0;
#ifdef __unix__
#include <signal.h>
extern "C" void quit_signal_handler(int signum) {
 if (quit_signal!=0) exit(0); // just exit already
 quit_signal=1;
 printf("Will quit at next camera frame (repeat to kill now)\n");
}
#endif





#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


using namespace AL;
using namespace cv;
using namespace std;

QString randString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    return str;
}


//Class Implementation

VideoThread::VideoThread() : isConnected(false),
    isRecording(false),
    savePictureLockFlag(false),
    screenshotCounter(0),
    firstScreenshot(true),
    isWebcam(false),
    functionSelected("Nenhuma")
{
#ifdef __unix__
   signal(SIGINT,quit_signal_handler); // listen for ctrl-C
#endif

}

VideoThread::~VideoThread()
{  
}


void VideoThread::connectVideo(bool connect, const QString &naoIP)
{
    if(connect){
        if(isConnected)
        {
            return;
        }

        isAlive = true;
        storeVideo = false;
        strIP = naoIP.toUtf8().constData();

        if(naoIP == "0")
        {
            isWebcam = true;
            cap = new cv::VideoCapture;
            cap->set(CV_CAP_PROP_FRAME_WIDTH, 640);
            cap->set(CV_CAP_PROP_FRAME_HEIGHT, 480);
            if(!cap->open(0))
            {
                QString message;
                message = "Cannot open Webcam.";
                emit statusMessage(message);
                emit connection(false);
                return;
            }
        }
        else
        {
            isWebcam = false;
            try
            {
                camProxy = new ALVideoDeviceProxy(strIP);
                record = new ALVideoRecorderProxy(strIP);
            }
            catch(const AL::ALError &e)
            {
                QString message;
                message = "Cannot connect to robot.";
                emit statusMessage(message);
                emit connection(false);
                return;
            }

            record->setFrameRate(30);
            record->setResolution(kVGA);
            record->setColorSpace(kBGRColorSpace);

            QString rndStr = randString(14);

            clientName = rndStr.toUtf8().constData();
            clientName = camProxy->subscribe(clientName, kVGA, kBGRColorSpace, 30);

            /**Change Camera */
            cout << "Change Camera. " << clientName << endl;
            camProxy->setParam(kCameraSelectID,0);  //CHANGE TO THE BOTTOM CAMERA (0 - TOP, 1 - BOTTOM)
            record->setCameraID(0);
            cameraID = "top";

        }

        imgHeader = Mat(cv::Size(640, 480), CV_8UC3);
        imgSafe = Mat(cv::Size(640, 480), CV_8UC3);

        isConnected = true;
        emit connection(true);
        emit startLoop();
    }
    else{
        //Essa parte ainda não funciona :(
        isConnected = false;
        emit connection(false);
        cout << "desconectando" << endl;
        if(isWebcam){
            cap->release();
            isWebcam = false;
            cout<< "fechou =" << cap->isOpened() << endl;
            delete(cap);
        }
    }
}

void VideoThread::videoLoop()
{
    if(isConnected){
        if(!isWebcam)
        {
            ALValue img = camProxy->getImageRemote(clientName);
            if(img.getSize() < 7)
            {
                QString message;
                message = "Fail to Get Frame.";
                emit statusMessage(message);
                return;
            }

            imgHeader.data = (uchar*) img[6].GetBinary();

            QImage image((uchar*)imgHeader.data, imgHeader.cols, imgHeader.rows, imgHeader.step, QImage::Format_RGB888);

            imgContainer.image = image.rgbSwapped();
            imagePipe.save(imgContainer);

            perception2Frednator(functionSelected);

            camProxy->releaseImage(clientName);


        }
        else
        {
            (*cap) >> imgHeader;
            if (quit_signal) exit(0); // exit cleanly on interrupt

            QImage image((uchar*)imgHeader.data, imgHeader.cols, imgHeader.rows, imgHeader.step, QImage::Format_RGB888);

            imgContainer.image = image.rgbSwapped();
            imagePipe.save(imgContainer);

            perception2Frednator(functionSelected);

        }


    }
    else
    {
        emit sendFrame();
    }
}

void VideoThread::perception2Frednator(QString functionName){
    cv::Mat cvMatImg;
    cv::Mat dstcvMatImg;

    if(functionName == "Nenhuma"){
        emit sendFrame();
        return;
    }
    else{
        if(functionName == "ballCandidate"){
            emit sendFrame();
            return;
          }

        //Parece que funciona
        if(functionName == "ballDetector"){
            cvMatImg = ballDetector.run(imgHeader, imgHeader, &visionData);
        }

        //Funciona
        if(functionName == "ellipseDetector"){
            cvMatImg = ellipseDetector.run(imgHeader, imgHeader, &visionData);
        }

        //Funciona
        if(functionName == "fieldDetector"){
            cvMatImg = fieldDetector.run(imgHeader, imgHeader, &visionData);
        }

        //Funciona
        if(functionName == "goalDetector"){
            cvMatImg = goalDetector.run(imgHeader, imgHeader, &visionData);
        }

        //Funciona
        if(functionName == "lineDetector"){
            cvMatImg = lineDetector.run(imgHeader, imgHeader, &visionData);
        }

        //Funciona
        if(functionName == "yellowDetector"){
            cvMatImg = yellowDetector.run(imgHeader, imgHeader, &visionData);
        }

        int w = imgHeader.cols;
        int h = imgHeader.rows;
        QImage qImg((uchar*)cvMatImg.data, cvMatImg.cols, cvMatImg.rows, cvMatImg.step, QImage::Format_RGB888);
        QRgb pixel;

        //dstcvMatImg.size() = imgHeader.size();
        //resize(cvMatImg, cvMatImg, imgHeader.size(), 0, 0, INTER_AREA);


        /*for(int i=0;i<w;i++)
        {
            for(int j=0;j<h;j++)
            {
                int gray = (int)cvMatImg.at<unsigned char>(j, i);
                pixel = qRgb(gray,gray,gray);
                qImg.setPixel(i,j,pixel);
            }
        }*/

        imgContainer.image = qImg.rgbSwapped();;
        imagePipe.save(imgContainer);
        emit sendFrame();
    }


}

void VideoThread::changeCamera(const int &camera)
{
    if(isWebcam)
    {
        return;
    }
    if(!isConnected)
    {
        QString message;
        message = "Not Connected.";
        emit statusMessage(message);
        return;
    }
    if(isRecording)
    {
        QString message;
        message = "Cannot change camera while recording a video.";
        emit statusMessage(message);
        return;
    }
    cout << "change camera" << endl;

    if(camera)
        cameraID = "bot";
    else
        cameraID = "top";
    QMutex mutex;
    mutex.lock();
    camProxy->setParam(kCameraSelectID,camera);  //CHANGE TO THE BOTTOM CAMERA (0 - TOP, 1 - BOTTOM)
    record->setCameraID(camera);
    mutex.unlock();
}

void VideoThread::stopThread()
{
    cout << "stoping thread" << endl;
    if(!isConnected)
    {
        return;
    }
    if(!isWebcam)
    {
        camProxy->unsubscribe(clientName);
    }
    else
    {
        delete(cap);
    }
    emit terminateThread();
}

void VideoThread::startRecording(QString fileName)
{
    if(isWebcam)
    {
        return;
    }
    if(!isConnected)
    {
        QString message;
        message = "Not Connected.";
        emit statusMessage(message);
        return;
    }
    string file = fileName.toUtf8().constData();
    file = file + ".avi";
    cout << file << endl;

    record->startRecording("/home/nao", file);

    copyExec = "scp nao@" + strIP + ":/home/nao/" + file + " ./../recordings \n ssh nao@" + strIP + " 'rm /home/nao/" + file + "'";

    cout << copyExec << endl;

    system("mkdir -p ../recordings");

    isRecording = true;
}

void VideoThread::stopRecording()
{
    if(isWebcam)
    {
        return;
    }
    if(!isRecording)
    {
        QString message;
        message = "Not recording. Fail to save video.";
        emit statusMessage(message);
        return;
    }

    record->stopRecording();

    if(system(copyExec.c_str()) == 0)
    {
        QString message;
        message = "File saved successfully.";
        emit statusMessage(message);
    }
    else
    {
        QString message;
        message = "Fail to transfer file.";
        emit statusMessage(message);
    }

    isRecording = false;

}

void VideoThread::savePicture()
{
    cout << "test!" << endl;
    if(!isConnected)
    {
        QString message;
        message = "Not Connected.";
        emit statusMessage(message);
        return;
    }

    if(firstScreenshot)
    {
        system("mkdir -p ../screenshots");
        firstScreenshot = false;
    }



    QDateTime current = QDateTime::currentDateTime();
    uint unixtime = current.toTime_t();
    QDateTime timestamp;
    timestamp.setTime_t(unixtime);

    QString tmpString = timestamp.toString("yyyy-MM-dd_hh:mm:ss");
    string str_timestamp = tmpString.toUtf8().constData();

    string pictureFileName;
    pictureFileName = "../screenshots/camera_" + cameraID + "_screenshot_" + str_timestamp + ".jpg";

    cout << "Screenshot!" << endl;


    Mat imgcv(cv::Size(640, 480), CV_8UC3);
    if(isWebcam)
    {
        (*cap) >> imgcv;
    }
    else
    {
        ALValue img = camProxy->getImageRemote(clientName);
        imgcv.data = (uchar*) img[6].GetBinary();
    }


    imwrite(pictureFileName, imgcv);

    if(!isWebcam)
    {
        camProxy->releaseImage(clientName);
    }
}

void VideoThread::functionChanged(QString functionToChange){
    functionSelected = functionToChange;
}
