#include "board.h"
#include "ship.h"
#include <QTextStream>
#include <QtGlobal>
#include <QPoint>
#include <QDebug>

/*
 * Converts a overloaded string into a Direction enum value
 * and returns it, otherwise WRONG is returned.
 */
Board::Direction Board::directionFromString(const QString direction) {
    if (direction == "NORTH")
        return NORTH;
    else if (direction == "EAST")
        return EAST;
    else if (direction == "SOUTH")
        return SOUTH;
    else if (direction == "WEST")
        return WEST;
    else
        return WRONG;
}

/*
 * Returns a random value between 0 and
 * the overloaded parameter max
 */
quint8 Board::randomValue(const quint8 max) {
    quint8 min = 0;
    return qrand() % ((max + 1) - min) + min;
}



/*
 *
 */
Board::Board(QObject *parent)
    :QObject(parent)
{}


/*
 * Constructor with board initialisation of
 * width and height
 */
Board::Board(quint8 width, quint8 height)
    :height(height), width(width)
{
}

/*
 * Set board width
 */
void Board::setWidth(const quint8& width) {
    if (this->width != width) {
        this->width = width;
        emit widthChanged();
    }
}

/*
 * Returns board width
 */
quint8 Board::getWidth() const {
    return this->width;
}

/*
 * Returns board height
 */
void Board::setHeight(const quint8& height) {
    if (this->height != height) {
        this->height = height;
        emit heightChanged();
    }
}

/*
 * Returns board height
 */
quint8 Board::getHeight() const {
    return this->height;
}

/*
 * Place a ship
 */
bool Board::place(Ship *ship, quint8 x, quint8 y, Direction d) {
    if (!ships.contains(ship)) {
        qDebug() << "Ship does not belong to this board";
        return false;
    }

    QSet<quint16> positions;            // placeholder QSet for calculated positions

    // Loop for the overloaded ship length
    for (quint8 i = 0; i < ship->getLength(); ++i) {
        // Calculates the index of the ship inital coordinates
        quint16 index = indexFromCoordinates(x,y);
        /*
         * If calculated index already in use or the index is out of board dimensions,
         * return false and discart the placeholder QSet positions
         * The is is not placed until all indexes are ok
         */
        if (shipPositions.contains(index) || index == quint16(-1))
            return false;

        // If index ok insert the index to the placeholder list positions
        positions.insert(index);

        // Adjusts the coordinate due to the overloaded Direction
        if (d == NORTH) --y;
        else if (d == EAST) ++x;
        else if (d == SOUTH) ++y;
        else if (d == WEST) --x;
    }

    ship->setPositions(positions);      // save ship positions in the ship object
    addShipPositions(positions);        // save ship positions in the united board position list

    foreach(const quint16 i, positions) {
        QPoint s = coordinatesFromIndex(i);
        emit shipAdded(s.x(), s.y());
    }

    return true;
}

/*
 * Shoot function checks if overloaded parameters are inside the board dimensions.
 * If not, return false, otherwise the calculated index will be added to the shots list
 * which holds all fired shots.
 */
bool Board::shoot(quint8 x, quint8 y) {
    quint16 index = indexFromCoordinates(x,y);
    if (index == quint16(-1))
        return false;
    shots.insert(index);
    emit shotAdded(x,y);
    return true;
}

/*
 * Prints the battleship board into the console
 */
void Board::print() {
    QString placeholder_bg = " . ";
    QString placeholder_ship = "[ ]";
    QString placeholder_damage = "[#]";
    QString placeholder_shot = " x ";
    quint8 counter = 0;
    quint8 counter2 = 0;
    QTextStream out(stdout);


    // Prints the column index on the x dimension of the board
    out << "    ";
    for (quint8 i = 0; i < width; ++i)
        out << qSetFieldWidth(3) << counter2++ << flush;
    out << "\n    ";
    for (quint8 j = 0; j < width; ++j)
        out << "---";
    out << "\n";
    // Prints the remaining board
    for (quint8 y = 0; y < height; ++y) {
        out << qSetFieldWidth(2) << counter++ << " | " << qSetFieldWidth(3) << flush;
        for (quint8 x = 0; x < width; ++x) {
            quint16 index = indexFromCoordinates(x,y);

            if (shipPositions.contains(index)) {
                if (shots.contains(index))
                    /*
                     * Prints the damage placeholder if the current
                     * index is part of the shipPosition and shots QSet
                     */
                    out << placeholder_damage;
                else
                    /*
                     * Prints the ship placeholder if the current
                     * index is only part of the shipPositions QSet
                     */
                    out << placeholder_ship;
            }
            else if (!shipPositions.contains(index) && shots.contains(index))
                /*
                 * Prints the shot placeholder if the current index is
                 * only part of the shots list
                 */
                out << placeholder_shot;
            else
                /*
                 * Prints the bg placeholder if the current index
                 * is not part of those lists.
                 */
                out << placeholder_bg;
        }
        out << "\n";
    }
}

/*
 * If a new ship is placed on the board, this function appends the
 * shipPositions QSet of the new ship to the board QSet shipPositions,
 * which holds all indexes of all ships
 */
void Board::addShipPositions(const QSet<quint16> shipPositions) {
    this->shipPositions.unite(shipPositions);
}

/*
 * Returns the shipPositions QSet which holds all indexes of all ships
 */
QSet<quint16> Board::getShipPositions() const {
    return shipPositions;
}

void Board::addShipsPositionsMulti(quint16 index)
{
    shipsPositionsMulti.insert(index);
    emit shipsPositionsMultiChanged();
    QPoint point = this->coordinatesFromIndex(index);
    emit shipAdded(point.x(), point.y());
}

QSet<quint16> Board::getShipsPositionsMulti()
{
    return shipsPositionsMulti;
}

/*
 * Calculates the index on the board due to the overloaded parameters x and y.
 * If the parameters are out of the board range a error is returned.
 */
quint16 Board::indexFromCoordinates(const quint8 x, const quint8 y) {
    if (width <= x || height <= y)
        return -1;
    else
        return y*width+x;
}

/*
 * Returns coordinates calculated from index
 */
QPoint Board::coordinatesFromIndex(const quint16 index)
{
    return QPoint(index % width, index / width);
}

/*
 * Returns the list which holds the fired shots
 */
QSet<quint16> Board::getShots() const {
    return shots;
}


/*
 * Returns true if there is a ship on position (x,y)
 */
bool Board::shipDamaged(quint8 x, quint8 y)
{
    return getShipPositions().contains(indexFromCoordinates(x,y));
}

bool Board::shipDamagedMulti(quint8 x, quint8 y)
{
    return getShipsPositionsMulti().contains(indexFromCoordinates(x,y));
}


/*
 * Returns true if all ships are destroyed
 */
bool Board::allShipsDestroyed()
{
    foreach(const Ship *ship, ships)
    {
        QSet<quint16> shipPositions = ship->getPositions();
        if (!shots.contains(shipPositions)) {
            return false;
        }
    }
    return true;
}

/*
 * Returns true if a given ship is destroyed
 */
 bool Board::shipDestroyed(Ship* ship)
{
    if (shots.contains(ship->getPositions())) {
        return true;
    }
    return false;
 }

 /*
  * Returns the damaged ship
  */
 Ship* Board::shipFromCoordinates(quint8 x, quint8 y)
 {
     foreach (Ship* ship, ships)
     {
         QSet<quint16> shipPositions = ship->getPositions();
         if (shipPositions.contains(indexFromCoordinates(x, y))) {
            return ship;
         }
     }
 }

 /*
  * Returns true if there is a ship on the position(x,y)
  */
bool Board::shipOnPosition(quint8 x, quint8 y)
{
    if(shipPositions.contains(indexFromCoordinates(x, y))) {
            return true;
    } else {
            return false;
    }
}

bool Board::shipOnPositionMulti(quint8 x, quint8 y)
{
    if(shipsPositionsMulti.contains(indexFromCoordinates(x, y))) {
        return true;
    } else {
        return false;
    }
}

/*
 * Returns true if there is a shot on the position(x,y)
 */
bool Board::shotOnPosition(quint8 x, quint8 y)
{
    if(shots.contains(indexFromCoordinates(x, y))) {
            return true;
    } else {
            return false;
    }
}

/*
 * Clears all list to reset the board
 */
void Board::reset()
{
    shipPositions.clear();
    shots.clear();
    emit boardReset();
}


/*
 * Returns ships QList
 */
QList<Ship *> Board::getShips() const
{
    return ships;
}

/*
 * Makes the ships QList available for the gui (qml)
 */
QQmlListProperty<Ship> Board::getShips_Quick()
{
    return QQmlListProperty<Ship> (this, 0, 0, ships_count, ships_at, 0);
}

int Board::ships_count(QQmlListProperty<Ship> *property)
{
    Board* This = qobject_cast<Board*>(property->object);
    return This->ships.count();
}

Ship *Board::ships_at(QQmlListProperty<Ship> *property, int index)
{
    Board* This = qobject_cast<Board*>(property->object);
    return This->ships.at(index);
}


/*
 * Sets the ships list
 */
void Board::setShips(const QList<Ship *> &value)
{
    foreach (Ship* ship, value) {
        ships.append(new Ship(ship->getLength(), ship->getName()));
    }
}

