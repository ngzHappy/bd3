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

SUBDIRS += $$PWD/tool/opencv_maker/opencv_maker.pro

library_opencv_basic.file=$$PWD/opencv_basic/opencv_basic.pro

SUBDIRS += library_opencv_basic

opencv3_basic_library_test.file=$$PWD/test/opencv3_basic_library_test/opencv3_basic_library_test.pro
opencv3_basic_library_test.depends+=library_opencv_basic
SUBDIRS += opencv3_basic_library_test












