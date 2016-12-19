
QT += gui
QT += qml
QT += core
QT += network
QT += widgets

TARGET = baiduimage
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    BaiduUser.cpp \
    _PrivateBaiduUser.cpp \
    _PrivateBaiduStaticData.cpp \
    LoginTest.cpp \
    ImageTest.cpp

HEADERS  += MainWindow.hpp \
    BaiduUser.hpp \
    _PrivateBaiduUser.hpp \
    _PrivateBaiduStaticData.hpp \
    LoginTest.hpp \
    BaiduImage.hpp \
    ImageTest.hpp

FORMS    += MainWindow.ui \
    LoginTest.ui \
    ImageTest.ui

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

CONFIG += precompile_header
win32-msvc*{
PRECOMPILED_HEADER  += $$PWD/private/_msvc_core_utility_prebuild.hpp
}else{
PRECOMPILED_HEADER  += $$PWD/private/_core_utility_prebuild.hpp
}

