#ifndef TESTTREEVIEW_HPP
#define TESTTREEVIEW_HPP

#include <QtWidgets/qtreeview.h>

class TestTreeView : public QTreeView {
    using _Super=QTreeView;
public:
    TestTreeView();
public:
    void paintEvent(QPaintEvent *event) override;
    QVector<QModelIndex> _p_getAllVisibleItems();
private:
    Q_DECLARE_PRIVATE(QTreeView)
};

#endif // TESTTREEVIEW_HPP
