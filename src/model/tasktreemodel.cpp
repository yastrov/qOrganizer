#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem(QString("Node"), 0, nullptr);
}

TaskTreeModel::~TaskTreeModel()
{
    if(rootItem)
        delete rootItem;
}

TreeItem *TaskTreeModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) {
            return item;
        }
    }
    return rootItem;
}

QVariant TaskTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();
    switch(section) {
    case TaskTreeModelColumn::Name:
        return tr("Name");
        break;
    case TaskTreeModelColumn::Finished:
        return tr("Finished");
        break;
    case TaskTreeModelColumn::Color:
        return tr("Color");
        break;
    case TaskTreeModelColumn::DateStart:
        return tr("Date start");
        break;
    case TaskTreeModelColumn::DateEnd:
        return tr("Date end");
        break;
    case TaskTreeModelColumn::Time:
        return tr("Time");
        break;
    default:
        break;
    }

    return QVariant();
}

QModelIndex TaskTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    TreeItem *parentItem = itemForIndex(parent);
    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TaskTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = itemForIndex(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TaskTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *item = itemForIndex(parent);
    return item->childCount();
}

int TaskTreeModel::columnCount(const QModelIndex &parent) const
{
    return _maxColumn;
}

QVariant TaskTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    TreeItem *item = itemForIndex(index);
    return item->data(index.column(), role);
}

bool TaskTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        TreeItem *item = itemForIndex(index);
        bool flag = item->setData(index.column(), value, role);
        if(flag)
            emit dataChanged(index, index, QVector<int>() << role);
        return flag;
    }
    return false;
}

Qt::ItemFlags TaskTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable;
    return flags;
}

bool TaskTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool TaskTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

TreeItem *TaskTreeModel::getInvisibleRoot()
{
    return rootItem;
}
