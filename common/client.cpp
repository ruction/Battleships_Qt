#include "client.h"
#include <QHostAddress>
#include <QDebug>


Client::Client(QObject* parent): QObject(parent)
{
    qDebug() << "Client initialized." << flush;
    network.setSocket(&socket, "client");
    connect(&socket, SIGNAL(connected()), this, SLOT(saveSocket()));
}

void Client::start(QString address, quint16 port)
{
    qDebug() << "Client connected to host" << address << "/" << port << flush;
    QHostAddress addr(address);
    socket.connectToHost(addr, port);
}

void Client::saveSocket()
{
    qDebug() << "Client socket available!" << flush;
}

void Client::disconnect()
{
    qDebug() << "Client closed" << flush;
    socket.close();
}

bool Client::connected()
{
    return true;
}

Network* Client::getNetwork()
{
    return &network;
}
