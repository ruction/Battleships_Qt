#include "battleships.h"

/*
 * Default constructor with initial values for playerName
 * and shotsFired parameter
 */
Battleships::Battleships()
    :playerName("empty"), shotsFired(0)
{
    /*
     * Fills QList<Ship*> availableShips with five
     * ship instances
     */
    availableShips
    << new Ship(5, "aircraft_carrier")
    << new Ship(4, "battleship")
    << new Ship(3, "submarine")
    << new Ship(3, "cruiser")
    << new Ship(2, "destroyer");
}

Battleships::~Battleships()
{
    qDeleteAll(availableShips);
}

/*
 * Sets the playerName
 */
void Battleships::setPlayerName(const QString& playerName) {
    this->playerName = playerName;
}

/*
 * Returns the playerName parameter
 */
QString Battleships::getPlayerName() const {
    return playerName;
}

/*
 * Inkrements shotsFired parameter on function call
 */
void Battleships::inkrementShots() {
    shotsFired++;
}

/*
 * Returns the shotsFired parameter
 */
quint16 Battleships::getShotsFired() const {
   return shotsFired;
}

/*
 * Returns the list of available ships which will
 * be placed later on the board
 */
QList<Ship*> Battleships::getAvailableShips() const {
    return availableShips;
}
