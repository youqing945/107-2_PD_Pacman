#ifndef PACMAN_H
#define PACMAN_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "character.h"
#include "map.h"

class Pacman : public QGraphicsItem, public Character
{

public:
    Pacman();
    QRectF boundingRect() const;
    void advance();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void changeGeometry() { prepareGeometryChange(); }
    void move(Map*);

    QPixmap left1,left2,left3,left4;
    QPixmap up1,up2,up3,up4;
    QPixmap down1,down2,down3,down4;
    QPixmap right1,right2,right3,right4;

};

#endif // PACMAN_H
