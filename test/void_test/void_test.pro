
QT += core gui
QT += widgets

TARGET = void_test
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp

FORMS    += MainWindow.ui

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR



