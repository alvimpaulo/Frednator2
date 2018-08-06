#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Aldebaran includes.
#include <alvision/alimage.h>
#include <alcommon/alproxy.h>
#include <alproxies/alvideodeviceproxy.h>

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

// Opencv includes.
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "unBoard.hpp"
#include "frednatorData.hpp"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>
#include <qi/os.hpp>


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:
    void displayImage(); //Display the video on the screen when it's connected and a dark screen when disconnected
    void threadFinishedslot();
    void updateStatusMessage(QString message);
    void checkConnection(bool connection); //Receives a signal when the connection is stablished and changes the connectButton text

private slots:
    void on_connectButton_clicked(); //Calls the connectVideo slot
    void on_StartRecordingButton_clicked();
    void on_changeCameraButton_clicked();
    void on_pushButton_clicked();
    void on_FunctionSelected_activated(QString functionName); //selects the function to be used on camera

signals:
    void connectCamera(bool connection, QString naoIP);
    void changeCamera(int cameraID);
    void finishThread();
    void record(QString fileName);
    void stopRecording();
    void savePicture();
    void newFunctionSelected(QString);

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *);
    bool threadFinished;
    bool isRecording;
    bool isConnected;
    int camera;
    unBoard<frednatorData> imagePipe;
    frednatorData imgContainer;

};

#endif // MAINWINDOW_H
