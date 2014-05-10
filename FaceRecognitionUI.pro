#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T00:12:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceRecognitionUI
TEMPLATE = app


SOURCES += main.cpp\
        mainscreen.cpp

HEADERS  += mainscreen.h

FORMS    += mainscreen.ui

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv