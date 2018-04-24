#ifndef BLOCK_H
#define BLOCK_H

#include "game.h"
#include "ball.h"
#include <QWidget>
#include <QPropertyAnimation>

enum MoveFlag {moveLeft, moveRight, moveRandom};

class Block: public QWidget
{
    Q_OBJECT
public:
    Block(Game*, Ball*, uint);
    ~Block();
    QWidget *widget;
    MoveFlag mf;
    void start_move_to_right();
    void start_move_to_left();
    void stop_move();

private:
    int posH;
    int posStart, posEnd;
    Ball *ball;
    QRect rectBlock, rectBall;
    QPropertyAnimation *animation;
    QPropertyAnimation* takePropertyAnimation() {return animation;}
    QString takeBlock();
    void initAnimation(QWidget**, Game**);
    bool act;
    void SWAP();

signals:
    void swap(int);

public slots:
    void start_move(MoveFlag mf = moveRandom);
    void activator(bool a=true) {act=a;}

protected:
    void timerEvent(QTimerEvent *);
};

#endif // BLOCK_H
