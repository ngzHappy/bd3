#include "TreeViewItemWidget.hpp"

TreeViewItemWidget::TreeViewItemWidget(QWidget * p)
    :_Super(p){

}

#include <QtCore>
#include <QtGui/QPainter>
void TreeViewItemWidget::paintEvent(QPaintEvent *event){
    //_Super::paintEvent(event);
    QPainter painter(this);
    painter.setPen( Qt::NoPen );
    painter.setBrush( QColor(222,111,33) );
    painter.drawRect(this->rect());
    return;
    (void)event;
}

TreeViewItemWidget::~TreeViewItemWidget(){
    qDebug()<< $m$ModelIndexWhenOpened;
}

