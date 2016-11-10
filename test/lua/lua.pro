TARGET = lua
TEMPLATE = app

QT -= core
QT -= gui

CONFIG += console

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

SOURCES += \
    $$PWD/../../cplusplus_basic/lua/src/lua.cpp
