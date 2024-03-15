

#include "Player.h"
Player::Player() :health(100){
    pos={WINDOW_W/2,WINDOW_H-PLAYER_HEIGHT-20};
}

Player::~Player(){
    pos={0,0};
    health=0;
}

void Player::goLeft(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.x-1);
}

void Player::goRight(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.x+1);
}

void Player::goUp(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.y-1);
}

void Player::goDown(const Map &map) {
    if(map.freePixel(pos.x,pos.y))
        setPositionX(pos.y+1);
}

void Player::testRegression() {
    Player player;
    assert(WINDOW_W/2 == player.getPosition().x && WINDOW_H-PLAYER_HEIGHT == player.getPosition().y);
    player.setPositionX(WINDOW_X);
    assert(WINDOW_X == player.getPosition().x);
    player.setPositionY(WINDOW_Y);
    assert(WINDOW_Y == player.getPosition().y);
    assert(player.getHealth() == 100);
    player.setHealth(50);
    assert(player.getHealth() == 50);
    std::cout<<"Test de regression complete"<<std::endl;
}