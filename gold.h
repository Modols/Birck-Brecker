#ifndef GOLD_H
#define GOLD_H


#include <QGraphicsTextItem>
#include <QtDebug>



class Gold: public QGraphicsTextItem
{

public:
    Gold(QGraphicsTextItem * parent=0);
    void increase();
    int getGold() const;
    void setGold(int value);

private:
    int gold;
};



#endif // GOLD_H
