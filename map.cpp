#include "map.h"

Map::Map()
{
    mappic.load(":/images/pac_map.png");
    ball=new Ball;
    powerball=new PowerBall;

    AddPathPoints(30, 30, 200, 30);
    AddPathPoints(250, 30, 420, 30);
    AddPathPoints(30, 90, 420, 90);
    AddPathPoints(30, 130, 110, 130);
    AddPathPoints(150, 130, 200, 130);
    AddPathPoints(250, 130, 300, 130);
    AddPathPoints(340, 130, 420, 130);
    AddPathPoints(150, 180, 300, 180);
    AddPathPoints(0, 230, 150, 230);
    AddPathPoints(300, 230, 450, 230);
    AddPathPoints(150, 270, 300, 270);
    AddPathPoints(30, 320, 200, 320);
    AddPathPoints(250, 320, 420, 320);
    AddPathPoints(30, 360, 60, 360);
    AddPathPoints(110, 360, 340, 360);
    AddPathPoints(390, 360, 420, 360);
    AddPathPoints(30, 410, 110, 410);
    AddPathPoints(150, 410, 200, 410);
    AddPathPoints(250, 410, 300, 410);
    AddPathPoints(340, 410, 420, 410);
    AddPathPoints(30, 450, 420, 450);

    AddPathPoints(30, 30, 30, 130);
    AddPathPoints(30, 320, 30, 360);
    AddPathPoints(30, 410, 30, 450);
    AddPathPoints(60, 360, 60, 410);
    AddPathPoints(110, 30, 110, 410);
    AddPathPoints(150, 90, 150, 130);
    AddPathPoints(150, 180, 150, 320);
    AddPathPoints(150, 360, 150, 410);
    AddPathPoints(200, 30, 200, 90);
    AddPathPoints(200, 135, 200, 180);
    AddPathPoints(200, 320, 200, 360);
    AddPathPoints(200, 410, 200, 450);
    AddPathPoints(250, 30, 250, 90);
    AddPathPoints(250, 135, 250, 180);
    AddPathPoints(250, 320, 250, 360);
    AddPathPoints(250, 410, 250, 450);
    AddPathPoints(300, 90, 300, 130);
    AddPathPoints(300, 180, 300, 320);
    AddPathPoints(300, 360, 300, 410);
    AddPathPoints(340, 30, 340, 410);
    AddPathPoints(390, 360, 390, 410);
    AddPathPoints(420, 30, 420, 130);
    AddPathPoints(420, 320, 420, 360);
    AddPathPoints(420, 410, 420, 450);

    QPoint p;
    //QVector<QPoint> tmpvec;
    //int temp=0;
    QPoint p1,p2,p3,p4;
    p1.setX(30);
    p1.setY(450);
    p2.setX(30);
    p2.setY(35);
    p3.setX(420);
    p3.setY(35);
    p4.setX(420);
    p4.setY(450);
    powerballpoints.push_front(p1);
    powerballpoints.push_front(p2);
    powerballpoints.push_front(p3);
    powerballpoints.push_front(p4);

    for (int i=0; i<450-1; i++){
        for(int j=0;j<480-1;j++){
            p.setX(i);
            p.setY(j);

            if(j%10==0 && i%10==0){
                if (pacpoints.contains(p)){
                    //painter->drawLine(0, 260, 150, 260);
                    //painter->drawLine(300, 260, 450, 260);
                    if(p!=p1 && p!=p2 && p!=p3 && p!=p4){
                        if(p.x()>0) ballpoints.push_front(p);
                    }
                }
            }
        }
        /*for(int i=0;i<ballpoints.size();i+2){
              if(i%5==0){
                  ballpoints.pop_back();
              }
        }*/
    }
    generateBalls();
}

QRectF Map::boundingRect() const{
    return QRect(0,0,450,480);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,450,480,mappic);

    QPen pen=QPen(Qt::red);
    pen.setWidth(2);
    painter->setPen(pen);
}

void Map::advance()
{
}

void Map::generateBalls()
{
    QPainter painter;
    //QRect bounds = QRect(0, 0, 450, 550);
    //mappic = QPixmap(bounds.size());
    //mappic.fill(Qt::transparent);
    painter.begin(&mappic);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::yellow);
    for(int i=0;i<ballpoints.size();i++){
        //painter.drawPixmap( ballpoints[i].x(, ballpoints[i].y(), ballpix );
        painter.drawEllipse(ballpoints[i].x(),ballpoints[i].y(),3,3);
    }
    for(int i=0;i<powerballpoints.size();i++){
        //painter.drawPixmap( ballpoints[i].x(, ballpoints[i].y(), ballpix );
        painter.drawEllipse(powerballpoints[i].x()-5,powerballpoints[i].y()-5,10,10);
    }
}

bool Map::canmove(QPoint point){
    for(int i=0;i<pacpoints.size();i++){
        if(pacpoints[i]==point) return true;
    }
    return false;
}

void Map::fillpacpoints(int pacx, int pacy){
    QPainter painter;
    QRect rec(pacx,pacy,3,3);
    QRect rec2(pacx-5,pacy-5,10,10);
    painter.begin(&mappic);
    //painter.setBrush(Qt::black);
    painter.fillRect(rec,Qt::black);
    if((pacx==powerballpoints[0].x() && pacy==powerballpoints[0].y())||
           (pacx==powerballpoints[1].x() && pacy==powerballpoints[1].y())||
           (pacx==powerballpoints[2].x() && pacy==powerballpoints[2].y())||
           (pacx==powerballpoints[3].x() && pacy==powerballpoints[3].y())){
       painter.fillRect(rec2,Qt::black);
   }
   painter.end();
}

void Map::setballpoints(QVector<QPoint> points){
    ball->setpoints(points);
}

void Map::setpowerballpoints(QVector<QPoint> points){
    powerball->setpoints(points);
}

QVector<QPoint> Map::getballpoints(){
    return ballpoints;
}

QVector<QPoint> Map::getpowerballpoints(){
    return powerballpoints;
}
void Map::AddPathPoints(int x1, int y1, int x2, int y2){
    QPoint p;
    if (x1 == x2){
        if (y1 < y2){
            for (int y=y1; y<y2+1; y++){
                p.setX(x1);
                p.setY(y);//= new QPoint(x1, y);
                if (! pacpoints.contains(p)){pacpoints.push_front(p);
                    //if(y%25==0){ballpoints.push_front(p);}
                }
            }
        }
        else{
            for (int y=y1; y>y2-1; y--){
                p.setX(x1);
                p.setY(y);//= new QPoint(x1, y);
                if (! pacpoints.contains(p)){pacpoints.push_front(p);
                    //if(y%25==0){ballpoints.push_front(p);}
                }
            }
        }
    }
    else{
        if (x1 < x2){
            for (int x=x1; x<x2+1; x++){
                p.setX(x);
                p.setY(y1);//= new QPoint(x1, y);
                if (! pacpoints.contains(p)){pacpoints.push_front(p);
                    //if(x%25==0){ballpoints.push_front(p);}
                }
            }
        }
        else{
            for (int x=x1; x>x2-1; x--){
                p.setX(x);
                p.setY(y1);//= new QPoint(x1, y);
                if (! pacpoints.contains(p)){pacpoints.push_front(p);
                    //if(x%25==0){ballpoints.push_front(p);}
                }
            }
        }
    }

    /*
    for (int i=0; i<550-1; i++){
        for(int j=0;j<450-1;j++){
            p.setX(i);
            p.setY(j);
            if (pacpoints.contains(p)){
                if(j%25==0)  ballpoints.push_front(p);
            }
        }
    }
    */
}
