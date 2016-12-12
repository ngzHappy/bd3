#ifndef ITEMSMODEL_HPP
#define ITEMSMODEL_HPP

#include <vector>
#include <QtCore/QAbstractItemModel>

class ItemsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ItemsModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<int> virtualData;
};

#endif // ITEMSMODEL_HPP
