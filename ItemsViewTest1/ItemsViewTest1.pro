QT += core gui
QT += widgets

QT += gui_private
QT += core_private
QT += widgets_private

TARGET = ItemsViewTest1
TEMPLATE = app

CONFIG += c++14
CONFIG += console

SOURCES += main.cpp\
        BasicTreeView.cpp \
    TreeView.cpp \
    TreeViewItemModel.cpp \
    TreeViewItemData.cpp \
    TreeViewItemDataList.cpp \
    TreeViewItemWidget.cpp \
    BoostTest.cpp

HEADERS  += BasicTreeView.hpp \
    cplusplus_basic.hpp \
    TreeView.hpp \
    TreeViewItemModel.hpp \
    TreeViewItemData.hpp \
    TreeViewItemDataList.hpp \
    TreeViewItemWidget.hpp \
    TreeViewItemDelegate.hpp \
    BoostTest.hpp

INCLUDEPATH += $$PWD/../cplusplus_basic












