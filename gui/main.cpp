#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
//    qmlRegisterType<Battleships>("Battleships", 1, 0, "Battleships");
    QQmlApplicationEngine engine(QUrl("qrc:/StartScreen.qml"));

    return app.exec();
}
