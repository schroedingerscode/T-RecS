#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T23:58:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Camera_Stream
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tracking/Encoder.cpp \
    tracking/Serial.cpp \
    tracking/Tracker.cpp

HEADERS  += mainwindow.h \
    tracking/Headers/Common.h \
    tracking/Headers/Encoder.h \
    tracking/Headers/Serial.h \
    tracking/Headers/Tracker.h \
    tracking/not_main.h

FORMS    += \
    mainwindow.ui

LIBS += `pkg-config opencv --libs`
