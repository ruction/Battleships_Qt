#ifndef NETWORKCLIENT
#define NETWORKCLIENT

#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <battleships.h>


class Network: public QObject
{
    Q_OBJECT
public:
    Network(QObject* parent = 0);
    void setSocket(QTcpSocket *socket, QString kind);
    Q_INVOKABLE void sendGameOffer();
    Q_INVOKABLE void sendShot(QString x, QString y);
    Q_INVOKABLE void sendShotReply(QString result, QString ship, QString fields);
    Q_INVOKABLE void sendGameOfferReply(QString success);
    Q_INVOKABLE void sendFinished(QString reason);
    void setBattleships(Battleships* battleships);
private slots:
    void readData();
private:
    QTcpSocket *socket;
    QTextStream stream;
    QString kind;
    void receivedGameOffer(QJsonObject options);
    void receivedShot(QJsonObject options);
    void receivedShotReply(QJsonObject options);
    void receivedGameOfferReply(QJsonObject options);
    void receivedFinished(QJsonObject options);
    void sendData(QString message);
    Battleships *battleships;
};

#endif // NETWORKCLIENT
