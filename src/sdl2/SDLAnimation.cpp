#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer * renderer, char *_animationIMG, int _sourceY, Player _player) {
    nbClips =6;
    player.playerSource.y =_sourceY;
    this->animationIMG = _animationIMG;
    animation_speed = SDL_GetTicks() / 175;
    idx = animation_speed % nbClips;
    vitesse=2.4;
}

SDLAnimation::~SDLAnimation() {
    delete [] posDownClips;
    delete [] posLeftClips;
    delete [] posRightClips;
    delete [] posUpClips;
}

void SDLAnimation::loadClips(int indiceDepart, int width, int height) {

    posLeftClips = new Position[nbClips];
    posRightClips = new Position[nbClips];
    posDownClips = new Position[nbClips];
    posUpClips = new Position[nbClips];
    for (int i = 0; i < 6; ++i) {
        posUpClips[i].x = i*width;
        posUpClips[i].y = height * indiceDepart;
        posLeftClips[i].x = i*width;
        posLeftClips[i].y = height * (indiceDepart+1);
        posDownClips[i].x = i * width;
        posDownClips[i].y = height * (indiceDepart+2);
        posRightClips[i].y = height * (indiceDepart+3);
        posRightClips[i].x = i * width;
    }
}
