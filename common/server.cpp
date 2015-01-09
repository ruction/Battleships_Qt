#include "server.h"
#include <QDebug>


Server::Server(QObject* parent): QObject(parent)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            this->setIp(address.toString());
    }
    qDebug() << "Server initialized." << flush;
    connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));
}

void Server::start(quint16 port)
{
    network.setBattleships(this->battleships);
    qDebug() << "Server startet and listening..." << flush;
    server.listen(QHostAddress::Any, port);
}

void Server::acceptConnection()
{
    qDebug() << "Server accepted connection..." << flush;

    QTcpSocket *client = server.nextPendingConnection();
    if (this->socket) {
        qDebug() << "Disconnected second client.";
        client->disconnectFromHost();
    } else {
        this->socket = client;
        this->network.setSocket(this->socket, "server");
        connect(this->socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    }
}

void Server::clientDisconnected()
{
    network.setSocket(NULL, QString());

    this->socket->deleteLater();
}

void Server::disconnect()
{
    qDebug() << "Server closed" << flush;
    if (this->socket)
        this->socket->disconnectFromHost();
}

QString Server::getIp()
{
    return this->ip;
}

void Server::setIp(QString ip)
{
    this->ip = ip;
}

Network* Server::getNetwork()
{
    return &network;
}

void Server::setBattleships(Battleships *battleships)
{
    this->battleships = battleships;
}
