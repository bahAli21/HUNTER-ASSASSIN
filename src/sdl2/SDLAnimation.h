#ifndef HUNTERASSASSIN_SDLANIMATION_H
#define HUNTERASSASSIN_SDLANIMATION_H

#include "../core/config.h"
#include "../core/point.h"
#include "../core/Player.h"
#include "../core/Garde.h"
#include "SDL.h"
#include "../core/Rect.h"
#include "SDLSprite.h"
#include "../core/Direction.h"
#include "SDLSound.h"
#include "SDL_mixer.h"


/**
 * @brief Class for handling player animations using SDL.
 */
class SDLAnimation {
public:
    Player player; /**< Player object for animation. */
    SDLSprite fireArrow;
    SDLSound sound;
    bool deathAnimationPlayed = false;
    int * ptrStop;
    Mix_Chunk * shootEffect;
    /** Pour les autre sprite aussi */
    SDLSprite allAnimation; /**< Sprite object containing all animations. */
    Position PlayerHurtClips[7];
    /**
     * @brief Constructor for SDLAnimation class.
     * @param renderer SDL_Renderer object for rendering.
     * @param path Path to sprite image.
     * @param _player Player object.
     */
    SDLAnimation(SDL_Renderer* renderer, const char * path,  Player _player);
    const Uint8* state;
    /**
     * @brief Destructor for SDLAnimation class.
     */
    ~SDLAnimation();

    char keyBoardK{}; /**< Key pressed by player. */

    /**
     * @brief Handles input from keyboard.
     */
    void handleInput();

    /**
     * @brief Updates player state.
     */
     void updatePlayer(int dirForTest);

    /**
     * @brief Draws animation on renderer.
     * @param renderer SDL_Renderer object for rendering.
     */
    void DrawAnimation(SDL_Renderer * renderer) const;

    void drawArrow(SDL_Renderer * renderer) const;
};

#endif //HUNTERASSASSIN_SDLANIMATION_H
