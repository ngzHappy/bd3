#include "TestTreeView.hpp"

#include <memory>
#include <QtCore>
#include <private/qtreeview_p.h>
#include <QtWidgets/qheaderview.h>

#include <vector>

namespace {

class TreeModel :public QAbstractItemModel {
    constexpr static int deepth(void *arg){return (char *)arg-(char *)deepth_0()-1;}
    constexpr static void * deepth_1(int arg){return 1+arg+(char *)(deepth_0());}
    constexpr static void * deepth_0(){ return (char *)1; }
public:
    TreeModel(QObject *s):QAbstractItemModel(s){}

    virtual int columnCount(const QModelIndex & ) const override {
        return 1;
    }

    virtual QVariant data(const QModelIndex &index, int role ) const override {

        if(index.isValid()==false){
            return {};
        }

        if(role == Qt::DisplayRole){
           if( index.internalPointer() == deepth_0() ){
               return 10.0*index.row();
             }else{
               return index.row()+deepth(index.internalPointer())*10+0.5;
           }
        }

        return{};
    }


    virtual QModelIndex index(
            int row,
            int column,
            const QModelIndex &parent ) const override{
        if( parent.internalPointer() == deepth_0() ){
            return this->createIndex( row, column, deepth_1(parent.row()) );
        }else if( parent.internalPointer() == nullptr ){
            return this->createIndex( row, column, deepth_0() );
        }
        return {};
    }


    virtual QModelIndex  parent(const QModelIndex &index) const override{
        if( index.internalPointer() == deepth_0() ){return{};}
        else if( index.internalPointer() == nullptr ){ return {}; }
        return this->createIndex(
                   deepth( index.internalPointer() ),
                    0,
                    deepth_0());
    }


    virtual int rowCount(const QModelIndex &parent ) const {
        if( parent.internalPointer() == nullptr ){
            return 5;
        }else if( parent.internalPointer() == deepth_0() ){
            return 5;
        }
        return 0;
    }

};

}

TestTreeView::TestTreeView(){
    std::unique_ptr<QObject> varOldModel{ model() };
    auto varModel = new TreeModel(this);
    this->setModel(varModel);
}

QVector<QModelIndex> TestTreeView::_p_getAllVisibleItems(){

    QTreeViewPrivate *varPrivate = d_func();
    const QVector<QTreeViewItem> viewItems = varPrivate->viewItems;

    if (viewItems.count() == 0  /*rows==0*/
            || varPrivate->header->count() == 0 /*cols==0*/
            || !varPrivate->itemDelegate/*draw function is null*/) {
        return {};
    }

    int firstVisibleItemOffset = 0;
    const auto firstVisibleItem = varPrivate->firstVisibleItem(&firstVisibleItemOffset);
    const auto lastVisibleItem = varPrivate->lastVisibleItem(firstVisibleItem,firstVisibleItemOffset);

    QVector<QModelIndex> varAns;

    for(firstVisibleItemOffset=firstVisibleItem;
        firstVisibleItemOffset<=lastVisibleItem;
        ++firstVisibleItemOffset){
        varAns.push_back( viewItems[firstVisibleItemOffset].index );
    }

    return std::move(varAns);
}

void TestTreeView::paintEvent(QPaintEvent *event){
    _Super::paintEvent(event);

    const auto itmes = _p_getAllVisibleItems();
    QVector<double> values;
    for(const QModelIndex & i :itmes){
        values.push_back(i.data().toDouble());
    }
    qDebug()<<values;

}


