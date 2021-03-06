#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

#ifndef __PACKET
#define __PACKET
struct packet
{
    unsigned short event;
    char message[256];
};
#endif

//! [0]
class Server: public QObject
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
public slots:
    void sendPacket(packet);
private slots:
    void sendFortune();

private:
    void initServer();

    QTcpServer *tcpServer = nullptr;
    QVector<QString> fortunes;
    QTcpSocket *clientConnection = nullptr;
};
//! [0]

#endif // SERVER_H
