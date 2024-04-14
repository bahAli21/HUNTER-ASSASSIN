#ifndef HUNTERASSASSIN_SDLANIMATION_H
#define HUNTERASSASSIN_SDLANIMATION_H

#include "../core/config.h"
#include "../core/point.h"

#include "../core/_Player.h"

#include "SDL.h"
#include "../core/Rect.h"
#include "SDLSprite.h"
#include "../core/Direction.h"
#include "SDLSound.h"
#include "SDL_mixer.h"
#include "Level.h"

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
    void patrouilleGardeUpLeft(int vitesse, int idx);
    void patrouilleGardeUpRight(int vitesse, int idx);
    void patrouilleGardeDownLeft(int vitesse, int idx);
    void patrouilleGardeDownRight(int vitesse, int idx);

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
    void updateCharacter(int index, Level &level);
    bool checkCollision(SDL_Rect rect1, SDL_Rect rect2);
    bool collisionWithLevel(SDL_Rect playerRect, Level &level);
    void closeDoor(Level & level);
    void openDoor(Level & level);
    void getKey(Level & level);
    SDL_Rect smallRect;

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

    float distanceToTarget; /**< Distance to target. */
    float distanceMove; /**< Distance moved. */
    const Uint8* state; /**< Current keyboard state. */
};

#endif //HUNTERASSASSIN_SDLANIMATION_H
