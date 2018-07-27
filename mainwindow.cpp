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

    QPixmap background(640,480);
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
    imgContainer = imagePipe.load();
    ui->image_frame->setPixmap(QPixmap::fromImage(imgContainer.image, Qt::AutoColor));
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
    if(naoIP.isEmpty())
    {
        ui->statusBar->showMessage("Write IP before connecting.");
        return;
    }
    emit connectCamera(naoIP);
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
    //emit finishThread();
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


