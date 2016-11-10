#.subdir
#Use the specified subdirectory instead of SUBDIRS value.
#.file
#Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends
#This subproject depends on specified subproject.
#.makefile
#The makefile of subproject. Available only on platforms that use makefiles.
#.target
#Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.


TEMPLATE = subdirs

library_cplusplus_basic.file=$$PWD/cplusplus_basic/cplusplus_basic.pro

lua_test.file=$$PWD/test/lua/lua.pro
lua_test.depends+=library_cplusplus_basic

qt_basic_library.file=$$PWD/qt_basic/qt_basic.pro
qt_basic_library.depends+=library_cplusplus_basic

app_quick_test.file=$$PWD/test/quick_test/quick_test/quick_test.pro
app_quick_test.depends+=library_cplusplus_basic
app_quick_test.depends+=qt_basic_library

app_baiduimage.file=$$PWD/baiduimage/baiduimage.pro
app_baiduimage.depends+=library_cplusplus_basic
app_baiduimage.depends+=qt_basic_library

SUBDIRS += \
    test/void_test \
    tool/memory_maker \
    library_cplusplus_basic \
    app_quick_test \
    lua_test \
    qt_basic_library \
    app_baiduimage












