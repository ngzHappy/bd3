QT -= core
QT -= gui

TARGET = memory_maker
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DEFINES+=THIS_PROJECT_DIR=\\\"$$PWD\\\"

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

