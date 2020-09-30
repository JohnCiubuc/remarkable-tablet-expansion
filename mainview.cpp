#include "mainview.h"
#define db qDebug() << this <<


MainView::MainView()
{

    bat_images << "qrc:/images/battery/battery_discharging_020.png";
    bat_images << "qrc:/images/battery/battery_discharging_060.png";
    bat_images << "qrc:/images/battery/battery_discharging_080.png";
    bat_images << "qrc:/images/battery/battery_discharging_100.png";

}

void MainView::connections()
{
    QObject* home = this->rootObject();


    QObject::connect(home, SIGNAL(qmlSignal(int,int)),
                     this, SLOT(mousePosition(int,int)));
    QObject::connect(home, SIGNAL(launchSignal(QString)),
                     this, SLOT(launchProcess(QString)));
    vol_block = home->findChild<QObject*>("vol_block");
    bat_block << home->findChild<QObject*>("bat_percent");
    bat_block << home->findChild<QObject*>("bat_image");
//    qDebug() << (vol_block);
//    qDebug() << "Property value:" << QQmlProperty::read(vol_block, "x").toInt();

//    QQmlProperty::write(vol_block, "width", 200);

//    qDebug() << "Property value:" << object->property("someNumber").toInt();
//    object->setProperty("someNumber", 100);
}

void MainView::keyPressEvent(QKeyEvent* ke)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "mw" << ke->key() << "down";
    QQuickView::keyPressEvent(ke); // base class implementation
}

void MainView::mouseMoveEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mouseMoveEvent(me);
}

void MainView::mousePressEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mousePressEvent(me);
}

void MainView::mouseReleaseEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mouseReleaseEvent(me);
}

void MainView::tabletEvent(QTabletEvent* te)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << te;
}

void MainView::touchEvent(QTouchEvent* te)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << te;
}

void MainView::mousePosition(int x, int y)
{
//    qDebug() << x << ", " << y;
    if (y > 1820)
    {
        QQmlProperty::write(vol_block, "x", x);
    }
}

void MainView::stylusOnTablet(bool b)
{
    db "stylusOnTablet - " << b;
//    if(b)
//        this->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/pen-landed.qml"));
//    else
//        this->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/hex-grid.qml"));
}

void MainView::stylusPresence(bool b)
{
    db "stylusPresence - " << b;
//    if(b)
//        this->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/hex-grid.qml"));
//    else
//        this->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/prime.qml"));
    //    connections();
}

void MainView::batteryUpdate(int bat_amount, int bat_status)
{
    QQmlProperty::write(bat_block[0], "text", QString::number(bat_amount) + "%");
    QQmlProperty::write(bat_block[1], "source", bat_images.at(int(float(bat_amount)/25.)));
}

void MainView::getVolume()
{
    QProcess *p = new QProcess;
    connect(p, &QProcess::readAllStandardOutput, [=]()
    {
        qDebug() << p->readAll();
    });
    p->start("amixer", QStringList() << "-c"<< "1"<<"-M"<<"-D"<<"pulse"<<"get"<<"Master");
}

void MainView::launchProcess(QString s)
{

    QByteArray data;
    data.append("launch");
    data.append("==split==");
    data.append(s);
//        a.write(data);
    emit sendPacket(data);
}
