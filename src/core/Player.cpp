

#include "Player.h"
Player::Player() :health(100){
    playerDest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT*2};
    playerSource = new Rect{PLAYER_WIDTH/2,PLAYER_HEIGHT*27,PLAYER_WIDTH,PLAYER_HEIGHT*2};
    dest = new Rect{WINDOW_W/2-70,WINDOW_H-PLAYER_HEIGHT*4, PLAYER_WIDTH, PLAYER_HEIGHT};
    loadClips();
    //this->direction = 1;
    //shootKey = 's';
}

Player::~Player(){
    health=0;
}

void Player::Walk(Position *tabPos, int index) {
    for (int i = 0; i < 8; ++i) {
        tabPos[i].x = (i*2) * (WIDTH_A);
        tabPos[i].y = HEIGHT_A * index;
    }
}

void Player::AttackInit(Position *tabPos, int index) {
    for (int i = 0; i <=12; ++i) {
        tabPos[i].x = (i)*(WIDTH_A);
        tabPos[i].y = (HEIGHT_A) * index;
    }
}

void Player::makeAnimation(int index, Position *tabPos) {
    playerSource->x = tabPos[index].x;
    playerSource->y = tabPos[index].y;
    playerSource->w = WIDTH_A;
    playerDest->w = WIDTH_A;
    playerSource->h = HEIGHT_A;
    playerDest->h = HEIGHT_A;
}


void Player::WalkingAnimation(Position *tabPos, int speed, int indexClips, int direction) {
    playerSource->x =  tabPos[indexClips].x;
    playerSource->y =  tabPos[indexClips].y;
    playerSource->w = WIDTH_A * 2; // Multiplication par 2 pour l'animation de marche
    playerSource->h = HEIGHT_A * 2;

    // Réinitialisation de la taille du rectangle de destination
    playerDest->w = WIDTH_A*2;
    playerDest->h = HEIGHT_A*2;

    // Ajustement de la position en fonction de la direction
    if(direction == 0 || direction == 2) // Haut ou Bas
        playerDest->y += speed / 2; // Division par 2 pour compenser la multiplication par 2
    else if(direction == 1 || direction == 3) // Gauche ou Droite
        playerDest->x += speed;

}


//ALL ANIMATION SEQUENCE USE w , x and s
void Player::UP(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackUp);
    }
}

void Player::LEFT(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackLeft);
    }
}

void Player::DOWN(int idxAtt) {
    if(shootKey == 's') { //shoot
        //Animation Attack up normal
        makeAnimation(idxAtt,attackDown);
    }
}

void Player::RIGHT(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackRight);
    }
}

void Player::updateArrowPos() {
    for (auto& arrow: listArrow) {
        if(arrow.direction == WEST || arrow.direction == EAST)
            arrow.arrowPos.x += arrow.speed;
        if(arrow.direction == NORTH || arrow.direction == SOUTH)
            arrow.arrowPos.y += arrow.speed;
    }
}

void Player::loadClips() {
    //WALKING UP
    Walk(player_up_clips, 21);
    //WALKING LEFT
    Walk(player_left_clips, 23);
    //WALKING DOWN
    Walk(player_down_clips, 25);
    //WALKING RIGHT
    Walk(player_right_clips, 27);
    //UP
    AttackInit(attackUp, 16);

    //LEFT
    AttackInit(attackLeft, 17);

    //DOWN

    AttackInit(attackDown, 18);

    //RIGHT
    AttackInit(attackRight, 19);

    //Player Dead
    AttackInit(PlayerHurtClips, 20);
}

void Player::createArrow(int direct) {
    // Augmentation de la zone de test sur la gauche et vers le haut
    int playerLeft = playerDest->x - 29; // Ajout d'un décalage à gauche
    int playerRight = playerDest->x + playerDest->w;
    int playerTop = playerDest->y - 30; // Ajout d'un décalage vers le haut
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
        int playerCenterY = (playerDest->y + playerDest->h / 2) - 25;

        Arrow arrow{};
        arrow.arrowPos = {playerCenterX, playerCenterY};
        arrow.direction = direct;
        if (arrow.direction == 0) {
            arrow.angleRotate = -90;
            arrow.speed = -ARR_SPEED;
        } else if (arrow.direction == 1) {
            arrow.angleRotate = 360;
            arrow.speed = +ARR_SPEED;
        } else if (arrow.direction == 2) {
            arrow.angleRotate = 90;
            arrow.speed = +ARR_SPEED;
        } else {
            arrow.angleRotate = 180;
            arrow.speed = -ARR_SPEED;
        }
        listArrow.push_back(arrow);
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
