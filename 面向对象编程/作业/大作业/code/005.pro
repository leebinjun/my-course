#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T21:56:16
#
#-------------------------------------------------

QT       += core gui

QT       +=serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 005
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workthread.cpp \
    keyevent.cpp \
    horse.cpp \
    cdydialog.cpp

HEADERS  += mainwindow.h \
    workthread.h \
    keyevent.h \
    horse.h \
    cdialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    005.qrc

RC_FILE=icon.rc
