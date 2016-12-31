QT += core gui
QT += widgets
QT += multimedia

QT += gui_private
QT += core_private
QT += widgets_private

TARGET = easyPlayer
TEMPLATE = app

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/OneDeepTree/onedeeptree.pri)
include($$PWD/_.test._OneDeepTree/testOneDeepTree.pri)
