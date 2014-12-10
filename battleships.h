#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <ship.h>
#include <QString>


class Battleships {
public:
    Battleships();
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
};

#endif // BATTLESHIPS_H
