###opencv_resize.pro

QT += core
QT += gui
QT += widgets
#QT += script
#QT += network

TARGET = opencv_resize
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    Application.cpp \
    ResizeDialog.cpp

HEADERS  += MainWindow.hpp \
    Application.hpp \
    ResizeDialog.hpp

FORMS    +=

RESOURCES +=

DISTFILES += \
    $$PWD/opencv_resize.lua \
    $$PWD/dialog_opencv_resize.lua

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/../../opencv_basic/opencv_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lopencv3_basic_library

