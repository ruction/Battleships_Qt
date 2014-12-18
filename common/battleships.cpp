#include "battleships.h"

/*
 * Default constructor with initial values for playerName
 * and shotsFired parameter
 */
Battleships::Battleships(QObject *parent)
    :QObject(parent), playerName("empty"), shotsFired(0)
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

    m_board.setShips(availableShips);
    m_enemyBoard.setShips(availableShips);
}

Battleships::~Battleships()
{
    qDeleteAll(availableShips);
}

/*
 * Sets the playerName
 */
void Battleships::setPlayerName(const QString& playerName) {
    if (this->playerName != playerName) {
        this->playerName = playerName;
        emit playerNameChanged();
    }
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

QQmlListProperty<Ship> Battleships::getAvailableShips_Quick()
{
    return QQmlListProperty<Ship> (this, 0, 0, availableShips_count, availableShips_at, 0);
}

Board *Battleships::board()
{
    return &m_board;
}

Board *Battleships::enemyBoard()
{
    return &m_enemyBoard;
}

int Battleships::availableShips_count(QQmlListProperty<Ship> *property)
{
    Battleships* This = qobject_cast<Battleships*>(property->object);
    return This->availableShips.count();
}

Ship *Battleships::availableShips_at(QQmlListProperty<Ship> *property, int index)
{
    Battleships* This = qobject_cast<Battleships*>(property->object);
    return This->availableShips.at(index);
}

/*
 * Returns the list of available ships which will
 * be placed later on the board
 */
QList<Ship*> Battleships::getAvailableShips() const {
    return availableShips;
}
