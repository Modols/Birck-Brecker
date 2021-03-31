#include "button.h"
#include <QBrush>
#include <QGraphicsTextItem>
#include <QDebug>


Button::Button( QString const name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    color = new QColor(191,62,171);
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*color);
    setBrush(brush);

    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

Button::~Button()
{
    delete text;

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //chnage color on hover
    colorHover = new QColor(223,67,199);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*colorHover);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    color = new QColor(191,62,171);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*color);
    setBrush(brush);
}
