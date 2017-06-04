#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMenu>
#include <QApplication>
#include <QMessageBox>
#include <QCursor>
#include <QPoint>
#include <QStyle>
#include "../structures.h"
#include <math.h>
#include <algorithm>

namespace TIME_CONSTANTS {
    const int MSEC_TO_SEC_MULT = 1000;
    const int MINUTE = 60*MSEC_TO_SEC_MULT;
    const int HALF_OF_HOUR = 30*MINUTE;
    const int HOUR = 60*MINUTE;

    const int EPSILON_MINUTE_IN_SEC = 60;
    const int REGULAR_INTERVAL= MINUTE*15;
}

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent=nullptr);
    virtual ~TrayIcon();
    void setMainTimerInterval(int msec);
    void startMainTimer();
    void stopMainTimer();
    void loadDatesForDate(const QDate &date);

public slots:
    void on_exit(bool checked);

private slots:
    void on_timer();
    void on_activated(QSystemTrayIcon::ActivationReason reason);
    void on_message_clicked();

private:
    void createMenu();
    QMenu *menu;
    QTimer timer;
    QList<DateNotifyElement> dateTimes;
};

#endif // TRAYICON_H
