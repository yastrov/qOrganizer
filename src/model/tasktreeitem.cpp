#include "tasktreeitem.h"

TaskTreeItem::TaskTreeItem(const QString& name, int id, bool finished, TreeItem *parent)
    :TreeItem(name, id, TreeItemType::Task, parent),
      _color(Qt::white), _finished(finished)
{
    QDate now = QDate::currentDate();
    _startDate = now;
    _endDate = now;
    _time = QTime::currentTime();
}

TaskTreeItem::TaskTreeItem(const QString& name, int id, TreeItem *parent)
    : TaskTreeItem(name, id, TreeItemType::Task, parent)
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
    switch(role){
    case Qt::DisplayRole:
        switch(column) {
        case TaskTreeItemColumn::Finished: return QVariant();
        case TaskTreeItemColumn::Color: return QVariant();
        }
    case Qt::EditRole:
        switch(column) {
        case TaskTreeItemColumn::Name: return _name;
        case TaskTreeItemColumn::Finished: return _finished;
        case TaskTreeItemColumn::Color: return _color;
        case TaskTreeItemColumn::DateStart: return _startDate;
        case TaskTreeItemColumn::DateEnd: return _endDate;
        case TaskTreeItemColumn::Time: return _time;
        }
        break;
    case Qt::BackgroundColorRole:
        if(column == TaskTreeItemColumn::Color)
            return _color;
        break;
    case Qt::CheckStateRole:
        if(column == TaskTreeItemColumn::Finished) {
            if(_finished)
                return Qt::Checked;
            else return Qt::Unchecked;
        }
        break;
    case Qt::ToolTipRole:
    default:
        ;
    }

    return QVariant();
}

bool TaskTreeItem::setData(int column, const QVariant &value, int role)
{
    if (column >= _maxColumn)
        return false;
    if(role == Qt::CheckStateRole) {
        if(column == TaskTreeItemColumn::Finished) {
            if (value.toInt() == Qt::Checked) {
                _finished = true;
            } else {
                _finished = false;
            }
            return true;
        }
        return false;
    }
    if (role != Qt::EditRole)
        return false;
    switch(column){
    case TaskTreeItemColumn::Name:
        _name = value.toString();
        break;
    case TaskTreeItemColumn::Finished:
        _finished = value.toBool();
        break;
    case TaskTreeItemColumn::Color:
        _color = value.value<QColor>();
        break;
    case TaskTreeItemColumn::DateStart:
        _startDate = value.toDate();
        break;
    case TaskTreeItemColumn::DateEnd:
        _endDate = value.toDate();
        break;
    case TaskTreeItemColumn::Time:
        _time = value.toTime();
        break;
    default:
        return false;
    }
    return true;
    return false;
}
