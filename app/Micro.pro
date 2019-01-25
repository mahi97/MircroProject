#-------------------------------------------------
#
# Project created by QtCreator 2019-01-13T21:46:43
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MICRO
TEMPLATE = app


SOURCES += src/main.cpp\
              src/mainwindow.cpp \
    src/controltab.cpp \
    src/infotab.cpp \
    src/configtab.cpp \
    src/serialwriter.cpp \
    src/serialreader.cpp \
    src/baseserial.cpp \
    src/replwidget.cpp

INCLUDEPATH +=include/

HEADERS  += include/mainwindow.h \
    include/controltab.h \
    include/infotab.h \
    include/configtab.h \
    include/serialwriter.h \
    include/serialreader.h \
    include/baseserial.h \
    include/replwidget.h

OBJECTS_DIR += objs/
MOC_DIR += objs/
