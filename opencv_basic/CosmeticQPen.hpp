#ifndef COSMETICQPEN_HPP
#define COSMETICQPEN_HPP

#include <QtGui/qpen.h>
#include <cplusplus_basic.hpp>

class CosmeticQPen :public QPen {
    void _p_construct_() {
        this->setCosmetic(true)/*线宽不受缩放影响*/;
    }
    using P=QPen;
public:
    CosmeticQPen():P() { _p_construct_(); }
    CosmeticQPen(Qt::PenStyle style):P(style) { _p_construct_(); }
    CosmeticQPen(const QColor &color):P(color) { _p_construct_(); }
    CosmeticQPen(const QBrush &brush,
         qreal width,
         Qt::PenStyle style=Qt::SolidLine,
         Qt::PenCapStyle cap=Qt::SquareCap,
         Qt::PenJoinStyle join=Qt::BevelJoin):
        P(brush,width,style,cap,join) {
        _p_construct_();
    }
    CosmeticQPen(const QPen &arg):P(arg) { _p_construct_(); }
    CosmeticQPen(QPen &&arg):P(std::move(arg)) { _p_construct_(); }
    CosmeticQPen(const CosmeticQPen&)=default;
    CosmeticQPen(CosmeticQPen&&)=default;
    CosmeticQPen&operator=(const CosmeticQPen&)=default;
    CosmeticQPen&operator=(CosmeticQPen&&)=default;
private:
    CPLUSPLUS_OBJECT(CosmeticQPen)
};

#endif // COSMETICQPEN_HPP
