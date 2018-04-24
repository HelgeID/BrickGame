#ifndef TEXT_H
#define TEXT_H

#include "game.h"
#include <QWidget>
#include <QLabel>

enum choice {over, win};

class BrickText: public QWidget
{
private:
    QWidget *widget;
    QLabel *label;
    QString str;
    Game* game;

public:
    BrickText(Game *);
    BrickText(Game *, choice);
    void addToScene();
    int getSEC();
    void setSEC(int);

    QWidget* takeWidget() {return widget;}
};

#endif // TEXT_H
