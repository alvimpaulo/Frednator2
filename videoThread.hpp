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
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include <yellowDetector.hpp>
#include <ballDetector.hpp>
#include <fieldDetector.hpp>
#include <ellipseDetector.hpp>
#include <lineDetector.hpp>
#include <goalDetector.hpp>


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
    QGridLayout* paramLayout; //Layout que possui os parametros de uma classe para se alterar
    bool flagVectorSelectionChanged;

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



    //Atualiza algum parametro das classes




public:
    VideoThread();
    ~VideoThread();
    void changeCamera(const int &camera);
    void stopThread();
    void startRecording(QString fileName);
    void stopRecording();
    void functionChanged(QString functionToChange, QComboBox* vectorSelection, QGridLayout* paramLayout);
    void perception2Frednator(QString functionName, QComboBox* vectorSelection);

    BallDetector ballDetector;
    EllipseDetector ellipseDetector;
    FieldDetector fieldDetector;
    GoalDetector goalDetector;
    LineDetector lineDetector;
    YellowDetector yellowDetector;

    PerceptionData visionData;


};

#endif //_VIDEO_THREAD_HPP_
