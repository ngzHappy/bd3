#ifndef TREEVIEWITEMMODEL_HPP
#define TREEVIEWITEMMODEL_HPP

#include <cplusplus_basic.hpp>
#include <QtCore/qabstractitemmodel.h>

#include "TreeViewItemData.hpp"
#include "TreeViewItemDataList.hpp"

class TreeViewItemModel : public QAbstractItemModel{
    Q_OBJECT
private:
    using _Super=QAbstractItemModel;
public:
    TreeViewItemModel(QObject*);
    virtual ~TreeViewItemModel();
public:
    virtual int columnCount(const QModelIndex &) const override{ return 1; }
    virtual QVariant data(const QModelIndex &,int ) const override;
    virtual QModelIndex index(int ,int ,const QModelIndex &) const override;
    virtual QModelIndex parent(const QModelIndex &) const override ;
    virtual int rowCount(const QModelIndex &) const;
public:

    enum {
        Role_Type=Qt::UserRole+1,
    };

    enum ItemType : int{
        GroupHeader=17,
        TreeItem,
    };

public:
    TreeViewItemDataList * createList(const QString &/*title*/);
    TreeViewItemDataList * getList(const QString &/*title*/) const;
    void addListData(const QString &/*title*/,TreeViewItemData::type);
private:
    class _PrivateTreeViewItemModel;
    _PrivateTreeViewItemModel * $m$this;
private:
    CPLUSPLUS_OBJECT(TreeViewItemModel)
};

#endif // TREEVIEWITEMMODEL_HPP
