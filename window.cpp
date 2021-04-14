#include "window.h"
#include "ui_window.h"
#include <QThread>

window::window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window)
{
    score=0;
    gosx=450/2;
    gosy=480/2;
    gosx1=450/2;
    gosy1=480/2;
    gosx2=450/2;
    gosy2=480/2;
    gosx3=450/2;
    gosy3=480/2;
    pacx=410/2;
    pacy=360;
    ghostmoving=false;
    ghostmoving1=false;
    ghostmoving2=false;
    ghostmoving3=false;
    scared=false;
    scared1=false;
    scared2=false;
    scared3=false;
    start=false;
    direction=0;
    moving=false;
    delayb=false;
    playing=false;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(0,0,640,480);
    ui->graphicsView->setSceneRect(scene->sceneRect());
    pacman=new Pacman;
    pacx=410/2;
    //pacy=410;


    text=new Textdrawing;
    text->over=false;
    scene->addItem(text);
    text->setZValue(7);

}

void window::start_Game(){

    gosx=450/2;
    gosy=480/2;
    gosx1=450/2;
    gosy1=480/2;
    gosx2=450/2;
    gosy2=480/2;
    gosx3=450/2;
    gosy3=480/2;

    pacx=410/2;
    pacy=360;
    pac_map=new Map;

    pinky = new Ghost;
    clyde = new Ghost;
    blinky = new Ghost;
    inky = new Ghost;

    clyde->setColor("orange");
    blinky->setColor("red");
    inky->setColor("blue");
    ballpoints=pac_map->getballpoints();
    Powerballpoints=pac_map->getpowerballpoints();

    ball=new Ball;
    powerball=new PowerBall;
    ball->setpoints(ballpoints);
    scene->removeItem(text);
    powerball->setpoints(Powerballpoints);

    scene->addItem(pac_map);
    scene->addItem(pacman);
    scene->addItem(pinky);
    scene->addItem(clyde);
    scene->addItem(blinky);
    scene->addItem(inky);
    scene->addItem(text);

    text->playing=true;
    ghostmoving=false;
    ghostmoving1=false;
    ghostmoving2=false;
    ghostmoving3=false;
    direction=0;
    moving=false;
    ghoststart=false;
    ghoststart1=false;
    ghoststart2=false;
    ghoststart3=false;

    state=0;

    timer = new QTimer(this);
    ghoststimer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(updater()));
    connect(ghoststimer, SIGNAL(timeout()), this,SLOT(ghostupdater()));
    this->show();
    scene->update();
    this->update();
    delayb=true;

    timer->start(30);
    ghoststimer->start(45);
    this->setFocus();
}

void window::delay(){
    QTime dieTime= QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime ){}
    delayb=false;
}

void window::end_Game(){
    text->over=true;
    text->playing=false;
    scene->removeItem(pac_map);
    scene->removeItem(pacman);
    scene->removeItem(pinky);
    scene->removeItem(clyde);
    scene->removeItem(blinky);
    scene->removeItem(inky);
    score=0;
    playing=false;
    scene->update();
}

void window::pacman_move(){
    QPoint p;
    if(nextdirection!=direction){
        switch(nextdirection){
        case 1:
            p.setX(pacx-5);
            p.setY(pacy);
            if(pac_map->canmove(p)){
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 4:
            p.setX(pacx+5);
            p.setY(pacy);
            if(pac_map->canmove(p)){
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 3:
            p.setX(pacx);
            p.setY(pacy+5);
            if(pac_map->canmove(p)){
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 2:
            p.setX(pacx);
            p.setY(pacy-5);
            if(pac_map->canmove(p)){
                direction=nextdirection;
                nextdirection=0;
            }
            break;
        }

    }

    switch(direction){
    case 1:
        p.setX(pacx-5);
        p.setY(pacy);
        pacman->setDirection(direction);

        if(pac_map->canmove(p)){
            pacx-=5;
            moving=true;
        }
        else moving=false;
        break;

    case 4:
        pacman->setDirection(direction);
        p.setX(pacx+5);
        p.setY(pacy);
        if(pac_map->canmove(p)){
            pacx+=5;
            moving=true;
        }
        else moving=false;
        break;

    case 3:
        pacman->setDirection(direction);
        p.setX(pacx);
        p.setY(pacy+5);
        if(pac_map->canmove(p)){
            pacy+=5;
            moving=true;
        }
        else moving=false;
        break;

    case 2:
        pacman->setDirection(direction);
        p.setX(pacx);
        p.setY(pacy-5);
        if(pac_map->canmove(p)){
            pacy-=5;
            moving=true;
        }
        else moving=false;
        break;
    }

    if(pacx<=0){
        pacx=450;
        pacy=230;
    }
    else if(pacx>=450){
        pacx=0;
        pacy=230;
    }


    pacman->setx(pacx);
    pacman->sety(pacy);

}

void window::moveghostsinrect3(){
    if(gosx3==450/2+40 || gosx3==450/2-40){
        if(ghostdir3==4) ghostdir3=1;
        else ghostdir3=4;
    }

    if(ghostdir3==4) gosx3-=5;
    else gosx3+=5;

    inky->setx(gosx3);
    inky->sety(gosy3);
}

void window::moveghostsinrect2(){
    if(gosx2==450/2+40 || gosx2==450/2-40){
        if(ghostdir2==4) ghostdir2=1;
        else ghostdir2=4;
    }

    if(ghostdir2==4) gosx2+=5;
    else gosx2-=5;

    blinky->setx(gosx2);
    blinky->sety(gosy2);
}

void window::moveghostsinrect1(){
    if(gosx1==450/2+40 || gosx1==450/2-40){
        if(ghostdir1==4) ghostdir1=1;
        else ghostdir1=4;
    }

    if(ghostdir1==4) gosx1+=5;
    else gosx1-=5;

    clyde->setx(gosx1);
    clyde->sety(gosy1);
}

void window::moveghostsinrect(){
    if(gosx==450/2+40 || gosx==450/2-40){
        if(ghostdir==4) ghostdir=1;
        else ghostdir=4;
    }

    if(ghostdir==4) gosx+=5;
    else gosx-=5;

    pinky->setx(gosx);
    pinky->sety(gosy);
}

void window::checklost(){
    if(ballpoints.isEmpty()){
        timer->stop();
        ghoststimer->stop();
        end_Game();
    }

    if(pacman->collidesWithItem(pinky) ||
            pacman->collidesWithItem(clyde) ||
            pacman->collidesWithItem(blinky) ||
            pacman->collidesWithItem(inky)){
        if(scared){
            score+=100;
            if(pacman->collidesWithItem(pinky)){
                gosx=450/2;
                gosy=450/2;
                ghoststart=false;
            }
            if(pacman->collidesWithItem(clyde)){
                gosx1=450/2;
                gosy1=450/2;
                ghoststart1=false;
            }
            if(pacman->collidesWithItem(blinky)){
                gosx2=450/2;
                gosy2=450/2;
                ghoststart2=false;
            }
            if(pacman->collidesWithItem(inky)){
                gosx3=450/2;
                gosy3=450/2;
                ghoststart3=false;
            }
            //chomp->play("sounds/pacman_eatghost.wav");
        }
        else{
            //chomp->play("sounds/pacman_death.wav");
            delay();
            timer->stop();
            ghoststimer->stop();
            end_Game();
        }
    }
}

void window::keyPressEvent(QKeyEvent *event){

    QPoint p;
    switch(event->key()){
    /*case Qt::Key_Left:
        if(!pacman->moving) pacman->direction=1;
        else pacman->nextdirection=1;
        break;

    case Qt::Key_Right:
        if(!pacman->moving) pacman->direction=4;
        else pacman->nextdirection=4;
        break;

    case Qt::Key_Down:
        if(!pacman->moving) pacman->direction=3;
        else pacman->nextdirection=3;
        break;

    case Qt::Key_Up:
        if(!pacman->moving) pacman->direction=2;
        else pacman->nextdirection=2;
        break;
        */
    case Qt::Key_Left:
        if(!moving) direction=1;
        else nextdirection=1;
        break;

    case Qt::Key_Right:
        if(!moving) direction=4;
        else nextdirection=4;
        break;

    case Qt::Key_Down:
        if(!moving) direction=3;
        else nextdirection=3;
        break;

    case Qt::Key_Up:
        if(!moving) direction=2;
        else nextdirection=2;
        break;

    case Qt::Key_Space:
        if(!playing){
            start_Game();
            playing=true;
        }
        else{
            end_Game();
            start_Game();
        }
        break;

    default:
        break;
    }
    //}
}

int scarestate=0;
int soundstate=0;
void window::updater(){
    checklost();
    pacman_move();
    pacman->move(pac_map);

    for(int i=0;i<ballpoints.size();i++){
        if(pacman->posx==ballpoints[i].x() && pacman->posy==ballpoints[i].y()){
            ballpoints.remove(i);
            score++;
            text->score=score;
        }
    }

    for(int i=0;i<Powerballpoints.size();i++){
        if(pacman->posx==Powerballpoints[i].x() && pacman->posy==Powerballpoints[i].y()){
            Powerballpoints.remove(i);
            if(scared){scarestate=0;}
            scared=true;
        }
    }

    if(scared){
        pinky->is_Scared=true;
        clyde->is_Scared=true;
        blinky->is_Scared=true;
        inky->is_Scared=true;
        scarestate+=1;
        if(scarestate==1) ghoststimer->setInterval(80);
        if(scarestate==100){
            pinky->whiteb=true;
            clyde->whiteb=true;
            blinky->whiteb=true;
            inky->whiteb=true;
        }
        if(scarestate==150){
            scared=false; scarestate=0; ghoststimer->setInterval(45);
            pinky->whiteb=false;
            clyde->whiteb=false;
            blinky->whiteb=false;
            inky->whiteb=false;
        }
    }
    else{
        pinky->is_Scared=false;
        clyde->is_Scared=false;
        blinky->is_Scared=false;
        inky->is_Scared=false;
    }
    ball->setpoints(ballpoints);
    powerball->setpoints(Powerballpoints);
    pac_map->setballpoints(ballpoints);
    pac_map->setpowerballpoints(Powerballpoints);
    pac_map->fillpacpoints(pacx,pacy);
    pacman->advance();
    pinky->advance();
    clyde->advance();
    blinky->advance();
    inky->advance();
    this->setFocus();
    scene->update(pac_map->boundingRect());
    if(delayb) delay();
}

void window::ghostupdater(){
    if(ghoststart || ghoststart1 || ghoststart2 || ghoststart3){
        if(ghoststart) pinky->move(pacx, pacy, pac_map);
        if(ghoststart1) clyde->move(pacx, pacy, pac_map);
        if(ghoststart2) blinky->move(pacx, pacy, pac_map);
        if(ghoststart3) inky->move(pacx, pacy, pac_map);

    }

    if(gosx3==450/2) state++;
    if(state==3){
        start=true;
        state=0;
    }
    if(!start){
        moveghostsinrect3();
        moveghostsinrect2();
        moveghostsinrect1();
        moveghostsinrect();
    }
    else if(!ghoststart3 || !ghoststart2 || !ghoststart1 || !ghoststart){
        QPoint p,p1,p2,p3;
        if(!ghoststart3){
            gosy3-=5;
            inky->setx(gosx3);
            inky->sety(gosy3);
            p3.setX(gosx3);
            p3.setY(gosy3);
            if(pac_map->pacpoints.contains(p3)){ghoststart3=true;}
        }
        if(!ghoststart2){
            gosy2-=5;
            blinky->setx(gosx2);
            blinky->sety(gosy2);
            p2.setX(gosx2);
            p2.setY(gosy2);
            if(pac_map->pacpoints.contains(p2)){ghoststart2=true;}
        }
        if(!ghoststart1){
            gosy1-=5;
            clyde->setx(gosx1);
            clyde->sety(gosy1);
            p1.setX(gosx1);
            p1.setY(gosy1);
            if(pac_map->pacpoints.contains(p1)){ghoststart1=true;}
        }
        if(!ghoststart){
            gosy-=5;
            pinky->setx(gosx);
            pinky->sety(gosy);
            p.setX(gosx);
            p.setY(gosy);
            if(pac_map->pacpoints.contains(p)){ghoststart=true;}
        }
    }
    if(delayb) delay();
}

window::~window(){
    delete ui;
}
