
QT += core gui
QT += widgets

TARGET = quick_test
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TestMemory.cpp \
    TestException.cpp \
    TestLua.cpp

HEADERS  += MainWindow.hpp \
    TestMemory.hpp \
    TestException.hpp \
    TestLua.hpp

FORMS    += MainWindow.ui

include($$PWD/../../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library
