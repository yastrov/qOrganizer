#include "treeitem.h"

TreeItem::TreeItem(const QString& name, int id, TreeItemType type, TreeItem *parent):
    parentItem(parent), _name(name), _id(id), _type(type)
{
    if(parentItem)
        parentItem->appendChild(this);
}

TreeItem::TreeItem(const QString& name, int id, TreeItem *parent):
    TreeItem(name, id, TreeItemType::Folder, parent)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItemType TreeItem::type() const
{
   return _type;
}

void TreeItem::setType(TreeItemType type)
{
    _type = type;
}

int TreeItem::id() const
{
    return _id;
}

void TreeItem::setId(int id)
{
    _id = id;
}

QString TreeItem::name() const
{
    return _name;
}

QString TreeItem::setName(const QString &name)
{
    _name = name;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

int TreeItem::childCount() const
{
    return childItems.count();
}

bool TreeItem::hasChild() const
{
    return !childItems.isEmpty();
}

int TreeItem::rowOfChild(TreeItem *child) const
{
    return childItems.indexOf(child);
}

int TreeItem::row() const
{
    if(parentItem) {
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}

TreeItem *TreeItem::takeChild(int row)
{
    TreeItem *item = childItems.takeAt(row);
    Q_ASSERT(item);
    item->parentItem = nullptr;
    return item;
}

TreeItem* TreeItem::child(int row)
{
    return childItems.value(row);
}

void TreeItem::insertChild(int row, TreeItem *item)
{
    item->parentItem = this;
    childItems.insert(row, item);
}

void TreeItem::appendChild(TreeItem *item)
{
    item->parentItem = this;
    childItems << item;
}

int	TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data(int column, int role) const
{
    if(column == 0 && (role == Qt::DisplayRole || role == Qt::EditRole) )
        return _name;
    return QVariant();
}

bool TreeItem::setData(int column, const QVariant &value, int role)
{
    if(column == 0 && role == Qt::EditRole) {
        _name = value.toString();
        return true;
    }
    return false;
}
