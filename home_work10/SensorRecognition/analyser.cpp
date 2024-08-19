#include "analyser.h"
#include <algorithm>

Analyser::Analyser(QObject *parent)
    : QObject{parent}
{}

void Analyser::analyseData(const SensorMetric& aSensorMetric){
    Analyser::dataSensorsMetric[aSensorMetric.name].append(aSensorMetric);
}

int Analyser::getMax(QString name)const{
    int maxSensorValue = 0;
    if(!name.isNull() && dataSensorsMetric.contains(name)){
        QList temp_list(dataSensorsMetric[name]);
        QList<SensorMetric>::Iterator maxSensorData = std::max_element(temp_list.begin(),
                                         temp_list.end(), [](SensorMetric a, SensorMetric b){
                                        return a.value < b.value;
                                    });
        maxSensorValue = maxSensorData->value;

    }
    return maxSensorValue;
}


int Analyser::getMin(QString& name)const{
    int res = 0;
    if(!name.isNull() && dataSensorsMetric.contains(name)){
        QList<SensorMetric> metric = dataSensorsMetric[name];
        QList<SensorMetric>::Iterator maxSensorData = std::min_element(metric.begin(),
                                          metric.end(), [](SensorMetric a, SensorMetric b){
                                              return a.value < b.value;
                                          });
        res = maxSensorData->value;
    }
    return res;
}

int Analyser::getMediana(QString name)const{
    int mediana = 0;
    if(!name.isNull() && dataSensorsMetric.contains(name)){
        QList temp_list(dataSensorsMetric[name]);
        std::sort(temp_list.begin(), temp_list.end(),[](SensorMetric a, SensorMetric b){
            return a.value < b.value;
        });
        mediana = temp_list.length() % 2 == 0 ?
                      (temp_list[temp_list.length() / 2].value + temp_list[temp_list.length() / 2 + 1].value) / 2
                    :
                      temp_list[temp_list.length() / 2].value;
    }
    return mediana;
}

float Analyser::getAvg(QString name) const
{
    float avg = 0;
    if(!name.isNull() && dataSensorsMetric.contains(name)){
        QList temp_list(dataSensorsMetric[name]);
        avg =  std::accumulate(temp_list.begin(), temp_list.end(), 0, [](int a, SensorMetric b){
            return a + b.value;
        }) / temp_list.length();
    }
    return avg;
}

void Analyser::reportPrint(int param, QString name)
{
    if(param == 0){
        return;
    }
    QString report = "";
    QList<QString> sensorsName;
    if(name.isEmpty()){
        sensorsName = dataSensorsMetric.keys();
    }else{
        if(dataSensorsMetric.contains(name)){
            sensorsName.append(name);
        }else{
            return;
        }

    }
    for(QString &sensor: sensorsName){
        report = QString("Sensor name:%1 \n").arg(sensor);
        if (param & 0x0001){
            report = report + QString("     min: %1 \n").arg(QString::number(getMin(sensor)));
        }
        if (param & 0x0002){
            report = report + QString("     max: %1 \n").arg(QString::number(getMax(sensor)));
        }
        if (param & 0x0004){
            report = report + QString("     avg: %1 \n").arg(QString::number(getAvg(sensor)));
        }
        if (param & 0x0008){
            report = report + QString("     med: %1 \n").arg(QString::number(getMediana(sensor)));
        }
        emit sendToIO(report);
    }
}
