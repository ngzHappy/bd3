#include <vector>
#include "TreeView.hpp"
#include "TreeViewItemModel.hpp"
#include "TreeViewItemWidget.hpp"

class TreeView::_PrivateTreeView {
public:
    template<typename $m$T>using vector=std::vector<$m$T>;
    vector<TreeViewItemWidget *> $m$OpendWidgets;
    TreeView * super;
    void closeAll(){
        for(auto varI : $m$OpendWidgets){
            varI->aboutToClosed();
            super->closePersistentEditor( varI->getModelIndex() );
        }
        $m$OpendWidgets.clear();
    }

private:
    CPLUSPLUS_OBJECT(_PrivateTreeView)
};

TreeView::TreeView(QWidget *parent):
    BasicTreeView(parent){
    $m$this=new _PrivateTreeView;
    $m$this->super=this;
    std::unique_ptr<QObject> varOldModel{ this->model() };
    this->setModel( new TreeViewItemModel(this) );
    this->setIndentation( 0 );
}

TreeView::~TreeView(){
    delete $m$this;
}

void TreeView::gcEvent(){

    auto & varWidgets = $m$this->$m$OpendWidgets;
    if(varWidgets.empty()){
        return;
    }

    const auto varVisibleItems = getAllVisibleItems();

    if( varVisibleItems.empty() ){
        $m$this->closeAll();
        return;
    }

    using T = TreeViewItemWidget *;
    using CT =const TreeViewItemWidget *;
    using U = const QModelIndex &;
    _PrivateTreeView::vector<T> varAboutToClosed;
    _PrivateTreeView::vector<T> varAllOpenedWidgets;
    class Compare{
    public:
        class is_transparent{};
        bool operator()(CT l,CT r)const{return l<r;}
        bool operator()(U l,U r)const{return l<r;}
        bool operator()(CT l,U r)const{ return l->getModelIndex()<r; }
        bool operator()(U l,CT r)const{ return l < r->getModelIndex(); }
    };
    constexpr Compare varCompare;

    for(T varI :  varWidgets ){

        if( std::binary_search(
                    varVisibleItems.cbegin(),
                    varVisibleItems.cend(),
                    varI,varCompare)){
            varAllOpenedWidgets.push_back(varI);
        }else{
            varAboutToClosed.push_back(varI);
        }

    }

    varWidgets=std::move(varAllOpenedWidgets);

    for(T varI : varAboutToClosed){
        varI->aboutToClosed();
        this->closePersistentEditor( varI->getModelIndex() );
    }

}

void TreeView::paintEvent(QPaintEvent * argEvent){
    _Super::paintEvent(argEvent);
    gcEvent();
}


