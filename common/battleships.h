#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <ship.h>
#include <QObject>


class Battleships : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString playerName READ getPlayerName WRITE setPlayerName NOTIFY playerNameChanged)
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
};

#endif // BATTLESHIPS_H
