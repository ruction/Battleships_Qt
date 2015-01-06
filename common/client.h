#ifndef NETWORK
#define NETWORK

#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>

class Client: public QObject
{
public:
    Client(QObject* parent = 0);
    Q_INVOKABLE void connect(QString address, quint16 port);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE bool connected();
private:
    QTcpSocket client;
};
#endif // CLIENT_H
