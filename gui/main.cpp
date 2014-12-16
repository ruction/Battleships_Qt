#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <battleships.h>
#include <board.h>
#include <ship.h>


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Battleships>("Battleships", 1, 0, "Battleships");
    qmlRegisterType<Board>("Battleships", 1, 0, "Board");
    qmlRegisterType<Ship>("Battleships", 1, 0, "Ship");
    QQmlApplicationEngine engine(QUrl("qrc:/StartScreen.qml"));

    return app.exec();
}
