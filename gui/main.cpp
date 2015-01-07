#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <battleships.h>
#include <board.h>
#include <ship.h>

#include "client.h"
#include "server.h"
#include "network.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Battleships>("Battleships", 1, 0, "Battleships");
    qmlRegisterType<Board>("Battleships", 1, 0, "Board");
    qmlRegisterType<Ship>("Battleships", 1, 0, "Ship");
    qmlRegisterType<Server>("Battleships", 1, 0, "Server");
    qmlRegisterType<Client>("Battleships", 1, 0, "Client");
    qmlRegisterType<Network>("Battleships", 1, 0, "Network");
    QQmlApplicationEngine engine(QUrl("qrc:/StartScreen.qml"));

    return app.exec();
}
