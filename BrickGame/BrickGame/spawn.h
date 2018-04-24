#ifndef SPAWN_H
#define SPAWN_H

#include "game.h"
#include "player.h"
#include "block.h"
#include "ball.h"
#include "text.h"
#include <QObject>

class Spawn: public QObject
{
    Q_OBJECT
private:
    Game* game;
    uint random();
    uint random(const uint, const uint);

    QMap<QString, uint> map;
    uint random_ex();

    Ball *ball;
    Player *player;

    BrickText *SEC;
    BrickText *objGameOver, *objWin;
    int tSEC;

public:
    Spawn(Game* );
    ~Spawn();
    void spawn();
    void spawnPlayer();
    void spawnBall();

public slots:
    void spawnBlock();

private slots:
    void updateTimer();

protected:
    void timerEvent(QTimerEvent *);
};

#endif // SPAWN_H
