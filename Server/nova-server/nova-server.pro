#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T13:50:49
#
#-------------------------------------------------

QT       += core gui
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nova-server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mytablemodel.cpp \
    ship.cpp

HEADERS  += mainwindow.h \
    mytablemodel.h \
    ship.h

FORMS    += mainwindow.ui
