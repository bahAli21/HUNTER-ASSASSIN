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

void SDLAnimation::updateCharacter() {
    int animation_speed = SDL_GetTicks() / 170;
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;
    int idx = animation_speed % 7;//for walking frame
    int vitesse = 2;

    if(state[SDL_SCANCODE_S] > 0 && idxAtt==8 && character.canShootNow) {
        character.createArrow(character.direction);
        // Lecture de l'effet sonore une fois
        SDLSound::PlayChunk(shootEffect);
    }

    if(state[SDL_SCANCODE_LEFT] > 0)
        character.WalkingAnimation(character.player_left_clips, -vitesse, idx, EAST);
    if(state[SDL_SCANCODE_RIGHT] > 0)
        character.WalkingAnimation(character.player_right_clips, vitesse, idx, WEST);
    if(state[SDL_SCANCODE_UP] > 0)
        character.WalkingAnimation(character.player_up_clips, -vitesse, idx, NORTH);
    if(state[SDL_SCANCODE_DOWN] > 0)
        character.WalkingAnimation(character.player_down_clips, vitesse, idx, SOUTH);

    character.updateArrowPos();
    /*
    if (character.tabNoeud[0].x != -1 && character.tabNoeud[0].y !=-1){
        if(character.dest->x < character.tabNoeud[0].x){
            character.WalkingAnimation(character.player_right_clips, vitesse, idx, WEST);
            character.dest->x++;
        }
        else if(character.dest->y < character.tabNoeud[1].y){
            character.WalkingAnimation(character.player_down_clips, vitesse, idx, SOUTH);
            character.dest->y++;
        }
        else if(character.dest->x < character.tabNoeud[2].x){
            character.WalkingAnimation(character.player_right_clips, vitesse, idx, WEST);
            character.dest->x++;
        }
        else if(character.dest->y > character.tabNoeud[3].y){
            character.WalkingAnimation(character.player_up_clips, vitesse, idx, NORTH);
            character.dest->y--;
        }
        else if(character.dest->x < character.tabNoeud[4].x){
            character.WalkingAnimation(character.player_right_clips, vitesse, idx, WEST);
            character.dest->x++;
        }
    }*/

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
