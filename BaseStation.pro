#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T21:06:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaseStation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    updatedisplay.cpp \
    receiver.cpp \
    flighttime.cpp

HEADERS  += mainwindow.h \
    updatedisplay.h \
    receiver.h \
    flighttime.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    quad_textboxLogo.png

RESOURCES += \
    resedit.qrc

CONFIG += debug
