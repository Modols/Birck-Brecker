#include "vie.h"
#include <QFont>
#include "game.h"
extern Game * game;

Vie::Vie(QGraphicsTextItem *parent) : QGraphicsTextItem(parent),vie(1)
{
    //draw health
    setPlainText(QString("Vie: ") + QString::number(vie));
    setDefaultTextColor(Qt::red);
    setFont(QFont("comic sans",16));
}

void Vie::decrease()
{
    vie--;
    //refresh the health's text
    setPlainText(QString("Vie: ") + QString::number(vie));
}

int Vie::getVie()
{
    return vie;
}
