
TARGET = itemsview_test0
TEMPLATE = app

QT += core
QT += gui
QT += widgets

QT += core_private
QT += gui_private
QT += widgets_private

DEFINES +=

SOURCES += \
    main.cpp \
    TestWidget.cpp \
    TestTreeView.cpp \
    TableView.cpp

HEADERS += \
    TestWidget.hpp \
    TestTreeView.hpp \
    TableView.hpp


include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

