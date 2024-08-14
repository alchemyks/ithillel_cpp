#include "analyzer.h"
#include "logger.h"
#include "sensor.h"
#include "sensormetric.h"
#include <QCoreApplication>
#include <QList>
#include <QCommandLineParser>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser parser;
    QCommandLineOption name_param(QStringList()<<"n"<<"name","Name","sensor-name");
    QCommandLineOption min_param("min", QCoreApplication::translate("main", "Min value"));
    QCommandLineOption max_param("max", QCoreApplication::translate("max","Max value"));
    QCommandLineOption avg_param("avg", QCoreApplication::translate("avg", "Average value"));
    QCommandLineOption med_param("med", QCoreApplication::translate("med", "Median value"));


    parser.addOption(name_param);
    parser.addOption(min_param);
    parser.addOption(max_param);
    parser.addOption(avg_param);
    parser.addOption(med_param);

    parser.process(a);

    qRegisterMetaType<SensorMetric>("SensorMetric");
    Sensor cpuTempSensor("CPU_temp");
    Sensor fanSpeedSensor("FAN_Speed_RPM");
    Analyzer analyzer;
    Logger logger;


    QObject::connect(&cpuTempSensor, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);
    QObject::connect(&cpuTempSensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&fanSpeedSensor, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);
    QObject::connect(&fanSpeedSensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&analyzer, &Analyzer::sendToIO, &logger, &Logger::writeConsole);

    for (int i = 0; i < 10; ++i) {
        cpuTempSensor.newData(i + 20);
        fanSpeedSensor.newData(i + 1000);
    }

    /*
    b'0001' min  id dec 1
    b'0010' max  /----/ 2
    b'0100' avg  /----/ 4
    b'1000' med  /----/ 8
    b'1111' med  /----/ 15
    */

    int param = 0;
    if(parser.isSet(min_param)){
        param = param | 0x0001;
    }
    if(parser.isSet(max_param)){
        param = param | 0x0002;
    }
    if(parser.isSet(avg_param)){
        param = param | 0x0004;
    }
    if(parser.isSet(med_param)){
        param = param | 0x0008;
    }

    if(param == 0 and parser.isSet(name_param)){
        param = 15;
    }

    if(parser.isSet(name_param)){
        analyzer.reportPrint(param, parser.value(name_param));
    }else{
        analyzer.reportPrint(param);
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
