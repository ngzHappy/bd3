#ifndef TESTWIDGET_HPP
#define TESTWIDGET_HPP

#include <QtWidgets/qlistview.h>

class TestWidget : public QListView {
    Q_OBJECT
private:
    using _Super=QListView;
public:
    TestWidget();
protected:
    void paintEvent(QPaintEvent *e) override;
    QVector<QModelIndex> _p_getAllVisibleItems();
private:
    Q_DECLARE_PRIVATE(QListView)
};

#endif // TESTWIDGET_HPP
