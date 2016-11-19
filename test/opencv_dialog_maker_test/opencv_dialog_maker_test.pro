
QT += core gui
QT += widgets

TARGET = opencv_dialog_maker_test
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    XDialog.cpp

HEADERS  += MainWindow.hpp \
    XDialog.hpp

FORMS    += MainWindow.ui

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

