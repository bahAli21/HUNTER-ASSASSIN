#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "point.h"

/**
 * @brief The SDLTtf class provides functionality to work with TrueType fonts in SDL.
 */
class SDLTtf {
private:
    //{} vide par defaut
    SDL_Texture* _texture{}; ///< The texture used for rendering text.
    SDL_Surface* _surface{}; ///< The surface used for rendering text.

public:
    /**
     * @brief Constructs an SDLTtf object.
     */
    SDLTtf();

    /**
     * @brief Destroys the SDLTtf object.
     */
    ~SDLTtf();

    /**
     * @brief Loads a TrueType font from a file.
     *
     * @param fontPath The path to the TrueType font file.
     * @param size The font size.
     * @return A pointer to the loaded font.
     */
    static TTF_Font* loadFont(const char* fontPath, int size);

    /**
     * @brief Loads text from a font and renders it onto a surface.
     *
     * @param renderer The SDL renderer to render onto.
     * @param font A pointer to the TTF_Font object.
     * @param message The text message to render.
     * @param color The color of the rendered text.
     */
    void loadFromFont(SDL_Renderer* renderer, TTF_Font* font, const char* message, SDL_Color color);

    /**
     * @brief Renders the text onto the renderer at the specified position.
     *
     * @param renderer The SDL renderer to render onto.
     * @param posMessage The position where the text should be rendered.
     */
    void Draw(SDL_Renderer* renderer, Position posMessage);
};

