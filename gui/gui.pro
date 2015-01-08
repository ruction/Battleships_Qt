INCLUDEPATH += ../common

LIBS += ../common/libcommon.a
PRE_TARGETDEPS = ../common/libcommon.a

QT += qml quick

SOURCES += main.cpp

HEADERS += \


RESOURCES += \
    gui.qrc
