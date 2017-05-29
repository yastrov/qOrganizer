#ifndef TASKTREEMODEL_H
#define TASKTREEMODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"
#include "tasktreeitem.h"

enum TaskTreeModelColumn: int {
    Name = 0,
    Finished,
    Color,
    DateStart,
    DateEnd,
    Time
};

class TaskTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TaskTreeModel(QObject *parent = nullptr);
    virtual ~TaskTreeModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    TreeItem * getInvisibleRoot();

private:
    TreeItem *rootItem;
    TreeItem *itemForIndex(const QModelIndex &index) const;
    static const int _maxColumn = 6;
};

#endif // TASKTREEMODEL_H
