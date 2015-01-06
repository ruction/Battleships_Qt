#ifndef NETWORK
#define NETWORK

#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include "network.h"


class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    Q_INVOKABLE void start(QString address, quint16 port);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE bool connected();
private slots:
    void saveSocket();
private:
    QTcpSocket socket;
    Network network;
};
#endif // CLIENT_H
