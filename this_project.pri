CONFIG += c++14

!win32-msvc*{
QMAKE_CFLAGS*=-std=c11
}else{
DEFINES *=_CRT_SECURE_NO_DEPRECATE
}

CONFIG(debug,debug|release){
    DEFINES*=_DEBUG
    CONFIG += console
}else{
    DEFINES*=NDEBUG
    DEFINES*=QT_NO_DEBUG
}

win32-msvc*{
    CONFIG(debug,debug|release){
        THIS_PROJECT_DESTDIR=$$PWD/binlib/debug_msvc_bind
    }else{
        THIS_PROJECT_DESTDIR=$$PWD/binlib/release_msvc_bin
    }
}else{
    CONFIG(debug,debug|release){
        THIS_PROJECT_DESTDIR=$$PWD/binlib/debug_common_bind
    }else{
        THIS_PROJECT_DESTDIR=$$PWD/binlib/release_common_bin
    }
}

!win32 {
    LIBS += -ld
    DEFINES *= LUA_USE_LINUX
    QMAKE_LFLAGS += -Wl,-rpath .
}

###########################################
#
#
#
#
###########################################
