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


/**
 * @brief Class for handling player animations using SDL.
 */
class SDLAnimation {
public:
    Player player; /**< Player object for animation. */
    SDLSprite fireArrow;
    /** Pour les autre sprite aussi */
    SDLSprite allAnimation; /**< Sprite object containing all animations. */
    Position player_left_clips[9]{}; /**< Array of positions for left movement animation. */
    Position player_right_clips[9]{}; /**< Array of positions for right movement animation. */
    Position player_up_clips[9]{}; /**< Array of positions for up movement animation. */
    Position player_down_clips[9]{}; /**< Array of positions for down movement animation. */
    Position attackUp[13]{}; /**< Array of positions for attacking upwards animation. */
    Position attackUpReverse[7]{}; /**< Array of positions for reverse attacking upwards animation. */
    Position attackLeft[13]{}; /**< Array of positions for attacking left animation. */
    Position attackLeftReverse[7]{}; /**< Array of positions for reverse attacking left animation. */
    Position attackDown[13]{}; /**< Array of positions for attacking downwards animation. */
    Position attackDownReverse[7]{}; /**< Array of positions for reverse attacking downwards animation. */
    Position attackRight[13]{}; /**< Array of positions for attacking right animation. */
    Position attackRightReverse[7]{}; /**< Array of positions for reverse attacking right animation. */
    Position attackUpStabbed[7]{}; /**< Array of positions for attacking upwards with stabbing animation. */
    Position attackLeftStabbed[7]{}; /**< Array of positions for attacking left with stabbing animation. */
    Position attackDownStabbed[7]{}; /**< Array of positions for attacking downwards with stabbing animation. */
    Position attackRightStabbed[7]{}; /**< Array of positions for attacking right with stabbing animation. */
    Position PlayerHurtClips[7];
    /**
     * @brief Constructor for SDLAnimation class.
     * @param renderer SDL_Renderer object for rendering.
     * @param path Path to sprite image.
     * @param _player Player object.
     */
    SDLAnimation(SDL_Renderer* renderer, const char * path, const Player& _player);
    const Uint8* state;
    void updateArrowPos();
    /**
     * @brief Destructor for SDLAnimation class.
     */
    ~SDLAnimation();
    void Arrow(SDL_Renderer * renderer) const;
    char keyBoard{}; /**< Key pressed by player. */
    char keyBoardD{}; /**< Key pressed by player. */
    char keyBoardK{}; /**< Key pressed by player. */
    bool isDraw = false;
    bool moving_left{}; /**< Flag indicating left movement. */
    bool moving_right{}; /**< Flag indicating right movement. */
    bool moving_up{}; /**< Flag indicating up movement. */
    bool moving_down{}; /**< Flag indicating down movement. */

    /**
     * @brief Initiates walking animation.
     */
    void Walk(Position tabPos[], int index);

    /**
     * @brief Initializes attack animation.
     * @param tabPos Array of positions for animation.
     * @param index Index of animation.
     */
    static void AttackInit(Position tabPos[], int index);

    /**
     * @brief Creates animation frames.
     * @param index Index of animation.
     * @param tabPos Array of positions for animation.
     */
    void makeAnimation(int index, Position tabPos[]) const;

    /**
     * @brief Loads animation clips.
     */
    void loadClips();

    /**
     * @brief Handles input from keyboard.
     */
    void handleInput();

    /**
     * @brief Performs walking animation.
     * @param tabPos Array of positions for animation.
     * @param speed Animation speed.
     * @param indexClips Index of animation clip.
     * @param direction Direction of movement.
     */
    void walkingAnimation(Position tabPos[], int speed, int indexClips, int direction);

    /**
     * @brief Updates player state.
     */
    void updatePlayer();

    /**
     * @brief Draws animation on renderer.
     * @param renderer SDL_Renderer object for rendering.
     */
    void DrawAnimation(SDL_Renderer * renderer) const;

    /**
 * @brief Handles movement animation for moving upwards.
 * @param idxAtt Index of the attack animation.
 * @param c Character representing the direction of animation.
 */
    void UP(int idxAtt, char c);

    /**
     * @brief Handles movement animation for moving leftwards.
     * @param idxAtt Index of the attack animation.
     * @param c Character representing the direction of animation.
     */
    void LEFT(int idxAtt, char c);

    /**
     * @brief Handles movement animation for moving downwards.
     * @param idxAtt Index of the attack animation.
     * @param c Character representing the direction of animation.
     */
    void DOWN(int idxAtt, char c);

    /**
     * @brief Handles movement animation for moving rightwards.
     * @param idxAtt Index of the attack animation.
     * @param c Character representing the direction of animation.
     */
    void RIGHT(int idxAtt, char c);

};

#endif //HUNTERASSASSIN_SDLANIMATION_H
