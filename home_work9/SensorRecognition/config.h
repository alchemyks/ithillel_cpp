#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT

private:
    QString logFilePath;
    QString defaultLogFileName;

public:
    explicit Config(QObject *parent = nullptr);
    QString getFileName();

signals:
};

#endif // CONFIG_H
