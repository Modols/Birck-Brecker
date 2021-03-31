#ifndef MYRECT_H
#define MYRECT_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>
#include "bullet.h"
#include "mechants.h"
#include "etoiles.h"
#include "mechantrare.h"
#include "mechantstandard.h"
#include "mechantepic.h"
#include "mechantlegendaire.h"

using namespace std;

class MyRect: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MyRect(QGraphicsItem *parent=NULL);
    ~MyRect();
    void keyPressEvent(QKeyEvent* event);

    void shoot();

    vector<Mechants *> getLesMechants() const;

    Bullet *getBullet() const;


private:
    int changeSideBullet=0;
    vector<Mechants*> lesMechants;
    MechantLegendaire *mechantLegendaire;
    MechantEpic *mechantEpic;
    MechantRare *mechantRare;
    MechantStandard *mechantstandard;
    QTimer *timerKillMechant;
    Bullet * bullet;
    Etoiles *etoile;

public slots:
    void spawn();
    void cleanEnemies();
    void spawnEtoile();
};

#endif // MYRECT_H
