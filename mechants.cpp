#include "game.h"
#include "myrect.h"
#include "score.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>
#include <fstream>
#include "mechantstandard.h"
#include <iostream>
using namespace std;

extern Game * game;

Mechants::Mechants(QGraphicsItem *parent)
{
    setVitesse(game->getVitesseEnemie());

    // set radom Position
    int random_number = rand() % 700;
    setPos(random_number, -110);

    //Temps pour move le méchant
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    resume();
}

Mechants::~Mechants()
{
    delete timer;
}

int Mechants::getVitesse() const
{
    return vitesse;
}

void Mechants::setVitesse(int value)
{
    vitesse = value;
}

bool Mechants::getIsDead() const
{
    return isDead;
}

void Mechants::setIsDead(bool value)
{
    isDead = value;
}

void Mechants::pause()
{
    timer->stop();
}

void Mechants::resume()
{
    timer->start(60);
}

void Mechants::move()
{
    QList<QGraphicsItem *> collisionMechant = collidingItems();
    for (int i = 0, n = collisionMechant.size(); i< n; i++)
    {
        if (typeid(*(collisionMechant[i])) == typeid(MyRect))
        {
            if(game->getVie()->getVie() <= 1)
            {
                game->displayEndGame();
                return;
            }

            //-1 vie
            game->getVie()->decrease();

            //Supprimer l'enemie
            if(!isDead){
                scene()->removeItem(this);
                isDead = true;
            }
            return;
        }
    }

    //faire descendre les enemies
    setPos(x(),y()+ (game->getVitesseEnemie() + game->getAugmentationVitesseEnnemie()));
    if(pos().y() > 600)
    {
        if(!isDead){
            scene()->removeItem(this);
            isDead = true;
        }
        delete this;
    }
}


