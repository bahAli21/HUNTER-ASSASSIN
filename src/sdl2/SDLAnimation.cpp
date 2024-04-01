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



