#include "SDLTtf.h"

SDLTtf::SDLTtf() {
    if(TTF_Init()==-1) {
        SDL_Log("Erreur lors de l'initialisation de la SDL TTF");
        return ;
    }
}

SDLTtf::~SDLTtf() {
    SDL_DestroyTexture(_texture);
}

TTF_Font *SDLTtf::loadFont(const char *fontPath, int size) {
    TTF_Font * font = TTF_OpenFont(fontPath, size);
    if(!font) {
        SDL_Log("Erreur lors du chargement de la  de la font");
        return 0;
    }
    return font;
}

void SDLTtf::loadFromFont(SDL_Renderer * renderer, TTF_Font * font, const char * message, SDL_Color color) {
    _surface = TTF_RenderText_Solid(font, message, color);
    if (_surface == nullptr) {
        // TODO: Gére l'erreur (par exemple, fichier introuvable
        SDL_Log("Impossible de charger la font %s! Erreur SDL: %s\n", font, SDL_GetError());
        return;
    }
    // je Crée une texture à partir de la surface
    _texture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (_texture == nullptr) {
        // TODO: Gére l'erreur (par exemple, impossible de créer la texture)
        SDL_Log("Impossible de créer une texture à partir de %s! Erreur SDL: %s\n", font, SDL_GetError());
        SDL_FreeSurface(_surface);
        return;
    }
}

void SDLTtf::Draw(SDL_Renderer *renderer, Position posMessage) {
    SDL_Rect dest = {posMessage.x, posMessage.y, _surface->w, _surface->h};
    SDL_RenderCopy(renderer, _texture, nullptr, &dest);
}

