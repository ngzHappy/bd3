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

SUBDIRS += $$PWD/tool/opencv_maker/opencv_maker.pro \
    tool/opencv_dialog_maker \
    test/opencv_dialog_maker_test

library_opencv_basic.file=$$PWD/opencv_basic/opencv_basic.pro

SUBDIRS += library_opencv_basic

opencv3_basic_library_test.file=$$PWD/test/opencv3_basic_library_test/opencv3_basic_library_test.pro
opencv3_basic_library_test.depends+=library_opencv_basic
SUBDIRS += opencv3_basic_library_test

opencv_fitEllipse.file=$$PWD/opencv/opencv_point_algorithm/opencv_fitEllipse/opencv_fitEllipse.pro
opencv_fitEllipse.depends+=library_opencv_basic
SUBDIRS += opencv_fitEllipse

opencv_fitLine.file=$$PWD/opencv/opencv_point_algorithm/opencv_fitLine/opencv_fitLine.pro
opencv_fitLine.depends+=library_opencv_basic
SUBDIRS += opencv_fitLine

opencv_minAreaRect.file=$$PWD/opencv/opencv_point_algorithm/opencv_minAreaRect/opencv_minAreaRect.pro
opencv_minAreaRect.depends+=library_opencv_basic
SUBDIRS += opencv_minAreaRect

opencv_simple_contour.file=$$PWD/opencv/opencv_simple_contour/opencv_simple_contour.pro
opencv_simple_contour.depends+=library_opencv_basic
SUBDIRS += opencv_simple_contour

opencv_minEnclosingCircle.file=$$PWD/opencv/opencv_point_algorithm/opencv_minEnclosingCircle/opencv_minEnclosingCircle.pro
opencv_minEnclosingCircle.depends+=library_opencv_basic
SUBDIRS += opencv_minEnclosingCircle

opencv_allinone.file=$$PWD/opencv/opencv_allinone/opencv_allinone.pro
opencv_minEnclosingCircle.depends+=library_opencv_basic
SUBDIRS += opencv_allinone

opencv_minEnclosingTriangle.file=$$PWD/opencv/opencv_point_algorithm/opencv_minEnclosingTriangle/opencv_minEnclosingTriangle.pro
opencv_minEnclosingTriangle.depends+=library_opencv_basic
SUBDIRS += opencv_minEnclosingTriangle

