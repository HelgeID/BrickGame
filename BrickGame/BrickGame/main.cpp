//file: main.cpp
#include "game.h"
#include <QApplication>

Game *game;
int main(int argc, char *argv[])
{
    QApplication app {argc, argv};
    game = new Game;
    return app.exec();
}
