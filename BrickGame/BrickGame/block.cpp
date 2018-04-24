//file: block.cpp
#include "block.h"
#include <QList>
#include <QTime>
#include <QTimerEvent>

#define blockWidth 60
#define blockHeight 60

Block::Block(Game *game, Ball *ball, uint id): QWidget(),
  rectBlock(QPoint(0, 0), QSize(blockWidth, blockHeight)),
  rectBall(QPoint(0, 0), QSize(60, 60)),
  act(true)
{
    this->ball = ball;

    widget = new QWidget();
    QBrush brush;
    brush.setTextureImage(QImage(takeBlock()));
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Background, brush);
    widget->setPalette(palette);
    widget->setFixedSize(blockWidth, blockHeight);

    switch (id) {
        case 1: posH = 0; break;
        case 2: posH = 45; break;
        case 3: posH = 90; break;
        case 4: posH = 135; break;
        case 5: posH = 180; break;
    }
    this->posStart=0;
    this->posEnd=0;
    initAnimation(&widget, &game);

    this->startTimer(120);
    connect(animation, SIGNAL(finished()), this, SLOT(start_move()));
    connect(this, SIGNAL(swap(int)), ball, SLOT(swap(int)));
}

Block::~Block()
{
}

void Block::start_move_to_right()
{
    posStart = -70;
    posEnd = 640;
    QPropertyAnimation *animation = takePropertyAnimation();
    animation->setStartValue(QRect(posStart, posH, 70, 70));
    animation->setEndValue(QRect(posEnd, posH, 70, 70));
    animation->start();
    mf = moveLeft;
}

void Block::start_move_to_left()
{
    posStart = 640;
    posEnd = -70;
    QPropertyAnimation *animation = takePropertyAnimation();
    animation->setStartValue(QRect(posStart, posH, 70, 70));
    animation->setEndValue(QRect(posEnd, posH, 70, 70));
    animation->start();
    mf = moveRight;
}

void Block::stop_move()
{
    QPropertyAnimation *animation = takePropertyAnimation();
    animation->stop();
}

QString Block::takeBlock()
{
    int counter(0);

    //for getting random value
    QTime t(0, 0, 0);
    qsrand(t.msecsTo(QTime::currentTime()));

    QString listblock;
    QList <QString> ListBlock;
    ListBlock.append(":/pictures/blocks/black_block.png");
    ListBlock.append(":/pictures/blocks/blue_block.png");
    ListBlock.append(":/pictures/blocks/green_block.png");
    ListBlock.append(":/pictures/blocks/light_blue_block.png");
    ListBlock.append(":/pictures/blocks/orange_block.png");
    ListBlock.append(":/pictures/blocks/purple_block.png");
    ListBlock.append(":/pictures/blocks/red_block.png");
    ListBlock.append(":/pictures/blocks/yellow_block.png");

    QString random = QString("%0").arg(qrand()%7 + 1);
    foreach (QString lb, ListBlock) {
        if (QString::number(counter)==random) {
            listblock = lb;
            counter = 0;
            break;
        }
        ++counter;
    }
    return listblock;
}

void Block::initAnimation(QWidget **widget, Game **game)
{
    animation = new QPropertyAnimation(*widget, "geometry", *game);
    animation->setDuration(8000);
    animation->setEasingCurve(QEasingCurve::InOutExpo);
    mf = moveLeft;
}

void Block::SWAP()
{
    QString bloksArr[] = {
        "black_block.png", "blue_block.png", "green_block.png", "light_blue_block.png",
        "orange_block.png", "purple_block.png", "red_block.png", "yellow_block.png"
    };

    QString ballsArr[] = {
        "black_ball.png", "blue_ball.png", "green_ball.png", "light_blue_ball.png",
        "orange_ball.png", "purple_ball.png", "red_ball.png", "yellow_ball.png"
    };
    const int size(8);

    QBrush bloksBr[size];
    for (int i(0); i<size; ++i) {
        QString pathway(":/pictures/blocks/"+bloksArr[i]);
        bloksBr[i].setTextureImage(QImage(pathway));
    }

    QBrush ballsBr[size];
    for (int i(0); i<size; ++i) {
        QString pathway(":/pictures/balls/"+ballsArr[i]);
        ballsBr[i].setTextureImage(QImage(pathway));
    }

    QPalette::ColorRole cr = widget->backgroundRole();
    QBrush br = widget->palette().brush(cr);
    int indx;
    for (int i(0); i<size; ++i)
        if (bloksBr[i].textureImage() == br.textureImage())
            indx=i+1;

    //change the color of the block
    QBrush brushBlock;
    QPalette paletteBlock = widget->palette();
    brushBlock.setTextureImage(QImage(":/pictures/blocks/black_block.png"));
    paletteBlock.setBrush(QPalette::Background, brushBlock);
    widget->setPalette(paletteBlock);

    //when the black block collided with the ball
    if (ballsArr[indx-1]==*ballsArr)
        widget->hide();
    emit swap(indx);
}

void Block::start_move(MoveFlag mf)
{
    if (mf != moveRandom)
        mf ? this->mf = moveLeft : this->mf = moveRight;

    if (this->mf == moveLeft) {
        start_move_to_left();
        return;
    }

    if (this->mf == moveRight) {
        start_move_to_right();
        return;
    }
}

void Block::timerEvent(QTimerEvent *event)
{
    if (event->type() == QEvent::Timer) {

        //get rect for block
        int x(widget->x()+10);
        int y(widget->y()+10);
        rectBlock.setRect(x, y, 50, 50);

        //get rect for ball
        x = this->ball->widget->x()+10;
        y = this->ball->widget->y()+10;
        rectBall.setRect(x, y, 50, 50);

        if (rectBlock.intersects(rectBall) && act) {
            activator(false);//from double-crossing objects(bung)
            SWAP();
        }
    }
}
