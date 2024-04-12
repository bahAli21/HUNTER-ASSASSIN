#ifndef HUNTERASSASSIN_SDLANIMATION_H
#define HUNTERASSASSIN_SDLANIMATION_H

#include "../core/config.h"
#include "../core/point.h"
#include "../core/Player.h"
#include "../core/_Player.h"
#include "../core/Garde.h"
#include "SDL.h"
#include "../core/Rect.h"
#include "SDLSprite.h"
#include "../core/Direction.h"
#include "SDLSound.h"
#include "SDL_mixer.h"
#include "../Part2/Vector2D.h"
#include "../Part2/Level.h"

/**
 * @brief Class for handling player animations using SDL.
 *
 * This class manages animations for the player character in the game,
 * including movement, attacks, and other actions.
 */
class SDLAnimation {
public:
    Character character; /**< Player object for animation. */
    SDLSprite fireArrow; /**< Sprite for fire arrow animation. */
    SDLSound sound; /**< Sound effects for animations. */
    bool deathAnimationPlayed = false; /**< Flag indicating if death animation has been played. */
    int * ptrStop; /**< Pointer to stop animation. */
    Mix_Chunk * shootEffect; /**< Sound effect for shooting. */
    /** Sprite object containing all animations for the player and other entities. */
    SDLSprite allAnimation;
    Position PlayerHurtClips[7]; /**< Array of positions for player hurt animation. */

    /**
     * @brief Constructor for SDLAnimation class.
     *
     * @param renderer SDL_Renderer object for rendering.
     * @param _player Player object.
     */
    SDLAnimation(SDL_Renderer* renderer, Character _player);

    /**
     * @brief Default constructor for SDLAnimation class.
     */
    SDLAnimation();

    /**
     * @brief Destructor for SDLAnimation class.
     */
    ~SDLAnimation();

    char keyBoardK{}; /**< Key pressed by player. */

    /**
     * @brief Handles input from keyboard.
     *
     * This function updates the keyboard state and determines
     * the action to be performed based on the pressed keys.
     */
    void handleInput();

    /**
     * @brief Updates player state.
     *
     * This function updates the state of the player animation,
     * including movement and actions.
     *
     * @param index Index of the animation to update.
     */
    void updateCharacter(int index);

    /**
     * @brief Draws animation on renderer.
     *
     * This function draws the current animation frame on the specified renderer.
     *
     * @param renderer SDL_Renderer object for rendering.
     */
    void DrawAnimation(SDL_Renderer * renderer) const;

    /**
     * @brief Draws arrow animation on renderer.
     *
     * This function draws the arrow animation on the specified renderer.
     *
     * @param renderer SDL_Renderer object for rendering.
     */
    void drawArrow(SDL_Renderer * renderer) const;

    /**
     * @brief Updates animation based on time and game state.
     *
     * This function updates the animation based on the elapsed time
     * since the last update and the current game state.
     *
     * @param dT Delta time since last update.
     * @param level Current game level.
     */
    void updateTest(float dT, Level& level);

    float distanceToTarget; /**< Distance to target. */
    float distanceMove; /**< Distance moved. */
    const Uint8* state; /**< Current keyboard state. */
};

#endif //HUNTERASSASSIN_SDLANIMATION_H
