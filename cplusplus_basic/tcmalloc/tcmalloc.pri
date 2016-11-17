CONFIG(debug,debug|release){

}else{

##windows
win32{

###########################################
win32-msvc*{

DEFINES *= HAS_TCMALLOC_CONCEPT
LIBS += -llibtcmalloc_minimal

}
###########################################

}else{
##not windows

}

}##debug|release










