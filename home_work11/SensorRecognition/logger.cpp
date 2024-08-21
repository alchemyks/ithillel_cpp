#include <QDateTime>

#include "logger.h"
//#include "config.h"


Logger::Logger(QObject *parent): QObject{parent}
{

}

Logger::Logger(QString pathLogFile){
    logFile.setFileName(pathLogFile);
    if(logFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        fileTextStream = new QTextStream(&logFile);
    }
    consoleTextStream = new QTextStream(stdout);

}



QString Logger::getFormatLine(const SensorMetric &aSensorMetric){
    QString formattedString = QString("%1 | name=%2 | value=%3\n")
                                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                       aSensorMetric.name, QString::number(aSensorMetric.value));

    return formattedString;
}

void Logger::writeToLogFile(QString line)
{
    if(logFile.isOpen()){
        *fileTextStream << line;
        fileTextStream->flush();
    }
}

void Logger::writeToConsole(QString line)
{
    *consoleTextStream << line;
    consoleTextStream->flush();
}

void Logger::writeData(const SensorMetric &aSensorMetric)
{
    QString prepareData = getFormatLine(aSensorMetric);
    writeToConsole(prepareData);
    writeToLogFile(prepareData);

}

void Logger::writeConsole(const QString &lineToWtite){
    writeToConsole(lineToWtite);
}


