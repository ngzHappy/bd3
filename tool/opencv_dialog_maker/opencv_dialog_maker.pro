
QT       += core gui
QT += widgets

TARGET = opencv_dialog_maker
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp


include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library



