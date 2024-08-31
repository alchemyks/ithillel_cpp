#ifndef ANALYSER_H
#define ANALYSER_H

#include "sensormetric.h"
#include <QObject>
#include <QMap>


class Analyser : public QObject
{
    Q_OBJECT

private:
    QMap<QString, QList<SensorMetric>> dataSensorsMetric;
public:
    explicit Analyser(QObject *parent = nullptr);

    int getMax(QString name)const;

    int getMin(QString& name)const;

    int getMediana(QString name)const;

    float getAvg(QString name)const;

    void reportPrint(int param, QString name = nullptr);

public slots:
    void analyseData(const SensorMetric& aSensorMetric);

signals:
    void sendToIO(const QString& formatedTextData);
};

#endif // ANALYSER_H