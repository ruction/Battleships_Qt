#include "consoleclient.h"
#include <ship.h>
#include <QTime>


ConsoleClient::ConsoleClient()
    :in(stdin), out(stdout), exp("\\d+")
{
}

void ConsoleClient::run() {
    QList<Ship*> ships = battleships.getAvailableShips();
    Board* board = readInitialData();
    placeShips(board, ships);
    shootLoop(board, ships);
}

Board* ConsoleClient::readInitialData() {
    out << "#### WELCOME TO BATTLESHIP ####\n";

    // Read player name
    out << "What is your name? " << flush;
    QString playerName = in.readLine();
    battleships.setPlayerName(playerName);

    // Read board dimensions
    out << "Hi, " << battleships.getPlayerName() << "\n";
    out << "Type in the width of the Board: " << flush;
    QString width;
    // Loop until input is valid
    while(true) {
        width = in.readLine();
        // Checks if input is a number (exp) and width < 30
        if (!exp.exactMatch(width) || width.toUInt() > 30)
            out << "Try again...: " << flush;
        else
            break;
    }
    out << "Type in the height of the Board: " << flush;
    QString height;
    // Loop until input is valid
    while(true) {
        height = in.readLine();
        // Checks if input is a number (exp) and height < 30
        if (!exp.exactMatch(height) || height.toUInt() > 30)
            out << "Try again...: " << flush;
        else
            break;
    }

    // Creates board with the input values
    Board* board = new Board(width.toUInt(), height.toUInt());
    board->print();
    return board;
}

void ConsoleClient::placeShips(Board *board, QList<Ship*> ships) {
    QString randomSingle = "n";
    QString randomAll = "n";
    qsrand(QTime::currentTime().msec());        // Qrand seed

    out << "\nPlace your ships: \n" << flush;
    out << "Place all ships randomly? (y/n): " << flush;
    randomAll = in.readLine();

    // Loop to place ships. Random or each ship by hand or each ship random or by hand
    for (quint8 i = 0; i < ships.count(); ++i) {
        Ship* ship = ships.at(i);           // Current ship

        // Tries to place all ships randomly, until all are placed
        if (randomAll == "y") {
            if(board->place(ship, Board::randomValue(board->getWidth()), Board::randomValue(board->getHeight()), Board::Direction(Board::randomValue(3)) )) {}
            else {
                --i;
                continue;
            }
        }
        // Otherwise place manually
        else {
            out << "#" << i+1 << ": " << ships.at(i)->getName() << " | " << ships.at(i)->getLength() << "\n" << flush;
            if (randomSingle == "n") {
                out << "Place ship randomly? (y/n): " << flush;
                randomSingle = in.readLine();
            }

            // Place a single ship randomly
            if (randomSingle == "y") {
                if(board->place(ship, Board::randomValue(board->getWidth()), Board::randomValue(board->getHeight()), Board::Direction(Board::randomValue(3)) )) {}
                else {
                    --i;
                    continue;
                }
            }
            // Place a single ship manually
            else {
                out << "Type in x coordinate: " << flush;
                QString x;
                while(true) {
                    x = in.readLine();
                    if (!exp.exactMatch(x))
                        out << "Try again...: " << flush;
                    else
                        break;
                }

                out << "Type in y coordinate: " << flush;
                QString y;
                while(true) {
                    y = in.readLine();
                    if (!exp.exactMatch(y))
                        out << "Try again...: " << flush;
                    else
                        break;
                }

                out << "Type in direction: (NORTH | EAST | SOUTH | WEST) " << flush;

                QString directionString;
                // Checks if direction input is valid
                while(true) {
                     directionString = in.readLine();
                     if (Board::directionFromString(directionString) == Board::WRONG)
                         out << "Try again...: " << flush;
                     else
                         break;
                }
                // Finally place ship
                if(board->place(ship, x.toUInt(), y.toUInt(), Board::directionFromString(directionString))) {}
                else {
                    out << "Ship placement error! Try again.\n" << flush;
                    --i;
                    continue;
                }
            }
            randomSingle = "n";
            board->print();
        }
    }
}

void ConsoleClient::shootLoop(Board *board, QList<Ship*> ships)
{
    /*
     * Ships are now placed. Here is the loop to shoot
     */
    out << "Now you are ready to shoot!! \n" << flush;
    board->print();

    // Loop until all ships are destroyed
    while (true) {
        out << "Type in x coordinate: " << flush;
        QString shotX;              // X coordinate of the shot
        // Loop until input is valid
        while(true) {
            shotX = in.readLine();
            // Checks if input is a number (exp) and inside the board dimensions
            if (!exp.exactMatch(shotX) || shotX.toUInt() > board->getWidth())
                out << "Try again...: " << flush;
            else
                break;
        }
        out << "Type in y coordinate: " << flush;
        QString shotY;              // Y coordinate of the shot
        // Loop until input is valid
        while(true) {
            shotY = in.readLine();
            // Checks if input is a number (exp) and inside the board dimensions
            if (!exp.exactMatch(shotY) || shotY.toUInt() > board->getHeight())
               out << "Try again...: " << flush;
            else
                break;
        }

        quint8 counter = 0;         // Counter for destroyed ships

        // Checks if shoot is valid
        if (board->shoot(shotX.toUInt(), shotY.toUInt())) {
            battleships.inkrementShots();           // Inkrements shotsFired parameter
            // If shipPositions contains shot coordinates its a damage
            if (board->getShipPositions().contains(board->indexFromCoordinates(shotX.toUInt(), shotY.toUInt()))) {
                out << "Shot #" << battleships.getShotsFired() << " - DAMAGE!! \n" << flush;

                // Checks if a complete ship is damaged/destroyed and inkrements counter
                for (int i = 0; i < ships.size(); ++i) {
                    if (board->getShots().contains(ships.at(i)->getPositions())) {
                        out << ships.at(i)->getName() << " - DESTROYED!!!!\n" << flush;
                        counter++;
                    }
                }
                // If all ships are destroyed game loop ends
                if (counter == ships.length()) {
                    board->print();
                    out << "All ships are destroyed! You WON! \n" << flush;
                    break;
                }
                board->print();
            }
            // Otherwise it no damage
            else {
                out << "Shot #" << battleships.getShotsFired() << " - Nothing damaged...\n" << flush;
                board->print();
            }
        } else {
            out << "Wrong input! Try again.\n" << flush;
        }
    }
}
