#include <vector>
#include "TreeView.hpp"
#include "TreeViewItemModel.hpp"
#include "TreeViewItemWidget.hpp"
#include "TreeViewItemDelegate.hpp"

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

    {/*初始化私有数据*/
        $m$this=new _PrivateTreeView;
        $m$this->super=this;
    }

    {/*初始化model*/
        std::unique_ptr<QObject> varOldModel{ this->model() };
        this->setModel( new TreeViewItemModel(this) );
        this->setIndentation( 0 );
    }

    {/*初始化代理*/
        std::unique_ptr<QObject> varOldDelegate{ this->itemDelegate() };
        this->setItemDelegate( new TreeViewItemDelegate(this) );
    }

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

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

class TreeViewItemDelegate::_PrivateTreeViewItemDelegate{
public:
    TreeView * superWidget;
    TreeViewItemDelegate * super;
private:
    CPLUSPLUS_OBJECT(_PrivateTreeViewItemDelegate)
};

TreeViewItemDelegate::TreeViewItemDelegate(TreeView *arg):_Super(arg){
    $m$this=new _PrivateTreeViewItemDelegate;
    $m$this->superWidget=arg;
    $m$this->super=this;
}

TreeViewItemDelegate::~TreeViewItemDelegate(){
    delete $m$this;
}

void TreeViewItemDelegate::paint(
        QPainter * painter,
        const QStyleOptionViewItem & styleOption,
        const QModelIndex & index) const {

    if( index.isValid() ){
          auto super = $m$this->superWidget;
          super->openPersistentEditor( index );
          return;
    }

    return _Super::paint(painter,styleOption,index);

}

QWidget *TreeViewItemDelegate::createEditor(
        QWidget * parent,
        const QStyleOptionViewItem & option,
        const QModelIndex & index) const {

    if( index.isValid() ){

        auto varType = index.data( TreeViewItemModel::Role_Type ).toInt();

        if( varType == TreeViewItemModel::GroupHeader ){
            auto varAns = new TreeViewItemWidget(parent);
            varAns->setModelIndex( index );
            auto super = $m$this->superWidget;
            super->$m$this->$m$OpendWidgets.push_back( varAns );
            return varAns;
        }else if( varType == TreeViewItemModel::TreeItem ){
            auto varAns = new TreeViewItemWidget(parent);
            varAns->setModelIndex( index );
            auto super = $m$this->superWidget;
            super->$m$this->$m$OpendWidgets.push_back( varAns );
            return varAns;
        }

    }
    return _Super::createEditor(parent,option,index);
}

void TreeViewItemDelegate::destroyEditor(
        QWidget * argWidget,
        const QModelIndex & argIndex) const {
    return _Super::destroyEditor(argWidget,argIndex);
}

void TreeViewItemDelegate::updateEditorGeometry(
        QWidget * widget,
        const QStyleOptionViewItem & option,
        const QModelIndex & index) const{
    return _Super::updateEditorGeometry(widget,option,index);
}
