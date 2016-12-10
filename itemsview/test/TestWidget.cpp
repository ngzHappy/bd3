//#define QT_BUILD_INTERNAL
//#define QT_SHARED

#include <memory>
#include <QtCore>
#include "TestWidget.hpp"
#include <QStringListModel>
#include <private/qlistview_p.h>

TestWidget::TestWidget() {
    std::unique_ptr<QObject> varOldModel{ model() };
    auto varModel=new QStringListModel(this);
    varModel->setStringList({ QString("a"),
                             QString("b"),
                             QString("c"),
                             QString("d"),
                             QString("e"),
                             QString("f"),
                             QString("g"),
                             QString("h"),
                             QString("i"),
                             QString("j"),
                             QString("k"),
                             QString("l"),
                             QString("m"),
                             QString("n"),
                             QString("o") });
    this->setModel(varModel);
}

QVector<QModelIndex> TestWidget::_p_getAllVisibleItems() {
    QListViewPrivate* varPrivate=d_func();
    QRect area=this->rect()
        .translated(horizontalOffset(),verticalOffset());
    QRect a=(this->isRightToLeft()?
                   varPrivate->flipX(area.normalized()):
                   area.normalized());
    return varPrivate->commonListView->intersectingSet(a);
}

void TestWidget::paintEvent(QPaintEvent *e) {
    _Super::paintEvent(e);
    auto v=_p_getAllVisibleItems();
    QVector<QString> vtmp;
    for (const QModelIndex & i:qAsConst(v)) {
        vtmp.push_back(i.data().toString());
    }
    qDebug()<<vtmp;
}







