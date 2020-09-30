#include <QtQuick>
#include <QThread>
#include <QObject>
//#include <QtGui>
//#include <QtPlugin>
#include "mainview.h"
#include "handler.h"
#include "devinput.h"


#include <QtPlugin>
#include "server.h"
#include "systemwatcher.h"
Q_IMPORT_PLUGIN(QsgEpaperPlugin)

int main(int argc, char *argv[])
{

    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");

    system("/usr/bin/button-capture &");

    QGuiApplication app(argc, argv);


//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QDir(DEPLOYMENT_PATH).filePath("qml/prime.qml"));
//    if (engine.rootObjects().isEmpty())
//        return -1;


//    return app.exec();

    MainView * view = new MainView;

    srand(time(NULL));

    view->rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view->engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view->setSource(QDir(DEPLOYMENT_PATH).filePath("qml/prime.qml"));

//    Options options(&view, &app);

    view->connections();
    view->show();




    QThread* thread = new QThread;
    devinput * worker = new devinput();
    worker->moveToThread(thread);
//    QObject::connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    QObject::connect(thread, &QThread::started, worker, &devinput::process);
    QObject::connect(worker, &devinput::finished, thread, &QThread::quit);
    QObject::connect(worker, &devinput::finished, worker, &devinput::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);


    QObject::connect(worker, &devinput::stylusOnTablet, view, &MainView::stylusOnTablet);
    QObject::connect(worker, &devinput::stylusPresence, view, &MainView::stylusPresence);
    thread->start();

    Server * s = new Server;
    QObject::connect(view, &MainView::sendPacket, s, &Server::sendPacket);

    SystemWatcher * sWatcher = new SystemWatcher;
    QObject::connect(sWatcher, &SystemWatcher::batteryUpdate, view, &MainView::batteryUpdate);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QDir(DEPLOYMENT_PATH).filePath("qml/prime.qml"));
//    if (engine.rootObjects().isEmpty())
//        return -1;


    return app.exec();
}
