#ifndef CHARACTER_H
#define CHARACTER_H


class Character{
public:
    Character();
    void setx(int);
    void sety(int);
    void setDirection(int);
    virtual void move(){
    }

public:
    int posx, posy;
    int direction;
    int nextdirection;
    bool moving;

    int animestate;
};

#endif // CHARACTER_H
