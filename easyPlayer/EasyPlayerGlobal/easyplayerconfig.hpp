#ifndef __EASYPLAYER_GLOBAL__CONFIG__
#define __EASYPLAYER_GLOBAL__CONFIG__

#include <QtGui/qpainter.h>

inline static auto defaultQPainterRenderHints(){
    const static auto ans=QPainter::Antialiasing|
            QPainter::TextAntialiasing|
            QPainter::SmoothPixmapTransform|
            QPainter::HighQualityAntialiasing;
    return ans;
}

#endif
