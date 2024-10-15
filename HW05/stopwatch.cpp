#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject{parent} {
    timer = new QTimer(this);
    time.setHMS(0, 0, 0, 0);
    stop_time.setHMS(0, 0, 0, 0);
    timer->setInterval(INTERVAL);
    connect(timer, &QTimer::timeout, this, &Stopwatch::UpdateTime);
}

Stopwatch::~Stopwatch() {
    delete timer;
}

void Stopwatch::UpdateTime() {
    time = time.addMSecs(100);
    current_time = time.toString("mm:ss.z");
    emit sig_UpdateTime(current_time);
}

void Stopwatch::StartTimer() {
    timer->start();
    UpdateTime();
}

void Stopwatch::StopTimer() {
    timer->stop();
}

void Stopwatch::ReceiveCircle() {
    int msec = stop_time.msecsTo(time);
    stop_time.setHMS(0, 0, 0, 0);
    stop_time = stop_time.addMSecs(msec);

    circle_time =   "Круг №"
                  + QString::number(circle_count++)
                  + " - "
                  + stop_time.toString("mm:ss.z");
    stop_time = time;
}


void Stopwatch::ReceiveClear() {
    circle_count = 1;
    time.setHMS(0, 0, 0, 0);
    stop_time.setHMS(0, 0, 0, 0);
}

QString Stopwatch::GetCurrentTime() {
    return this->current_time;
}

QString Stopwatch::GetCircleTime() {
    return this->circle_time;
}
