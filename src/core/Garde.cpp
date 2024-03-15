
#include "Garde.h"

Garde::Garde() :health(50){
    pos={WINDOW_W/2,PLAYER_HEIGHT+20};
}

Garde::~Garde(){
    pos={0,0};
    health=0;
}

void Garde::goLeft(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.x-1);
}

void Garde::goRight(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.x+1);
}

void Garde::goUp(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.y-1);
}

void Garde::goDown(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.y+1);
}

void Garde::testRegression() {
    Garde Garde;
    assert(WINDOW_W/2 == Garde.getPosition().x && WINDOW_H-PLAYER_HEIGHT == Garde.getPosition().y);
    Garde.setPositionX(WINDOW_X);
    assert(WINDOW_X == Garde.getPosition().x);
    Garde.setPositionY(WINDOW_Y);
    assert(WINDOW_Y == Garde.getPosition().y);
    assert(Garde.getHealth() == 100);
    Garde.setHealth(50);
    assert(Garde.getHealth() == 50);
    std::cout<<"Test de regression complete"<<std::endl;
}