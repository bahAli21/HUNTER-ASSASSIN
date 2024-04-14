#pragma once

#include "SDLAnimation.h" // include SDLSprite.h
#include "../core/Game.h"
#include "SDL.h"
#include "../core/config.h"
#include "Level.h"

/**
 * @brief Class managing the game with SDL display.
 *
 * This class handles the main game loop and SDL display, including
 * initializing the game, running the game loop, and cleaning up resources.
 */
class SDLGame {
private:
    Game game; /**< Instance of the Game class. */
    SDL_Window *window; /**< SDL window for display. */
    SDL_Renderer *renderer; /**< SDL rendering context for display. */
    Position camera {}; /**< Camera position for rendering. */
public:
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
     *
     * This method initializes the SDL window and renderer, starts the game loop,
     * handles user input, updates game state, and renders graphics until the game ends.
     */
    void runProject();
};

