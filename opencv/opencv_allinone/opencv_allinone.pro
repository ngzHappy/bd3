##pro

QT += gui
QT += core
QT += widgets
QT += charts
QT += qml
QT += quick

TARGET = opencv_allinone
CONFIG += console

TEMPLATE = app

SOURCES += $$PWD/main.cpp \
    $$PWD/Application.cpp
SOURCES += $$PWD/CreateMainWindowQml.cpp
SOURCES += $$PWD/MainWindow.cpp

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/Application.hpp
HEADERS += $$PWD/CreateMainWindowQml.hpp

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

DISTFILES += $$PWD/allinone.lua

RESOURCES += $$PWD/qmlSource.qrc

win32:{
RC_ICONS=$$PWD/ico/100008.ico
}

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/../../opencv_basic/opencv_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lopencv3_basic_library

