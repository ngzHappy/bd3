win32{

###########################################
win32-msvc*{

DEFINES *= HAS_TCMALLOC_CONCEPT

CONFIG(debug,debug|release){
LIBS += -llibtcmalloc_minimal-debug
}else{
LIBS += -llibtcmalloc_minimal
}

}
###########################################

}else{

}

SOURCES += \
    $$PWD/tcmalloc_fore_load.cpp











