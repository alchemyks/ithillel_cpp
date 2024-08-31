#include <QDateTime>
#include "logger.h"


Logger::Logger(QObject *parent): QObject{parent}
{

}

Logger::Logger(QString pathLogFile){
    logFile.setFileName(pathLogFile);
    if(logFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        fileTextStream = new QTextStream(&logFile);
    }
}



QString Logger::getFormatLine(const QString &calcEvent){
    QString formattedString = QString("%1 | %2 \n")
                                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), calcEvent);

    return formattedString;
}

void Logger::writeToLogFile(QString line)
{
    if(logFile.isOpen()){
        *fileTextStream << line;
        fileTextStream->flush();
    }
}


void Logger::writeData(const QString calcEvent)
{
    QString prepareData = getFormatLine(calcEvent);
    writeToLogFile(prepareData);

}



