#include "text.h"

BrickText::BrickText(Game *game)
{
    this->game = game;
    QString clock("00");
    QFont font("Mistral", 300, QFont::Bold);
    widget = new QWidget();
    label = new QLabel(clock, widget);
    QPalette pal = label->palette();
    pal.setBrush(QPalette::Background, QBrush(QColor(255, 255, 255, 255)));
    label->setAutoFillBackground(true);
    label->setPalette(pal);
    label->setFont(font);
    label->setStyleSheet("color: rgb(120, 120, 120, 20)");
    widget->move(140, 0);
}

BrickText::BrickText(Game *game, choice ch)
{
    QString str;
    if (ch==win)
        str="You Won";
    else if (ch==over)
        str="Game Over";
    this->game = game;
    QFont font("Times", 60, QFont::Bold);
    widget = new QWidget();
    label = new QLabel(str, widget);
    QPalette pal = label->palette();
    pal.setBrush(QPalette::Background, QBrush(QColor(255, 255, 255, 255)));
    label->setAutoFillBackground(true);
    label->setPalette(pal);
    label->setFont(font);
    if (ch==over)
        label->setStyleSheet("color: rgb(220, 120, 120, 220)");
    if (ch==win)
        label->setStyleSheet("color: rgb(120, 120, 220, 220)");
    widget->move(120, 150);
}

void BrickText::addToScene()
{
    game->takeGS().addWidget(widget);
}

int BrickText::getSEC()
{
    QString clock = label->text();
    if (clock.isEmpty())
        return 0;
    return clock.toInt();
}

void BrickText::setSEC(int number)
{
    if (!number)
        label->setText("");
    else {
        QString clock(QString::number(number));
        if (number>=1 && number<=9)
            clock = '0' + clock;
        label->setText(clock);
    }
}
