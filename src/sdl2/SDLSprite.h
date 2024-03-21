/**
 * @file SDLSprite.h
 * @brief Definition of the SDLSprite class
 */

#ifndef HUNTERASSASSIN_SDLSPRITE_H
#define HUNTERASSASSIN_SDLSPRITE_H

#include "SDL.h"
#include "../core/Rect.h"

/**
 * @class SDLSprite
 * @brief Class for handling SDL sprites
 */
class SDLSprite {
public:
    SDL_Surface *_surface; /**< SDL surface for the sprite */
    SDL_Texture *_texture; /**< SDL texture for the sprite */
public:
    /**
     * @brief Default constructor of the SDLSprite class
     */
    SDLSprite();

    /**
     * @brief Destructor of the SDLSprite class
     */
    ~SDLSprite();

    /**
     * @brief Copy constructor of the SDLSprite class
     * @param im The instance of SDLSprite to copy
     */
    SDLSprite(const SDLSprite &im);

    /**
     * @brief Load an image file as a sprite
     * @param filename The path of the image file
     * @param renderer The SDL renderer to load the texture
     */
    void loadSpriteFile(const char *filename, SDL_Renderer *renderer);

    /**
     * @brief Draw the sprite on the SDL renderer
     * @param renderer The SDL renderer to draw on
     * @param x The horizontal position of the sprite
     * @param y The vertical position of the sprite
     * @param w The width of the sprite (default is 64)
     * @param h The height of the sprite (default is 64)
     * @param recSource The source rectangle for clipping (default is nullptr)
     */
    void draw(SDL_Renderer *renderer, int x, int y, int w = 64, int h = 64, SDL_Rect* recSource = nullptr) const;

    /**
     * @brief Draw an animation sequence of the sprite on the SDL renderer
     * @param renderer The SDL renderer to draw on
     * @param rectSource The source rectangle for clipping
     * @param rectPlayer The destination rectangle for rendering
     */
    void drawAnimationSequence(SDL_Renderer *renderer, Rect rectSource, Rect rectPlayer);

    /**
     * @brief Get the SDL texture of the sprite
     * @return The SDL texture of the sprite
     */
    SDL_Texture *getTexture() const;

    /**
     * @brief Set the SDL surface of the sprite
     * @param surf The SDL surface to set
     */
    void setSurface(SDL_Surface *surf);
};

#endif // HUNTERASSASSIN_SDLSPRITE_H
