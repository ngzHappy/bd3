QT -= core gui

include($$PWD/cplusplus_basic.pri)

TARGET = cplusplus_basic_library
TEMPLATE = lib

include($$PWD/_private_cplusplus_basic_headers.pri)
include($$PWD/_private_cplusplus_basic_files.pri)
DEFINES*=CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR












