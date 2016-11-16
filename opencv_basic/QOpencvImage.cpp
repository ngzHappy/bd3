#include "QOpencvImage.hpp"
#include <private/qimage_p.h>

/************************************************************************/
/*构造函数*/
QOpencvImage::~QOpencvImage(){
}
QOpencvImage::QOpencvImage(){
}
QOpencvImage::QOpencvImage(const QOpencvImage&arg):_Super(arg){
}
QOpencvImage::QOpencvImage(QOpencvImage&&arg):
    _Super(std::move(std::move(arg)._p_getImage())){
}
QOpencvImage::QOpencvImage(const QImage&arg):_Super(arg){
}
QOpencvImage::QOpencvImage(QImage&&arg):_Super(std::move(arg)){
}

/************************************************************************/











