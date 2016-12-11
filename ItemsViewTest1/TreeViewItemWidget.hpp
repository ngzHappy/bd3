#ifndef TREEVIEWITEMWIDGET_HPP
#define TREEVIEWITEMWIDGET_HPP

#include <cplusplus_basic.hpp>
#include <QtCore/QModelIndex>
#include <QtWidgets/qwidget.h>
#include "TreeViewItemData.hpp"

class TreeViewItemWidget : public QWidget{
    Q_OBJECT
private:
    using _Super=QWidget;
private:
    std::weak_ptr<TreeViewItemData> $m$Watcher/*判断数据是否失效*/;
    QModelIndex $m$ModelIndexWhenOpened/*用于gc*/;
public:
    TreeViewItemWidget(QWidget *);

    const QModelIndex& getModelIndex()const{return $m$ModelIndexWhenOpened;}
    std::weak_ptr<TreeViewItemData> getDataWatcher(){  return $m$Watcher; }

    void setModelIndex(const QModelIndex& arg){$m$ModelIndexWhenOpened = arg;}
    void setDataWatcher(std::weak_ptr<TreeViewItemData> && arg){ $m$Watcher=std::move(arg); }
    void setDataWatcher(const std::weak_ptr<TreeViewItemData> & arg){ $m$Watcher=arg; }

    virtual void aboutToClosed()/*提前释放大型资源*/{}
    ~TreeViewItemWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TREEVIEWITEMWIDGET_HPP



