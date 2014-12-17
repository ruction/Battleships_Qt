QT       = core qml quick

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += ../common
LIBS += ../common/libcommon.a

SOURCES  += main.cpp \
    consoleclient.cpp

HEADERS   += \
    consoleclient.h
