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
    Position camera {};
public:
    /**
     * @brief Draws the map using SDL.
     * @param map The map to be drawn.
     */
    //void drawTheMap(const Map &map) const;

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
};

#endif //HUNTERASSASSIN_SDLGAME_H
