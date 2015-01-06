#include "server.h"
#include <iostream>
#include <QDebug>
using namespace std;


Server::Server(QObject* parent): QObject(parent)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            this->setIp(address.toString());
    }
    qDebug() << "Server initialized." << flush;
    connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));
    server.listen(QHostAddress::Any, 8888);
}

Server::~Server()
{
    server.close();
}

QString Server::getMessage()
{
    return this->message;
}

QString Server::getIp()
{
    return this->ip;
}

void Server::setIp(QString ip)
{
    this->ip = ip;
}

void Server::setMessage(QString message)
{
    this->message = message;
}

void Server::acceptConnection()
{
    client = server.nextPendingConnection();

    connect(client, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void Server::startRead()
{
    char buffer[2048] = {0};
    client->read(buffer, client->bytesAvailable());
    cout << "server received: " << buffer << flush << endl;
    this->message = buffer;
    emit messageChanged();
    //    client->close();
}

void Server::writeMessage()
{
    client->write("abc", 4);
}
