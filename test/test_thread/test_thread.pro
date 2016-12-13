###test_thread.pro

QT += core
QT += gui
QT += widgets
#QT += charts
#QT += script
#QT += network

TARGET = test_thread
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        MainWindow.cpp \
    TestSingleThreadPool.cpp

HEADERS  += MainWindow.hpp \
    TestSingleThreadPool.hpp

FORMS    += MainWindow.ui

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

