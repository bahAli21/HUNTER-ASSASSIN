#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, Character character): character(character),
sound(44100, MIX_DEFAULT_FORMAT, 2, 248){
    allAnimation.loadSpriteFile(character.theSpritePath, renderer);
    fireArrow.loadSpriteFile("../data/imgAnimation/fire-arrow.bmp", renderer);
    shootEffect = SDLSound::LoadChunkFromFile("../data/audio/fire_bow_sound.wav");
    ptrStop = new int;


    *ptrStop = 0;
}

SDLAnimation::~SDLAnimation() = default;

void SDLAnimation::handleInput() {
    state = SDL_GetKeyboardState(nullptr);

    if(state[SDL_SCANCODE_K] > 0)
        keyBoardK = 'k';

    if (state[SDL_SCANCODE_S] > 0)
        character.shootKey = 's';
}

void SDLAnimation::drawArrow(SDL_Renderer * renderer) const {

    //Angle -90 (up) 0 ou 360 (right) 180(left) et 90(down)
    for (auto arrow: character.listArrow){
        SDL_Rect tmp = {arrow.arrowPos.x,
                        arrow.arrowPos.y,
                        50,
                        fireArrow._surface->h-20};

        SDL_RenderCopyEx(renderer,
                         fireArrow._texture,
                         nullptr,
                         &tmp,
                         arrow.angleRotate,
                         nullptr,
                         SDL_FLIP_NONE);

    }
}

bool SDLAnimation::checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
    // Calcul des coordonnées du petit rectangle
    int smallRectX = rect1.x + rect1.w / 4;
    int smallRectY = rect1.y + rect1.h / 4;
    int smallRectW = rect1.w / 2;
    int smallRectH = rect1.h / 2;

// Création du petit rectangle
     smallRect = {smallRectX, smallRectY, smallRectW, smallRectH};

    // Les conditions pour qu'il n'y ait pas de collision
    if (smallRect.x + smallRect.w <= rect2.x ||
            smallRect.x >= rect2.x + rect2.w ||
            smallRect.y + smallRect.h  <= rect2.y ||
            smallRect.y >= rect2.y + rect2.h) {
        return false; // Pas de collision
    } else {
        return true; // Collision
    }
}

bool SDLAnimation::collisionWithLevel(SDL_Rect playerRect, Level &level) {
    // Vérification des collisions avec les rectangles spécifiques du niveau
    if (checkCollision(playerRect, level.destWallUp) ||
        checkCollision(playerRect, level.destSmallWallUpLeft) ||
        checkCollision(playerRect, level.destSmallWallUpRight) ||
        checkCollision(playerRect, level.destWallDown) ||
        checkCollision(playerRect, level.destWallLeft) ||
        checkCollision(playerRect, level.destWallRight) ||
        checkCollision(playerRect, level.destBlockGrisTopLeft) ||
        checkCollision(playerRect, level.destBlockGrisTopRight) ||
        checkCollision(playerRect, level.destBlockGrisMiddleLeft) ||
        checkCollision(playerRect, level.destBlockGrisMiddleRight) ||
        checkCollision(playerRect, level.destBlockGrisDownLeft) ||
        checkCollision(playerRect, level.destBlockGrisDownRight)) {
        return true; // Collision avec l'un des rectangles spécifiques du niveau
    } else {
        return false; // Pas de collision
    }
}

void SDLAnimation::openDoor(Level & level){
    SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};
    if(character.hasKey)
        if(checkCollision(characterDest, level.destDoorUp)) {
            if(level.destDoorUp.w > 0){
                level.destDoorUp.w--;
            }
    }
}

void SDLAnimation::closeDoor(Level & level){
    int originalDoorWidth = 40;
    SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};
    if(!checkCollision(characterDest, level.destDoorUp)) {
        if(level.destDoorUp.w < originalDoorWidth){ // originalDoorWidth est la largeur initiale de la porte
            level.destDoorUp.w++;
        }
    }
}

void SDLAnimation::getKey(Level & level) {
  SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};
    if(checkCollision(characterDest, level.destKey)) {
        character.hasKey = true;
        //Je dois maintenant detruire la clef
        level.destKey = {-1, -1, 0, 0};
    }
}

void SDLAnimation::updateCharacter(int index, Level &level) {
    int animation_speed = SDL_GetTicks() / 170;
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;
    int idx = animation_speed % 7;//for walking frame
    int vitesse = 1;

    if(state[SDL_SCANCODE_S] > 0 && idxAtt==8 ) {
        character.createArrow(character.direction);
        // Lecture de l'effet sonore une fois
        SDLSound::PlayChunk(shootEffect);
    }


    if(index == 0) { //Concerne un joueur pas les gardes
        getKey(level);
        openDoor(level);
        closeDoor(level);

        SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};
        if(state[SDL_SCANCODE_LEFT] > 0){
            // Vérifier la collision avant de déplacer le joueur
            //if (!collisionWithLevel(characterDest, level)) {
                character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
            //}
        }
        if(state[SDL_SCANCODE_RIGHT] > 0){
            //if (!collisionWithLevel(characterDest, level)) {
                character.WalkingAnimation(character.player_right_clips, vitesse, idx, WEST);
            //}
        }
        if(state[SDL_SCANCODE_UP] > 0){
            //if (!collisionWithLevel(characterDest, level)) {
                character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
            //}
        }
        if(state[SDL_SCANCODE_DOWN] > 0){
            //if (!collisionWithLevel(characterDest, level)) {
                character.WalkingAnimation(character.player_down_clips, vitesse, idx, SOUTH);
            //}

        }
    }
    character.updateArrowPos();



/*
    if (index != 0){ //Concerne un garde pas le joueur
        if(character.dest->x < character.tabNoeud[0].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        }
        else if(character.dest->y < character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_down_clips, +vitesse, idx, SOUTH);

        }
        else if(character.dest->x < character.tabNoeud[2].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);

        }
        else if(character.dest->y > character.tabNoeud[3].y){
            character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);

        }
        else if(character.dest->x < character.tabNoeud[4].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        }
    }
*/
    if (idxAtt>5)
        *ptrStop = 1;
    if(keyBoardK == 'k' && *ptrStop==0)
         character.makeAnimation(idxDead, character.PlayerHurtClips);

        if(character.direction == NORTH) {
            character.UP(idxAtt);
        }
        if(character.direction == EAST) {
            character.LEFT(idxAtt);
        }
        if(character.direction == SOUTH) {
            character.DOWN(idxAtt);
        }
        if(character.direction == WEST) {
            character.RIGHT(idxAtt);
        }
    character.shootKey = ' '; //don't repeat animation
}

void SDLAnimation::DrawAnimation(SDL_Renderer * renderer) const {

    drawArrow(renderer);

    SDL_RenderCopy(renderer,
                   allAnimation._texture,
                   reinterpret_cast<const SDL_Rect *>(character.source),
                   reinterpret_cast<const SDL_Rect *>(character.dest));
}


//Test
// Fonction de mise à jour de l'unité
