#ifndef SERVER
#define SERVER

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPointer>
#include "network.h"
#include "battleships.h"


class Server: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ getIp WRITE setIp)
    Q_PROPERTY(Network *network READ getNetwork CONSTANT)
    Q_PROPERTY(Battleships *battleships WRITE setBattleships MEMBER battleships)
public:
    Server(QObject * parent = 0);
    Q_INVOKABLE void start(quint16 port);
    Q_INVOKABLE void close();
    void setIp(QString ip);
    QString getIp();
    Network* getNetwork();
    void setBattleships(Battleships *battleships);
private slots:
    void acceptConnection();
private:
    QTcpServer server;
    QPointer<QTcpSocket> socket;
    QString ip;
    Network network;
    Battleships *battleships;
};

#endif // SERVER

