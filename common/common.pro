TEMPLATE = lib

CONFIG += staticlib
QT += qml quick network

SOURCES += battleships.cpp \
    board.cpp \
    ship.cpp \
    client.cpp \
    server.cpp

HEADERS += \
    battleships.h \
    board.h \
    ship.h \
    client.h \
    server.h
