#ifndef CONSOLECLIENT_H
#define CONSOLECLIENT_H

#include <battleships.h>
#include <board.h>
#include <QCoreApplication>
#include <QtGlobal>
#include <QTextStream>


class ConsoleClient
{
public:
    ConsoleClient();
    void run();
    void placeShips(Board *board, QList<Ship*> ships);
    void shootLoop(Board *board, QList<Ship*> ships);
    void readInitialData();
private:
    QTextStream in;
    QTextStream out;
    QRegExp exp;
    Battleships battleships;
};

#endif // CONSOLECLIENT_H
