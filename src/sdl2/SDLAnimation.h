#pragma once

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
    Mix_Chunk * shootEffect; /**< Sound effect for shooting. */
    /** Sprite object containing all animations for the player and other entities. */
    SDLSprite allAnimation;
    /**
 * @brief Executes patrolling behavior for the guard character moving up and left.
 *
 * This function controls the patrolling behavior of the guard character, moving it up and left.
 *
 * @param vitesse The speed of movement.
 * @param idx Index of the animation.
 */
    void patrouilleGardeUpLeft(int vitesse, int idx);

/**
 * @brief Executes patrolling behavior for the guard character moving up and right.
 *
 * This function controls the patrolling behavior of the guard character, moving it up and right.
 *
 * @param vitesse The speed of movement.
 * @param idx Index of the animation.
 */
    void patrouilleGardeUpRight(int vitesse, int idx);

/**
 * @brief Executes patrolling behavior for the guard character moving down and left.
 *
 * This function controls the patrolling behavior of the guard character, moving it down and left.
 *
 * @param vitesse The speed of movement.
 * @param idx Index of the animation.
 */
    void patrouilleGardeDownLeft(int vitesse, int idx);

/**
 * @brief Executes patrolling behavior for the guard character moving down and right.
 *
 * This function controls the patrolling behavior of the guard character, moving it down and right.
 *
 * @param vitesse The speed of movement.
 * @param idx Index of the animation.
 */
    void patrouilleGardeDownRight(int vitesse, int idx);

/**
 * @brief Initializes collision attributes for the level.
 *
 * This function initializes collision attributes for the game level.
 *
 * @param level Reference to the game level object.
 */
    void initCollisionAttribute(Level & level);

    bool doorOpenNow{false}; /**< Indicates whether the door is currently open. */

    int colLeft{false}, colRight{false}, colDown{false}, colUp{false}; /**< Collision flags for left, right, down, and up directions. */


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

    /**
     * @brief Checks for collision between two rectangles.
     *
     * This function checks for collision between two SDL_Rect structures.
     *
     * @param rect1 First SDL_Rect structure.
     * @param rect2 Second SDL_Rect structure.
     * @return True if collision occurs, false otherwise.
     */
    bool checkCollision(SDL_Rect rect1, SDL_Rect rect2) const;
    void makeSmallRectCollision();

    /**
     * @brief Checks for collision between player and level objects.
     *
     * This function checks for collision between the player character
     * and objects in the game level.
     *
     * @param playerRect SDL_Rect structure representing player character.
     * @param level Reference to the game level object.
     * @return True if collision occurs, false otherwise.
     */
    bool collisionWithLevel(SDL_Rect playerRect, Level &level);

    /**
     * @brief Closes the door in the game level.
     *
     * This function closes the door in the game level.
     *
     * @param level Reference to the game level object.
     */
    void closeDoor(Level & level);

    /**
     * @brief Opens the door in the game level.
     *
     * This function opens the door in the game level.
     *
     * @param level Reference to the game level object.
     */
    void openDoor(Level & level);

    /**
     * @brief Gets the key in the game level.
     *
     * This function enables the player character to get the key
     * required to open the door in the game level.
     *
     * @param level Reference to the game level object.
     */
    void getKey(Level & level);

    //SDL_Rect smallRect; /**< SDL_Rect structure for small rectangle. */
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

