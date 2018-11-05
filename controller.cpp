#include "controller.hpp"

using namespace std;

Controller::Controller(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainWindow w;
    timer = new QTimer(this);
    w.setWindowTitle("Frednator");
    w.show();

    videoThread = new VideoThread;

    videoThread->moveToThread(&workerThread);

    int frame_rate = 20;
    timer->setInterval( ceil(1000.0 / frame_rate) );

    //Connect the button on the GUI to start and stop the video stream
    connect(&w, SIGNAL(connectCamera(bool,QString)), videoThread, SLOT(connectVideo(bool,QString)));

    //Tells the mainwindow if the connection was successfull
    connect(videoThread, SIGNAL(connection(bool)), &w, SLOT(checkConnection(bool)));

	//Connect the function selector
    connect(&w, SIGNAL(newFunctionSelected(QString, QComboBox*, QFormLayout*)),this, SLOT(functionChanged(QString, QComboBox*, QFormLayout*)));

    //Connect the image on the thread to show it on the GUI
    connect(videoThread, SIGNAL(sendFrame()), &w, SLOT(displayImage()));

    //Start the timer that will control the FPS
    connect(videoThread, SIGNAL(startLoop()), this, SLOT(startTimer()));

    //Call each frame of the video stream on the correct time
    connect(timer,SIGNAL(timeout()), videoThread, SLOT(videoLoop()));

    //Connect the record button to start recording the video
    connect(&w, SIGNAL(record(QString)), this, SLOT(startRecording(QString)));

    //Connect the record button to stop recording the video
    connect(&w, SIGNAL(stopRecording()), this, SLOT(stopRecording()));

    //Connect the change camera button to change the camera
    connect(&w, SIGNAL(changeCamera(int)), this, SLOT(changeCamera(int)));

    //Connect the closure of the GUI to end the thread
    connect(&w, SIGNAL(finishThread()), this, SLOT(stopThread()));

    //Connect the end of the thread loop to terminate the thread
    connect(videoThread, SIGNAL(terminateThread()), &workerThread, SLOT(terminate()));

    //Connect the end of the thread to close the GUI
    connect(videoThread, SIGNAL(terminateThread()), &w, SLOT(threadFinishedslot()));

    //Connect the error messages to the GUI
    connect(videoThread, SIGNAL(statusMessage(QString)), &w, SLOT(updateStatusMessage(QString)));

    //Connect the Save Picture Button with the thread routine
    connect(&w, SIGNAL(savePicture()), videoThread, SLOT(savePicture()));




    workerThread.start();
    prog.exec();

    //stopThread();
}

Controller::~Controller()
{
    if(timer->isActive())
        timer->stop();
    workerThread.quit();
    workerThread.wait(500);
    if(!workerThread.isFinished())
    {
        workerThread.terminate();
    }
}

void Controller::stopThread()
{
    timer->stop();
    videoThread->stopThread();
    workerThread.quit();
    workerThread.wait(500);
    if(!workerThread.isFinished())
    {
        workerThread.terminate();
    }
}

void Controller::changeCamera(const int &camera)
{
    videoThread->changeCamera(camera);
}

void Controller::startTimer()
{
    timer->start();
}

void Controller::startRecording(QString fileName)
{
    videoThread->startRecording(fileName);
}

void Controller::stopRecording()
{
    videoThread->stopRecording();
}

void Controller::functionChanged(QString newFunction, QComboBox* vectorSelection, QFormLayout* paramLayout){
    newfunction = newFunction;

    if(newFunction == "yellowDetector"){ // adicionar os line edits e labels com os argumentos da classe do detector

        //iLowH
        QLineEdit* iLowHLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iLowH));
        iLowHLineEdit->setPlaceholderText("ILowH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowH", iLowHLineEdit)); // nao sei se vou usar
        connect(iLowHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("ILowH", iLowHLineEdit);


        //iHighH
        QLineEdit* iHighHLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iHighH));
        iHighHLineEdit->setPlaceholderText("iHighH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighH", iHighHLineEdit)); // nao sei se vou usar
        connect(iHighHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighH", iHighHLineEdit);

        //iLowS
        QLineEdit* iLowSLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iLowS));
        iLowSLineEdit->setPlaceholderText("iLowS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowS", iLowSLineEdit)); // nao sei se vou usar
        connect(iLowSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowS", iLowSLineEdit);

        //iHighS
        QLineEdit* iHighSLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iHighS));
        iHighSLineEdit->setPlaceholderText("iHighS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighS", iHighSLineEdit)); // nao sei se vou usar
        connect(iHighSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighS", iHighSLineEdit);

        //iLowV
        QLineEdit* iLowVLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iLowV));
        iLowVLineEdit->setPlaceholderText("iLowV");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowV", iLowVLineEdit)); // nao sei se vou usar
        connect(iLowVLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowV", iLowVLineEdit);

        //iHighV
        QLineEdit* iHighVLineEdit = new QLineEdit(QString::number(videoThread->yellowDetector.iHighV));
        iHighVLineEdit->setPlaceholderText("iHighV");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighV", iHighVLineEdit)); // nao sei se vou usar
        connect(iHighVLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighV", iHighVLineEdit);

    }

    if(newFunction == "fieldDetector2"){ // adicionar os line edits e labels com os argumentos da classe do detector

        //iLowH
        QLineEdit* iLowHLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iLowH));
        iLowHLineEdit->setPlaceholderText("ILowH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowH", iLowHLineEdit)); // nao sei se vou usar
        connect(iLowHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("ILowH", iLowHLineEdit);


        //iHighH
        QLineEdit* iHighHLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iHighH));
        iHighHLineEdit->setPlaceholderText("iHighH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighH", iHighHLineEdit)); // nao sei se vou usar
        connect(iHighHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighH", iHighHLineEdit);

        //iLowL
        QLineEdit* iLowLLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iLowL));
        iLowLLineEdit->setPlaceholderText("iLowL");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowL", iLowLLineEdit)); // nao sei se vou usar
        connect(iLowLLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowL", iLowLLineEdit);

        //iHighL
        QLineEdit* iHighLLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iHighL));
        iHighLLineEdit->setPlaceholderText("iHighL");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighL", iHighLLineEdit)); // nao sei se vou usar
        connect(iHighLLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighL", iHighLLineEdit);

        //iLowS
        QLineEdit* iLowSLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iLowS));
        iLowSLineEdit->setPlaceholderText("iLowS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowS", iLowSLineEdit)); // nao sei se vou usar
        connect(iLowSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowS", iLowSLineEdit);

        //iHighS
        QLineEdit* iHighSLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.iHighS));
        iHighSLineEdit->setPlaceholderText("iHighS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighS", iHighSLineEdit)); // nao se vou usar
        connect(iHighSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighS", iHighSLineEdit);

    }

    else{
       QLayoutItem* child;
       while((child = paramLayout->takeAt(0)) != 0){
           if (child->widget()) {
               delete child->widget();
           }
           else{
               delete child;
           }
       }
    }

    videoThread->functionChanged(newFunction, vectorSelection, paramLayout);
}

void Controller::paramChanged(){
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());

    if(newfunction == "yellowDetector"){
        if(lineEdit->placeholderText() == "ILowH"){
            videoThread->yellowDetector.iLowH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighH"){
            videoThread->yellowDetector.iHighH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowS"){
            videoThread->yellowDetector.iLowS = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighS"){
            videoThread->yellowDetector.iHighS = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowV"){
            videoThread->yellowDetector.iLowV = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighV"){
            videoThread->yellowDetector.iHighV = (lineEdit->text().toInt());
        }
    }

    if(newfunction == "fieldDetector2"){
        if(lineEdit->placeholderText() == "ILowH"){
            videoThread->fieldDetector2.iLowH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighH"){
            videoThread->fieldDetector2.iHighH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowL"){
            videoThread->fieldDetector2.iLowL = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighL"){
            videoThread->fieldDetector2.iHighL = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowS"){
            videoThread->fieldDetector2.iLowS = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighS"){
            videoThread->fieldDetector2.iHighS = (lineEdit->text().toInt());
        }
    }


}


