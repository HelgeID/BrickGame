#ifndef BALL_H
#define BALL_H

#include "game.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class Ball: public QWidget
{
    enum {left, right, center, shoot};
    Q_OBJECT
public:
    Ball(Game*);
    ~Ball();
    QWidget *widget;
    void start();

private:
    int state;
    int counter;
    QPropertyAnimation *animation;

    QPropertyAnimation *animUp;
    QPropertyAnimation *animDown;
    QPropertyAnimation *animFreeFall;
    QSequentialAnimationGroup *groupUpDown;
    QSequentialAnimationGroup *groupFreeFall;

    Game* game;
    void setBlackBall();

public slots:
    void mb_centre();
    void mb_right(int);
    void mb_left(int);
    void mb_shoot();
    void mb_gameover();

private slots:
    void swap(int);

signals:
    void enable_keys();
};

#endif // BALL_H
