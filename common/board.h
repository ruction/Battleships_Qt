#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSet>

/*
 * Direction enum
 */
enum Direction {
    NORTH, EAST, SOUTH, WEST, WRONG
};

Direction directionFromString(const QString direction);
quint8 randomValue(const quint8 max);

class Ship;

class Board : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint8 width READ getWidth NOTIFY widthChanged)
    Q_PROPERTY(quint8 height READ getHeight NOTIFY heightChanged)
    Q_PROPERTY(QSet<quint16> shipPositions READ getShipPositions NOTIFY shipPositionsChanged)
    Q_PROPERTY(QSet<quint16> shots READ getShots NOTIFY shotsChanged)
public:
    Board(QObject* parent = 0);
    Board(quint8 width, quint8 height);
    quint8 getWidth() const;
    quint8 getHeight() const;
    bool place(Ship *ship, quint8 x, quint8 y, Direction d);
    bool shoot(quint8 x, quint8 y);
    void print();
    void addShipPositions(const QSet<quint16> shipPositions);
    QSet<quint16> getShipPositions() const;
    quint16 indexFromCoordinates(const quint8 x, const quint8 y);
    QSet<quint16> getShots() const;
private:
    quint8 height;                  // Board height
    quint8 width;                   // Board width
    QSet<quint16> shipPositions;    // Set with all indexes of every ship
    QSet<quint16> shots;            // Set with all shots
signals:
    void widthChanged();
    void heightChanged();
    void shipPositionsChanged();
    void shotsChanged();
};

#endif // BOARD_H
