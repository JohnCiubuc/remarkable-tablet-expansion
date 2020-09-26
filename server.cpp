#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QDebug>

#include "server.h"

Server::Server(QWidget *parent)
{

    initServer();

    //! [2]
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
    //! [2]
    //! [3]
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendFortune);
    //! [3]


}

void Server::sendPacket(QString s)
{
    if(clientConnection != nullptr)
    {
        clientConnection->write(s.toLocal8Bit().data());
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
    qDebug() << QString(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                           "Run the Fortune Client example now.")
                        .arg(ipAddress).arg(tcpServer->serverPort()));
//! [1]
}

//! [4]
void Server::sendFortune()
{
//! [5]
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_10);

    out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())].toLocal8Bit().data();
//! [4] //! [7]

    clientConnection = tcpServer->nextPendingConnection();
    QObject::connect(clientConnection, &QAbstractSocket::disconnected,
                     clientConnection, &QObject::deleteLater);
//! [7] //! [8]

    clientConnection->write(block);
//    clientConnection->disconnectFromHost();
//! [5]
}
//! [8]
