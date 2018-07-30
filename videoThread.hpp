#ifndef _VIDEO_THREAD_HPP_
#define _VIDEO_THREAD_HPP_

#include <alproxies/alvideodeviceproxy.h>
#include <alproxies/alvideorecorderproxy.h>
#include <opencv2/opencv.hpp>

#include "unBoard.hpp"
#include "frednatorData.hpp"

#include <string>
#include <vector>

#include <QThread>
#include <QImage>

class VideoThread : public QObject
{
    Q_OBJECT
    QThread workerThread;

signals:
    void startLoop();
    void sendFrame();
    void terminateThread();
    void statusMessage(QString message);
    void connection(bool connected);

public slots:

    void connectVideo(bool connect, const QString &naoIP);
    void videoLoop();
    void savePicture();


private:
    bool isAlive;
    bool storeVideo;
    bool thereIsFile;
    bool isConnected;
    bool isRecording;
    bool savePictureLockFlag;
    bool firstScreenshot;
    bool isWebcam;

    int screenshotCounter;
    AL::ALVideoDeviceProxy *camProxy;
    AL::ALVideoRecorderProxy *record;
    cv::Mat imgSafe;
    //cv::VideoWriter *record;
    std::string clientName;
    cv::Mat imgHeader;
    std::string strIP;
    std::string copyExec;
    std::string cameraID;
    unBoard<frednatorData> imagePipe;
    frednatorData imgContainer;
    cv::VideoCapture *cap;


public:
    VideoThread();
    ~VideoThread();
    void changeCamera(const int &camera);
    void stopThread();
    void startRecording(QString fileName);
    void stopRecording();
};

#endif //_VIDEO_THREAD_HPP_
