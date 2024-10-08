#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watch = new Stopwatch(this);

    this->setFixedSize(250, 355);


    ui->groupBox->setTitle("Время");
    ui->groupBox->setFont(QFont("Segoe UI", 12));

    ui->tb_TimeTable->setFont(QFont("Segoe UI", 14));

    ui->la_Time->setText("0:00.0");
    ui->la_Time->setFont(QFont("Arial black", 23));

    ui->pb_Start_Stop->setText("Старт");
    ui->pb_Start_Stop->setStyleSheet("background-color:green");

    ui->pb_Clear->setText("Очистить");

    ui->pb_Circle->setText("Круг");
    ui->pb_Circle->setEnabled(false);

    connect(watch, &Stopwatch::sig_UpdateTime, this, &MainWindow::lapTime);
    connect(this, &MainWindow::sig_Start, watch, &Stopwatch::StartTimer);
    connect(this, &MainWindow::sig_Stop, watch, &Stopwatch::StopTimer);
    connect(this, &MainWindow::sig_Clear, watch, &Stopwatch::ReceiveClear);
    connect(this, &MainWindow::sig_Circle, watch, &Stopwatch::ReceiveCircle);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lapTime(QString &text){
    ui->la_Time->setText(text);
}

void MainWindow::on_pb_Start_Stop_clicked()
{
    if (checked){
        ui->pb_Start_Stop->setText("Пауза");
        ui->pb_Start_Stop->setStyleSheet("background-color:red");
        ui->pb_Circle->setEnabled(true);
        emit sig_Start();
        checked = false;
    } else {
        ui->pb_Start_Stop->setText("Старт");
        ui->pb_Start_Stop->setStyleSheet("background-color:green");
        ui->pb_Circle->setEnabled(false);
        emit sig_Stop();
        checked = true;
    }
}


void MainWindow::on_pb_Circle_clicked()
{
    emit sig_Circle();
    QString text = watch->GetCircleTime();
    ui->tb_TimeTable->append(text);
}


void MainWindow::on_pb_Clear_clicked()
{
    ui->tb_TimeTable->clear();
    ui->la_Time->setText("0:00.0");
    emit sig_Clear();
}

