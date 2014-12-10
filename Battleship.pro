#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T21:46:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Battleship
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    battleships.cpp \
    board.cpp \
    ship.cpp \
    consoleclient.cpp

HEADERS += \
    battleships.h \
    board.h \
    ship.h \
    consoleclient.h
