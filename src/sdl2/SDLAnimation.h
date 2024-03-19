#ifndef HUNTERASSASSIN_SDLANIMATION_H
#define HUNTERASSASSIN_SDLANIMATION_H

#include "../core/config.h"
#include "../core/point.h"
#include "../core/Player.h"
#include "../core/Garde.h"
#include "SDL.h"
#include "../core/Rect.h"
#include "SDLSprite.h"
class SDLAnimation {
public:
    char *animationIMG;
    int idx;
    int animation_speed;
    float vitesse;
    Position *posLeftClips, *posRightClips, *posDownClips, *posUpClips;
    Player player;
    int nbClips;
public:
    SDLAnimation(SDL_Renderer * renderer, char *_animationIMG, int _sourceY, Player _player);
    ~SDLAnimation();

    void loadClips(int indiceDepart, int width=PLAYER_WIDTH, int height=PLAYER_HEIGHT);

    void animationUp();
    void animationLeft();
    void animationDown();
    void animationRight();
};


//UP
inline void SDLAnimation::animationUp() {
    player.playerSource.x =  posUpClips[idx].x;
    player.playerSource.y =  posUpClips[idx].y;
    player.playerDest.y -=vitesse;
}

//LEFT
inline void SDLAnimation::animationLeft() {
    player.playerSource.x =  posLeftClips[idx].x;
    player.playerSource.y =  posLeftClips[idx].y;
    player.playerDest.x -=vitesse;
}

//DOWN
inline void SDLAnimation::animationDown() {
    player.playerSource.x =  posDownClips[idx].x;
    player.playerSource.y =  posDownClips[idx].y;
    player.playerDest.y +=vitesse;
}

//RIGHT
inline void SDLAnimation::animationRight() {
    player.playerSource.x =  posRightClips[idx].x;
    player.playerSource.y =  posRightClips[idx].y;
    player.playerDest.y +=vitesse;
}

#endif //HUNTERASSASSIN_SDLANIMATION_H
