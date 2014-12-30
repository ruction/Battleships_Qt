#ifndef NETWORK
#define NETWORK

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    Q_INVOKABLE void start(QString address, quint16 port);
    Q_INVOKABLE void writeMessage();
    void readData();
public slots:
    void startTransfer();
private:
    QTcpSocket client;
};
#endif // CLIENT_H
