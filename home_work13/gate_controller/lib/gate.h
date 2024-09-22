#ifndef GATE_H
#define GATE_H

#include <QObject>

class Gate : public QObject
{
    Q_OBJECT
public:
    explicit Gate(QObject *parent = nullptr);

    // Конструктор, задає початковий стан воріт (0-100%)
    Gate(int initial_opening);

    // Функція для відкриття воріт на певний відсоток
    void open(int percentage);

    // Функція для закриття воріт на певний відсоток
    void close(int percentage);

    // Перевірка, чи ворота повністю закриті
    bool isClosed() const;

    // Повертає поточний відсоток відкриття
    int getOpening() const;

private:
    // Поточний стан відкриття (0-100%)
    int current_opening;

    bool isSpanValid(int percentage);
signals:
};

#endif // GATE_H
