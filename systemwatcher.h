#ifndef SYSTEMWATCHER_H
#define SYSTEMWATCHER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QTimer>

class SystemWatcher : public QObject
{
    Q_OBJECT
public:
    explicit SystemWatcher(QObject *parent = nullptr);

signals:
    void batteryUpdate(int, int);
private slots:
    void updateBattery();
private:
    QProcess * cat;

};

#endif // SYSTEMWATCHER_H
