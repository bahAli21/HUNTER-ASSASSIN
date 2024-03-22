

#include "Player.h"
Player::Player() :health(100){
    playerDest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT};
    playerSource = new Rect{0,PLAYER_HEIGHT*8,PLAYER_WIDTH,PLAYER_HEIGHT};
    dest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT};
}

Player::~Player(){
    health=0;
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
