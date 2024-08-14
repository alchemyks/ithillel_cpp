#ifndef ANALYZER_H
#define ANALYZER_H

#include "sensormetric.h"
#include <QObject>
#include <QMap>


class Analyzer : public QObject
{
    Q_OBJECT

private:
    QMap<QString, QList<SensorMetric>> dataSensorsMetric;
public:
    explicit Analyzer(QObject *parent = nullptr);

    int getMax(QString name)const;

    int getMin(QString& name)const;

    int getMediana(QString name)const;

    float getAvg(QString name)const;

    void reportPrint(int param, QString name = nullptr);

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

signals:
    void sendToIO(const QString& formatedTextData);
};

#endif // ANALYZER_H
