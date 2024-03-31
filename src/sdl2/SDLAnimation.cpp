#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, Character _player): player(_player),
sound(44100, MIX_DEFAULT_FORMAT, 2, 248){
    allAnimation.loadSpriteFile(_player.theSpritePath, renderer);
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
        player.shootKey = 's';
}

void SDLAnimation::drawArrow(SDL_Renderer * renderer) const {

    //Angle -90 (up) 0 ou 360 (right) 180(left) et 90(down)
    for (auto arrow: player.listArrow){
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

void SDLAnimation::updatePlayer(int dirForTest) {
    int animation_speed = SDL_GetTicks() / 170;
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;

    if(state[SDL_SCANCODE_S] > 0 && idxAtt==8 && player.canShootNow) {
        player.createArrow(dirForTest);
        // Lecture de l'effet sonore une fois
        SDLSound::PlayChunk(shootEffect);
    }
    player.updateArrowPos();
    if (idxAtt>5)
        *ptrStop = 1;
    if(keyBoardK == 'k' && *ptrStop==0)
         player.makeAnimation(idxDead, PlayerHurtClips);

        if(dirForTest == NORTH && player.canShootNow) {
            player.UP(idxAtt);
        }

        if(dirForTest == EAST && player.canShootNow) {
            player.LEFT(idxAtt);
        }

        if(dirForTest == SOUTH && player.canShootNow) {
            player.DOWN(idxAtt);
        }
        if(dirForTest == WEST && player.canShootNow) {
            player.RIGHT(idxAtt);
        }
    player.shootKey = ' '; //don't repeat animation

}

void SDLAnimation::DrawAnimation(SDL_Renderer * renderer) const {

    drawArrow(renderer);
    SDL_RenderCopy(renderer,
                   allAnimation._texture,
                   reinterpret_cast<const SDL_Rect *>(player.source),
                   reinterpret_cast<const SDL_Rect *>(player.dest));

}



