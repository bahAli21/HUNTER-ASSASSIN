#ifndef HUNTERASSASSIN_SDLGAME_H
#define HUNTERASSASSIN_SDLGAME_H

#include "SDLAnimation.h" // include SDLSprite.h
#include "../core/Game.h"
#include "SDL.h"
#include "../core/config.h"

/**
 * @brief Class managing the game with SDL display.
 */
class SDLGame {
private:
    Game game; /**< Instance of the Game class. */
    SDL_Window *window; /**< SDL window for display. */
    SDL_Renderer *renderer; /**< SDL rendering context for display. */
    SDLSprite sp_player; /**< SDL sprite for the player. */
    SDLSprite sp_garde; /**< SDL sprite for the guards. */
    SDLSprite sourceAnimation;
    char *animImg;
    // Sprite for the map
    SDLSprite sp_greyBoxe; // represented by 'g'
    SDLSprite sp_redBoxe1; // represented by 'i'
    SDLSprite sp_redBoxe2; // represented by 'j'
    SDLSprite sp_redBoxe3; // represented by 'k'
    SDLSprite sp_redBoxe4; // represented by 'l'
    SDLSprite sp_door; // represented by '|'
    SDLSprite sp_smallBoxe; // represented by 'b'
    SDLSprite sp_blueDoor; // represented by 'd'
    SDLSprite sp_wall1; // represented by '#'
    SDLSprite sp_wall2; // represented by 'p'
    SDLSprite sp_moqGrey; // represented by '_'
    SDLSprite sp_moqBlack; // represented by '.'

public:
    /**
     * @brief Draws the map using SDL.
     * @param map The map to be drawn.
     */
    void drawTheMap(const Map &map) const;

    /**
     * @brief Default constructor of the SDLGame class.
     */
    SDLGame();

    /**
     * @brief Destructor of the SDLGame class.
     */
    ~SDLGame();

    /**
     * @brief Main method to run the game.
     */
    void runProject();

    /**
     * @brief Method to draw the game with SDL.
     */
    void sdlDraw();

    /**
     * @brief Method to get the elapsed time.
     * @return The time elapsed since the start of the game.
     */
    float temps();
};

#endif //HUNTERASSASSIN_SDLGAME_H
