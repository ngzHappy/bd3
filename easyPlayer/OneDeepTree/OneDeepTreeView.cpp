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

OneDeepTreeView::OneDeepTreeView(QWidget * p ):Super(p){
    $m$thisp=new _PrivateOneDeepTreeView;
}

OneDeepTreeView::~OneDeepTreeView(){
    delete $m$thisp;
}

/*
 * 本函数摘自Qt 5.8源代码，如果Qt源代码变动请改变此函数
 * 此函数返回所有可见项的index（QModelIndex）
 * 请保证返回是有序的并且没有重复（其实就是返回一个set）
*/
QVector<QModelIndex> OneDeepTreeView::getAllVisibleItems(){
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
    if(lastVisibleItem<firstVisibleItem){ /*is threre a qt bug???*/ return{};}

    QVector<QModelIndex> varAns;
    varAns.reserve( lastVisibleItem-firstVisibleItem+1 );

    for (firstVisibleItemOffset=firstVisibleItem;
         firstVisibleItemOffset<=lastVisibleItem;
        ++firstVisibleItemOffset) {
        varAns.push_back(viewItems[firstVisibleItemOffset].index);
    }

    std::sort( varAns.begin(),varAns.end() );
    assert( (std::unique(varAns.begin(),varAns.end())==varAns.end())
            &&"is there a qt bug???" );

    return std::move(varAns);
}

void OneDeepTreeView::paintEvent(QPaintEvent *argEvent){
    Super::paintEvent(argEvent);
    _p_start_gcevent();
}

/*进行滤波，消除过于频繁的gc调用*/
void OneDeepTreeView::_p_start_gcevent(){
    ++($m$thisp->$m$gc_tag);
    QTimer::singleShot(10,this,[this,arg_tag=$m$thisp->$m$gc_tag](){
        if(arg_tag!=$m$thisp->$m$gc_tag){return;}
        this->gcEvent();
    });
}

/*删除看不到的元素*/
void OneDeepTreeView::gcEvent(){

}

/*********************************************************************************/

OneDeepTreeDelegate::OneDeepTreeDelegate(OneDeepTreeView * p): Super(p) {
    $m$thisp = new _PrivateOneDeepTreeDelegate;
}

OneDeepTreeDelegate::~OneDeepTreeDelegate(){
    delete $m$thisp;
}

/*********************************************************************************/

OneDeepTreeItemWidget::OneDeepTreeItemWidget(QWidget * p):Super(p){

}

/*********************************************************************************/

_PrivateOneDeepTreeView::~_PrivateOneDeepTreeView(){

}

/*********************************************************************************/

_PrivateOneDeepTreeDelegate::~_PrivateOneDeepTreeDelegate(){

}

/*********************************************************************************/
