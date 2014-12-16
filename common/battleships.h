#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <ship.h>
#include <QObject>


class Battleships : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString playerName READ getPlayerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(quint16 shotsFired READ getShotsFired NOTIFY shotsFiredChanged)
    Q_PROPERTY(QList<Ship*> availableShips READ getAvailableShips NOTIFY availableShipsChanged)
public:
    Battleships(QObject* parent = 0);
    ~Battleships();
    void setPlayerName(const QString& playerName);
    QString getPlayerName() const;
    void inkrementShots();
    quint16 getShotsFired() const;
    QList<Ship*> getAvailableShips() const;
private:
    QString playerName;             // Player name
    quint16 shotsFired;             // Counter for fired shots
    QList<Ship*> availableShips;    // List of ships, to be placed
signals:
    void playerNameChanged();
    void shotsFiredChanged();
    void availableShipsChanged();
};

#endif // BATTLESHIPS_H
