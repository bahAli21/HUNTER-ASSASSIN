/**
 * @file SDLSprite.h
 * @brief Définition de la classe SDLSprite
 */

#ifndef HUNTERASSASSIN_SDLSPRITE_H
#define HUNTERASSASSIN_SDLSPRITE_H

#include "SDL.h"

/**
 * @class SDLSprite
 * @brief Classe pour la manipulation de sprites SDL
 */
class SDLSprite {
public:
    SDL_Surface *_surface; /**< Surface SDL pour le sprite */
    SDL_Texture *_texture; /**< Texture SDL pour le sprite */
public:
    /**
     * @brief Constructeur par défaut de la classe SDLSprite
     */
    SDLSprite();

    /**
     * @brief Destructeur de la classe SDLSprite
     */
    ~SDLSprite();

    /**
     * @brief Constructeur de copie de la classe SDLSprite
     * @param im L'instance de SDLSprite à copier
     */
    SDLSprite(const SDLSprite &im);

    /**
     * @brief Charge un fichier image en tant que sprite
     * @param filename Le chemin du fichier image
     * @param renderer Le renderer SDL pour charger la texture
     */
    void loadSpriteFile(const char *filename, SDL_Renderer *renderer);

    /**
     * @brief Dessine le sprite sur le renderer SDL
     * @param renderer Le renderer SDL sur lequel dessiner
     * @param x La position horizontale du sprite
     * @param y La position verticale du sprite
     * @param w La largeur du sprite (par défaut 24)
     * @param h La hauteur du sprite (par défaut 37)
     */
    void draw(SDL_Renderer *renderer, int x, int y, int w = 24, int h = 37) const;

    /**
     * @brief Obtient la texture SDL du sprite
     * @return La texture SDL du sprite
     */
    SDL_Texture *getTexture() const;

    /**
     * @brief Définit la surface SDL du sprite
     * @param surf La surface SDL à définir
     */
    void setSurface(SDL_Surface *surf);
};

#endif // HUNTERASSASSIN_SDLSPRITE_H
