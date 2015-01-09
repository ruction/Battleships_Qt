#include "network.h"
#include <QDebug>
#include <QTcpSocket>


Network::Network(QObject* parent)
    : QObject(parent)
    , socket(NULL)
{
    qDebug() << "Network initialized." << flush;
}

void Network::setSocket(QTcpSocket *socket, QString kind)
{
    if (this->socket) {
        disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(readData()));
    }

    this->socket = socket;
    this->kind = kind;
    qDebug() << "Socket set." << flush;
    stream.setDevice(this->socket);

    if (this->socket) {
        connect(this->socket, SIGNAL(readyRead()), this, SLOT(readData()));
    }
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

    if (battleships->board()->getHeight() == boardHeight && battleships->board()->getWidth() == boardWidth) {
        battleships->setEnemyName(playerName);
        emit startGame();
        sendGameOfferReply(true);
    } else {
        sendGameOfferReply(false);
        socket->disconnectFromHost();
    }
}

void Network::receivedShot(QJsonObject options)
{
    quint8 x = options.value("x").toInt();
    quint8 y = options.value("y").toInt();

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
                if(battleships->board()->allShipsDestroyed()) {
                    qDebug() << "allShipsDestroyed!!";
                    sendFinished("won");
                    emit battleships->enemyBoard()->gameFinished();
                }
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
    QString ship = options.value("ship").toString();
    // shipname only set if ship sunk

    // Only set if ship is sunk otherwise its null

    if (result == "hit") {
        qDebug() << "hit!! received.";
        quint16 index = battleships->enemyBoard()->indexFromCoordinates(this->x, this->y);
        battleships->enemyBoard()->addShipsPositionsMulti(index);
    } else if (result == "sunk") {
        qDebug() << "sunk!! received.";
        quint16 index = battleships->enemyBoard()->indexFromCoordinates(this->x, this->y);
        battleships->enemyBoard()->addShipsPositionsMulti(index);
        emit sunk(ship);
    } else if (result == "miss") {
    }
}

void Network::receivedGameOfferReply(QJsonObject options)
{
    QString playerName = options.value("player_name").toString();
    bool success = options.value("success").toBool();

    if (success) {
        battleships->setEnemyName(playerName);
        emit startGame();
    } else {
        emit gameRefused();
    }
}

void Network::receivedFinished(QJsonObject options)
{
    // { "type": "FINISHED", "options": { "reason": "" } } won, quit or error
    QString reason = options.value("reason").toString();

    qDebug() << "finished received";
    if (reason == "won") {
        emit battleships->enemyBoard()->gameFinished();
    } else if (reason == "quit") {
        emit enemyQuitGame();
    } else if (reason == "error") {

    }
}

void Network::sendGameOffer()
{
    // { "type": "GAME_OFFER", "options": { "player_name": "example name", "board_size_x": 10, "board_size_y": 10, "ships_preset": "default" } }
    QJsonObject options;
    options.insert("player_name", battleships->getPlayerName());
    options.insert("board_size_x", battleships->board()->getWidth());
    options.insert("board_size_y", battleships->board()->getHeight());
    options.insert("ships_preset", "default");

    sendData("GAME_OFFER", options);
}

void Network::sendShot(quint8 x, quint8 y)
{
    // { "type": "SHOT", "options": { "x": 5, "y": 5 } }
    this->x = x;
    this->y = y;
    QJsonObject options;
    options.insert("x", x);
    options.insert("y", y);

    sendData("SHOT", options);
}

void Network::sendShotReply(QString result, QString ship, QString fields)
{
    // { "type": "SHOT_REPLY", "options": { "result": "", "ship": "", "fields": [ { "x": 0, "y": 0 } ] } }
    QJsonObject options;
    options.insert("result", result);
    options.insert("ship", ship);
    options.insert("fields", fields);

    sendData("SHOT_REPLY", options);
}

void Network::sendGameOfferReply(bool success)
{
    // { "type": "GAME_OFFER_REPLY", "options": { "player_name": "example name", "success ": true } }
    QJsonObject options;
    options.insert("player_name", battleships->getPlayerName());
    options.insert("success", success);

    sendData("GAME_OFFER_REPLY", options);
}

void Network::sendFinished(QString reason)
{
    // { "type": "FINISHED", "options": { "reason": "" } }
    QJsonObject options;
    options.insert("reason", reason);
    qDebug() << "finished send.";

    sendData("FINISHED", options);
}

void Network::setBattleships(Battleships *battleships)
{
    this->battleships = battleships;
}

void Network::sendData(QString type, QJsonObject options)
{
    QJsonObject root;
    root.insert("type", type);
    root.insert("options", options);
    QJsonDocument document(root);

    stream << document.toJson(QJsonDocument::Compact) << '\n' << flush;
}







