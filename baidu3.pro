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

SUBDIRS += \
    test/void_test \
    tool/memory_maker \
    library_cplusplus_basic












