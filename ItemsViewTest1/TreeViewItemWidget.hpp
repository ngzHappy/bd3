#ifndef TREEVIEWITEMWIDGET_HPP
#define TREEVIEWITEMWIDGET_HPP

#include <cplusplus_basic.hpp>
#include <QtCore/QModelIndex>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qstyleoption.h>
#include "TreeViewItemData.hpp"

class TreeViewItemWidget : public QWidget{
    Q_OBJECT
private:
    using _Super=QWidget;
private:
    std::weak_ptr<TreeViewItemData> $m$Watcher/*判断数据是否失效*/;
    QModelIndex $m$ModelIndexWhenOpened/*用于gc*/;
    QStyleOptionViewItem $m$QStyleOptionViewItem/*用于update*/;
    
public:
    TreeViewItemWidget(QWidget *);
    using _Super::update;

    const QModelIndex& getModelIndex()const{return $m$ModelIndexWhenOpened;}
    std::weak_ptr<TreeViewItemData> getDataWatcher(){  return $m$Watcher; }

    void setModelIndex(const QModelIndex& arg){$m$ModelIndexWhenOpened = arg;}
    void setDataWatcher(std::weak_ptr<TreeViewItemData> && arg){ $m$Watcher=std::move(arg); }
    void setDataWatcher(const std::weak_ptr<TreeViewItemData> & arg){ $m$Watcher=arg; }

    virtual void aboutToClosed()/*提前释放大型资源*/;
    virtual void update(const QStyleOptionViewItem&,const QModelIndex&);
    virtual bool isOptionChanged(const QStyleOptionViewItem&);
    virtual void setData(const QModelIndex &);
    bool isPainting() const {return this->testAttribute(Qt::WA_WState_InPaintEvent); }

    ~TreeViewItemWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};

#endif // TREEVIEWITEMWIDGET_HPP



