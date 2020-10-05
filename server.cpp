#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QDebug>

#include "server.h"

Server::Server(QWidget *parent)
{

    initServer();
    qRegisterMetaType<packet>("packet");
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendFortune);

}

void Server::sendPacket(packet s)
{
    if(clientConnection != nullptr)
    {

        char buffTemp[sizeof(s)];

        memcpy(buffTemp, &s, sizeof(s));

        clientConnection->write(QByteArray::fromRawData(buffTemp,sizeof(s)));
    }
}

void Server::initServer()
{
//! [0] //! [1]
    tcpServer = new QTcpServer();
    if (!tcpServer->listen(QHostAddress::Any, 13337))
    {
        qDebug() << "Failed tos tart server";
        return;
    }
//! [0]
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << QString("The server is running on IP: %1, port: %2")
             .arg(ipAddress).arg(tcpServer->serverPort());
//! [1]
}

//! [4]
void Server::sendFortune()
{
//! [5]
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_10);

//! [4] //! [7]

    clientConnection = tcpServer->nextPendingConnection();
    QObject::connect(clientConnection, &QAbstractSocket::disconnected,
                     clientConnection, &QObject::deleteLater);

    QObject::connect(clientConnection, &QAbstractSocket::readyRead,
                     this, [=]()
    {
        qDebug() << "Ready Rad";
        packet p;
        char buffer[258];
        auto numRead  = clientConnection->read(buffer, 258);
        memcpy(&p, buffer, sizeof(buffer));

        // do whatever with array
        qDebug() << p.event;
        qDebug() << p.message;
    });
//    forever
//    {
//        packet p;
//        char buffer[258];

////        auto const data = read(sizeof(Information));
//        auto numRead  = clientConnection->read(buffer, 258);
//        memcpy(&p, buffer, sizeof(buffer));

//        // do whatever with array
//        qDebug() << p.event;
//        qDebug() << p.message;

////        numReadTotal += numRead;
//        if (numRead == 0 && !clientConnection->waitForReadyRead())
//            break;
//    }
//! [7] //! [8]

//    clientConnection->write(block);
//    clientConnection->disconnectFromHost();
//! [5]
}
//! [8]
