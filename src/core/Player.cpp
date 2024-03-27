

#include "Player.h"
Player::Player() :health(100){
    playerDest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT*2};
    playerSource = new Rect{PLAYER_WIDTH/2,PLAYER_HEIGHT*21,PLAYER_WIDTH,PLAYER_HEIGHT*2};
    dest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT};
}

Player::~Player(){
    health=0;
}

void Player::createArrow() {
    Arrow b{};
    b.arrowPos = {playerDest->x, playerDest->y};
    b.direction = this->direction;
    if(direction == 0)
        b.angleRotate = -90;
    else if(direction == 1)
        b.angleRotate = 360;
    else if(direction == 2)
        b.angleRotate = 90;
    else if(direction == 3)
        b.angleRotate = 180;

    listArrow.push_back(b);
}

void Player::goLeft() const {
        playerDest->x-=1;
}

void Player::goRight() const {
        playerDest->x+=1;
}

void Player::goUp() const {
        playerDest->y-=1;
}

void Player::goDown() const {
        playerDest->y+=1;
}
