#include "sensorgui.h"
#include <QtConcurrentRun>
#include <QThread>
#include <QApplication>
#include <QDebug>

SensorGui::SensorGui(QWidget *parent): QWidget(parent) {

    listSensorWidget = new QListWidget();

    buttonAddSensor = new QPushButton();
    buttonAddSensor->setText("Add Sensor");
    buttonDelSensor = new QPushButton();
    buttonDelSensor->setText("Delete Sensor");
    buttonDelSensor->setDisabled(true);
    buttonSimSensor = new QPushButton();
    buttonSimSensor->setText("Simulate");
    buttonSimSensor->setDisabled(true);
    logTextBlock = new QTextEdit();

    mainLayout = new QHBoxLayout();

    sensorViewLayout = new QHBoxLayout();
    sensorViewLayout->addWidget(listSensorWidget);

    buttonGroup = new QHBoxLayout();
    buttonGroup->addWidget(buttonAddSensor);
    buttonGroup->addWidget(buttonDelSensor);

    bttnLogSimLayout = new QVBoxLayout();
    bttnLogSimLayout->addLayout(buttonGroup);
    bttnLogSimLayout->addWidget(logTextBlock);
    bttnLogSimLayout->addWidget(buttonSimSensor);

    mainLayout->addLayout(sensorViewLayout);
    mainLayout->addLayout(bttnLogSimLayout);

    connect(buttonSimSensor, &QPushButton::clicked, this, &SensorGui::pressedButtonSimulate);
    connect(buttonAddSensor, &QPushButton::clicked, this, &SensorGui::pressedAddButton);
    connect(buttonDelSensor, &QPushButton::clicked, this, &SensorGui::pressedDelButton);
    connect(listSensorWidget, &QListWidget::itemClicked, this, &SensorGui::activateButtonDel);
    connect(listSensorWidget, &QListWidget::currentItemChanged, this, &SensorGui::deActivateButtonDel);

    setWindowTitle("Sensor Manager");
    setFixedSize(700, 500);

    setLayout(mainLayout);
}

void SensorGui::slotReceiveSensorData(const QMap<QString, QList<SensorMetric> > *data)
{
    listSensorWidget->clear();
    if(data->empty() || isSimulate){
        buttonSimSensor->setDisabled(true);
    }else{
        buttonSimSensor->setDisabled(false);
    }
    for(auto [key, value] : data->asKeyValueRange()){
        new QListWidgetItem(key, listSensorWidget);
    }
}

void SensorGui::receiveSimResult(QString textData)
{
    logTextBlock->append(textData);
}

void SensorGui::pressedAddButton()
{
    emit addSensor(QString("Sensor-%1"));
    emit getSensorsData();
}

void SensorGui::pressedButtonSimulate()
{
    QList<QListWidgetItem *> items = listSensorWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    QList<QString> names;
    foreach (QListWidgetItem *item, items) {
        names.append(item->text());
    }
    isSimulate = true;
    buttonSimSensor->setDisabled(true);
    emit startSimulateSensor(names);
}



void SensorGui::activateButtonDel()
{
    buttonDelSensor->setDisabled(false);
}

void SensorGui::deActivateButtonDel()
{
    buttonDelSensor->setDisabled(true);
}

void SensorGui::pressedDelButton()
{
    emit deleteSensor(listSensorWidget->currentItem()->text());
}

void SensorGui::simulationIsStoped()
{
    isSimulate = false;
    buttonSimSensor->setDisabled(false);
}
