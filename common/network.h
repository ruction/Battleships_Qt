#ifndef NETWORKCLIENT
#define NETWORKCLIENT

#include <QtNetwork>
#include <QTcpSocket>


class Network
{
public:
    Network();
    void setSocket(QTcpSocket *socket);
private:
    QTcpSocket *socket;

};

#endif // NETWORKCLIENT
