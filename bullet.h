#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include<QGraphicsItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent=NULL);
    ~Bullet();
    void changeVitesseTir();
    void changeVitesseDefilement();
    void changeVitesseDeplacement();

public slots:
    void move();
private:
    QTimer * timer;
};

#endif // BULLET_H
