
QT += core gui
QT += widgets

QT += qml
QT += quick


CONFIG += c++14

TARGET = itemsViewTest2
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ItemsModel.cpp

HEADERS  += MainWindow.hpp \
    ItemsModel.hpp

DISTFILES +=

RESOURCES += \
    source.qrc







