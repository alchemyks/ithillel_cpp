#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

#include "sensormetric.h"


class Sensor : public QObject
{
    Q_OBJECT
private:
    QString name;

public:
    explicit Sensor(QObject *parent = nullptr);
    explicit Sensor(QString name);

    void newData(int value);

signals:
    void dataReady(const SensorMetric& aSensorMetric);
};

#endif // SENSOR_H
