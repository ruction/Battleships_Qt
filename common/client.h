#ifndef NETWORK
#define NETWORK

#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include "network.h"


class Client: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Network *network READ getNetwork CONSTANT)
    Q_PROPERTY(Battleships *battleships WRITE setBattleships MEMBER battleships)
public:
    Client(QObject* parent = 0);
    Q_INVOKABLE void start(QString address, quint16 port);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE bool connected();
    Network* getNetwork();
    void setBattleships(Battleships *battleships);
private slots:
    void sendGameOffer();
private:
    QTcpSocket socket;
    Network network;
    Battleships *battleships;
};
#endif // CLIENT_H
