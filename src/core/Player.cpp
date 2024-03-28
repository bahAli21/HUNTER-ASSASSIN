

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
    // Augmentation de la zone de test sur la gauche et vers le haut
    int playerLeft = playerDest->x - 29; // Ajout d'un décalage à gauche
    int playerRight = playerDest->x + playerDest->w;
    int playerTop = playerDest->y - 20; // Ajout d'un décalage vers le haut
    int playerBottom = playerDest->y + playerDest->h;

    // Vérifie si une flèche existe déjà dans tout le rectangle du joueur
    bool arrowExistsInPlayerRect = false;
    for (const auto& arrow : listArrow) {
        // Vérifie si les coordonnées de la flèche se trouvent dans le rectangle du joueur étendu
        if (arrow.arrowPos.x >= playerLeft && arrow.arrowPos.x <= playerRight &&
            arrow.arrowPos.y >= playerTop && arrow.arrowPos.y <= playerBottom) {
            arrowExistsInPlayerRect = true;
            break;
        }
    }

    // Si aucune flèche n'existe dans le rectangle du joueur, ajoutez une nouvelle flèche
    if (!arrowExistsInPlayerRect) {
        // Calcul des coordonnées du centre du joueur
        int playerCenterX = (playerDest->x + playerDest->w / 2) - 20;
        int playerCenterY = (playerDest->y + playerDest->h / 2) - 20;

        Arrow b{};
        b.arrowPos = {playerCenterX, playerCenterY};
        b.direction = this->direction;
        if (b.direction == 0) {
            b.angleRotate = -90;
            b.speed = -ARR_SPEED;
        } else if (b.direction == 1) {
            b.angleRotate = 360;
            b.speed = +ARR_SPEED;
        } else if (b.direction == 2) {
            b.angleRotate = 90;
            b.speed = +ARR_SPEED;
        } else {
            b.angleRotate = 180;
            b.speed = -ARR_SPEED;
        }
        listArrow.push_back(b);
    }
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
