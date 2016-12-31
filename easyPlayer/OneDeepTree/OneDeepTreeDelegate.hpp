#ifndef ONEDEEPTREEDELEGATE_HPP
#define ONEDEEPTREEDELEGATE_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/qstyleditemdelegate.h>

#ifndef $m$ONEDEEPTREEDELEGATE_PROTECTED /*模拟java包组织权限*/
#define $m$ONEDEEPTREEDELEGATE_PROTECTED protected
#endif

class OneDeepTreeView;
class OneDeepTreeItemWidget;
class _PrivateOneDeepTreeDelegate;
class OneDeepTreeDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:
    using Super=QStyledItemDelegate;
    friend class _PrivateOneDeepTreeDelegate;
protected:
    OneDeepTreeDelegate(_PrivateOneDeepTreeDelegate *,OneDeepTreeView *);
public:
    OneDeepTreeDelegate(OneDeepTreeView *);
    virtual ~OneDeepTreeDelegate();
protected:
    virtual OneDeepTreeItemWidget *doCreateEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const ;
    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const override;
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void destroyEditor(QWidget *, const QModelIndex &) const override;
    void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void setEditorData(QWidget *,const QModelIndex &) const override;
$m$ONEDEEPTREEDELEGATE_PROTECTED:
    _PrivateOneDeepTreeDelegate *$m$thisp=nullptr;
private:
    CPLUSPLUS_OBJECT(OneDeepTreeDelegate)
};

#endif // ONEDEEPTREEDELEGATE_HPP
