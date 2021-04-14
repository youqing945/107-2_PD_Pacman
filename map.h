#ifndef MAP_H
#define MAP_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>
#include "ball.h"
#include "powerball.h"
class Map : public QGraphicsItem
{

public:
    Map();
    Ball *ball;
    PowerBall *powerball;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();
    void generateBalls();
    void AddPathPoints(int, int, int, int);
    bool canmove(QPoint);
    void fillpacpoints(int pacx,int pacy);
    void setballpoints(QVector<QPoint> points);
    void setpowerballpoints(QVector<QPoint> points);

    void changeGeometry() { prepareGeometryChange(); }

    QVector<QPoint> getballpoints();
    QVector<QPoint> getpowerballpoints();
    QPixmap mappic;
    QVector<QPoint> pacpoints,ballpoints;
    QVector<QPoint> powerballpoints;
    //QPoint peos[];
};

#endif // MAP_H
