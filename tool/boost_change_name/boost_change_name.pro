QT += core
QT += concurrent

QT -= gui

TARGET = boost_change_name
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR


