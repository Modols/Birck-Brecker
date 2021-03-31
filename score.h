#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsTextItem>
#include "mechants.h"

class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsTextItem * parent=0);
    void increase();
    int getScore();

private:
    int score;
    int compteur;
};

#endif // SCORE_H
