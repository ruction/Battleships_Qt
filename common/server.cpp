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
    qDebug() << "Server startet and listening..." << flush;
    server.listen(QHostAddress::Any, port);
}

void Server::acceptConnection()
{
    qDebug() << "Server accepted connection..." << flush;
    socket = server.nextPendingConnection();
    //here socket to network
}

void Server::close()
{
    qDebug() << "Server closed" << flush;
    server.close();
}

QString Server::getIp()
{
    return this->ip;
}

void Server::setIp(QString ip)
{
    this->ip = ip;
}
