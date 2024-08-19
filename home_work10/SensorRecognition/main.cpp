#include "analyser.h"
#include "config.h"
#include "logger.h"
#include "sensor.h"
#include "sensormetric.h"
//#include "config.h"
#include <QCoreApplication>
#include <QList>
#include <QCommandLineParser>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    qRegisterMetaType<SensorMetric>("SensorMetric");
    Config config(&a);
    Sensor cpuTempSensor("CPU_temp");
    Sensor fanSpeedSensor("FAN_Speed_RPM");
    Analyser analyser;
    Logger logger(config.getLogFileName());
    //Config *config = Config::GetInstance(&a);
    QObject::connect(&cpuTempSensor, &Sensor::dataReady, &analyser, &Analyser::analyseData);
    QObject::connect(&cpuTempSensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&fanSpeedSensor, &Sensor::dataReady, &analyser, &Analyser::analyseData);
    QObject::connect(&fanSpeedSensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&analyser, &Analyser::sendToIO, &logger, &Logger::writeConsole);

    for (int i = 0; i < 10; ++i) {
        cpuTempSensor.newData(i + 20);
        fanSpeedSensor.newData(i + 1000);
    }


    if(!config.getNameSensorAnalyse().isEmpty()){
        analyser.reportPrint(config.getParamAnalyse(), config.getNameSensorAnalyse());
    }else{
        analyser.reportPrint(config.getParamAnalyse());
    }

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    //return a.exec();
}
