#ifndef TREEVIEWITEMDELEGATE_HPP
#define TREEVIEWITEMDELEGATE_HPP

#include "cplusplus_basic.hpp"
#include <QtWidgets/qstyleditemdelegate.h>
class TreeView;

class TreeViewItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
private:
    using _Super=QStyledItemDelegate;
public:
    TreeViewItemDelegate(TreeView * );
    ~TreeViewItemDelegate();
protected:

    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const override;
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void destroyEditor(QWidget *, const QModelIndex &) const override;
    void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;

private:
    class _PrivateTreeViewItemDelegate;
    _PrivateTreeViewItemDelegate * $m$this;
private:
    CPLUSPLUS_OBJECT(TreeViewItemDelegate)
};

#endif // TREEVIEWITEMDELEGATE_HPP
