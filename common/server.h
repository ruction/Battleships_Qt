#ifndef SERVER
#define SERVER

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ getMessage WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString ip READ getIp WRITE setIp)
public:
    Server(QObject * parent = 0);
    Q_INVOKABLE void writeMessage();
    QString getMessage();
    QString getIp();
    void setIp(QString ip);
    void setMessage(QString message);
    ~Server();
public slots:
    void acceptConnection();
    void startRead();
private:
    QTcpServer server;
    QTcpSocket* client;
    QString message;
    QString ip;
signals:
    void messageChanged();

};

#endif // SERVER

