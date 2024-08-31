#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <cstdio>

class Logger : public QObject
{
    Q_OBJECT


private:
    QFile logFile;
    QTextStream *fileTextStream;


public:
    explicit Logger(QObject *parent = nullptr);
    explicit Logger(QString pathLogFile);
    QString getFormatLine(const QString &calcEvent);
    void writeToLogFile(QString line);
    Q_INVOKABLE void writeData(const QString calcEvent);

};

#endif // LOGGER_H
