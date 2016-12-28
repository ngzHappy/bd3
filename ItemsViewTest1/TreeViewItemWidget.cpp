#include "TreeViewItemWidget.hpp"

TreeViewItemWidget::TreeViewItemWidget(QWidget * p)
    :_Super(p) {
    startTimer(50);
}

#include <QtCore>
#include <QtGui/QPainter>
void TreeViewItemWidget::paintEvent(QPaintEvent *event) {
   
    _Super::paintEvent(event);

    const bool isSelected= $m$QStyleOptionViewItem.state & QStyle::State_Selected ;

    QPainter painter(this);

    if (isSelected) {
        painter.setPen(QPen(QColor(0,0,0),2));
        painter.setBrush(QColor(255,255,255));
        painter.drawRect(this->rect());
    }
    else {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(),QColor(rand()&255,rand()&255,133));
    }

    painter.setBrush(QColor(122,255,33));
    painter.setPen(QPen(QColor(0,0,0),2));
    painter.drawText(10,10,
        QString::number( reinterpret_cast<std::uintptr_t>( this )) );

    return;
    (void)event;
}

void TreeViewItemWidget::aboutToClosed() {
    this->hide();
}

void TreeViewItemWidget::update(
    const QStyleOptionViewItem & option,const QModelIndex &) {
    if (isOptionChanged(option)) {
        _Super::update();
    }
}

bool TreeViewItemWidget::isOptionChanged(const QStyleOptionViewItem & option) {

    if (option.rect==$m$QStyleOptionViewItem.rect) {
        if (option.state==$m$QStyleOptionViewItem.state) {
            return false;
        }
    }

    $m$QStyleOptionViewItem=option;

    return true;
}

void TreeViewItemWidget::setData(const QModelIndex &) {
    _Super::update();
}

TreeViewItemWidget::~TreeViewItemWidget() {
    //qDebug()<<$m$ModelIndexWhenOpened;
}

void TreeViewItemWidget::timerEvent(QTimerEvent *event) {
    _Super::timerEvent(event);
}

