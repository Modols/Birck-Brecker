#ifndef VIE_H
#define VIE_H

#include <QGraphicsTextItem>

class Vie: public QGraphicsTextItem
{
public:
    Vie(QGraphicsTextItem * parent=0);
    void decrease();
    int getVie();

private:
    int vie;
};

#endif // VIE_H


