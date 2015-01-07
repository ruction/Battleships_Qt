#include "network.h"
#include <QDebug>
#include <QTcpSocket>


Network::Network(QObject* parent): QObject(parent)
{
    qDebug() << "Network initialized." << flush;
}

void Network::setSocket(QTcpSocket *socket, QString kind)
{
    this->socket = socket;
    this->kind = kind;
    qDebug() << "Socket set." << flush;
    stream.setDevice(this->socket);
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Network::readData()
{
    qDebug() << "readData!!";
    while(true) {
        QString line = stream.readLine();
        if (line.isNull()) {
            break;
        }
        qDebug() << "message line: " << line;
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8(), &error);
        QJsonObject json = doc.object();
        QString type = json.value("type").toString();
        QJsonObject options = json.value("options").toObject();
        qDebug() << error.errorString();

        if (type == "GAME_OFFER") {
            qDebug() << "GAME_OFFER sent!!";
            receivedGameOffer(options);
        } else if (type == "SHOT") {
            qDebug() << "SHOT sent!!";
            receivedShot(options);
        } else if (type == "SHOT_REPLY") {
            qDebug() << "SHOT_REPLY sent!!";
            receivedShotReply(options);
        } else if (type == "GAME_OFFER_REPLY") {
            qDebug() << "GAME_OFFER_REPLY sent!!";
            receivedGameOfferReply(options);
        } else if (type == "FINISHED") {
            qDebug() << "FINISHED sent!!";
            receivedFinished(options);
        } else {
            qDebug() << "Invalid message recieved";
        }
    }
}

void Network::receivedGameOffer(QJsonObject options)
{

}

void Network::receivedShot(QJsonObject options)
{

}

void Network::receivedShotReply(QJsonObject options)
{

}

void Network::receivedGameOfferReply(QJsonObject options)
{

}

void Network::receivedFinished(QJsonObject options)
{

}

void Network::sendGameOffer()
{
    sendData("gameOffer");
}

void Network::sendShot()
{

}

void Network::sendShotReply()
{

}

void Network::sendGameOfferReply()
{

}

void Network::sendFinished()
{

}

void Network::sendData(QString message)
{
    stream << "Testnachricht!!! :)" << '\n' << flush;
}







