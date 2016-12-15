
QT += core
QT += gui
QT += widgets
QT += script
QT += network

TARGET = baiduimage
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    BaiduUser.cpp \
    _PrivateBaiduUser.cpp \
    _PrivateBaiduStaticData.cpp

HEADERS  += MainWindow.hpp \
    BaiduUser.hpp \
    _PrivateBaiduUser.hpp \
    _PrivateBaiduStaticData.hpp

FORMS    += MainWindow.ui

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library


