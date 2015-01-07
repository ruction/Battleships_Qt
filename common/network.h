#ifndef NETWORKCLIENT
#define NETWORKCLIENT

#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>


class Network: public QObject
{
    Q_OBJECT
public:
    Network(QObject* parent = 0);
    void setSocket(QTcpSocket *socket, QString message);
    Q_INVOKABLE void sendGameOffer();
    Q_INVOKABLE void sendShot();
    Q_INVOKABLE void sendShotReply();
    Q_INVOKABLE void sendGameOfferReply();
    Q_INVOKABLE void sendFinished();
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
};

#endif // NETWORKCLIENT
