#ifndef TASKTREEITEM_H
#define TASKTREEITEM_H
#include "treeitem.h"
#include <QColor>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QString>
#include <QVariant>

class TaskTreeItem : public TreeItem
{
public:
    explicit TaskTreeItem(const QString& name="Node", int id=0, bool finished=false, TreeItem *parent=nullptr);
    explicit TaskTreeItem(const QString& name="Node", int id=0, TreeItem *parent=nullptr);
    virtual ~TaskTreeItem();

    QColor color() const;
    void setColor(const QColor &color);
    QDate startDate() const;
    void setStartDate(const QDate &date);
    QDate endDate() const;
    void setEndDate(const QDate &date);
    QTime time() const;
    void setTime(const QTime &time);
    bool finished() const;
    void setFinished(bool finished);

    int	columnCount() const Q_DECL_OVERRIDE;
    QVariant data(int column, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(int column, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    enum TaskTreeItemColumn: int {
        Name = 0,
        Finished,
        Color,
        DateStart,
        DateEnd,
        Time
    };

private:
    QColor _color;
    QDate _startDate;
    QDate _endDate;
    QTime _time;
    bool _finished;
    static const int _maxColumn = 6;
};

#endif // TASKTREEITEM_H
