#ifndef SETTINGS_H
#define SETTINGS_H

#endif // SETTINGS_H

#include <QString>
#include <QStringList>

struct Settings{
    int maxRecords = 10000;
    int timeSimulation = 10000;
    QString *pathToLogFile = new QString("./logs/");
    QString *logFileName = new QString("sensor.log");
    QString *pathToConfigFile = new QString("./configs/config.json");





    ~Settings(){
        delete pathToLogFile;
        delete logFileName;
        pathToLogFile = nullptr;
        logFileName = nullptr;
    }
};
