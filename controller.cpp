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

    QLayoutItem* child;
    while((child = paramLayout->takeAt(0)) != 0){
        if (child->widget()) {
            delete child->widget();
        }
        else{
            delete child;
        }
    }

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

    else if(newFunction == "fieldDetector2"){ // adicionar os line edits e labels com os argumentos da classe do detector

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

        //factor
        QLineEdit* factorLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.factor));
        factorLineEdit->setPlaceholderText("factor");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("factor", factorLineEdit)); // nao se vou usar
        connect(factorLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("factor", factorLineEdit);

        //dp
        QLineEdit* dpLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.dp));
        dpLineEdit->setPlaceholderText("dp");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("dp", dpLineEdit)); // nao se vou usar
        connect(dpLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("dp", dpLineEdit);

        //minDist
        QLineEdit* minDistLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.minDist));
        minDistLineEdit->setPlaceholderText("minDist");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minDist", minDistLineEdit)); // nao se vou usar
        connect(minDistLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minDist", minDistLineEdit);

        //param1
        QLineEdit* param1LineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.param1));
        param1LineEdit->setPlaceholderText("param1");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("param1", param1LineEdit)); // nao se vou usar
        connect(param1LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("param1", param1LineEdit);

        //param2
        QLineEdit* param2LineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.param2));
        param2LineEdit->setPlaceholderText("param2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("param2", param2LineEdit)); // nao se vou usar
        connect(param2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("param2", param2LineEdit);

        //maxRadius
        QLineEdit* maxRadiusLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.maxRadius));
        maxRadiusLineEdit->setPlaceholderText("maxRadius");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("maxRadius", maxRadiusLineEdit)); // nao se vou usar
        connect(maxRadiusLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("maxRadius", maxRadiusLineEdit);

        //minRadius
        QLineEdit* minRadiusLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.minRadius));
        minRadiusLineEdit->setPlaceholderText("minRadius");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minRadius", minRadiusLineEdit)); // nao se vou usar
        connect(minRadiusLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minRadius", minRadiusLineEdit);

        //kernel
        QLineEdit* kernelLineEdit = new QLineEdit(QString::number(videoThread->fieldDetector2.kernel));
        kernelLineEdit->setPlaceholderText("kernel");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("kernel", kernelLineEdit)); // nao se vou usar
        connect(kernelLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("kernel", kernelLineEdit);

    }

    else if(newFunction == "ballDetector2"){
        //iLowH
        QLineEdit* iLowHLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowH));
        iLowHLineEdit->setPlaceholderText("ILowH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowH", iLowHLineEdit)); // nao sei se vou usar
        connect(iLowHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("ILowH", iLowHLineEdit);


        //iHighH
        QLineEdit* iHighHLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighH));
        iHighHLineEdit->setPlaceholderText("iHighH");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighH", iHighHLineEdit)); // nao sei se vou usar
        connect(iHighHLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighH", iHighHLineEdit);

        //iLowL
        QLineEdit* iLowLLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowL));
        iLowLLineEdit->setPlaceholderText("iLowL");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowL", iLowLLineEdit)); // nao sei se vou usar
        connect(iLowLLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowL", iLowLLineEdit);

        //iHighL
        QLineEdit* iHighLLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighL));
        iHighLLineEdit->setPlaceholderText("iHighL");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighL", iHighLLineEdit)); // nao sei se vou usar
        connect(iHighLLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighL", iHighLLineEdit);

        //iLowS
        QLineEdit* iLowSLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowS));
        iLowSLineEdit->setPlaceholderText("iLowS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowS", iLowSLineEdit)); // nao sei se vou usar
        connect(iLowSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowS", iLowSLineEdit);

        //iHighS
        QLineEdit* iHighSLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighS));
        iHighSLineEdit->setPlaceholderText("iHighS");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighS", iHighSLineEdit)); // nao se vou usar
        connect(iHighSLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighS", iHighSLineEdit);



        //iLowH2
        QLineEdit* iLowH2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowH2));
        iLowH2LineEdit->setPlaceholderText("iLowH2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowH2", iLowH2LineEdit)); // nao sei se vou usar
        connect(iLowH2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowH2", iLowH2LineEdit);


        //iHighH2
        QLineEdit* iHighH2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighH2));
        iHighH2LineEdit->setPlaceholderText("iHighH2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighH2", iHighH2LineEdit)); // nao sei se vou usar
        connect(iHighH2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighH2", iHighH2LineEdit);

        //iLowL2
        QLineEdit* iLowL2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowL2));
        iLowL2LineEdit->setPlaceholderText("iLowL2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowL2", iLowL2LineEdit)); // nao sei se vou usar
        connect(iLowL2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowL2", iLowL2LineEdit);

        //iHighL2
        QLineEdit* iHighL2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighL2));
        iHighL2LineEdit->setPlaceholderText("iHighL2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighL2", iHighL2LineEdit)); // nao sei se vou usar
        connect(iHighL2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighL2", iHighL2LineEdit);

        //iLowS2
        QLineEdit* iLowS2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iLowS2));
        iLowS2LineEdit->setPlaceholderText("iLowS2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iLowS2", iLowS2LineEdit)); // nao sei se vou usar
        connect(iLowS2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iLowS2", iLowS2LineEdit);

        //iHighS2
        QLineEdit* iHighS2LineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.iHighS2));
        iHighS2LineEdit->setPlaceholderText("iHighS2");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("iHighS2", iHighS2LineEdit)); // nao se vou usar
        connect(iHighS2LineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("iHighS2", iHighS2LineEdit);



        //kernel
        QLineEdit* kernelLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.kernel));
        kernelLineEdit->setPlaceholderText("kernel");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("kernel", kernelLineEdit)); // nao se vou usar
        connect(kernelLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("kernel", kernelLineEdit);

        //minThreshold
        QLineEdit* minThresholdLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.minThreshold));
        minThresholdLineEdit->setPlaceholderText("minThreshold");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minThreshold", minThresholdLineEdit)); // nao se vou usar
        connect(minThresholdLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minThreshold", minThresholdLineEdit);

        //maxThreshold
        QLineEdit* maxThresholdLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.maxThreshold));
        maxThresholdLineEdit->setPlaceholderText("maxThreshold");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("maxThreshold", maxThresholdLineEdit)); // nao se vou usar
        connect(maxThresholdLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("maxThreshold", maxThresholdLineEdit);

        //minArea
        QLineEdit* minAreaLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.minArea));
        minAreaLineEdit->setPlaceholderText("minArea");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minArea", minAreaLineEdit)); // nao se vou usar
        connect(minAreaLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minArea", minAreaLineEdit);

        //minCircularity
        QLineEdit* minCircularityLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.minCircularity));
        minCircularityLineEdit->setPlaceholderText("minCircularity");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minCircularity", minCircularityLineEdit)); // nao se vou usar
        connect(minCircularityLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minCircularity", minCircularityLineEdit);

        //minConvexity
        QLineEdit* minConvexityLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.minConvexity));
        minConvexityLineEdit->setPlaceholderText("minConvexity");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minConvexity", minConvexityLineEdit)); // nao se vou usar
        connect(minConvexityLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minConvexity", minConvexityLineEdit);

        //minInertiaRatio
        QLineEdit* minInertiaRatioLineEdit = new QLineEdit(QString::number(videoThread->ballDetector2.minInertiaRatio));
        minInertiaRatioLineEdit->setPlaceholderText("minInertiaRatio");
        this->lineEditMap.insert(std::pair<QString, QLineEdit*>("minInertiaRatio", minInertiaRatioLineEdit)); // nao se vou usar
        connect(minInertiaRatioLineEdit, SIGNAL(returnPressed()), this, SLOT(paramChanged()));
        paramLayout->addRow("minInertiaRatio", minInertiaRatioLineEdit);

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

    else if(newfunction == "fieldDetector2"){
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
        else if(lineEdit->placeholderText() == "factor"){
            videoThread->fieldDetector2.factor = (lineEdit->text().toFloat());
        }
        else if(lineEdit->placeholderText() == "dp"){
            videoThread->fieldDetector2.dp = (lineEdit->text().toDouble());
        }
        else if(lineEdit->placeholderText() == "minDist"){
            videoThread->fieldDetector2.minDist = (lineEdit->text().toDouble());
        }
        else if(lineEdit->placeholderText() == "param1"){
            videoThread->fieldDetector2.param1 = (lineEdit->text().toDouble());
        }
        else if(lineEdit->placeholderText() == "param2"){
            videoThread->fieldDetector2.param2 = (lineEdit->text().toDouble());
        }
        else if(lineEdit->placeholderText() == "maxRadius"){
            videoThread->fieldDetector2.maxRadius = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minRadius"){
            videoThread->fieldDetector2.minRadius = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "kernel"){
            videoThread->fieldDetector2.kernel = (lineEdit->text().toInt());
        }
    }

    else if(newfunction == "ballDetector2"){
        if(lineEdit->placeholderText() == "ILowH"){
            videoThread->ballDetector2.iLowH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighH"){
            videoThread->ballDetector2.iHighH = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowL"){
            videoThread->ballDetector2.iLowL = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighL"){
            videoThread->ballDetector2.iHighL = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowS"){
            videoThread->ballDetector2.iLowS = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighS"){
            videoThread->ballDetector2.iHighS = (lineEdit->text().toInt());
        }

        else if(lineEdit->placeholderText() == "ILowH2"){
            videoThread->ballDetector2.iLowH2 = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighH2"){
            videoThread->ballDetector2.iHighH2 = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowL2"){
            videoThread->ballDetector2.iLowL2 = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighL2"){
            videoThread->ballDetector2.iHighL2 = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iLowS2"){
            videoThread->ballDetector2.iLowS2 = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "iHighS2"){
            videoThread->ballDetector2.iHighS2 = (lineEdit->text().toInt());
        }

        if(lineEdit->placeholderText() == "kernel"){
            videoThread->ballDetector2.kernel = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minThreshold"){
            videoThread->ballDetector2.minThreshold = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "maxThreshold"){
            videoThread->ballDetector2.maxThreshold = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minArea"){
            videoThread->ballDetector2.minArea = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minCircularity"){
            videoThread->ballDetector2.minCircularity = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minConvexity"){
            videoThread->ballDetector2.iHighS = (lineEdit->text().toInt());
        }
        else if(lineEdit->placeholderText() == "minInertiaRatio"){
            videoThread->ballDetector2.minInertiaRatio = (lineEdit->text().toInt());
        }


    }

}


