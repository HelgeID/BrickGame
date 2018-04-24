#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView
{
private:
    bool flgOver;
    bool flgWin;
    QGraphicsScene *scene;
    QGraphicsView view;

public:
    Game(void);
    ~Game(void);
    QGraphicsScene& takeGS() {return *scene;}

    bool& gameover() {return flgOver;}
    bool& win() {return flgWin;}
};

#endif // GAME_H
