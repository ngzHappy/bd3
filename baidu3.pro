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

tool_test_maker.file=$$PWD/tool/test_maker/test_maker.pro
tool_test_maker.depends+=library_cplusplus_basic
tool_test_maker.depends+=qt_basic_library

SUBDIRS += \
    test/void_test \
    tool/memory_maker \
    library_cplusplus_basic \
    app_quick_test \
    lua_test \
    qt_basic_library \
    app_baiduimage \
    tool_test_maker

test_qt_charts.file=$$PWD/test/test_qt_charts/test_qt_charts.pro
test_qt_charts.depends+=library_cplusplus_basic
test_qt_charts.depends+=qt_basic_library
SUBDIRS += test_qt_charts

tool_set_get.file=$$PWD/tool/tool_set_get/tool_set_get.pro
tool_set_get.depends+=library_cplusplus_basic
tool_set_get.depends+=qt_basic_library
SUBDIRS += tool_set_get
