#ifndef SERVER
#define SERVER

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ getIp WRITE setIp)
public:
    Server(QObject * parent = 0);
    Q_INVOKABLE void start(quint16 port);
    Q_INVOKABLE void close();
    void setIp(QString ip);
    QString getIp();
private slots:
    void acceptConnection();
private:
    QTcpServer server;
    QTcpSocket* socket;
    QString ip;
};

#endif // SERVER

