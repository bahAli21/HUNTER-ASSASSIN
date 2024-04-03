#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, Character character): character(character),
sound(44100, MIX_DEFAULT_FORMAT, 2, 248){
    allAnimation.loadSpriteFile(character.theSpritePath, renderer);
    fireArrow.loadSpriteFile("../data/imgAnimation/fire-arrow.bmp", renderer);
    shootEffect = SDLSound::LoadChunkFromFile("../data/audio/fire_bow_sound.wav");
    ptrStop = new int;
    *ptrStop = 0;
}

SDLAnimation::SDLAnimation() = default;

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

void SDLAnimation::updateCharacter(int dirForTest) {
    int animation_speed = SDL_GetTicks() / 170;
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;

    if(state[SDL_SCANCODE_S] > 0 && idxAtt==8 && character.canShootNow) {
        character.createArrow(dirForTest);
        // Lecture de l'effet sonore une fois
        SDLSound::PlayChunk(shootEffect);
    }
    character.updateArrowPos();
    if (idxAtt>5)
        *ptrStop = 1;
    if(keyBoardK == 'k' && *ptrStop==0)
         character.makeAnimation(idxDead, character.PlayerHurtClips);

        if(dirForTest == NORTH && character.canShootNow) {
            character.UP(idxAtt);
        }

        if(dirForTest == EAST && character.canShootNow) {
            character.LEFT(idxAtt);
        }

        if(dirForTest == SOUTH && character.canShootNow) {
            character.DOWN(idxAtt);
        }
        if(dirForTest == WEST && character.canShootNow) {
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
void SDLAnimation::updateTest(float dT, Level& level) {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 7;//for walking frame

    // Calcul de la distance à la cible depuis la position actuelle de l'unité
    Vector2D targetPos(character.targetPos->x, character.targetPos->y);
    Vector2D destCh(character.dest->x, character.dest->y);
    distanceToTarget = (level.getTargetPos() - destCh).magnitude(); //Un type vecteur est retourner par la difference , magnitude() pour l'heristic

    // Calcul de la distance à déplacer pendant cette frame
    //En physique d = v * t haha
    distanceMove = character.speed * dT;
    if (distanceMove > distanceToTarget) {
        //Yes destination atteinte
        distanceMove = distanceToTarget;
        character.canShootNow = true;
    }else
        character.canShootNow = false;
    // Calcul de la direction de déplacement combinant la direction du champ de flux et de la séparation normale
    Vector2D directionNormalFlowField(level.getFlowNormal((int)destCh.x/28, (int)destCh.y)/28); //Recupere la direction de la tuile
    Vector2D directionNormalCombined = directionNormalFlowField * 3.0f;
    directionNormalCombined.normalize();
    Vector2D posAdd = directionNormalCombined * distanceMove;

    // Vérification des collisions avec les autres unités
    bool moveOk = true;

    if(distanceMove == distanceToTarget)
        moveOk = false;
    // Mise à jour de la position si aucun obstacle rencontré
    if (moveOk) {
        if (posAdd.x != 0.0f) {

            character.dest->x += 1 * (int)copysign(1, posAdd.x); // Déplace le joueur vers la gauche ou la droite selon la direction de la cible
            int vitesse = 1 * (int)copysign(1, posAdd.x);
            if (vitesse < 0) {
                character.direction = EAST;
                // Si la vitesse est négative, l'unité se déplace vers la gauche
                character.WalkingAnimation(character.player_left_clips, -character.speed, idx, WEST); // Utilise l'animation pour le mouvement vers la gauche

            } else {
                character.direction = WEST;
                // Si la vitesse est positive, l'unité se déplace vers la droite
                character.WalkingAnimation(character.player_right_clips, character.speed, idx, EAST); // Utilise l'animation pour le mouvement vers la droite
            }
        }

        if (posAdd.y != 0.0f) {

            character.dest->y += 1 * (int)copysign(1, posAdd.y); // Déplace le joueur vers le haut ou le bas selon la direction de la cible
            int vitesse = 1 * (int)copysign(1, posAdd.y);
            if (vitesse < 0) {
                character.direction = NORTH;
                // Si la vitesse est négative, l'unité se déplace vers le haut
                character.WalkingAnimation(character.player_up_clips, (int)-character.speed, idx, NORTH); // Utilise l'animation pour le mouvement vers le haut
            } else {
                character.direction = SOUTH;
                // Si la vitesse est positive, l'unité se déplace vers le bas
                character.WalkingAnimation(character.player_down_clips, (int)character.speed, idx, SOUTH); // Utilise l'animation pour le mouvement vers le bas
            }
        }
    }
}



