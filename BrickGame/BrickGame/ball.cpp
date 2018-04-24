//file: ball.cpp
#include "ball.h"

#define ballWidth 60
#define ballHeight 60

Ball::Ball(Game *game): state(Ball::center), counter(0)
{
    this->game = game;

    widget = new QWidget();
    widget->setFixedSize(ballWidth, ballHeight);
    setBlackBall();

    //set position
    widget->move(game->width()/2-ballWidth/2, game->height()-125);

    //create animation
    animation = new QPropertyAnimation(widget, "geometry", this);
    animation->setDuration(350);
    connect(animation, SIGNAL(finished()), this, SLOT(mb_centre()));

    //create animation UP
    animUp = new QPropertyAnimation(widget, "geometry", this);
    animUp->setDuration(1000);
    animUp->setEasingCurve(QEasingCurve::Linear);

    //create animation DOWN
    animDown = new QPropertyAnimation(widget, "geometry", this);
    animDown->setDuration(3000);
    animDown->setEasingCurve(QEasingCurve::OutBounce);

    //create animation FreeFall
    animFreeFall = new QPropertyAnimation(widget, "geometry", this);
    animFreeFall->setDuration(1000);
    animFreeFall->setEasingCurve(QEasingCurve::Linear);

    //create group UP-DOWN
    groupUpDown = new QSequentialAnimationGroup();
    groupUpDown->addAnimation(animUp);
    groupUpDown->addAnimation(animDown);

    //create group FreeFall
    groupFreeFall = new QSequentialAnimationGroup();
    groupFreeFall->addAnimation(animFreeFall);

    connect(groupUpDown, SIGNAL(finished()), this, SLOT(mb_centre()));
}

Ball::~Ball()
{
}

void Ball::start()
{
}

void Ball::setBlackBall()
{
    QBrush brush;
    brush.setTextureImage(QImage(":/pictures/balls/black_ball.png"));
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Background, brush);
    widget->setPalette(palette);
}

void Ball::mb_centre()
{
    if (game->win()) {
        setBlackBall();
        return;
    }

    if (state == Ball::shoot) {
        state = Ball::center;
        emit enable_keys();
        setBlackBall();
        return;
    }

    int value = widget->x();
    (state == Ball::right) ? value += 15 : NULL;
    (state == Ball::left)  ? value -= 15 : NULL;
    if (state != Ball::center) {
        animation->stop();
        animation->setEndValue(QRect(value, widget->y(), ballWidth, ballHeight));
        animation->start();
        state = Ball::center;
    }
}

void Ball::mb_right(int value)
{
    value-=5;
    animation->stop();
    animation->setEndValue(QRect(value, widget->y(), ballWidth, ballHeight));
    animation->start();
    state = Ball::right;
}

void Ball::mb_left(int value)
{
    value+=25;
    animation->stop();
    animation->setEndValue(QRect(value, widget->y(), ballWidth, ballHeight));
    animation->start();
    state = Ball::left;
}

void Ball::mb_shoot()
{
    if (state == Ball::center) {
        animUp->setKeyValueAt(0, QRect(widget->x(), widget->y(), 60, 60));
        animUp->setKeyValueAt(1, QRect(widget->x(), 0, 60, 60));

        animDown->setKeyValueAt(0, QRect(widget->x(), 0, 60, 60));
        animDown->setKeyValueAt(1, QRect(widget->x(), widget->y(), 60, 60));

        groupUpDown->start();
        state = Ball::shoot;
    }
}

void Ball::mb_gameover()
{
    groupUpDown->stop();
    animFreeFall->setKeyValueAt(0, QRect(widget->x(), widget->y(), 60, 60));
    animFreeFall->setKeyValueAt(1, QRect(widget->x(), game->height()-120, 60, 60));
    groupFreeFall->start();
}

void Ball::swap(int indx)
{
    counter=counter+1;

    QString ArrBall[] = {
        ":/pictures/balls/black_ball.png",
        ":/pictures/balls/blue_ball.png",
        ":/pictures/balls/green_ball.png",
        ":/pictures/balls/light_blue_ball.png",
        ":/pictures/balls/orange_ball.png",
        ":/pictures/balls/purple_ball.png",
        ":/pictures/balls/red_ball.png",
        ":/pictures/balls/yellow_ball.png"
    };

    QBrush brushBall;
    QPalette paletteBall = widget->palette();
    brushBall.setTextureImage(QImage(ArrBall[indx-1]));
    paletteBall.setBrush(QPalette::Background, brushBall);
    widget->setPalette(paletteBall);

    if (ArrBall[indx-1]==*ArrBall) {
        brushBall.setTextureImage(QImage(":/pictures/blocks/black_block.png"));
        paletteBall.setBrush(QPalette::Background, brushBall);
        widget->setPalette(paletteBall);
        if (!game->gameover())
            { game->gameover() = true; mb_gameover(); }
    }

    if (counter==5 && !game->gameover())
        game->win() = true;
}
