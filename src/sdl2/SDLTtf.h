

#ifndef HUNTERASSASSIN_SDLTTF_H
#define HUNTERASSASSIN_SDLTTF_H
#include "SDL_ttf.h"
#include "SDL.h"
#include "point.h"

class SDLTtf {
private:
    SDL_Texture* _texture;
    SDL_Surface* _surface;
public:
    //Les Methodes
    SDLTtf();
    ~SDLTtf();
    TTF_Font * loadFont(const char * fontPath, int size);
    void loadFromFont(SDL_Renderer * renderer, TTF_Font * font, const char * message, SDL_Color color);
    void Draw(SDL_Renderer * renderer, Position posMessage);
};


#endif //HUNTERASSASSIN_SDLTTF_H
