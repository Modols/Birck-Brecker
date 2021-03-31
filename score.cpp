#include "score.h"
#include <QFont>
#include "game.h"

#include <QtDebug>

extern Game * game;

Score::Score(QGraphicsTextItem *parent) : QGraphicsTextItem(parent), score(0), compteur(0)
{
    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("comic sans",16));
}

void Score::increase()
{  
    if (compteur == 9)
    {
        compteur = 0;
        game->setAugmentationVitesseEnnemie(game->getAugmentationVitesseEnnemie() + 1); //vitesse défilement +
        game->getGold()->increase(); //Gold +1
    }else{
        compteur++;
    }

    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore()
{
    return score;
}
