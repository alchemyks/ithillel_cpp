#ifndef SENSORMETRIC_H
#define SENSORMETRIC_H

#include <QObject>
#include <QString>

struct SensorMetric{
    QString name;
    int value;

};

Q_DECLARE_METATYPE(SensorMetric)

#endif // SENSORMETRIC_H
