#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMutex>

using namespace AL;
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    threadFinished(false),
    isRecording(false),
    camera(0)
{
    ui->setupUi(this);

    QPixmap background(320,240);
    background.fill(Qt::darkGray);
    ui->image_frame->setPixmap(background);

    QPixmap unbeatables_logo(":/images/unbeatables.png");
    ui->unbeatablesLogo->setPixmap(unbeatables_logo);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::displayImage()
{
    if(isConnected){
        imgContainer = imagePipe.load();
        ui->image_frame->setPixmap(QPixmap::fromImage(imgContainer.image, Qt::AutoColor));
    }
    else
    {
        QPixmap background(320,240);
        background.fill(Qt::darkGray);
        ui->image_frame->setPixmap(background);
    }
}

void MainWindow::threadFinishedslot()
{
    cout<< "closing window" << endl;
    QMutex mutex;
    mutex.lock();
    threadFinished = true;
    mutex.unlock();
}

void MainWindow::updateStatusMessage(QString message)
{
    ui->statusBar->showMessage(message);
}

void MainWindow::on_connectButton_clicked()
{
    QString naoIP = ui->lineIP->text();
    if(!isConnected){
        if(naoIP.isEmpty())
        {
            ui->statusBar->showMessage("Write IP before connecting.");
            return;
        }
        emit connectCamera(true, naoIP);
    }
    else
    {
        cout << "tentando desconectar"<< endl;
        emit connectCamera(false, naoIP);

    }
}

void MainWindow::on_StartRecordingButton_clicked()
{
    if(!isRecording)
    {
        QString qstring = ui->fileNameLine->text();
        if(qstring.isEmpty())
        {
            ui->statusBar->showMessage("Write file name before start recording.");
            return;
        }
        emit record(qstring);
        ui->StartRecordingButton->setText("Stop and Save");
        isRecording = true;
    }
    else
    {
        emit stopRecording();
        ui->StartRecordingButton->setText("Start Recording");
        isRecording = false;
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    cout << "Emiting close" << endl;
    emit finishThread();
}

void MainWindow::on_changeCameraButton_clicked()
{
    if(camera)
        camera = 0;
    else
        camera = 1;
    emit changeCamera(camera);
    QCoreApplication::processEvents();
}

void MainWindow::on_pushButton_clicked()
{
    cout << "Button Test" << endl;
    emit savePicture();

    QCoreApplication::processEvents();
}

void MainWindow::on_FunctionSelected_activated(QString functionSelected){
      emit newFunctionSelected(functionSelected, ui->debugImageVectorSelector, ui->ParamLayout);
}

void MainWindow::checkConnection(bool connection)
{
    if(connection){
        ui->connectButton->setText("Disconnect");
        isConnected = true;
    }
    else{
        ui->connectButton->setText("Connect");
        isConnected = false;
    }
}



