#include "ship.h"

/*
 * Constructor with ship length initialisation
 */
Ship::Ship(QObject *parent)
    :QObject(parent)
{
}

Ship::Ship(quint8 length)
    :length(length)
{
}

/*
 * Second constructor with a name paramter
 * and initialisation
 */
Ship::Ship(quint8 length, QString name)
    :length(length), name(name)
{
}

/*
 * Returns ship length
 */
quint8 Ship::getLength() const {
    return length;
}

/*
 * Returns ship name
 */
QString Ship::getName() const {
    return name;
}

/*
 * Returns ship position QSet
 */
QSet<quint16> Ship::getPositions() const {
    return positions;
}

/*
 * Sets the ship position QSet
 */
void Ship::setPositions(QSet<quint16> positions) {
    this->positions = positions;
}
