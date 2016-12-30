#ifndef ONEDEEPTREEVIEW_HPP
#define ONEDEEPTREEVIEW_HPP

#include <cplusplus_basic.hpp>
#include <QtCore/qvector.h>
#include <QtWidgets/qtreeview.h>

#ifndef $m$ONEDEEPTREEVIEW_PROTECTED /*模拟java包组织权限*/
#define $m$ONEDEEPTREEVIEW_PROTECTED protected
#endif

class _PrivateOneDeepTreeView;
class OneDeepTreeView :public QTreeView  {
    Q_OBJECT
private:
    using Super=QTreeView;
    friend class _PrivateOneDeepTreeView;
public:
    OneDeepTreeView(QWidget * /**/=nullptr);
    ~OneDeepTreeView();
$m$ONEDEEPTREEVIEW_PROTECTED:
    _PrivateOneDeepTreeView *$m$thisp=nullptr;
     QVector<QModelIndex> getAllVisibleItems()/*获得所有可见的item的index*/;
     void paintEvent(QPaintEvent *) override;
     void verticalScrollbarValueChanged(int) override;
     void gcEvent();
private:
     void _p_start_gcevent();
private:
    Q_DECLARE_PRIVATE(QTreeView)/*使用Qt的私有模块*/
private:
    CPLUSPLUS_OBJECT(OneDeepTreeView)/*用此宏用于优化new/delete*/
};

#endif // ONEDEEPTREEVIEW_HPP










