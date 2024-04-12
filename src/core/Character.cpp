#include "Character.h"

Character::Character(Rect * _source, Rect * _dest, int _direction, int _health, const char * _theSpritePath, Rect * _targetPos,  int _speed, std::vector<Position> _tabNoeud): shootKey('a') {
    source = new Rect{_source->x, _source->y, _source->w, _source->h};
    dest = new Rect{_dest->x, _dest->y, _dest->w, _dest->h};
    targetPos = new Rect{_targetPos->x, _targetPos->y, 0, 0};
    direction = (_direction);
    health = (_health);
    theSpritePath = _theSpritePath;
    speed = (_speed);
    tabNoeud = _tabNoeud;
    loadClips();
}

Character::~Character() = default;

void Character::Walk(Position *tabPos, int index) {
    for (int i = 0; i < 8; ++i) {
        tabPos[i].x = (i*2) * (WIDTH_A);
        tabPos[i].y = HEIGHT_A * index;
    }
}

void Character::AttackInit(Position *tabPos, int index) {
    for (int i = 0; i <=12; ++i) {
        tabPos[i].x = (i)*(WIDTH_A);
        tabPos[i].y = (HEIGHT_A) * index;
    }
}

void Character::makeAnimation(int index, Position *tabPos) const {
    source->x = tabPos[index].x;
    source->y = tabPos[index].y;
    source->w = WIDTH_A;
    dest->w = WIDTH_A;
    source->h = HEIGHT_A;
    dest->h = HEIGHT_A;
}


void Character::WalkingAnimation(Position *tabPos, int speed, int indexClips, int _direction) {
    source->x =  tabPos[indexClips].x;
    source->y =  tabPos[indexClips].y;
    source->w = WIDTH_A * 2; // Multiplication par 2 pour l'animation de marche
    source->h = HEIGHT_A * 2;

    // Réinitialisation de la taille du rectangle de destination
    dest->w = WIDTH_A*2;
    dest->h = HEIGHT_A*2;
    this->direction = _direction;
    // Ajustement de la position en fonction de la direction
    if(this->direction == 0 || this->direction == 2) // Haut ou Bas
        dest->y += speed; // Division par 2 pour compenser la multiplication par 2
    else if(this->direction == 1 || this->direction == 3) // Gauche ou Droite
        dest->x += speed;

}


//ALL ANIMATION SEQUENCE USE  key s
void Character::UP(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackUp);
    }
}

void Character::LEFT(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackLeft);
    }
}

void Character::DOWN(int idxAtt) {
    if(shootKey == 's') { //shoot
        //Animation Attack up normal
        makeAnimation(idxAtt,attackDown);
    }
}

void Character::RIGHT(int idxAtt) {
    if(shootKey == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackRight);
    }
}

void Character::updateArrowPos() {
    for (auto& arrow: listArrow) {
        if(arrow.direction == WEST || arrow.direction == EAST)
            arrow.arrowPos.x += arrow.speed;
        if(arrow.direction == NORTH || arrow.direction == SOUTH)
            arrow.arrowPos.y += arrow.speed;
    }
}

void Character::loadClips() {
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

void Character::createArrow(int direct) {
    // Augmentation de la zone de test sur la gauche et vers le haut
    int playerLeft = dest->x - 29; // Ajout d'un décalage à gauche
    int playerRight = dest->x + dest->w;
    int playerTop = dest->y - 30; // Ajout d'un décalage vers le haut
    int playerBottom = dest->y + dest->h;

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
        int playerCenterX = (dest->x + dest->w / 2) - 20;
        int playerCenterY = (dest->y + dest->h / 2) - 25;

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


void Character::goLeft() const {
    dest->x-=1;
}

void Character::goRight() const {
    dest->x+=1;
}

void Character::goUp() const {
    dest->y-=1;
}

void Character::goDown() const {
    dest->y+=1;
}
