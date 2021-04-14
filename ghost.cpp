#include "ghost.h"

Ghost::Ghost():Character(){
    animestate=0;

    posx=450/2;
    posy=480/2;

    direction=1;
    is_Scared=false;
    whiteb=false;
    right1.load(":/images/ghostright1.png");
    right2.load(":/images/ghostright2.png");
    up1.load(":/images/ghostup1.png");
    up2.load(":/images/ghostup2.png");
    down1.load(":/images/ghostdown1.png");
    down2.load(":/images/ghostdown2.png");
    left1.load(":/images/ghostleft1.png");
    left2.load(":/images/ghostleft2.png");
    scareb.load(":/images/ghostscaredblue1.png");
    scareb1.load(":/images/ghostscaredblue2.png");
    scarew.load(":/images/ghostscaredwhite1.png");
    scarew1.load(":/images/ghostscaredwhite2.png");

    scared = false;
    start = false;
}

QRectF Ghost::boundingRect() const{
    return QRect(posx-15,posy-15,20,20);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //painter->setOpacity(0.3);
    if(!is_Scared){
        switch(direction){
        case 1:
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,left1);
            else painter->drawPixmap(posx-15,posy-15,30,30,left2);
            break;

        case 4:
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,right1);
            else painter->drawPixmap(posx-15,posy-15,30,30,right2);
            break;

        case 3:
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,down1);
            else painter->drawPixmap(posx-15,posy-15,30,30,down2);
            break;

        case 2:
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,up1);
            else painter->drawPixmap(posx-15,posy-15,30,30,up2);
            break;
        }
    }
    else{
        if(whiteb){
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,scareb);
            else painter->drawPixmap(posx-15,posy-15,30,30,scarew1);
        }
        else{
            if(animestate==0) painter->drawPixmap(posx-15,posy-15,30,30,scareb);
            else painter->drawPixmap(posx-15,posy-15,30,30,scareb1);
        }
    }
}

void Ghost::advance(){
    if(animestate>6) animestate = 0;
    else animestate++;
}

void Ghost::setColor(QString col){
    if(col=="blue"){
        right1.load(":/images/ghostrightblue1.png");
        right2.load(":/images/ghostrightblue2.png");
        up1.load(":/images/ghostupblue1.png");
        up2.load(":/images/ghostupblue2.png");
        down1.load(":/images/ghostdownblue1.png");
        down2.load(":/images/ghostdownblue2.png");
        left1.load(":/images/ghostleftblue1.png");
        left2.load(":/images/ghostleftblue2.png");
    }
    else if(col=="orange"){
        right1.load(":/images/ghostrightorange1.png");
        right2.load(":/images/ghostrightorange2.png");
        up1.load(":/images/ghostuporange1.png");
        up2.load(":/images/ghostuporange2.png");
        down1.load(":/images/ghostdownorange1.png");
        down2.load(":/images/ghostdownorange2.png");
        left1.load(":/images/ghostleftorange1.png");
        left2.load(":/images/ghostleftorange2.png");
    }
    else if(col=="red"){
        right1.load(":/images/ghostrightred1.png");
        right2.load(":/images/ghostrightred2.png");
        up1.load(":/images/ghostupred1.png");
        up2.load(":/images/ghostupred2.png");
        down1.load(":/images/ghostdownred1.png");
        down2.load(":/images/ghostdownred2.png");
        left1.load(":/images/ghostleftred1.png");
        left2.load(":/images/ghostleftred2.png");
    }
}

void Ghost::move(int pacx, int pacy, Map *pac_map){
    QPoint p;
    if(!moving) direction = (qrand()%4)+1;
    else{
        if((direction==4 && posy<pacy) || (direction==1 && posy>pacy)){
            if(direction==1 && posy>pacy) nextdirection = 2;
            else nextdirection = 3;
        }
        else if((direction==3 && posx<pacx) || (direction==2 && posx>pacx)){
            if(direction==2 && posx>pacx) nextdirection = 1;
            else nextdirection = 4;
        }
    }

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
