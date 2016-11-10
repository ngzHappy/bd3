
TARGET = qt_basic_library
TEMPLATE = lib

DEFINES += QT_BASIC_LIBRARY

SOURCES += QtBasicLibrary.cpp

HEADERS += QtBasicLibrary.hpp\
        qt_basic_global.hpp


include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library





