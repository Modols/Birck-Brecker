#ifndef ETOILES_H
#define ETOILES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>


using namespace std;

class Etoiles: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Etoiles(QGraphicsItem *parent=NULL);
    ~Etoiles();

private:
    QTimer *timer;

public slots:
    void move();

};

#endif // ETOILES_H
