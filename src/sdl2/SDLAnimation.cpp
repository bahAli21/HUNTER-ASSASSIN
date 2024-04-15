#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, Character character): character(character),
sound(44100, MIX_DEFAULT_FORMAT, 2, 248){
    allAnimation.loadSpriteFile(character.theSpritePath, renderer);
    fireArrow.loadSpriteFile("../data/imgAnimation/fire-arrow.bmp", renderer);
    shootEffect = SDLSound::LoadChunkFromFile("../data/audio/arrowChunck.wav");
}

SDLAnimation::~SDLAnimation() = default;

void SDLAnimation::handleInput() {
    state = SDL_GetKeyboardState(nullptr);
}
void SDLAnimation::makeSmallRectCollision(){
    // Calcul des coordonnées du petit rectangle
    int smallRectX = character.dest->x + character.dest->w / 4 + 20;
    int smallRectY = character.dest->y + character.dest->h / 4 + 12;
    int smallRectW = character.dest->w / 2 -40;
    int smallRectH = character.dest->h / 2 -15;

    character.smallRect = {smallRectX, smallRectY, smallRectW, smallRectH};
}

bool SDLAnimation::checkCollision(SDL_Rect rect1, SDL_Rect rect2) const {
    // Calcul des coordonnées du petit rectangle
    int smallRectX = rect1.x + rect1.w / 4 + 12;
    int smallRectY = rect1.y + rect1.h / 4 + 12;
    int smallRectW = rect1.w / 2 -20;
    int smallRectH = rect1.h / 2  -20;

// Création du petit rectangle
    SDL_Rect  smallRect = {smallRectX, smallRectY, smallRectW, smallRectH};

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

void SDLAnimation::drawArrow(SDL_Renderer * renderer) const {

    //Angle -90 (up) 0 ou 360 (right) 180(left) et 90(down)
    for (auto arrow: character.listArrow){
        SDL_Rect tmp = {arrow.arrowPos.x,
                        arrow.arrowPos.y,
                        50,
                        fireArrow._surface->h -20};

        //c'etait pour debugger
        //SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        //SDL_RenderDrawRect(renderer, &tmp);

        SDL_RenderCopyEx(renderer,
                         fireArrow._texture,
                         nullptr,
                         &tmp,
                         arrow.angleRotate,
                         nullptr,
                         SDL_FLIP_NONE);

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
            level.beta = -90;
            if(level.beta == -90)
                doorOpenNow = true;
    }
}

void SDLAnimation::closeDoor(Level & level){
    SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};
    if(!checkCollision(characterDest, level.destDoorUp)) {
        level.beta = 0;
        if(level.beta == 0)
            doorOpenNow = false;
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

void SDLAnimation::patrouilleGardeUpLeft(int vitesse, int idx){
    if(character.Aller) {
        if(character.dest->x < character.tabNoeud[1].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        } else if(character.dest->y < character.tabNoeud[2].y){
            character.WalkingAnimation(character.player_down_clips, +vitesse, idx, SOUTH);
        }

        if(character.dest->y == character.tabNoeud[2].y){
            character.Retour = true;
            character.Aller = false;
        }
    }
    if(character.Retour) {
        if(character.dest->y > character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
        } else if(character.dest->x > character.tabNoeud[0].x){
            character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
        }

        if(character.dest->x == character.tabNoeud[0].x){
            character.Retour = false;
            character.Aller = true;
        }
    }
}

void SDLAnimation::patrouilleGardeUpRight(int vitesse, int idx) {
    if(character.Aller) {
        if(character.dest->x > character.tabNoeud[1].x){
            character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
        } else if(character.dest->y < character.tabNoeud[2].y){
            character.WalkingAnimation(character.player_down_clips, +vitesse, idx, SOUTH);
        }

        if(character.dest->y == character.tabNoeud[2].y){
            character.Retour = true;
            character.Aller = false;
        }
    }
    if(character.Retour) {
        if(character.dest->y > character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
        } else if(character.dest->x < character.tabNoeud[0].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        }

        if(character.dest->x == character.tabNoeud[0].x){
            character.Retour = false;
            character.Aller = true;
        }
    }
}

//Marche pas encore
void SDLAnimation::patrouilleGardeDownLeft(int vitesse, int idx) {
    if(character.Aller) {
        if(character.dest->y < character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_down_clips, +vitesse, idx, SOUTH);
        } else if(character.dest->x < character.tabNoeud[2].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        }

        if(character.dest->x == character.tabNoeud[2].x){
            character.Retour = true;
            character.Aller = false;
        }
    }
    if(character.Retour) {
        if(character.dest->x > character.tabNoeud[1].x){
            character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
        } else if(character.dest->y > character.tabNoeud[0].y){
            character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
        }

        if(character.dest->y == character.tabNoeud[0].y){
            character.Retour = false;
            character.Aller = true;
        }
    }
}

void SDLAnimation::patrouilleGardeDownRight(int vitesse, int idx) {
    if(character.Aller) {
        if(character.dest->y < character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_down_clips, +vitesse, idx, SOUTH);
        } else if(character.dest->x > character.tabNoeud[2].x){
            character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
        }

        if(character.dest->x == character.tabNoeud[2].x){
            character.Retour = true;
            character.Aller = false;
        }
    }
    if(character.Retour) {
        if(character.dest->x < character.tabNoeud[1].x){
            character.WalkingAnimation(character.player_right_clips, +vitesse, idx, WEST);
        } else if(character.dest->y > character.tabNoeud[0].y){
            character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
        }

        if(character.dest->y == character.tabNoeud[0].y){
            character.Retour = false;
            character.Aller = true;
        }
    }
}

void SDLAnimation::initCollisionAttribute(Level & level) {
    SDL_Rect characterDest = {character.dest->x, character.dest->y, character.dest->w, character.dest->h};

    if(collisionWithLevel(characterDest, level)){
        if(character.direction == NORTH){
            colUp = true;
            colDown = false;
            colRight = false;
            colLeft = false;
        } else if(character.direction ==SOUTH){
            colUp = false;
            colRight = false;
            colLeft = false;
            colDown = true;
        } else if(character.direction == EAST){
            colUp = false;
            colDown = false;
            colRight = false;
            colLeft = true;
        } else{
            colUp = false;
            colDown = false;
            colLeft = false;
            colRight = true;
        }
    }else if(!doorOpenNow && checkCollision(characterDest, level.destDoorUp)){
        colUp = true;
        colDown = false;
        colLeft = false;
        colRight = false;
    } else{
        colUp = false;
        colDown = false;
        colLeft = false;
        colRight = false;
    }
}

void SDLAnimation::updateCharacter(int index, Level &level) {
    int animation_speed = SDL_GetTicks() / 170;
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;
    int idx = animation_speed % 7;//for walking frame
    int vitesseGarde = 1;
    int vitessePlayer = 2;

    if(index == -1) { //Concerne un joueur pas les gardes
        if(!character.isDead){
            if (state[SDL_SCANCODE_S] > 0 && idxAtt == 8) {
                character.createArrow(character.direction);
                // Lecture de l'effet sonore une fois
                SDLSound::PlayChunk(shootEffect);
            }

            if (character.direction == NORTH) {
                character.UP(idxAtt);
            }
            if (character.direction == EAST) {
                character.LEFT(idxAtt);
            }
            if (character.direction == SOUTH) {
                character.DOWN(idxAtt);
            }
            if (character.direction == WEST) {
                character.RIGHT(idxAtt);
            }
            //character.shootKey = ' '; //don't repeat animation

            getKey(level);
            openDoor(level);
            closeDoor(level);
            initCollisionAttribute(level);

            if (state[SDL_SCANCODE_LEFT] > 0) {
                // Vérifie la collision avant de déplacer le joueur
                if (!colLeft) {
                    character.WalkingAnimation(character.player_left_clips, -vitessePlayer, idx, EAST);
                }
            }
            if (state[SDL_SCANCODE_RIGHT] > 0) {
                if (!colRight) {
                    character.WalkingAnimation(character.player_right_clips, vitessePlayer, idx, WEST);
                }
            }
            if (state[SDL_SCANCODE_UP] > 0) {
                if (!colUp) {
                    character.WalkingAnimation(character.player_up_clips, -vitessePlayer, idx, NORTH);
                }
            }
            if (state[SDL_SCANCODE_DOWN] > 0) {
                if (!colDown) {
                    character.WalkingAnimation(character.player_down_clips, vitessePlayer, idx, SOUTH);
                }
            }
            character.updateArrowPos();
        } else {
            character.source = new Rect{WIDTH_A*5, HEIGHT_A*20, WIDTH_A, HEIGHT_A};
            character.dest->w = WIDTH_A;
            character.dest->h = HEIGHT_A;
        }

    }

    //Garde TOP LEFT
     if(index == 0){
         if(!character.isDead){
             if (character.shootKey == 's' && idxAtt == 8) {
                 character.createArrow(character.direction);
                 // Lecture de l'effet sonore une fois
                 SDLSound::PlayChunk(shootEffect);
             }
             character.updateArrowPos();
             if(character.shootKey != 's')
                patrouilleGardeUpLeft(vitesseGarde, idx);
             if (character.direction == NORTH) {
                 character.UP(idxAtt);
             }
             if (character.direction == EAST) {
                 character.LEFT(idxAtt);
             }
             if (character.direction == SOUTH) {
                 character.DOWN(idxAtt);
             }
             if (character.direction == WEST) {
                 character.RIGHT(idxAtt);
             }
         }else{
             character.source = new Rect{WIDTH_A*5, HEIGHT_A*20, WIDTH_A, HEIGHT_A};
             character.dest->w = WIDTH_A;
             character.dest->h = HEIGHT_A;
         }
     }
     if(index == 1){
         if(!character.isDead){
             if (character.shootKey == 's' && idxAtt == 8) {
                 character.createArrow(character.direction);
                 // Lecture de l'effet sonore une fois
                 SDLSound::PlayChunk(shootEffect);
             }
             character.updateArrowPos();
             if(character.shootKey != 's')
                patrouilleGardeUpRight(vitesseGarde, idx);
             if (character.direction == NORTH) {
                 character.UP(idxAtt);
             }
             if (character.direction == EAST) {
                 character.LEFT(idxAtt);
             }
             if (character.direction == SOUTH) {
                 character.DOWN(idxAtt);
             }
             if (character.direction == WEST) {
                 character.RIGHT(idxAtt);
             }
         }else{
             character.source = new Rect{WIDTH_A*5, HEIGHT_A*20, WIDTH_A, HEIGHT_A};
             character.dest->w = WIDTH_A;
             character.dest->h = HEIGHT_A;
         }
     }
     if(index == 2){
         if(!character.isDead){
             if (character.shootKey == 's' && idxAtt == 8) {
                 character.createArrow(character.direction);
                 // Lecture de l'effet sonore une fois
                 SDLSound::PlayChunk(shootEffect);
             }
             character.updateArrowPos();
             if(character.shootKey != 's')
                patrouilleGardeDownLeft(vitesseGarde, idx);
             if (character.direction == NORTH) {
                 character.UP(idxAtt);
             }
             if (character.direction == EAST) {
                 character.LEFT(idxAtt);
             }
             if (character.direction == SOUTH) {
                 character.DOWN(idxAtt);
             }
             if (character.direction == WEST) {
                 character.RIGHT(idxAtt);
             }
         }else{
             character.source = new Rect{WIDTH_A*5, HEIGHT_A*20, WIDTH_A, HEIGHT_A};
             character.dest->w = WIDTH_A;
             character.dest->h = HEIGHT_A;
         }
     }
     if(index == 3){
         if(!character.isDead){
             if (character.shootKey == 's' && idxAtt == 8) {
                 character.createArrow(character.direction);
                 // Lecture de l'effet sonore une fois
                 SDLSound::PlayChunk(shootEffect);
             }
             character.updateArrowPos();
             if(character.shootKey != 's')
                patrouilleGardeDownRight(vitesseGarde, idx);
             if (character.direction == NORTH) {
                 character.UP(idxAtt);
             }
             if (character.direction == EAST) {
                 character.LEFT(idxAtt);
             }
             if (character.direction == SOUTH) {
                 character.DOWN(idxAtt);
             }
             if (character.direction == WEST) {
                 character.RIGHT(idxAtt);
             }
         } else{
             character.source = new Rect{WIDTH_A*5, HEIGHT_A*20, WIDTH_A, HEIGHT_A};
             character.dest->w = WIDTH_A;
             character.dest->h = HEIGHT_A;
         }
     }
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
