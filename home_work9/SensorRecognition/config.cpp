#include "config.h"
#include <QFile>
#include <QStringList>
#include <QLatin1String>

Config::Config(QObject *parent)
    : QObject{parent}
{
    Config::defaultLogFileName = "sensor.log";
    Config::logFilePath = "./";
}

    QString Config::getFileName(){
    QString logFileName(defaultLogFileName);
    QStringList logFileSplit = logFileName.split(".");
    int fileCount = 1;
    while(QFile::exists(logFilePath + logFileName)){
        logFileName = logFileSplit[0] + QString::number(fileCount) + "." + logFileSplit[1];
        fileCount++;
    }
    return logFileName;
}
