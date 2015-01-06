#include "network.h"
#include <QDebug>
#include <QTcpSocket>


Network::Network()
{
    qDebug() << "Network initialized." << flush;
}

void Network::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
    qDebug() << "Socket set." << flush;
}




