#ifndef BASICTREEVIEW_HPP
#define BASICTREEVIEW_HPP

#include "cplusplus_basic.hpp"
#include <QtCore/qvector.h>
#include <QtWidgets/qtreeview.h>

/*just use for one deepth tree*/
class BasicTreeView : protected QTreeView{
    Q_OBJECT
private:
    using _Super=QTreeView;
public:
    BasicTreeView(QWidget *parent = nullptr);
    virtual ~BasicTreeView();
    using _Super::show;
public:
    QVector<QModelIndex> getAllVisibleItems();
private:
    Q_DECLARE_PRIVATE(QTreeView)
private:
    CPLUSPLUS_OBJECT(BasicTreeView)
};

#endif // BASICTREEVIEW_HPP
