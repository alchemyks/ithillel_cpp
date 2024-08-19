Робота з ресурсами, параметрами командного рядка у Qt та  робота з конфігураційним файлом 

Мета: 

    Отримати базове навички роботи з ресурсами в Qt
    Навчитися парсити параметри командного рядка, 
    працювати з конфігураційними файлами(JSON).

Потрібно модифікувати програму з минулого заняття(Заняття 6)"ДЗ 9. Обмін даними між кількома об'єктами",

всі налаштування винести в конфігураційний файл відповідно до умов даного завдання

Модифікувати програму з минулого заняття це не обовязково! але краще використати її.

Вимоги до виконання завдання

    Додаток повинен перевіряти наявність конфігураційного файлу за шляхом, вказаним через параметри командного рядка або використовувати дефолтний шлях config.json.
    Якщо конфігураційний файл відсутній, програма повинна скопіювати його з ресурсів на диск подефолтному шляху
    Програма повинна прочитати конфігураційний файл з диска і вивести налаштування у консоль.
    Програма повинна перевіряти і використовувати значення з перемінних середовища, якщо вони задані.(реализація не обовязкова)
    Програма повинна перевизначати налаштування, якщо вони вказані через параметри командного рядка.
    У випадку помилок (наприклад, невірний формат JSON або проблеми з доступом до файлу) програма повинна вивести відповідні повідомлення у консоль.

Пріоритет налаштувань визначений у такому порядку:

    Параметри командного рядка – найвищий пріоритет.
    Перемінні середовища – середній пріоритет.(реализація не обовязкова)
    Конфігураційний файл – найнижчий пріоритет.

робота з параметрами командного рядка відбувається за допомогою класу - QCommandLineParser

робота з параметрами перемінних середовища(Environment variable) за допомогою класу - QProcessEnvironment

Створіть файл ресурсів resources.qrc і додайте до нього config.json:

      

        


      
<RCC>
    <qresource prefix="/">
        <file>config.json</file>
    </qresource>
</RCC>

    

Приклад використання QProcessEnvironment

      

        


      
QString windowTitle = "my App"
QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
if (env.contains("WINDOW_TITLE")) {
    windowTitle = env.value("WINDOW_TITLE");
}

    

приклад роботи з Json в Qt

      

        


      
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void readJsonFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
	qWarning("Couldn't open save file.");
	return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
    
    if (error.error != QJsonParseError::NoError) {
	qWarning() << "Error parsing JSON:" << error.errorString();
	return;
    }

    QJsonObject obj = doc.object();
    qDebug() << "JSON content:" << obj;
}

    

links:

https://uk.wikipedia.org/wiki/%D0%97%D0%BC%D1%96%D0%BD%D0%BD%D1%96_%D1%81%D0%B5%D1%80%D0%B5%D0%B4%D0%BE%D0%B2%D0%B8%D1%89%D0%B0

https://doc.qt.io/qt-6/qprocessenvironment.html

https://doc.qt.io/qt-6/qjsonobject.html

https://www.weiy.city/2020/08/how-to-write-and-read-json-file-by-qt/