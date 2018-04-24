//file: game.cpp
#include "game.h"
#include "block.h"
#include "spawn.h"

Game::Game(void): scene(new QGraphicsScene()), view(scene)
{
    flgOver = false;//flag the end of the game
    flgWin = false;//flag of the victory
    //create the scene
    const uint VGA_w(640), VGA_h(480);
    scene->setSceneRect(0, 0, VGA_w, VGA_h);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(VGA_w, VGA_h);
    //view.setStyleSheet("background-color: lightGray");
    view.show();

    Spawn *spawn = new Spawn(this);
    spawn->spawn();
}

Game::~Game(void)
{
}
