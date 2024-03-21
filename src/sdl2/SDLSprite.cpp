#include "SDLSprite.h"

// Constructeur par défaut
SDLSprite::SDLSprite() : _surface(nullptr), _texture(nullptr) {}

// Destructeur
SDLSprite::~SDLSprite() {
    // Libére la texture si elle existe
    if (_texture != nullptr) {
        SDL_DestroyTexture(_texture);
    }
}

// Je Charge une image à partir d'un fichier
void SDLSprite::loadSpriteFile(const char *filename, SDL_Renderer *renderer) {
    // Chargons l'image depuis le fichier
    _surface = SDL_LoadBMP(filename);
    if (_surface == nullptr) {
        // TODO: Gére l'erreur (par exemple, fichier introuvable)
        SDL_Log("Impossible de charger l'image %s! Erreur SDL: %s\n", filename, SDL_GetError());
        return;
    }
    // je Crée une texture à partir de la surface
    _texture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (_texture == nullptr) {
        // TODO: Gére l'erreur (par exemple, impossible de créer la texture)
        SDL_Log("Impossible de créer une texture à partir de %s! Erreur SDL: %s\n", filename, SDL_GetError());
        SDL_FreeSurface(_surface);
        return;
    }
}

// Dessiner le sprite
void SDLSprite::draw(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Rect* recSource) const {
    if (_texture == nullptr) {
        // TODO: Gére l'erreur (par exemple, aucune texture à dessiner)
        //SDL_Log("Aucune texture à dessiner !\n");
        return;
    }
        // Définir le rectangle de destination pour le dessin
        SDL_Rect destRect = {x, y, w, h};
        SDL_RenderCopy(renderer, _texture, recSource, &destRect);

}