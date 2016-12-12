#include "ItemsModel.hpp"
#include <QtCore>
#include <QtGui>

ItemsModel::ItemsModel(QObject *parent)
    : QAbstractItemModel(parent){
    for(int i=0;i<100;++i){
     virtualData.push_back( 10+(std::rand()&255) );
    }
}

QVariant ItemsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole){
        return QString::fromUtf8( "1" );
    }
    return{};
    (void)section;
    (void)orientation;
}

QModelIndex ItemsModel::index(int row, int column, const QModelIndex &parent) const
{
    if( parent.internalId()==0 ){
        return this->createIndex(row,column,1);
    }else if(parent.internalId()==1){
        return this->createIndex(row,column,parent.row()+2);
    }
    return{};
}

QModelIndex ItemsModel::parent(const QModelIndex &index) const
{
    if( index.internalId()==0 ){return {};}
    else if( index.internalId()==1 ){ return {}; }
    auto parentIndex = index.internalId()-2;
    return this->createIndex(parentIndex,0,1);
}

int ItemsModel::rowCount(const QModelIndex &parent) const
{

    if( parent.internalId() == 0 ){
        return (int) virtualData.size();
    }
    else if( parent.internalId() == 1 ){
        auto row = parent.row() ;
        if(row < (int)virtualData.size() ){ return virtualData[row]; }
    }
    return 0;
}

int ItemsModel::columnCount(const QModelIndex & ) const{
    return 1;
}

QVariant ItemsModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role==Qt::DisplayRole){
        return "Hellow Word!";
    }if(role==Qt::SizeHintRole){
        return QSize(32,32);
    }

    // FIXME: Implement me!
    return QVariant();
}
