#include "analyser.h"
#include "config.h"
#include "logger.h"
#include "sensor.h"
#include "sensorgui.h"
#include "sensormetric.h"
//#include "config.h"
#include <QThread>
#include <QApplication>
#include <QList>
#include <QCommandLineParser>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <simulator.h>

#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    qRegisterMetaType<SensorMetric>("SensorMetric");
    Config config(&app);
    Analyser analyser;
    Logger logger(config.getLogFileName());
    Simulator simulator(config.getTimeSimulation());
    QObject::connect(&analyser, &Analyser::sendToIO, &logger, &Logger::writeConsole);


    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    SensorGui gui;

    QObject::connect(&gui, &SensorGui::getSensorsData, &analyser, &Analyser::slotSensorData);
    QObject::connect(&analyser, &Analyser::sendSensorsData, &gui, &SensorGui::slotReceiveSensorData);

    QObject::connect(&gui, &SensorGui::addSensor, &analyser, &Analyser::addSensor);
    QObject::connect(&gui, &SensorGui::deleteSensor, &analyser, &Analyser::deleteSensor);

    QThread *thread = new QThread;
    simulator.moveToThread(thread);
    thread->start();
    QObject::connect(&simulator, &Simulator::simSensor, &analyser, &Analyser::analyseData);
    QObject::connect(&gui, &SensorGui::startSimulateSensor, &simulator, &Simulator::startSimulate);
    QObject::connect(&simulator, &Simulator::sendLogToGui, &gui, &SensorGui::receiveSimResult);
    QObject::connect(&simulator, &Simulator::simulationIsStoped, &gui, &SensorGui::simulationIsStoped);


    gui.show();

    return app.exec();
}
