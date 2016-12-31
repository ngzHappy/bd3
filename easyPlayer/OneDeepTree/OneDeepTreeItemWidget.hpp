#ifndef ONEDEEPTREEITEMWIDGET_HPP
#define ONEDEEPTREEITEMWIDGET_HPP

#include <cplusplus_basic.hpp>
#include <QtCore/QModelIndex>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qstyleoption.h>

#ifndef $m$ONEDEEPTREEITEMWIDGET_PROTECTED /*模拟java包组织权限*/
#define $m$ONEDEEPTREEITEMWIDGET_PROTECTED protected
#endif

class OneDeepTreeItemWidget : public QWidget {
    Q_OBJECT
private:
    using Super=QWidget;
$m$ONEDEEPTREEITEMWIDGET_PROTECTED:
    QModelIndex $m$ModelIndexWhenOpened/*用于gc*/;
    QStyleOptionViewItem $m$QStyleOptionViewItem/*用于update*/;
public:
    OneDeepTreeItemWidget(QWidget * /**/=nullptr);

    const auto & getModelIndex() const { return $m$ModelIndexWhenOpened; }
    void setModelIndex( const QModelIndex &arg ){ $m$ModelIndexWhenOpened=arg; }
    void setModelIndex(QModelIndex &&arg ){ $m$ModelIndexWhenOpened=std::move(arg); }

    const auto & getStyleOption() const { return $m$QStyleOptionViewItem; }
    void setStyleOption(const QStyleOptionViewItem & arg){$m$QStyleOptionViewItem=arg;}
    void setStyleOption(QStyleOptionViewItem && arg){$m$QStyleOptionViewItem=std::move(arg);}

    using Super::update;
$m$ONEDEEPTREEITEMWIDGET_PROTECTED:
    virtual void aboutToClosed(){/*用于释放大对象*/}
    virtual void update(const QStyleOptionViewItem&,const QModelIndex&);
    virtual bool isOptionChanged(const QStyleOptionViewItem&);
    virtual void setData(const QModelIndex &);
protected:
    void paintEvent(QPaintEvent *)override;
private:
    CPLUSPLUS_OBJECT(OneDeepTreeItemWidget)
};

#endif // ONEDEEPTREEITEMWIDGET_HPP
