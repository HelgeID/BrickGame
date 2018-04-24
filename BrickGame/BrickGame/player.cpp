//file: player.cpp
#include "player.h"
#include <QGraphicsScene>
#include <QTimerEvent>

#define playerWidth 80
#define playerHeight 90

Player::Player(Game *game)
{
    widget = new QWidget();
    QBrush brush;
    brush.setTextureImage(QImage(":/pictures/player/player.png"));
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Background, brush);
    widget->setPalette(palette);
    widget->setFixedSize(playerWidth, playerHeight);

    //set position
    widget->move(game->width()/2-playerWidth/2, game->height()-playerHeight);

    //create animation
    animation = new QPropertyAnimation(widget, "geometry", this);
    animation->setDuration(350);

    this->keyRight = new QShortcut(widget);
    keyRight->setKey(Qt::Key_Right);
    keyRight->setAutoRepeat(false);
    connect(keyRight, SIGNAL(activated()), this, SLOT(on_keyRight_clicked()));

    this->keyLeft = new QShortcut(widget);
    keyLeft->setKey(Qt::Key_Left);
    keyLeft->setAutoRepeat(false);
    connect(keyLeft, SIGNAL(activated()), this, SLOT(on_keyLeft_clicked()));

    this->keySpace = new QShortcut(widget);
    keySpace->setKey(Qt::Key_Space);
    //keySpace->setAutoRepeat(true);//enabled by default
    connect(keySpace, SIGNAL(activated()), this, SLOT(on_keySpace_clicked()));

    this->startTimer(400);
}

Player::~Player()
{
}

void Player::start()
{
}

void Player::timerEvent(QTimerEvent *event)
{
    //correction position of the player
    if (event->type() == QEvent::Timer) {
        if (widget->x()<40||widget->x()>520) {
            animation->stop();
            if (widget->x()<40)
            { animation->setEndValue(QRect(40, widget->y(), 80, 90)); emit mb_right(40); }
            else if (widget->x()>520)
            { animation->setEndValue(QRect(520, widget->y(), 80, 90)); emit mb_left(520); }
            animation->start();
        }
    }
}

void Player::on_keyRight_clicked()
{
    if (widget->x()<520) {
        animation->stop();
        int wX(widget->x()+40);
        animation->setEndValue(QRect(wX, widget->y(), 80, 90));
        emit mb_right(wX);
        animation->start();
    }
}

void Player::on_keyLeft_clicked()
{
    if (widget->x()>40) {
        animation->stop();
        int wX(widget->x()-40);
        animation->setEndValue(QRect(wX, widget->y(), 80, 90));
        emit mb_left(wX);
        animation->start();
    }
}

void Player::on_keySpace_clicked()
{
    emit mb_shoot();
    keyRight->blockSignals(true);
    keyLeft->blockSignals(true);
}

void Player::enable_keys()
{
    keyRight->blockSignals(false);
    keyLeft->blockSignals(false);
}
