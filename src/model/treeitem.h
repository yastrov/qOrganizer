#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QString>

enum TreeItemType: int {
    Folder = 0,
    Task,
    Notification
};

class TreeItem
{
public:
    explicit TreeItem(const QString& name="Node", int id=0, TreeItemType type=TreeItemType::Folder, TreeItem *parent=nullptr);
    virtual ~TreeItem();

    TreeItemType type() const;
    void setType(TreeItemType type);
    int id() const;
    void setId(int id);
    QString name() const;
    QString setName(const QString& name);
    TreeItem *parent();
    int childCount() const;
    bool hasChild() const;
    int rowOfChild(TreeItem *child) const;
    int row() const;
    TreeItem* takeChild(int row);
    TreeItem* child(int row);
    void insertChild(int row, TreeItem *item);
    void appendChild(TreeItem *item);

    virtual int	columnCount() const;
    virtual QVariant data(int column, int role = Qt::DisplayRole) const;
    virtual bool setData(int column, const QVariant &value, int role = Qt::EditRole);

private:
    QList<TreeItem*> childItems;
    TreeItem *parentItem;
    QString _name;
    int _id;
    TreeItemType _type;
};

#endif // TREEITEM_H
