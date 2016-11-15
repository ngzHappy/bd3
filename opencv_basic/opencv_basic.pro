TARGET = opencv3_basic_library
TEMPLATE = lib

QT += core
QT += gui
QT += concurrent
QT += widgets

DEFINES += OPENCV3_BASIC_LIBRARY

SOURCES += \
    OpenCVBasic.cpp \
    ToolOpencvException.cpp \
    ToolOpencvMemory.cpp

HEADERS += \
    OpenCVBasic.hpp \
    ToolOpencvException.hpp \
    ToolOpencvMemory.hpp

include($$PWD/opencv_basic.pri)

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library
