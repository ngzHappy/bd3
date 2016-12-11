#include <cassert>
#include "BasicTreeView.hpp"
#include <QtWidgets/qheaderview.h>

//###################################
/*
 * those headers must be include after there ：
*/
//###################################
#include <private/qtreeview_p.h>


BasicTreeView::BasicTreeView(QWidget *parent)
    : _Super(parent){
}

BasicTreeView::~BasicTreeView(){

}

QVector<QModelIndex> BasicTreeView::getAllVisibleItems(){
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





