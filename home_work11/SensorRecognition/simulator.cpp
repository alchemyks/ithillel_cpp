#include "simulator.h"

#include <QTime>
#include <QDateTime>
#include <QRandomGenerator>
#include <QThread>


Simulator::Simulator(QObject *parent)
    : QObject{parent}
{}

Simulator::Simulator(int timeSim): timeSim(timeSim){}

void Simulator::startSimulate(QList<QString> listSensorName)
{
    QTime startTime = QTime::currentTime();
    QRandomGenerator generator;
    simulateStopFlag = false;
    emit sendLogToGui("Start sim!!!");
    while(startTime.secsTo(QTime::currentTime()) < timeSim){
        for(auto &name: listSensorName){
            int value = generator.bounded(10, 1000);

            emit simSensor(SensorMetric{name, value});
            emit sendLogToGui(QString("Sim sensor: %1, value: %2").arg(name, QString::number(value)));
            QThread::currentThread()->sleep(1);
        }
    }
    emit sendLogToGui(QString("Stop sim!!!!"));
    emit simulationIsStoped();
}

