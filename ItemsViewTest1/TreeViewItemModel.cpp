#include <map>
#include <vector>
#include <cassert>
#include "TreeViewItemData.hpp"
#include "TreeViewItemModel.hpp"
#include "TreeViewItemDataList.hpp"

class TreeViewItemModel::_PrivateTreeViewItemModel{
public:
    template<typename _$m$T>using vector=std::vector<_$m$T>;
    template<typename _$m$T,typename _$m$U,typename _$m$C =std::less<void> >using map=std::map<_$m$T,_$m$U,_$m$C>;
    using DataType = vector< std::unique_ptr< TreeViewItemDataList > >;

    class CompareTreeViewItemDataListPointer{
        using _utp=std::unique_ptr< TreeViewItemDataList >;
    public:
        class is_transparent{};
        bool operator()(const _utp & l,const _utp & r) const { return l.get() < r.get(); }
        bool operator()(const _utp & l,const void * r) const { return l.get() < r; }
        bool operator()(const void * l,const _utp & r) const { return l < r.get(); }
        bool operator()(const void * l,const void * r) const { return l < r;}
    };

    class CompareTreeViewItemDataListQString{
        using _utp=std::unique_ptr< TreeViewItemDataList >;
    public:
        class is_transparent{};
        bool operator()(const QString & l,const QString & r) const { return l < r ; }
        bool operator()(const _utp & l,const _utp & r) const { return l.get() < r.get();}
        bool operator()(const QString & l,const _utp r) const { return l  < r ->getTitle() ; }
        bool operator()(const _utp & l,const QString & r) const { return l->getTitle() < r ; }

    };

    /*关联数据库，最好用数据库代替，这只是简单示例*/
    DataType $m$Data;
    map<void *,int,CompareTreeViewItemDataListPointer> $m$DataPointerIndex;
    map<QString,int,CompareTreeViewItemDataListQString> $m$DataQStringIndex;

    int listIndex(void * pointer) const {
        auto varPos = $m$DataPointerIndex.find(pointer);
        if( varPos == $m$DataPointerIndex.end() ){ return -1; }
        return varPos->second;
    }

    QVariant treeData(
            const QModelIndex & argIndex,
            int role) const{
        auto varRow = argIndex.row();
        if( varRow >= static_cast<decltype(varRow)>( $m$Data.size() ) ){ return {}; }

        const auto & varItem = $m$Data[varRow];
        if(role == Qt::DisplayRole){
            return varItem->getTitle();
        }

        return {};
    }

    QVariant listData(
            const QModelIndex & argIndex,
            int role) const{
        auto varRow = argIndex.row();

        if(listIndex(argIndex.internalPointer())<0){
            return {};
        }

        auto varList= reinterpret_cast<TreeViewItemDataList*>(argIndex.internalPointer());
        if( varRow >= varList->size() ){
            return {};
        }

        auto varData = varList->getData(  varRow );
        if(role == Qt::DisplayRole){
            //return QVariant::fromValue( std::move(varData) );
            return "xxxx";
        }

        return {};
    }

private:
    CPLUSPLUS_OBJECT(_PrivateTreeViewItemModel)
};

TreeViewItemModel::TreeViewItemModel(QObject * varParent):
    _Super(varParent){
    $m$this=new _PrivateTreeViewItemModel;
}

TreeViewItemModel::~TreeViewItemModel(){
    delete $m$this;
}

QVariant TreeViewItemModel::data(
        const QModelIndex & argIndex,
        int role) const {

    if(false == argIndex.isValid()){
        return{};
    }

    if( argIndex.row() < 0 ){return {};}

    auto * varThisData = &( $m$this->$m$Data );
    if( argIndex.internalPointer() == varThisData ){
        return $m$this->treeData( argIndex,role );
    }else{
        return $m$this->listData( argIndex,role );
    }

    return{};
}

QModelIndex TreeViewItemModel::index(
        int argRow,
        int argColumn,
        const QModelIndex &argParent) const {

    if(argRow<0){return {};}
    if(argColumn!=0){return {};}

    auto * varThisData = &( $m$this->$m$Data );
    if( argParent.internalPointer() == nullptr ){
        return this->createIndex(argRow,argColumn,static_cast<void *>(varThisData));
    }else if( argParent.internalPointer() == varThisData ){
        auto varParentRow = argParent.row();
        if( varParentRow < 0 ){ return {}; }
        if( varParentRow < static_cast<decltype(varParentRow)>( varThisData->size() ) ){
            auto & varCurrentList = (*varThisData)[varParentRow];
            return this->createIndex( argRow,argColumn,static_cast<void *>(varCurrentList.get()) );
        }else{
            return {};
        }
    }
    return {};

}

QModelIndex TreeViewItemModel::parent(const QModelIndex & argIndex) const {
    auto * varThisData = &( $m$this->$m$Data );
    if( argIndex.internalPointer() == nullptr ){ return {}; }
    else if( argIndex.internalPointer() == varThisData ){ return {}; }
    else {
        auto varParentPointer = argIndex.internalPointer();
        auto varParentIndex = $m$this->listIndex( varParentPointer );
        if( varParentIndex < 0 ){ return {}; }
        if( varParentIndex > static_cast<decltype(varParentIndex)>(varThisData->size()) ){ return {}; }
        return this->createIndex(varParentIndex,0, static_cast<void*>(varThisData) );
    }
    return {};
}

int TreeViewItemModel::rowCount(const QModelIndex & argParent) const{
    auto * varThisData = &( $m$this->$m$Data );
    if( argParent.internalPointer() == nullptr ){
        return static_cast<int>( varThisData->size() );
    }else if( argParent.internalPointer() == varThisData ){
        auto varRow = argParent.row();
        if( varRow < static_cast<decltype(varRow)>( varThisData->size() ) ){
            const auto & varList = (*varThisData)[varRow];
            return varList->size();
        }else{
            return 0;
        }
    }
    return 0;
}

TreeViewItemDataList * TreeViewItemModel::createList(const QString & argTitle){
    if( argTitle.isEmpty() ){ return nullptr; }
    auto varPos = $m$this->$m$DataQStringIndex.find( argTitle );
    if( varPos == $m$this->$m$DataQStringIndex.end() ){
        /*创建新表*/
        std::unique_ptr< TreeViewItemDataList > varData{ new TreeViewItemDataList };
        varData->setTitle( argTitle );
        TreeViewItemDataList * varDataPointer = varData.get();

        auto varKey=static_cast<int>( this->$m$this->$m$Data.size() );
        /*change the tree*/
        this->rowsAboutToBeInserted( QModelIndex{},varKey,varKey,{} );
        this->$m$this->$m$Data.push_back(std::move(varData));
        this->$m$this->$m$DataPointerIndex.emplace(varDataPointer,varKey);
        this->$m$this->$m$DataQStringIndex.emplace(argTitle,varKey);
        this->rowsInserted( QModelIndex{},varKey,varKey,{} );

        return varDataPointer;

    }else{
        /*返回旧表*/
        return $m$this->$m$Data[ varPos->second ].get();
    }
}

void TreeViewItemModel::addListData(const QString & argTitle,TreeViewItemData::type arg){

    TreeViewItemDataList * varList = createList(argTitle);
    if( varList == nullptr ){ return; }

    auto varNewPos = static_cast<int>( varList->size() );
    auto varPos = this->$m$this->$m$DataPointerIndex.find( varList );
    assert( varPos!=this->$m$this->$m$DataPointerIndex.end() );
    auto varParent = this->createIndex( varPos->second,0,&( this->$m$this ) );

    /*change the tree*/
    this->rowsAboutToBeInserted( varParent ,varNewPos,varNewPos ,{});
    varList->addData( std::move(arg) );
    this->rowsInserted( varParent ,varNewPos,varNewPos ,{} );

}

TreeViewItemDataList * TreeViewItemModel::getList(const QString & argTitle) const{
    auto varPos = $m$this->$m$DataQStringIndex.find( argTitle );
    if( varPos == $m$this->$m$DataQStringIndex.end() ){
        return nullptr;
    }
    return $m$this->$m$Data[ varPos->second ].get();
}












