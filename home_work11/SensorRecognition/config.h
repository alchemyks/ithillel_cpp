#ifndef CONFIG_H
#define CONFIG_H

#include "settings.h"

#include <QObject>
#include <QCoreApplication>
#include <QSettings>

class Config : public QObject
{
    Q_OBJECT

private:

    Settings settings;

    int paramAnalyse;
    QString nameSensorAnalyse;

public:

    explicit Config(QObject *parent = nullptr);
    explicit Config(QCoreApplication *a);

    QString getLogFileName();
    bool readConfigFile(QString path = nullptr);
    bool writeConfigFile();
    QString toString();
    int getTimeSimulation();


    int getParamAnalyse() const;

    QString getNameSensorAnalyse() const;

signals:
    void writeToConsole(QString data);
};

#endif // CONFIG_H
