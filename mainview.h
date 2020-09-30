#pragma once

#include <QObject>
#include <QQuickView>
#include <QtQuick>
#include <QDebug>
#include <QProcess>

class MainView : public QQuickView
{
    Q_OBJECT
signals:
    void sendPacket(QString);
public:
    MainView();
    void connections();
public slots:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* me);
    void mousePressEvent(QMouseEvent* me);
    void mouseReleaseEvent(QMouseEvent* me);
    void tabletEvent(QTabletEvent* te);
    void touchEvent(QTouchEvent* te);
    void mousePosition(int x, int y);

    void stylusOnTablet(bool);
    void stylusPresence(bool);

    void batteryUpdate(int bat_amount, int bat_status);
private slots:
    void getVolume();
    void launchProcess(QString s);
private:
    QObject * vol_block ;
    QList<QObject *> bat_block ;
    QStringList bat_images;
};
