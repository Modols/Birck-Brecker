#include "etoiles.h"
#include <QDebug>

Etoiles::Etoiles(QGraphicsItem *parent)
{
    int randomEtoile = rand() % 2;

    if(randomEtoile == 0){
        setPixmap(QPixmap(":/Images/images/Etoile-blanche.png"));
    }else if(randomEtoile == 1){
        setPixmap(QPixmap(":/Images/images/Etoile-bleu.png"));
    }

    int random_number = rand() % 700;
    setPos(random_number, -10);

    int randomTimer = rand() % 19 + 20;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(randomTimer);
}

Etoiles::~Etoiles()
{
    delete timer;
}

void Etoiles::move()
{
    setPos(x(),y() + 10);
    if(pos().y()  > 600)
    {
        scene()->removeItem(this);
        delete this;
    }
}
