#pragma once

#include <QObject>
#include <QQuickView>
#include <QtQuick>
#include <QDebug>
#include <QProcess>
#include <QTimer>

#ifndef __PACKET
#define __PACKET
struct packet
{
    unsigned short event;
    char message[256];
};
#endif
class MainView : public QQuickView
{
    Q_OBJECT
signals:
    void sendPacket(packet);
public:
    MainView();
    void connections();
public slots:
    void mousePosition(int x, int y);

    void stylusOnTablet(bool);
    void stylusPresence(bool);

    void batteryUpdate(int bat_amount, int bat_status);
private slots:
    void getVolume();
    void launchProcess(int event, QString s);
    void loadQML(QString qml_file);
private:
    QObject * vol_block ;
    QObject * mpv_block ;
    QList<QObject *> bat_block ;
    QStringList bat_images;

    bool bDebugMPVView = false;
    QString sDebugMPCCache;
};
