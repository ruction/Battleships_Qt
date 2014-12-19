#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include "board.h"

#include <ship.h>
#include <QObject>
#include <QQmlListProperty>


class Battleships : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString playerName READ getPlayerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(quint16 shotsFired READ getShotsFired NOTIFY shotsFiredChanged)
    Q_PROPERTY(QQmlListProperty<Ship> availableShips READ getAvailableShips_Quick NOTIFY availableShipsChanged)
    Q_PROPERTY(Board* board READ board NOTIFY boardChanged)
    Q_PROPERTY(Board* enemyBoard READ enemyBoard NOTIFY enemyBoardChanged)
public:
    Battleships(QObject* parent = 0);
    ~Battleships();
    void setPlayerName(const QString& playerName);
    QString getPlayerName() const;
    Q_INVOKABLE void inkrementShots();
    quint16 getShotsFired() const;
    QList<Ship*> getAvailableShips() const;
    QQmlListProperty<Ship> getAvailableShips_Quick();
    Board *board();
    Board *enemyBoard();

private:
    QString playerName;             // Player name
    quint16 shotsFired;             // Counter for fired shots
    QList<Ship*> availableShips;    // List of ships, to be placed
    static int availableShips_count(QQmlListProperty<Ship> *property);
    static Ship *availableShips_at(QQmlListProperty<Ship> *property, int index);
signals:
    void playerNameChanged();
    void shotsFiredChanged();
    void availableShipsChanged();
    void boardChanged();
    void enemyBoardChanged();

protected:
    Board m_board;
    Board m_enemyBoard;
};

#endif // BATTLESHIPS_H
