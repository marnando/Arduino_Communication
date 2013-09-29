#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T19:01:06
#
#-------------------------------------------------

QT       += core gui\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arduino_Communication
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialcommunicationmanager.cpp \
    serialportconnectioncontrols.cpp \
    arduino.cpp \
    serialtransmissionmonitor.cpp \
    serialportsettingsdialog.cpp

HEADERS  += mainwindow.h \
    communicationmanager.h \
    serialcommunicationmanager.h \
    serialportconnectioncontrols.h \
    arduino.h \
    serialtransmissionmonitor.h \
    serialportsettingsdialog.h

FORMS    += mainwindow.ui \
    serialportconnectioncontrols.ui \
    serialtransmissionmonitor.ui \
    serialportsettingsdialog.ui
