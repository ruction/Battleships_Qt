#include "client.h"
#include <QHostAddress>
#include <QDebug>


Client::Client(QObject* parent): QObject(parent)
{
    qDebug() << "Client initialized." << flush;
    network.setSocket(&socket, "client");
    connect(&socket, SIGNAL(connected()), this, SLOT(sendGameOffer()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(clientIsDisconnected()));
}

void Client::start(QString address, quint16 port)
{
    qDebug() << "Client connected to host" << address << "/" << port << flush;
    network.setBattleships(this->battleships);
    QHostAddress addr(address);
    socket.connectToHost(addr, port);
}

void Client::sendGameOffer()
{
    qDebug() << "Send game offer!" << flush;
    network.sendGameOffer();
}

void Client::clientIsDisconnected()
{
    emit gameDisconnected();
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

void Client::setBattleships(Battleships *battleships)
{
    this->battleships = battleships;
}
