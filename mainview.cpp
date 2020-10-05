#include "mainview.h"
#define db qDebug() << this <<


MainView::MainView()
{
    bat_images << "qrc:/images/battery/battery_discharging_020.png";
    bat_images << "qrc:/images/battery/battery_discharging_060.png";
    bat_images << "qrc:/images/battery/battery_discharging_080.png";
    bat_images << "qrc:/images/battery/battery_discharging_100.png";
    bat_images << "qrc:/images/battery/battery_discharging_100.png";
    qRegisterMetaType<packet>("packet");
}

void MainView::connections()
{
    QObject* home = this->rootObject();


    QObject::connect(home, SIGNAL(qmlSignal(int,int)),
                     this, SLOT(mousePosition(int,int)));
    QObject::connect(home, SIGNAL(launchSignal(int, QString)),
                     this, SLOT(launchProcess(int, QString)));
    vol_block = home->findChild<QObject*>("vol_block");
    bat_block << home->findChild<QObject*>("bat_percent");
    bat_block << home->findChild<QObject*>("bat_image");
    mpv_block = home->findChild<QObject*>("mpv_block");
//    qDebug() << (vol_block);
//    qDebug() << "Property value:" << QQmlProperty::read(vol_block, "x").toInt();

//    QQmlProperty::write(vol_block, "width", 200);

//    qDebug() << "Property value:" << object->property("someNumber").toInt();
//    object->setProperty("someNumber", 100);
}

void MainView::mousePosition(int x, int y)
{
//    qDebug() << x << ", " << y;
    if(!bDebugMPVView)
    {
        if (y > 1820)
        {
            QQmlProperty::write(vol_block, "x", x);
        }
    }
    if(bDebugMPVView)
    {
        if( x < 180)
        {
            QQmlProperty::write(mpv_block, "y", y);
            float py = y / 1872. * 100;
            db QString::number(py, 'f', 0);
//            db y / 1872. * 100;
            packet p;
            p.event = 3;
            QString s = QString::number(py, 'f', 0);
            if (sDebugMPCCache == s) return;
            sDebugMPCCache = s;
            strcpy(p.message, s.toLocal8Bit());
            db "send";
            emit sendPacket(p);
            //        a.write(data);
//            emit sendPacket(p);
        }
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

void MainView::launchProcess(int event, QString s)
{
    db "start";
    // Youtube launcher, using it to swap MPV views for now
    if(event == 1)
    {
        bDebugMPVView = !bDebugMPVView;
        bDebugMPVView ? loadQML("mpv_controller") : loadQML("prime");

        db "end event";
        return;
    }

    db "post";
    s.append('\0');

    QByteArray data;
    data.append("launch");
    data.append("==split==");
    data.append(s);
    packet p;
    p.event = event;
    strcpy(p.message, s.toLocal8Bit());
//        a.write(data);
    emit sendPacket(p);
}

void MainView::loadQML(QString qml_file)
{
    QTimer::singleShot( 500, [=]()
    {
        this->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/" + qml_file + ".qml"));
        connections();
    });
}
