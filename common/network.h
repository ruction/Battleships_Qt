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
    Q_INVOKABLE void sendData(QString message);
private slots:
    void readData();
private:
    QTcpSocket *socket;
    QTextStream stream;
    QString kind;
    void sendGameOffer();
};

#endif // NETWORKCLIENT
