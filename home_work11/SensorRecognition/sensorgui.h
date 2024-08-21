#ifndef SENSORGUI_H
#define SENSORGUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <analyser.h>

class SensorGui: public QWidget
{
    Q_OBJECT

private:
    QLabel *lable;

    QListWidget *listSensorWidget;
    QPushButton *buttonAddSensor;
    QPushButton *buttonDelSensor;
    QPushButton *buttonSimSensor;
    QHBoxLayout *mainLayout;
    QHBoxLayout *buttonGroup;
    QHBoxLayout *sensorViewLayout;
    QVBoxLayout *bttnLogSimLayout;
    QTextEdit *logTextBlock;

    bool isSimulate = false;


public:
    SensorGui(QWidget *parent = nullptr);

public slots:
    void slotReceiveSensorData(const QMap<QString, QList<SensorMetric>> *data);
    void receiveSimResult(QString textData);
    void pressedAddButton();
    void pressedButtonSimulate();
    void activateButtonDel();
    void deActivateButtonDel();
    void pressedDelButton();
    void simulationIsStoped();



signals:
    void getSensorsData();
    void deleteSensor(QString name);
    void addSensor(QString name = nullptr);
    void startSimulateSensor(const QList<QString> &sensorNames);

};

#endif // SENSORGUI_H
