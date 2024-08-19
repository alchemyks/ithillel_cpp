#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <cstdio>

#include "sensormetric.h"

class Logger : public QObject
{
    Q_OBJECT


private:
    QFile logFile;
    QTextStream *consoleTextStream;
    QTextStream *fileTextStream;


public:
    explicit Logger(QObject *parent = nullptr);
    explicit Logger(QString pathLogFile);
    QString getFormatLine(const SensorMetric& aSensorMetric);
    void writeToLogFile(QString line);
    void writeToConsole(QString line);

public slots:
    void writeData(const SensorMetric& aSensorMetric);
    void writeConsole(const QString& lineToWtite);


};

#endif // LOGGER_H
