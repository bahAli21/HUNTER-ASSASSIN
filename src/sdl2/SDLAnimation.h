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
private:
    char *animationIMG;
    Rect source;
    int idx;
    int animation_speed;
    float vitesse;
    SDLSprite animationSprite;
    SDL_Renderer * renderer;
    SDL_Window * window;
    Position *posLeftClips, *posRightClips, *posDownClips, *posUpClips;
    Player player;
    int nbClips;
public:
    SDLAnimation(char * _animationIMG, int _sourceY, Position _pos, Player _player);
    ~SDLAnimation();

    void loadClips(int indiceDepart, int width=PLAYER_WIDTH, int height=PLAYER_HEIGHT);
    
    void animationUp();
    void animationLeft();
    void animationDown();
    void animationRight();
    Rect getSource();
    void setSoure(Rect source);
};

inline  Rect SDLAnimation::getSource() {return this->source;}
inline  void SDLAnimation::setSoure(Rect _source) {this->source = _source;}

//UP
inline void SDLAnimation::animationUp() {
    this->source.x =  posUpClips[idx].x;
    this->source.y =  posUpClips[idx].y;
    player.setPositionY(player.getPosition().y - vitesse);
}

//LEFT
inline void SDLAnimation::animationLeft() {
    this->source.x =  posLeftClips[idx].x;
    this->source.y =  posLeftClips[idx].y;
    player.setPositionX(player.getPosition().x - vitesse);
}

//DOWN
inline void SDLAnimation::animationDown() {
    this->source.x =  posDownClips[idx].x;
    this->source.y =  posDownClips[idx].y;
    player.setPositionY(player.getPosition().y + vitesse);
}

//RIGHT
inline void SDLAnimation::animationRight() {
    this->source.x =  posRightClips[idx].x;
    this->source.y =  posRightClips[idx].y;
    player.setPositionX(player.getPosition().x + vitesse);
}

#endif //HUNTERASSASSIN_SDLANIMATION_H
