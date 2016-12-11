#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

class TreeViewItemModel;
class TreeViewItemDelegate;
#include "BasicTreeView.hpp"

class TreeView :public BasicTreeView {
    Q_OBJECT
private:
    using _Super=BasicTreeView;
public:
    TreeView(QWidget * parent = nullptr);
    virtual ~TreeView();

    inline TreeViewItemModel * getItemsModel()const{/*因为这是单根继承*/
        return reinterpret_cast<TreeViewItemModel *>(this->model());
    }

protected:
    void paintEvent(QPaintEvent *) override;
    void timerEvent(QTimerEvent *event) override;
    void verticalScrollbarValueChanged(int) override;
    void gcEvent();
    Q_SIGNAL void verticalScrollbarValueChangeFinished();
private:
    class _PrivateTreeView;
    _PrivateTreeView * $m$this;
    friend class TreeViewItemDelegate;
private:
    CPLUSPLUS_OBJECT(TreeView)
};

#endif // TREEVIEW_HPP








