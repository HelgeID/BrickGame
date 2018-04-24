//file: spawn.cpp
#include "spawn.h"
#include <QTimer>
#include <QTimerEvent>
#include <QTime>

uint Spawn::random()
{
    QTime t(0, 0, 0);
    qsrand(t.msecsTo(QTime::currentTime()));
    return (qrand()%2);
}

uint Spawn::random(const uint min, const uint max)
{
    QTime t(0, 0, 0);
    qsrand(t.msecsTo(QTime::currentTime()));
    return (qrand()%max + min);
}

uint Spawn::random_ex()
{
    //ex - exception
    QTime t(0, 0, 0);
    qsrand(t.msecsTo(QTime::currentTime()));
    QString INDX("");
    foreach (QString key, map.keys())
        INDX+=key;
    QString remove(INDX[qrand()%INDX.size()]);
    map.remove(remove);
    return (remove.toUInt());
}

Spawn::Spawn(Game *game): tSEC(99)
{
    this->game = game;
    for (uint i(1); i<=5; i+=1)
        map.insert(QString::number(i), i);

    this->startTimer(250);

    SEC = new BrickText(game);
    SEC->addToScene();
    SEC->setSEC(tSEC);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(500);
}

Spawn::Spawn::~Spawn()
{
}

void Spawn::spawn()
{
    objGameOver = new BrickText(game, choice::over);
    objGameOver->addToScene(); objGameOver->takeWidget()->hide();
    objWin = new BrickText(game, choice::win);
    objWin->addToScene(); objWin->takeWidget()->hide();

    spawnPlayer();
    spawnBall();
    QObject::connect(ball, SIGNAL(enable_keys()), player, SLOT(enable_keys()));

    QObject::connect(player, SIGNAL(mb_right(int)), ball, SLOT(mb_right(int)));
    QObject::connect(player, SIGNAL(mb_left(int)), ball, SLOT(mb_left(int)));
    QObject::connect(player, SIGNAL(mb_shoot()), ball, SLOT(mb_shoot()));

    QTimer::singleShot(3000, this, SLOT(spawnBlock()));
    QTimer::singleShot(4500, this, SLOT(spawnBlock()));
    QTimer::singleShot(6000, this, SLOT(spawnBlock()));
    QTimer::singleShot(7500, this, SLOT(spawnBlock()));
    QTimer::singleShot(9000, this, SLOT(spawnBlock()));
}

void Spawn::spawnPlayer()
{
    player = new Player(game);
    game->takeGS().addWidget(player->widget); player->start();
}

void Spawn::spawnBall()
{
    ball = new Ball(game);
    game->takeGS().addWidget(ball->widget); ball->start();
}

void Spawn::spawnBlock()
{
    Block *block = new Block(game, ball, random_ex());
    MoveFlag mf;
    random();//for greater variability
    if (!random())
        mf = moveLeft;
    else
        mf = moveRight;

    QObject::connect(ball, SIGNAL(enable_keys()), block, SLOT(activator()));
    game->takeGS().addWidget(block->widget); block->start_move(mf);
}

void Spawn::updateTimer()
{
    if (game->gameover()||game->win())
        return;
    SEC->setSEC(tSEC);
    if (!SEC->getSEC())
        game->gameover()=true;
    else
        tSEC--;
}

void Spawn::timerEvent(QTimerEvent *event)
{
    static bool the_end(false);
    if (event->type() == QEvent::Timer && !the_end) {
        if (game->gameover() || game->win()) {
            QObject::disconnect(player, SIGNAL(mb_right(int)), ball, SLOT(mb_right(int)));
            QObject::disconnect(player, SIGNAL(mb_left(int)), ball, SLOT(mb_left(int)));
            QObject::disconnect(player, SIGNAL(mb_shoot()), ball, SLOT(mb_shoot()));

            SEC->takeWidget()->hide();
            if (game->gameover())
                objGameOver->takeWidget()->show();

            else if (game->win())
                objWin->takeWidget()->show();

            the_end = true;
        }
    }
}
