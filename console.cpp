#include "console.h"
#include <QTextStream>

QTextStream in(stdin);
QTextStream out(stdout);

Console::Console(Battleships battleships)
    :battleships(battleships)
{
    out << "#### WELCOME TO BATTLESHIP ####\n";
    out << "What is your name? " << flush;
    QString playerName = in.readLine();
    battleships.setPlayerName(playerName);
}

Board Console::createBoard()
{
    out << "Hi, " << battleships.getPlayerName() << "\n";
    out << "Type in the width of the Board: " << flush;
    QString width = in.readLine();
    out << "Type in the height of the Board: " << flush;
    QString height = in.readLine();

    Board board(width.toUInt(), height.toUInt());
    board.print();
    return board;
}
