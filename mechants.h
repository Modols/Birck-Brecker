#ifndef MECHANTS_H
#define MECHANTS_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>



class Mechants: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Mechants(QGraphicsItem *parent=NULL);
    ~Mechants();
    QTimer * timer;

    int getVitesse() const;
    void setVitesse(int value);

    bool getIsDead() const;
    void setIsDead(bool value);

    void pause();
    void resume();

private:
    int vitesse;
    bool isDead=false;

public slots:
    void move();
};



#endif // MECHANTS_H
