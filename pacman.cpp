#include "pacman.h"

Pacman::Pacman():Character(){
    animestate=0;

    posx=410/2;
    posy=360;
    direction=4;
    right1.load(":/images/pacclose.png");
    right2.load(":/images/pacopen1.png");
    right3.load(":/images/pacopen2.png");
    right4.load(":/images/pacopen3.png");

    up1.load(":/images/paccloseu.png");
    up2.load(":/images/pacopen1u.png");
    up3.load(":/images/pacopen2u.png");
    up4.load(":/images/pacopen3u.png");

    down1.load(":/images/pacclosed.png");
    down2.load(":/images/pacopen1d.png");
    down3.load(":/images/pacopen2d.png");
    down4.load(":/images/pacopen3d.png");

    left1.load(":/images/pacclosel.png");
    left2.load(":/images/pacopen1l.png");
    left3.load(":/images/pacopen2l.png");
    left4.load(":/images/pacopen3l.png");
}

QRectF Pacman::boundingRect() const{
    return QRect(posx-15, posy-15, 20, 20);
}

void Pacman::advance(){
    if(animestate>6) animestate = 0;
    else animestate++;
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    switch(direction){
    case 1:
        if(animestate<2) painter->drawPixmap(posx-15,posy-15,30,30,left1);
        else if(animestate<4) painter->drawPixmap(posx-15,posy-15,30,30,left2);
        else if(animestate<6) painter->drawPixmap(posx-15,posy-15,30,30,left3);
        else if(animestate<8) painter->drawPixmap(posx-15,posy-15,30,30,left4);
        break;

    case 4:
        if(animestate<2) painter->drawPixmap(posx-15,posy-15,30,30,right1);
        else if(animestate<4) painter->drawPixmap(posx-15,posy-15,30,30,right2);
        else if(animestate<6) painter->drawPixmap(posx-15,posy-15,30,30,right3);
        else if(animestate<8) painter->drawPixmap(posx-15,posy-15,30,30,right4);
        break;

    case 3:
        if(animestate<2) painter->drawPixmap(posx-15,posy-15,30,30,down1);
        else if(animestate<4) painter->drawPixmap(posx-15,posy-15,30,30,down2);
        else if(animestate<6) painter->drawPixmap(posx-15,posy-15,30,30,down3);
        else if(animestate<8) painter->drawPixmap(posx-15,posy-15,30,30,down4);
        break;

    case 2:
        if(animestate<2) painter->drawPixmap(posx-15,posy-15,30,30,up1);
        else if(animestate<4) painter->drawPixmap(posx-15,posy-15,30,30,up2);
        else if(animestate<6) painter->drawPixmap(posx-15,posy-15,30,30,up3);
        else if(animestate<8) painter->drawPixmap(posx-15,posy-15,30,30,up4);
        break;
    }
}

void Pacman::move(Map *pac_map){
    QPoint p;
    if(nextdirection!=direction){
        switch(nextdirection){
        case 1:
            p.setX(posx-5);
            p.setY(posy);
            break;

        case 2:
            p.setX(posx);
            p.setY(posy-5);
            break;

        case 3:
            p.setX(posx);
            p.setY(posy+5);
            break;

        case 4:
            p.setX(posx+5);
            p.setY(posy);
            break;
        }
        if(pac_map->canmove(p)){
            direction = nextdirection;
            nextdirection = 0;
        }
    }

    switch(direction){
    case 1:
        p.setX(posx-5);
        p.setY(posy);
        setDirection(direction);
        if(pac_map->canmove(p)){
            posx -= 5;
            moving = true;
        }
        else moving = false;
        break;

    case 2:
        p.setX(posx);
        p.setY(posy-5);
        setDirection(direction);
        if(pac_map->canmove(p)){
            posy -= 5;
            moving = true;
        }
        else moving = false;
        break;

    case 3:
        p.setX(posx);
        p.setY(posy+5);
        setDirection(direction);
        if(pac_map->canmove(p)){
            posy += 5;
            moving = true;
        }
        else moving = false;
        break;

    case 4:
        p.setX(posx+5);
        p.setY(posy);
        setDirection(direction);
        if(pac_map->canmove(p)){
            posx += 5;
            moving = true;
        }
        else moving = false;
        break;
    }
    if(posx<=0){
        posx = 450;
        posy = 230;
    }
    else if(posx>=450){
        posx = 0;
        posy = 230;
    }
}
