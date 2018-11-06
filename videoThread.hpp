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
#include <QString>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

#include <yellowDetector.hpp>
#include <ballDetector.hpp>
#include <ballDetector2.hpp>
#include <fieldDetector.hpp>
#include <fieldDetector2.hpp>
#include <ellipseDetector.hpp>
#include <lineDetector.hpp>
#include <goalDetector.hpp>
#include "./Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/balldetectorrapha.h"


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
    QString functionSelected; // Classe atualmente selecionada
    QString lastFunctionName; // Ultima classe a ser selecionada
    QComboBox* vectorSelection; //Seleciona qual imagem de debug se quer mostrar
    QFormLayout* paramLayout; //Layout que possui os parametros de uma classe para se alterar
    bool videoLoopRunning; //VideoLoop tá rodando


    int screenshotCounter;
    AL::ALVideoDeviceProxy *camProxy;
    AL::ALVideoRecorderProxy *record;
    cv::Mat imgSafe;
    //cv::VideoWriter *record;
    std::string clientName;

    cv::Mat imgHeader;
    cv::Mat imgHead; //img da cabeça do robo
    cv::Mat imgBody; //img do corpo do robo

    std::string strIP;
    std::string copyExec;
    std::string cameraID;
    unBoard<frednatorData> imagePipe;
    frednatorData imgContainer;
    cv::VideoCapture *cap;

    //selecao dos vetores
    cv::Mat vectorSelectionInterface(QComboBox *vectorSelection, PerceptionData *visionData, QString *functionName);




public:
    VideoThread();
    ~VideoThread();
    void changeCamera(const int &camera);
    void stopThread();
    void startRecording(QString fileName);
    void stopRecording();
    void functionChanged(QString functionToChange, QComboBox* vectorSelection, QFormLayout* paramLayout);
    void perception2Frednator(QString functionName, QComboBox* vectorSelection);

    BallDetector ballDetector;
    BallDetector2 ballDetector2;
    EllipseDetector ellipseDetector;
    FieldDetector fieldDetector;
    FieldDetector2 fieldDetector2;
    GoalDetector goalDetector;
    LineDetector lineDetector;
    YellowDetector yellowDetector;
    ballDetectorRapha raphaDetector;

    PerceptionData visionData;


};

#endif //_VIDEO_THREAD_HPP_
