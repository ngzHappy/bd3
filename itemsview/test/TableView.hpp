#ifndef TABLEVIEW_HPP
#define TABLEVIEW_HPP

#include <QtWidgets/qtableview.h>

class TableView : public QTableView
{
    Q_OBJECT
private:
    using _Super=QTableView;
public:
    TableView();
protected:
    void paintEvent(QPaintEvent *e) override;
    QVector<QModelIndex> _p_getAllVisibleItems();
private:
    Q_DECLARE_PRIVATE(QTableView)
};

#endif // TABLEVIEW_HPP
