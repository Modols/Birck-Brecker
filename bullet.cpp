#include "bullet.h"
#include "game.h"
#include "mechants.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //creation de la bullet
    setPixmap(QPixmap(":/Images/images/Missile.png"));
    //connect
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(40);

}

Bullet::~Bullet()
{
    delete timer;
}

void Bullet::changeVitesseTir()
{
    if(game->getVitesseTir() - game->getReductionVitesseTir() > 1)
    {
        game->setReductionVitesseTir(game->getReductionVitesseTir() + 1);
    }
}

void Bullet::changeVitesseDefilement()
{
    game->setAugmentationVitesseEnnemie(game->getAugmentationVitesseEnnemie() + 1);
}

void Bullet::changeVitesseDeplacement()
{
    game->setAugmentationVitesseDefilement(game->getAugmentationVitesseDefilement() + 1);
}

void Bullet::move()
{
    //Collision
    QList<QGraphicsItem *> collision = collidingItems();
    for (int i = 0, n = collision.size(); i< n; i++)
    {
        if (typeid(*(collision[i])) == typeid(MechantRare) || typeid(*(collision[i])) == typeid(MechantStandard) || typeid(*(collision[i])) == typeid(MechantLegendaire) || typeid(*(collision[i])) == typeid(MechantEpic))
        {
            //+1 score
            game->getScore()->increase();

            if(typeid(*(collision[i])) == typeid(MechantRare))
            {
                changeVitesseTir();
            }else if(typeid(*(collision[i])) == typeid(MechantEpic)){
                changeVitesseDefilement();
            }
            else if(typeid(*(collision[i])) == typeid(MechantLegendaire)){
                changeVitesseDeplacement();
            }

            scene()->removeItem(collision[i]);
            scene()->removeItem(this);

            delete collision[i];
            delete this;
            return;
        }
    }

    //faire monter le bullet
    setPos(x(),y() - (game->getVitesseTir() - game->getReductionVitesseTir()));
    if(pos().y() + 110 < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
