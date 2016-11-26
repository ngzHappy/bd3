###opencv_lab.pro

QT += core
QT += gui
QT += widgets
#QT += script
#QT += network

TARGET = opencv_lab
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    Application.cpp \
    LABDialog.cpp

HEADERS  += MainWindow.hpp \
    Application.hpp \
    LABDialog.hpp

FORMS    +=

RESOURCES +=

DISTFILES += \
    $$PWD/opencv_lab.lua \
    $$PWD/dialog_opencv_lab.lua

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/../../opencv_basic/opencv_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lopencv3_basic_library

