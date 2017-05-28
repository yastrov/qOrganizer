#include "tasktreeitem.h"

TaskTreeItem::TaskTreeItem(const QString& name, int id, bool finished, TreeItem *parent)
    :TreeItem(name, id, TreeItemType::Task, parent),
      _color(Qt::white), _finished(finished)
{

}

TaskTreeItem::TaskTreeItem(const QString& name, int id, TreeItem *parent)
    :TreeItem(name, id, TreeItemType::Task, parent),
      _color(Qt::white), _finished(false)
{

}

TaskTreeItem::~TaskTreeItem()
{

}

QColor TaskTreeItem::color() const
{
    return _color;
}

void TaskTreeItem::setColor(const QColor &color)
{
    _color = color;
}

QDate TaskTreeItem::startDate() const
{
    return _startDate;
}

void TaskTreeItem::setStartDate(const QDate &date)
{
    _startDate = date;
}

QDate TaskTreeItem::endDate() const
{
    return _endDate;
}

void TaskTreeItem::setEndDate(const QDate &date)
{
    _endDate = date;
}

QTime TaskTreeItem::time() const
{
    return _time;
}

void TaskTreeItem::setTime(const QTime &time)
{
    _time = time;
}

bool TaskTreeItem::finished() const
{
    return _finished;
}

void TaskTreeItem::setFinished(bool finished)
{
    _finished = finished;
}

int	TaskTreeItem::columnCount() const
{
    return _maxColumn;
}

QVariant TaskTreeItem::data(int column, int role) const
{
    if (column >= _maxColumn)
        return QVariant();

    return QVariant();
}

bool TaskTreeItem::setData(int column, const QVariant &value, int role)
{
    if (column >= _maxColumn)
        return false;

    return false;
}
