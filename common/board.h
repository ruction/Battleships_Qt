#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSet>
#include <QQmlListProperty>


class Ship;

class Board : public QObject {
    Q_OBJECT
    Q_ENUMS(Direction)
    Q_PROPERTY(quint8 width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(quint8 height READ getHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QSet<quint16> shipPositions READ getShipPositions NOTIFY shipPositionsChanged)
    Q_PROPERTY(QSet<quint16> shipsPositionsMulti READ getShipsPositionsMulti NOTIFY shipsPositionsMultiChanged)
    Q_PROPERTY(QSet<quint16> shots READ getShots NOTIFY shotsChanged)
    Q_PROPERTY(QQmlListProperty<Ship> ships READ getShips_Quick NOTIFY ShipsChanged)
public:
    /*
     * Direction enum
     */
    enum Direction {
        NORTH, EAST, SOUTH, WEST, WRONG
    };

    static Direction directionFromString(const QString direction);
    static quint8 randomValue(const quint8 max);

    Board(QObject* parent = 0);
    Board(quint8 width, quint8 height);
    void setWidth(const quint8& width);
    quint8 getWidth() const;
    void setHeight(const quint8& height);
    quint8 getHeight() const;
    Q_INVOKABLE bool place(Ship *ship, quint8 x, quint8 y, Direction d);
    Q_INVOKABLE bool shoot(quint8 x, quint8 y);
    void print();
    void addShipPositions(const QSet<quint16> shipPositions);
    QSet<quint16> getShipPositions() const;
    QSet<quint16> getShipsPositionsMulti();
    void addShipsPositionsMulti(quint16 index);
    quint16 indexFromCoordinates(const quint8 x, const quint8 y);
    QPoint coordinatesFromIndex(const quint16);
    QSet<quint16> getShots() const;
    Q_INVOKABLE bool shipDamaged(quint8 x, quint8 y);
    Q_INVOKABLE bool shipDamagedMulti(quint8 x, quint8 y);
    Q_INVOKABLE bool shipDestroyed(Ship *ship);
    Q_INVOKABLE Ship *shipFromCoordinates(quint8 x, quint8 y);
    Q_INVOKABLE bool allShipsDestroyed();
    Q_INVOKABLE bool shipOnPosition(quint8 x, quint8 y);
    Q_INVOKABLE bool shipOnPositionMulti(quint8 x, quint8 y);
    Q_INVOKABLE bool shotOnPosition(quint8 x, quint8 y);
    Q_INVOKABLE void reset();
    QList<Ship *> getShips() const;
    QQmlListProperty<Ship> getShips_Quick();
    void setShips(const QList<Ship *> &value);
private:
    QList<Ship*> ships;             // List of ships
    quint8 height;                  // Board height
    quint8 width;                   // Board width
    QSet<quint16> shipPositions;    // Set with all indexes of every ship
    QSet<quint16> shipsPositionsMulti;     // ship positions for multiplayer
    QSet<quint16> shots;            // Set with all shots
    static int ships_count(QQmlListProperty<Ship> *property);
    static Ship *ships_at(QQmlListProperty<Ship> *property, int index);
signals:
    void widthChanged();
    void heightChanged();
    void shipPositionsChanged();
    void shipsPositionsMultiChanged();
    void shotsChanged();
    void ShipsChanged();
    void boardReset();

    void shipAdded(int x, int y);
    void shotAdded(int x, int y);
    void gameFinished();
};

#endif // BOARD_H
