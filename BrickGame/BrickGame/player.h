#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QShortcut>

class Player: public QWidget
{
    Q_OBJECT
public:
    Player(Game*);
    ~Player();
    QWidget *widget;
    void start();

private:
    QPropertyAnimation *animation;
    QShortcut *keyRight;
    QShortcut *keyLeft;
    QShortcut *keySpace;
    void timerEvent(QTimerEvent *);

private slots:
    void on_keyRight_clicked();
    void on_keyLeft_clicked();
    void on_keySpace_clicked();
    void enable_keys();

signals:
    void mb_right(int);
    void mb_left(int);
    void mb_shoot();
};

#endif // PLAYER_H
