#include "character.h"

Character::Character(){
    animestate = 0;
    moving = false;
}

void Character::setx(int i){
    posx = i;
}

void Character::sety(int i){
    posy = i;
}

void Character::setDirection(int i){
    direction = i;
}
