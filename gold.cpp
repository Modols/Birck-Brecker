#include "gold.h"
#include "game.h"
#include <fstream>
#include <string>
#include <vector>
#include <QFont>
#include <iostream>

using namespace std;
extern Game *game;

Gold::Gold(QGraphicsTextItem *parent) : QGraphicsTextItem(parent)
{
    gold = stoi(game->getGolds());

    setPlainText(QString("Golds: ") + QString::number(gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("comic sans",16));
}

void Gold::increase()
{
    gold += 1;
    //refresh les golds
    setPlainText(QString("Golds: ") + QString::number(gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("comic sans",16));
}

int Gold::getGold() const
{
    return gold;
}

void Gold::setGold(int value)
{
    gold = value;
}



