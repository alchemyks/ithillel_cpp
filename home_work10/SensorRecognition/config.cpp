#include "config.h"

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QLatin1String>
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>



Config::Config(QObject *parent): QObject{parent}
{}

Config::Config(QCoreApplication *a){

    QCommandLineParser parser;
    QCommandLineOption name_param(QStringList()<<"n"<<"name","Name","sensor-name");
    QCommandLineOption min_param("min", QCoreApplication::translate("main", "Min value"));
    QCommandLineOption max_param("max", QCoreApplication::translate("max","Max value"));
    QCommandLineOption avg_param("avg", QCoreApplication::translate("avg", "Average value"));
    QCommandLineOption med_param("med", QCoreApplication::translate("med", "Median value"));
    QCommandLineOption path_config_file(QStringList() << "c" << "config",
                                        "Path to the configuration file.",
                                        "config",
                                        "config_user.json");
    QCommandLineOption records_count(QStringList() << "r" << "max_records_n",
                                        "max_records_n",
                                        "max_records_n",
                                        "max_records_n");
    QCommandLineOption time_simulation(QStringList() << "t" << "time_simulations",
                                        "time_simulations",
                                        "time_simulations",
                                        "time_simulations");

    parser.addOption(name_param);
    parser.addOption(min_param);
    parser.addOption(max_param);
    parser.addOption(avg_param);
    parser.addOption(med_param);
    parser.addOption(path_config_file);
    parser.addOption(records_count);
    parser.addOption(time_simulation);

    parser.process(*a);

    if(parser.isSet(path_config_file) && QFile::exists(parser.value(path_config_file))){
            settings.pathToConfigFile = new QString(parser.value(path_config_file));
            qDebug() << "Use user config file" << *settings.pathToConfigFile;

    }else{
        qDebug() << "Used default config file path!";
        if(!QFile::exists(*settings.pathToConfigFile)){
            qDebug() << "File " << *settings.pathToConfigFile << "isn't exist.";
            QDir testPath(settings.pathToConfigFile->section('/', 1, -2));
            if(!testPath.exists()){
                testPath.mkpath(".");
            }
            QFile::copy(":/configs/config.json", *settings.pathToConfigFile);
            qDebug() << "Created default cofig " << *settings.pathToConfigFile;
        }
    }

    if(readConfigFile(*settings.pathToConfigFile)){
        qDebug().noquote() << toString();
    }

    if(parser.isSet(records_count)){
        bool parseIntOk = false;
        int recors_count_temp = parser.value(records_count).toInt(&parseIntOk);
        if(parseIntOk){
            settings.maxRecords = recors_count_temp;
        }
    }

    if(parser.isSet(time_simulation)){
        bool parseIntOk = false;
        int time_simulation_temp = parser.value(time_simulation).toInt(&parseIntOk);
        if(parseIntOk){
            settings.timeSimulation = time_simulation_temp;
        }
    }

    /*param signature
    b'0001' min  id dec 1
    b'0010' max  /----/ 2
    b'0100' avg  /----/ 4
    b'1000' med  /----/ 8
    b'1111' all  /----/ 15
    */
    paramAnalyse = 0;
    if(parser.isSet(min_param)){
        paramAnalyse = paramAnalyse | 0x0001;
    }
    if(parser.isSet(max_param)){
        paramAnalyse = paramAnalyse | 0x0002;
    }
    if(parser.isSet(avg_param)){
        paramAnalyse = paramAnalyse | 0x0004;
    }
    if(parser.isSet(med_param)){
        paramAnalyse = paramAnalyse | 0x0008;
    }

    if(paramAnalyse == 0 and parser.isSet(name_param)){
        paramAnalyse = 15;
    }

    if(parser.isSet(name_param)){
        nameSensorAnalyse = parser.value(name_param);
    }
}



    bool Config::readConfigFile(QString path){
        {
            if(!QFile::exists(path)){
                qWarning() << QString("File %1 not exist\n").arg(path);
                return false;
            }
            QFile file(path);
            if( file.open( QIODevice::ReadOnly ) )
            {
                QByteArray jsonData = file.readAll();
                QJsonParseError error;
                QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

                if (error.error != QJsonParseError::NoError) {
                    qWarning() << QString("Error parsing JSON: %1\n").arg(error.errorString());
                    return false;
                }

                QJsonObject json_obj = doc.object();

                if (json_obj.contains("max_records_n")) {
                    settings.maxRecords = json_obj["max_records_n"].toInt();
                }

                if (json_obj.contains("time_simulations")) {
                    settings.timeSimulation = json_obj["time_simulations"].toInt();
                }

                if (json_obj.contains("path_to_logfile")){
                    settings.pathToLogFile = new QString(json_obj["path_to_logfile"].toString());
                }

                if (json_obj.contains("log_file_name")){
                    settings.logFileName = new QString(json_obj["log_file_name"].toString());
                }
                file.close();
            }
        }
        return true;
    }


    QString Config::toString(){
        return QString("MaxRecord: %1\n"
                       "TimeSimulation: %2\n"
                       "PathToLogFile: %3\n"
                       "LogFileName: %4\n"
                       "PathToConfigFile: %5\n")
            .arg(QString::number(settings.maxRecords), QString::number(settings.timeSimulation), *settings.pathToLogFile,
                 *settings.logFileName, *settings.pathToConfigFile);

    }

    int Config::getParamAnalyse() const
    {
        return paramAnalyse;
    }

    QString Config::getNameSensorAnalyse() const
    {
        return nameSensorAnalyse;
    }

    QString Config::getLogFileName(){
        QString logFileName(*settings.logFileName);
        QStringList logFileSplit = logFileName.split(".");
        if(QFile::exists(*settings.logFileName)){
            int fileCount = 1;
            while(QFile::exists(logFileName + logFileName)){
                logFileName = logFileSplit[0] + QString::number(fileCount) + "." + logFileSplit[1];
                fileCount++;
            }
            QFile::rename(*settings.logFileName, logFileName);
        }
        return *settings.logFileName;
    }



