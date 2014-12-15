#include <consoleclient.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ConsoleClient consoleClient;
    consoleClient.run();

    return false;
}
