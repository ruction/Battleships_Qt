#include "network.h"
#include <QDebug>
#include <QTcpSocket>


Network::Network(QObject* parent): QObject(parent)
{
    qDebug() << "Network initialized." << flush;
}

void Network::setSocket(QTcpSocket *socket, QString kind, Battleships* battleships)
{
    this->socket = socket;
    this->kind = kind;
    this->battleships = battleships;
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
        QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
        QJsonObject json = doc.object();
        QString type = json.value("type").toString();
        QJsonObject options = json.value("options").toObject();

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
    quint16 boardWidth = options.value("board_size_x").toInt();
    quint16 boardHeight = options.value("board_size_y").toInt();
    QString shipsPreset = options.value("ships_preset").toString();
    QString playerName = options.value("player_name").toString();
    qDebug() << boardWidth;
    qDebug() << boardHeight;
    qDebug() << shipsPreset;
    qDebug() << playerName;

    if (this->kind == "server") {

    } else {

    }

}

void Network::receivedShot(QJsonObject options)
{
    quint16 x = options.value("x").toInt();
    quint16 y = options.value("y").toInt();
    qDebug() << x;
    qDebug() << y;


    if (battleships->board()->shoot(x, y)) {
        QString result;
        QSet<quint16> fields;

        if (battleships->board()->shipDamaged(x, y)) {
            qDebug() << "hit";
            result = "hit";
            if (battleships->board()->shipDestroyed(battleships->board()->shipFromCoordinates(x,y))) {
                qDebug() << "sunk";
                result = "sunk";
                fields = battleships->board()->shipFromCoordinates(x,y)->getPositions(); // maybe wrong format
                sendShotReply(result, battleships->board()->shipFromCoordinates(x,y)->getName(), "coming soon");
                return;
            }
        } else {
            qDebug() << "miss";
            result = "miss";
        }
        sendShotReply(result, "", "");

    }
}

void Network::receivedShotReply(QJsonObject options)
{
    // hit, sunk or miss
    QString result = options.value("result").toString();
    // shipname only set if ship sunk
    QString ship = options.value("ship").toString();
    // Only set if ship is sunk otherwise its null
    QJsonObject fields = options.value("fields").toObject();
    qDebug() << result;
    qDebug() << ship;
    qDebug() << fields;
}

void Network::receivedGameOfferReply(QJsonObject options)
{
    QString playerName = options.value("player_name").toString();
    QString success = options.value("success").toString();
    qDebug() << playerName;
    qDebug() << success;
}

void Network::receivedFinished(QJsonObject options)
{
    // won, quit or error
    QString reason = options.value("reason").toString();
    qDebug() << reason;
}

void Network::sendGameOffer()
{
    // { "type": "GAME_OFFER", "options": { "player_name": "example name", "board_size_x": 10, "board_size_y": 10, "ships_preset": "default" } }
    QString message;
    QString playerName;
    quint16 boardWidth;
    quint16 boardHeight;
    QString shipsPreset;

    message = "{ \"type\": \"GAME_OFFER\", \"options\": { \"player_name\":" + playerName
            +  ", \"board_size_x\":" +  boardWidth + ", \"board_size_y\":" + boardHeight
            + ", \"ships_preset\":" + shipsPreset + "} }";

    sendData(message);
}

void Network::sendShot()
{
    // { "type": "SHOT", "options": { "x": 5, "y": 5 } }
}

void Network::sendShotReply(QString result, QString ship, QString fields)
{
    // { "type": "SHOT_REPLY", "options": { "result": "", "ship": "", "fields": [ { "x": 0, "y": 0 } ] } }
    QString message;

    message = "{ \"type\": \"SHOT_REPLY\", \"options\": { \"result\":" + result
            + ", \"ship\":" + ship + ", \"fields\":" + fields + "} }";

    sendData(message);
}

void Network::sendGameOfferReply(QString success)
{
    // { "type": "GAME_OFFER_REPLY", "options": { "player_name": "example name", "success ": true } }
    QString message;

    message = "{ \"type\": \"GAME_OFFER_REPLY\", \"options\": { \"player_name\":" + battleships->getPlayerName()
            +  ", \"success\":" +  success + "} }";

    sendData(message);

}

void Network::sendFinished()
{
    // { "type": "FINISHED", "options": { "reason": "" } }
}

void Network::sendData(QString message)
{
    stream << message << '\n' << flush;
}







