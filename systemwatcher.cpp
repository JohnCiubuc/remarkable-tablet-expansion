#include "systemwatcher.h"

SystemWatcher::SystemWatcher(QObject *parent) : QObject(parent)
{
    QTimer * batUpdates = new QTimer;
    connect(batUpdates, &QTimer::timeout, this, &SystemWatcher::updateBattery);
    batUpdates->start(1000);
    cat = new QProcess;
    connect(cat, &QProcess::readyReadStandardOutput, this, [=]()
    {
        auto all = cat->readAll();
        all.chop(1);
        // 0 - Normal
        // 1 - Charging
        emit batteryUpdate(all.toInt(), 0);
    });

}

void SystemWatcher::updateBattery()
{
    cat->start("cat", QStringList() << "/sys/class/power_supply/bq27441-0/capacity");
}
