#ifndef GHOST_H
#define GHOST_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "character.h"
#include "map.h"

class Ghost : public QGraphicsItem, public Character
{
public:
    Ghost();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();

    void setColor(QString col);
    void changeGeometry() { prepareGeometryChange(); }
    void move(int, int, Map*);


    QPixmap left1,left2;
    QPixmap up1,up2;
    QPixmap down1,down2;
    QPixmap right1,right2;
    QPixmap scareb,scareb1,scarew,scarew1;

    bool is_Scared, whiteb;
    bool scared, start;
};

#endif // GHOST_H
