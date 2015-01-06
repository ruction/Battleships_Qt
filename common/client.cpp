#include "client.h"
#include <QHostAddress>
#include <QDebug>


Client::Client(QObject* parent): QObject(parent)
{
    qDebug() << "Client initialized." << flush;
}

void Client::connect(QString address, quint16 port)
{
    qDebug() << "Client connect to host" << address << "/" << port << flush;
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

void Client::disconnect()
{
    qDebug() << "Client closed" << flush;
    client.close();
}

bool Client::connected()
{
    return true;
}
