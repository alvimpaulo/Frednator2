#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "mainwindow.h"
#include "videoThread.hpp"

#include <QThread>
#include <QApplication>
#include <QTimer>
#include <QFormLayout>



class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    Controller(int argc, char* argv[]);
    QString newfunction;
    ~Controller();

private slots:
    void stopThread();
    void changeCamera(const int &camera);
    void startTimer();
    void startRecording(QString fileName);
    void stopRecording();
    void functionChanged(QString, QComboBox*, QFormLayout*);
    void paramChanged();
private:
    VideoThread *videoThread;
    QTimer *timer;

    //map de lineEdits que contém os parametros da classe
    std::map<QString,QLineEdit*> lineEditMap;




};





#endif //_CONTROLLER_HPP_
