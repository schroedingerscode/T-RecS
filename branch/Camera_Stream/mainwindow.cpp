#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

std::ofstream ofs;
int fd;

int MainWindow::freq_array[13] = {0,5,10,25,50,100,250,500,750,1000,1500,2000,2500};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage imageObject;
    imageObject.load("/home/sschroeder/Pictures/StreamDisplayed.png");
    myScene = new QGraphicsScene(this);
    myScene->addPixmap(QPixmap::fromImage(imageObject));
    keyDelayTimer = 0;

    x_freq = 500;
    y_freq = 500;

    //File  Ops
    //ofs.open("/dev/ttyACM0", std::ofstream::out | std::ofstream::app);
    //std::cout << ofs.is_open() << std::endl;
    //ofs << " \r\n";

    if((fd = open("/dev/ttyACM0", O_RDWR|O_NOCTTY)) == -1) {
        printf("Error");
    }
    write(fd, " \r", 2);

}

MainWindow::~MainWindow()
{
    delete myScene;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *) {
    ui->primaryCamera->setScene(myScene);
    ui->primaryCamera->fitInView(myScene->sceneRect(),Qt::KeepAspectRatio);

    QString disp_string_x = "X Frequency: ";
    disp_string_x += QString::number(x_freq);
    ui->x_freq_disp->setText(disp_string_x);

    QString disp_string_y = "Y Frequency: ";
    disp_string_y += QString::number(y_freq);
    ui->y_freq_disp->setText(disp_string_y);
}

void MainWindow::on_switchStreamButton_clicked()
{
    QGraphicsScene *tempScene = ui->secondaryCamera->scene();
    ui->secondaryCamera->setScene(ui->primaryCamera->scene());
    ui->secondaryCamera->fitInView(ui->secondaryCamera->sceneRect(),Qt::KeepAspectRatio);
    ui->primaryCamera->setScene(tempScene);
    ui->primaryCamera->fitInView(ui->primaryCamera->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::on_upDirButton_clicked(bool released = false)
{
    if(!released) {
        //Set Down:Up ratio >1
        /*ofs << "y_freq: 1000\r";
        ofs << "y_pos: 1\r";*/
        char* output_string;
        output_string = (char*) malloc(sizeof(char)*20);
        std::sprintf(output_string, "y_freq: %d\r", y_freq);

        write(fd,output_string, strlen(output_string));
        //write(fd,"y_freq: 1000\r", 13);
        write(fd,"y_pos: 1\r", 9);
        free(output_string);
    } else {
        //Set Down:Up ratio 0
        /*ofs << "y_freq: 0\r";*/
        write(fd,"y_freq: 0\r", 10);
    }
}

void MainWindow::on_leftDirButton_clicked(bool released = false)
{
    if(!released) {
        //Set Down:Up ratio >1
        /*ofs << "x_freq: 1000\r";
        ofs << "x_pos: 0\r\n";*/
        char* output_string;
        output_string = (char*) malloc(sizeof(char)*20);
        std::sprintf(output_string, "x_freq: %d\r", x_freq);

        write(fd,output_string, strlen(output_string));
        //write(fd,"x_freq: 1000\r", 13);
        write(fd,"x_pos: 0\r", 9);
        free(output_string);
    } else {
        //Set Down:Up ratio 0
       /* ofs << "x_freq: 0\r";*/
       write(fd,"x_freq: 0\r", 10);
    }
}

void MainWindow::on_downDirButton_clicked(bool released = false)
{
    if(!released) {
        //Set Down:Up ratio >1
        /*ofs << "y_freq: 1000\r";
        ofs << "y_pos: 0\r";*/
        char* output_string;
        output_string = (char*) malloc(sizeof(char)*20);
        std::sprintf(output_string, "y_freq: %d\r", y_freq);

        write(fd,output_string, strlen(output_string));
        //write(fd,"y_freq: 1000\r", 13);
        write(fd,"y_pos: 0\r", 9);
        free(output_string);
    } else {
        //Set Down:Up ratio 0
        /*ofs << "y_freq: 0\r";*/
        write(fd,"y_freq: 0\r", 10);
    }
}

void MainWindow::on_rightDirButton_clicked(bool released = false)
{
    if(!released) {
        //Set Down:Up ratio >1
       /* ofs << "x_freq: 1000\r";
        ofs << "x_pos: 1\r\n";*/
        char* output_string;
        output_string = (char*) malloc(sizeof(char)*20);
        std::sprintf(output_string, "x_freq: %d\r", x_freq);

        write(fd,output_string, strlen(output_string));
        //write(fd,"x_freq: 1000\r", 13);
        write(fd,"x_pos: 1\r", 9);
        free(output_string);
    } else {
        //Set Down:Up ratio 0
       /* ofs << "x_freq: 0\r";*/
        write(fd,"x_freq: 0\r", 10);
    }
}

void MainWindow::change_x_freq(int dir) {
    for(unsigned int i = 0; i<(sizeof(freq_array)/sizeof(int)); ++i) {
        if(x_freq == freq_array[i]) {
            //(!dir) ? x_freq = freq_array[i-1] : x_freq = freq_array[i+1];

            (!dir) ? ((i==0) ? (x_freq) : (x_freq = freq_array[i-1])) : ((i==(sizeof(freq_array)/sizeof(int))-1) ? (x_freq) : (x_freq = freq_array[i+1]));
            QString disp_string_x = "X Frequency: ";
            disp_string_x += QString::number(x_freq);
            ui->x_freq_disp->setText(disp_string_x);
            break;
        }
    }
}

void MainWindow::change_y_freq(int dir) {
        for(unsigned int i = 0; i<(sizeof(freq_array)/sizeof(int)); ++i) {
            if(y_freq == freq_array[i]) {
                //(!dir) ? y_freq = freq_array[i-1] : y_freq = freq_array[i+1];

                (!dir) ? ((i==0) ? (y_freq) : (y_freq = freq_array[i-1])) : ((i==(sizeof(freq_array)/sizeof(int))-1) ? (y_freq) : (y_freq = freq_array[i+1]));
                QString disp_string_y = "Y Frequency: ";
                disp_string_y += QString::number(y_freq);
                ui->y_freq_disp->setText(disp_string_y);
                break;
            }
        }
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent) {
    if(!keyEvent->isAutoRepeat()) {
        switch(keyEvent->key()) {
        //TODO: Write click handlers for left,right,up,down.
        case Qt::Key_Left:
            ui->leftDirButton->click();
            if(!ui->leftDirButton->isDown())
                ui->leftDirButton->setDown(true);
            break;
        case Qt::Key_Right:
            ui->rightDirButton->click();
            if(!ui->rightDirButton->isDown())
                ui->rightDirButton->setDown(true);
            break;
        case Qt::Key_Up:
            ui->upDirButton->click();
            if(!ui->upDirButton->isDown())
                ui->upDirButton->setDown(true);
            break;
        case Qt::Key_Down:
            ui->downDirButton->click();
            if(!ui->downDirButton->isDown())
                ui->downDirButton->setDown(true);
            break;
        case Qt::Key_W:
            change_y_freq(1);
            if(ui->leftDirButton->isDown())
                ui->leftDirButton->click();
            if(ui->rightDirButton->isDown())
                ui->rightDirButton->click();
            if(ui->upDirButton->isDown())
                ui->upDirButton->click();
            if(ui->downDirButton->isDown())
                ui->downDirButton->click();
            break;
        case Qt::Key_A:
            change_x_freq(0);
            if(ui->leftDirButton->isDown())
                ui->leftDirButton->click();
            if(ui->rightDirButton->isDown())
                ui->rightDirButton->click();
            if(ui->upDirButton->isDown())
                ui->upDirButton->click();
            if(ui->downDirButton->isDown())
                ui->downDirButton->click();
            break;
        case Qt::Key_S:
            change_y_freq(0);
            if(ui->leftDirButton->isDown())
                ui->leftDirButton->click();
            if(ui->rightDirButton->isDown())
                ui->rightDirButton->click();
            if(ui->upDirButton->isDown())
                ui->upDirButton->click();
            if(ui->downDirButton->isDown())
                ui->downDirButton->click();
            break;
        case Qt::Key_D:
            change_x_freq(1);
            if(ui->leftDirButton->isDown())
                ui->leftDirButton->click();
            if(ui->rightDirButton->isDown())
                ui->rightDirButton->click();
            if(ui->upDirButton->isDown())
                ui->upDirButton->click();
            if(ui->downDirButton->isDown())
                ui->downDirButton->click();
            break;
        case Qt::Key_Space:
            if(!(keyDelayTimer++%10)){
                ui->switchStreamButton->click();
            }
            if(!ui->switchStreamButton->isDown())
                ui->switchStreamButton->setDown(true);
        default:
            //Do Nothing
            break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent) {
    if(!keyEvent->isAutoRepeat()) {
        switch(keyEvent->key()) {
        case Qt::Key_Left:
            ui->leftDirButton->clicked(true);
            ui->leftDirButton->setDown(false);
            break;
        case Qt::Key_Right:
            ui->rightDirButton->clicked(true);
            ui->rightDirButton->setDown(false);
            break;
        case Qt::Key_Up:
            ui->upDirButton->clicked(true);
            ui->upDirButton->setDown(false);
            break;
        case Qt::Key_Down:
            ui->downDirButton->clicked(true);
            ui->downDirButton->setDown(false);
            break;
        case Qt::Key_Space:
            keyDelayTimer = 0;
            ui->switchStreamButton->setDown(false);
        default:
            //Do Nothing
            break;
        }
    }
}
