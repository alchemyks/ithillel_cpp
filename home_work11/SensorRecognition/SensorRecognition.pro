QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += concurrent
CONFIG += c++17 cmdline
#CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        analyser.cpp \
        config.cpp \
        logger.cpp \
        main.cpp \
        sensor.cpp \
        sensorgui.cpp \
        simulator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    analyser.h \
    config.h \
    logger.h \
    sensor.h \
    sensorgui.h \
    sensormetric.h \
    settings.h \
    simulator.h

RESOURCES += \
    resources.qrc

FORMS +=
