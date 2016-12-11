#include "TableView.hpp"
#include <cmath>
#include <memory>
#include <cassert>
#include <algorithm>
#include <QtWidgets/qheaderview.h>
//############################
#include <private/qtableview_p.h>

#include <QtCore>
#include <QtCore/QAbstractTableModel>

class TableModel :public QAbstractTableModel {
public:

    using QAbstractTableModel::QAbstractTableModel;

    virtual int columnCount(const QModelIndex &) const override {
        return 100;
    }

    virtual int rowCount(const QModelIndex &) const {
        return 100;
    }

    virtual QVariant data(const QModelIndex &index,int role) const override {

        if (index.isValid()==false) {
            return{};
        }else if (role==Qt::DisplayRole) {
            return 10.0*index.row()+index.column();
        }

        return{};
    }

};

TableView::TableView(){
    std::unique_ptr<QObject> varOldModel{ this->model() };
    this->setModel( new TableModel(this) );
}

void TableView::paintEvent(QPaintEvent *e) {
    _Super::paintEvent(e);
    const auto indexs=_p_getAllVisibleItems();
    QVector<double> datas;
    for(const auto & varI:indexs){
        datas.push_back(varI.data().toDouble());
    }
    qDebug()<<datas;
}

QVector<QModelIndex> TableView::_p_getAllVisibleItems(){

    auto varModel = this->model();
    if( nullptr == varModel ){ return {}; }

    auto hH = horizontalHeader();
    auto vH = verticalHeader();

    auto firstVisualRow = std::max(vH->visualIndexAt(0),0);
    auto lastVisualRow = vH->visualIndexAt(vH->viewport()->height());

    QTableViewPrivate * varPrivate = d_func();
    const bool rightToLeft = this->isRightToLeft();

    if (lastVisualRow == -1){
        lastVisualRow = varPrivate->model->rowCount(varPrivate->root) - 1;
    }

    auto firstVisualColumn = hH->visualIndexAt(0);
    auto lastVisualColumn = hH->visualIndexAt(hH->viewport()->width());
    if ( rightToLeft ){
        std::swap(firstVisualColumn, lastVisualColumn);
    }
    if (firstVisualColumn == -1){ firstVisualColumn = 0; }
    if (lastVisualColumn == -1){ lastVisualColumn = hH->count() - 1;}

    if( lastVisualRow < firstVisualRow  ){ std::swap(lastVisualRow,firstVisualRow); }
    if( lastVisualColumn < firstVisualColumn ){ std::swap(lastVisualColumn,firstVisualColumn); }

    QVector<QModelIndex> varAns;
    varAns.reserve( (lastVisualRow-firstVisualRow+1)*
                    (lastVisualColumn-firstVisualColumn+1) );

    {
        QModelIndex varParent;
        for(auto varRow = firstVisualRow;varRow<=lastVisualRow;++varRow ){
            for(auto varCol=firstVisualColumn;varCol<=lastVisualColumn;++varCol){
                varAns.push_back(varModel->index(varRow,varCol,varParent));
            }
        }
    }

    //std::sort(varAns.begin(),varAns.end());
    assert( std::is_sorted(varAns.begin(),varAns.end())
            &&"???");
    assert( (std::unique(varAns.begin(),varAns.end())==varAns.end())
            &&"is there a qt bug???" );
    return std::move(varAns);

}














