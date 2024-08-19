#include "sensor.h"

Sensor::Sensor(QObject *parent)
    : QObject{parent}
{}

Sensor::Sensor(QString name): name(name){

}

void Sensor::newData(int value){
    emit dataReady(SensorMetric{name, value});
}
