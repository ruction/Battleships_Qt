#include "client.h"
#include <QHostAddress>
#include <iostream>
#include <QDebug>
using namespace std;


Client::Client(QObject* parent): QObject(parent)
{
    qDebug() << "Client initialized." << flush;
    connect(&client, SIGNAL(connected()),
    this, SLOT(startTransfer()) );
}

Client::~Client()
{
    client.close();
}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

void Client::startTransfer()
{
    client.write("Hi, i am the client! :)", 24);
}

void Client::readData()
{
    char buffer[1024] = {0};
    client.read(buffer, client.bytesAvailable());
    cout << "client received: " << buffer << endl;
//    client->close();
}

void Client::writeMessage()
{
    client.write("abc", 4);
}
