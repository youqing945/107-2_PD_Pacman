#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "pacman.h"
#include "map.h"
#include "ball.h"
#include "ghost.h"
#include "powerball.h"
#include "textdrawing.h"
#include "character.h"

namespace Ui {
class window;
}

class window : public QDialog
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = nullptr);
    void pacman_move();
    void moveghostsinrect3();
    void moveghostsinrect2();
    void moveghostsinrect1();
    void moveghostsinrect();
    void checklost();
    void delay();
    void start_Game();
    void end_Game();


    Pacman *pacman;
    Ghost *pinky;
    Ghost *clyde;
    Ghost *blinky;
    Ghost *inky;


    Map *pac_map;
    Ball *ball;
    PowerBall *powerball;
    Textdrawing *text;

    int pacx,pacy,direction,nextdirection;
    int gosx,gosy,ghostdir,nextghostdir;
    int gosx1,gosy1,ghostdir1,nextghostdir1;
    int gosx2,gosy2,ghostdir2,nextghostdir2;
    int gosx3,gosy3,ghostdir3,nextghostdir3;
    bool moving,ghostmoving,ghostmoving1,ghostmoving2,ghostmoving3;
    bool scared,scared1,scared2,scared3;
    int score,state;
    bool start,delayb;
    bool ghoststart,ghoststart1,ghoststart2,ghoststart3;
    bool playing;
    QVector<QPoint> ballpoints;
    QVector<QPoint> Powerballpoints;
    //QSound *chomp;
    QThread *sleeper;
    ~window();

public slots:
    void updater();
    void ghostupdater();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::window *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *ghoststimer;
};

#endif // WINDOW_H
