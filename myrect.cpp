#include "myrect.h"
#include "bullet.h"
#include "mechants.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <qtimer.h>
#include <iostream>
#include "game.h"

extern Game * game;

using namespace std;


MyRect::MyRect(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/Images/images/Joueur.png"));

    timerKillMechant = new QTimer();
    QObject::connect(timerKillMechant,SIGNAL(timeout()),this,SLOT(cleanEnemies()));
    timerKillMechant->start(10);
}

MyRect::~MyRect()
{
    delete timerKillMechant;
}

void MyRect::keyPressEvent(QKeyEvent *event)
{
    if(game->getTimer()->isActive() == true){
        if (event->key() == Qt::Key_Left){
            if (pos().x() > 0)
                setPos(x()- game->getVitesseDeplacement(), y());
        }
        else if (event->key() == Qt::Key_Right){
            if (pos().x() +100 < 800)
                setPos(x()+ (game->getVitesseDeplacement() + game->getAugmentationVitesseDefilement()), y());
        }
        else if (event->key() == Qt::Key_Space){
            shoot();
        }
        else if (event->key() == Qt::Key_P){
            game->pause();
        }
    }else{
        if (event->key() == Qt::Key_P){
            game->resume();
        }
    }
}

void MyRect::shoot()
{
    bullet = new Bullet();
    if (changeSideBullet == 0)
    {
        bullet->setPos(x()-25,y()-30);
        scene()->addItem(bullet);
        changeSideBullet++;
    }else{
        bullet->setPos(x(),y()-30);
        scene()->addItem(bullet);
        changeSideBullet = 0;
    }
}

void MyRect::spawn()
{
    //random de 0 à 99
    int random_number = rand() % 100;
    int randomMechant = rand() % 3;

    if (random_number<=9)
    {
        if(randomMechant == 0){
            mechantRare = new MechantRare();
            lesMechants.push_back(mechantRare);
            scene()->addItem(mechantRare);
        }else if(randomMechant == 1){
            mechantEpic = new MechantEpic();
            lesMechants.push_back(mechantEpic);
            scene()->addItem(mechantEpic);
        }else if(randomMechant == 2){
            mechantLegendaire = new MechantLegendaire();
            lesMechants.push_back(mechantLegendaire);
            scene()->addItem(mechantLegendaire);
        }
    }
    else
    {
        mechantstandard = new MechantStandard();
        lesMechants.push_back(mechantstandard);
        scene()->addItem(mechantstandard);
    }
    cleanEnemies();

}

void MyRect::cleanEnemies()
{
    int i = 0;

    for(auto mechant:getLesMechants()){
        if(mechant->getIsDead()){
            mechant = nullptr;
            lesMechants.erase(lesMechants.begin()+i);
            delete mechant;
        }
        i++;
    }
}

void MyRect::spawnEtoile()
{
    etoile = new Etoiles;
    scene()->addItem(etoile);
}

Bullet *MyRect::getBullet() const
{
    return bullet;
}

vector<Mechants *> MyRect::getLesMechants() const
{
    return lesMechants;
}
