#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSet>


class Ship;

class Board : public QObject {
    Q_OBJECT
    Q_ENUMS(Direction)
    Q_PROPERTY(quint8 width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(quint8 height READ getHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QSet<quint16> shipPositions READ getShipPositions NOTIFY shipPositionsChanged)
    Q_PROPERTY(QSet<quint16> shots READ getShots NOTIFY shotsChanged)
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
    bool shoot(quint8 x, quint8 y);
    void print();
    void addShipPositions(const QSet<quint16> shipPositions);
    QSet<quint16> getShipPositions() const;
    quint16 indexFromCoordinates(const quint8 x, const quint8 y);
    QPoint coordinatesFromIndex(const quint16);
    QSet<quint16> getShots() const;
    Q_INVOKABLE bool shipOnPosition(quint8 x, quint8 y);
    Q_INVOKABLE bool shotOnPosition(quint8 x, quint8 y);
    Q_INVOKABLE void reset();

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
    void boardReset();

    void shipAdded(int x, int y);
};

#endif // BOARD_H
