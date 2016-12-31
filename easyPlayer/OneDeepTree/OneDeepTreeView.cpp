#define $m$ONEDEEPTREEVIEW_PROTECTED public
#define $m$ONEDEEPTREEDELEGATE_PROTECTED public
#define $m$ONEDEEPTREEITEMWIDGET_PROTECTED public

#include <QtCore/qtimer.h>
#include "OneDeepTreeView.hpp"
#include <QtWidgets/qheaderview.h>
#include "OneDeepTreeDelegate.hpp"
#include "OneDeepTreeItemWidget.hpp"

#include "private/_.p._OneDeepTreeView.hpp"
#include "private/_.p._OneDeepTreeDelegate.hpp"

//###################################
/*
 * those headers must be include after there ：
*/
//###################################
#include <private/qtreeview_p.h>

/*********************************************************************************/

OneDeepTreeView::OneDeepTreeView(_PrivateOneDeepTreeView*p,QWidget*s):Super(s) {
    $m$thisp=p;
    $m$thisp->super=this;
}

OneDeepTreeView::OneDeepTreeView(QWidget * p):OneDeepTreeView(new _PrivateOneDeepTreeView,p) {
}

OneDeepTreeView::~OneDeepTreeView() {
    delete $m$thisp;
}

/*
 * 本函数摘自Qt 5.8源代码，如果Qt源代码变动请改变此函数
 * 此函数返回所有可见项的index（QModelIndex）
 * 请保证返回是有序的并且没有重复（其实就是返回一个set）
*/
QVector<QModelIndex> OneDeepTreeView::getAllVisibleItems() {
    QTreeViewPrivate *varPrivate=d_func();
    const QVector<QTreeViewItem> viewItems=varPrivate->viewItems;

    if (viewItems.count()==0/*rows==0*/
            ||varPrivate->header->count()==0/*cols==0*/
            ||!varPrivate->itemDelegate/*draw function is null*/) {
        return{};
    }

    int firstVisibleItemOffset=0;
    const auto firstVisibleItem=varPrivate->firstVisibleItem(&firstVisibleItemOffset);
    if (firstVisibleItem<0) { /*all can not be see*/ return{}; }
    const auto lastVisibleItem=varPrivate->lastVisibleItem(firstVisibleItem,firstVisibleItemOffset);
    if (lastVisibleItem<firstVisibleItem) { /*is threre a qt bug???*/ return{}; }

    QVector<QModelIndex> varAns;
    varAns.reserve(lastVisibleItem-firstVisibleItem+1);

    for (firstVisibleItemOffset=firstVisibleItem;
         firstVisibleItemOffset<=lastVisibleItem;
         ++firstVisibleItemOffset) {
        varAns.push_back(viewItems[firstVisibleItemOffset].index);
    }

    std::sort(varAns.begin(),varAns.end());
    assert((std::unique(varAns.begin(),varAns.end())==varAns.end())
            &&"is there a qt bug???");

    return std::move(varAns);
}

void OneDeepTreeView::paintEvent(QPaintEvent *argEvent) {
    Super::paintEvent(argEvent);
    _p_start_gcevent()/*启动gc，删除不可见元素*/;
}

/*进行滤波，消除过于频繁的gc调用*/
void OneDeepTreeView::_p_start_gcevent() {
    const auto arg_tag=++($m$thisp->$m$gc_tag);
    QTimer::singleShot(10,this,[this,arg_tag]() {
        if (arg_tag!=$m$thisp->$m$gc_tag) { return; }
        this->gcEvent();
    });
}

void OneDeepTreeView::verticalScrollbarValueChanged(int arg) {
    Super::verticalScrollbarValueChanged(arg);
    const auto varCurrentStamp=++($m$thisp->$m$VerticalScrollbarValueChangeStamp);
    QTimer::singleShot(200,this,[this,varCurrentStamp]() {
        /*200ms内没有再次调用此函数*/
        if (varCurrentStamp==$m$thisp->$m$VerticalScrollbarValueChangeStamp) {
            /*强制重绘*/
            for (auto * varI:qAsConst($m$thisp->$m$OpendWidgets)) {
                varI->update();
            }
        }
    });
}

/*删除看不到的元素*/
void OneDeepTreeView::gcEvent() {

    /*获得被管理的元素*/
    auto & varWidgets=$m$thisp->$m$OpendWidgets;
    if (varWidgets.empty()) {
        return;
    }

    /*获得可见元素*/
    const auto varVisibleItems=getAllVisibleItems();

    if (varVisibleItems.empty()) {
        $m$thisp->closeAll();
        return/*所有元素都不可见*/;
    }

    {/*查看可见序列与被管理序列是否相同，如果不同执行gc*/
        const auto varVS=varVisibleItems.size();
        const auto varWS=static_cast<DECLTYPE(varVS)>(varWidgets.size());
        auto varPos=varVisibleItems.constBegin();
        if (varVS==varWS) {
            for (auto * w:varWidgets) {
                if (w->getModelIndex()!=*varPos) { goto do_gc; }
                ++varPos;
            }
            return/*两个序列完全相同，放弃gc*/;
        }
    }

    do_gc:

    using Compare=_PrivateOneDeepTreeView::TreeViewItemWidgetCompare;
    constexpr Compare varCompare;

    _PrivateOneDeepTreeView::vector<OneDeepTreeItemWidget *> varAboutToClosed;
    DECLTYPE(varWidgets) varAllOpenedWidgets;

    for (auto * varI:qAsConst(varWidgets)) {

        if (std::binary_search(
            varVisibleItems.cbegin(),
            varVisibleItems.cend(),
            varI,varCompare)) {
            varAllOpenedWidgets.insert(varI);
        }
        else {
            varAboutToClosed.push_back(varI);
        }

    }

    varWidgets=std::move(varAllOpenedWidgets);

#ifndef NDEBUG
    {
        const auto varVS=varVisibleItems.size();
        const auto varWS=static_cast<DECLTYPE(varVS)>(varWidgets.size());
        /*可见元素数量应当多于被管理元素数量*/
        /*因为调用是异步的，所以它们的数量可能不同*/
        assert(varVS>=varWS);
    }
#endif

    /*关闭不可见元素*/
    for (auto * varI:qAsConst(varAboutToClosed)) {
        varI->aboutToClosed();
        this->closePersistentEditor(varI->getModelIndex());
    }

    return;
}

/*********************************************************************************/

OneDeepTreeDelegate::OneDeepTreeDelegate(OneDeepTreeView * p):
    OneDeepTreeDelegate(new _PrivateOneDeepTreeDelegate,p) {}

OneDeepTreeDelegate::OneDeepTreeDelegate(_PrivateOneDeepTreeDelegate * p,
                                         OneDeepTreeView *s):Super(s) {
    $m$thisp=p;
    $m$thisp->$m$view=s;
}

OneDeepTreeDelegate::~OneDeepTreeDelegate() {
    delete $m$thisp;
}

void OneDeepTreeDelegate::paint(QPainter *a,const QStyleOptionViewItem &b,const QModelIndex &c) const {
    {
        const auto & varWidgets=$m$thisp->$m$view->$m$thisp->$m$OpendWidgets;
        auto varPos=varWidgets.find(c);
        if (varPos==varWidgets.end()) {
            $m$thisp->$m$view->openPersistentEditor(c);
            return;
        }
        else {
            auto * v=*varPos;
            v->update(b,c);
            return;
        }
    }
    return Super::paint(a,b,c);
}

/*用于创建不同类型的工厂*/
OneDeepTreeItemWidget *OneDeepTreeDelegate::doCreateEditor(QWidget *a,const QStyleOptionViewItem &b,const QModelIndex &c) const {
    auto ans=new OneDeepTreeItemWidget(a);
    return ans;
    (void)b; (void)c;
}

QWidget *OneDeepTreeDelegate::createEditor(QWidget *a,const QStyleOptionViewItem &b,const QModelIndex &c) const {
    {
        auto ans=doCreateEditor(a,b,c);
        ans->setModelIndex(c);
        ans->setStyleOption(b);
        auto & varWidgets=$m$thisp->$m$view->$m$thisp->$m$OpendWidgets;
        assert(varWidgets.count(ans)==0);
        varWidgets.insert(ans);
        return ans;
    }
    return Super::createEditor(a,b,c);
    (void)b; (void)c;
}

void OneDeepTreeDelegate::destroyEditor(QWidget *a,const QModelIndex &b) const {
    return Super::destroyEditor(a,b);
}

void OneDeepTreeDelegate::updateEditorGeometry(QWidget *a,const QStyleOptionViewItem &b,const QModelIndex &c) const {
    return Super::updateEditorGeometry(a,b,c);
}

void OneDeepTreeDelegate::setEditorData(QWidget *a,const QModelIndex &b) const {
    {
        auto v=qobject_cast<OneDeepTreeItemWidget*>(a);
        if (v) {
            v->setData(b);
            return;
        }
    }
    return Super::setEditorData(a,b);
}

/*********************************************************************************/

OneDeepTreeItemWidget::OneDeepTreeItemWidget(QWidget * p):Super(p) {

}

void OneDeepTreeItemWidget::update(const QStyleOptionViewItem&a,const QModelIndex&b) {
    if (isOptionChanged(a)) {
        this->update();
    }
    assert($m$ModelIndexWhenOpened==b);
    return;
    (void)b;
}

bool OneDeepTreeItemWidget::isOptionChanged(const QStyleOptionViewItem&a) {
    auto & b=this->$m$QStyleOptionViewItem;
    if (a.rect==b.rect) {
        if (a.state==b.state) {
            return false;
        }
    }
    b=a;
    return true;
}

void OneDeepTreeItemWidget::setData(const QModelIndex &a) {
    assert($m$ModelIndexWhenOpened==a);
    this->update();
    (void)a;
}

void OneDeepTreeItemWidget::paintEvent(QPaintEvent *argEvent) {
    Super::paintEvent(argEvent);
}

/*********************************************************************************/

_PrivateOneDeepTreeView::~_PrivateOneDeepTreeView() {

}

/*********************************************************************************/

_PrivateOneDeepTreeDelegate::~_PrivateOneDeepTreeDelegate() {

}

/*********************************************************************************/
