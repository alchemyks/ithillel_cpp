#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "sensormetric.h"
#include <QObject>

class Simulator : public QObject
{
    Q_OBJECT

private:
     bool simulateStopFlag = false;
    int timeSim;

public:
    explicit Simulator(QObject *parent = nullptr);
    explicit Simulator(int timeSim);

public slots:
    void startSimulate(QList<QString> listSensorName);

signals:
    void simSensor(SensorMetric fakeData);
    void sendLogToGui(QString dataText);
    void simulationIsStoped();
};

#endif // SIMULATOR_H
