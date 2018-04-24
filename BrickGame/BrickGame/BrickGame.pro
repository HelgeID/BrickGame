QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrickGame
TEMPLATE = app


SOURCES += main.cpp \
    block.cpp \
    spawn.cpp \
    player.cpp \
    game.cpp \
    ball.cpp \
    text.cpp

HEADERS  += \
    block.h \
    spawn.h \
    player.h \
    game.h \
    ball.h \
    text.h

RESOURCES += \
    res.qrc
