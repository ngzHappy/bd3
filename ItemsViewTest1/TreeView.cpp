#include <set>
#include <vector>
#include <cassert>
#include "TreeView.hpp"
#include "TreeViewItemModel.hpp"
#include "TreeViewItemWidget.hpp"
#include "TreeViewItemDelegate.hpp"

#include <QtCore/qdebug.h>
#include <QtCore/qtimer.h>

class TreeView::_PrivateTreeView {
public:
    std::uint64_t $m$VerticalScrollbarValueChangeStamp=0;
    template<typename $m$T>using vector=std::vector<$m$T>;
    template<typename $m$T,typename $m$C>using set=std::set<$m$T,$m$C>;

    class TreeViewItemWidgetCompare {
        using T=const TreeViewItemWidget *;
        using U=const QModelIndex &;
    public:
        class is_transparent {};
        bool operator()(T l,T r)const {
            return l->getModelIndex()<r->getModelIndex();
        }
        bool operator()(U l,U r)const { return l<r; }
        bool operator()(U l,T r)const { return l<r->getModelIndex(); }
        bool operator()(T l,U r)const { return l->getModelIndex()<r; }
    };

    set<TreeViewItemWidget *,TreeViewItemWidgetCompare> $m$OpendWidgets;
    TreeView * super;
    void closeAll() {
        for (auto varI:$m$OpendWidgets) {
            varI->aboutToClosed();
            super->closePersistentEditor(varI->getModelIndex());
        }
        $m$OpendWidgets.clear();
    }

private:
    CPLUSPLUS_OBJECT(_PrivateTreeView)
};

TreeView::TreeView(QWidget *parent):
    BasicTreeView(parent) {

    {/*初始化私有数据*/
        $m$this=new _PrivateTreeView;
        $m$this->super=this;
    }

    {/*初始化model*/
        std::unique_ptr<QObject> varOldModel{ this->model() };
        this->setModel(new TreeViewItemModel(this));
        this->setIndentation(0);
    }

    {/*初始化代理*/
        std::unique_ptr<QObject> varOldDelegate{ this->itemDelegate() };
        this->setItemDelegate(new TreeViewItemDelegate(this));
    }
     
    {
        connect(this,&TreeView::_p_scroll_to,this,
            [this](const QModelIndex& argIndex) {
            this->scrollTo(argIndex,QAbstractItemView::PositionAtCenter);
        });
    }

}

void TreeView::currentChanged(
    const QModelIndex &current,
    const QModelIndex &previous) {
    _Super::currentChanged(current,previous);
    _p_scroll_to(current);
}

TreeView::~TreeView() {
    delete $m$this;
}

void TreeView::gcEvent() {

    auto & varWidgets=$m$this->$m$OpendWidgets;
    if (varWidgets.empty()) {
        return;
    }

    const auto varVisibleItems=getAllVisibleItems();

    if (varVisibleItems.empty()) {
        $m$this->closeAll();
        return;
    }

    using T=TreeViewItemWidget *;
    using CT=const TreeViewItemWidget *;
    using U=const QModelIndex &;
    _PrivateTreeView::vector<T> varAboutToClosed;
    std::remove_reference_t<decltype(varWidgets)> varAllOpenedWidgets;
    class Compare {
    public:
        class is_transparent {};
        bool operator()(CT l,CT r)const { return l<r; }
        bool operator()(U l,U r)const { return l<r; }
        bool operator()(CT l,U r)const { return l->getModelIndex()<r; }
        bool operator()(U l,CT r)const { return l<r->getModelIndex(); }
    };
    constexpr Compare varCompare;

    for (T varI:varWidgets) {

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

    for (T varI:varAboutToClosed) {
        varI->aboutToClosed();
        this->closePersistentEditor(varI->getModelIndex());
    }

}

void TreeView::paintEvent(QPaintEvent * argEvent) {
    _Super::paintEvent(argEvent);
    gcEvent();
}

void TreeView::timerEvent(QTimerEvent *event) {
    _Super::timerEvent(event);
}

void TreeView::verticalScrollbarValueChanged(int arg) {
    _Super::verticalScrollbarValueChanged(arg);
    auto varCurrentStamp =++( $m$this->$m$VerticalScrollbarValueChangeStamp );
    QTimer::singleShot(200,[this,varCurrentStamp]() {
        /*200ms内没有再次调用此函数*/
        if (varCurrentStamp==$m$this->$m$VerticalScrollbarValueChangeStamp) {
            /*强制重绘*/
            for (auto varI:$m$this->$m$OpendWidgets) {
                varI->update();
            }
        }
    });
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

class TreeViewItemDelegate::_PrivateTreeViewItemDelegate {
public:
    TreeView * superWidget;
    TreeViewItemDelegate * super;
private:
    CPLUSPLUS_OBJECT(_PrivateTreeViewItemDelegate)
};

TreeViewItemDelegate::TreeViewItemDelegate(TreeView *arg):_Super(arg) {
    $m$this=new _PrivateTreeViewItemDelegate;
    $m$this->superWidget=arg;
    $m$this->super=this;
}

TreeViewItemDelegate::~TreeViewItemDelegate() {
    delete $m$this;
}

void TreeViewItemDelegate::paint(
        QPainter * painter,
        const QStyleOptionViewItem & styleOption,
        const QModelIndex & index) const {

    if (index.isValid()) {
        auto super=$m$this->superWidget;
        auto & varOpenedWidgets=super->$m$this->$m$OpendWidgets;
        auto varPos=varOpenedWidgets.find(index);
        if (varPos==varOpenedWidgets.end()) {
            super->openPersistentEditor(index);
        }
        else {
            (*varPos)->update(styleOption,index);
        }
        return;
    }

    return _Super::paint(painter,styleOption,index);

}

QWidget *TreeViewItemDelegate::createEditor(
        QWidget * parent,
        const QStyleOptionViewItem & option,
        const QModelIndex & index) const {

    if (index.isValid()) {

        auto varType=index.data(TreeViewItemModel::Role_Type).toInt();

        if (varType==TreeViewItemModel::GroupHeader) {
            auto varAns=new TreeViewItemWidget(parent);
            varAns->setModelIndex(index);
            auto super=$m$this->superWidget;
            assert(super->$m$this->$m$OpendWidgets.count(varAns)==0);
            super->$m$this->$m$OpendWidgets.insert(varAns);
            return varAns;
        }
        else if (varType==TreeViewItemModel::TreeItem) {
            auto varAns=new TreeViewItemWidget(parent);
            varAns->setModelIndex(index);
            auto super=$m$this->superWidget;
            assert(super->$m$this->$m$OpendWidgets.count(varAns)==0);
            super->$m$this->$m$OpendWidgets.insert(varAns);
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

void TreeViewItemDelegate::updateEditorGeometry(QWidget * widget,const QStyleOptionViewItem & option,const QModelIndex & index) const {
    {
        auto varWidget=qobject_cast<TreeViewItemWidget*>(widget);
        if (varWidget) {
            varWidget->update(option,index);
            varWidget->setGeometry(option.rect);
            varWidget->update();
            return;
        }
    }
    _Super::updateEditorGeometry(widget,option,index);
}

void TreeViewItemDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const {
    auto varWidget=qobject_cast<TreeViewItemWidget*>(editor);
    if (varWidget) {
        varWidget->setData(index);
        return;
    }
    _Super::setEditorData(editor,index);
}


