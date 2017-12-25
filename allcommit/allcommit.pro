#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T14:34:28
#
#-------------------------------------------------

QT       += core gui
QT         +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = allcommit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    setserial.cpp \
    icread.cpp

HEADERS  += mainwindow.h \
    about.h \
    setserial.h \
    icread.h

FORMS    += mainwindow.ui \
    about.ui \
    setserial.ui \
    icread.ui
