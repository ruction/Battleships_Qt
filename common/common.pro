TEMPLATE = lib

CONFIG += staticlib
QT += qml quick

SOURCES += battleships.cpp \
    board.cpp \
    ship.cpp \

HEADERS += \
    battleships.h \
    board.h \
    ship.h \
