#ifndef HUNTERASSASSIN_PLAYER_H
#define HUNTERASSASSIN_PLAYER_H

#include "point.h"
#include "config.h"
#include <cassert>
#include "Rect.h"
#include "../../map/map.h"
#include <iostream>
#include "vector"
#include "Arrow.h"
#include "Direction.h"

/**
 * @brief Class representing the player in the game.
 */
class Player {
public:

    //bool left, right, up, down; ///< Direction indicators of the player.
    int health; ///< Health points of the player.
    Rect * playerDest; ///< Destination of the player.
    Rect * playerSource; ///< Source of the player.
    Rect * dest; /**< Destination of the AI. */
    int direction{}; /**< Direction indicators of the player.*/
    std::vector<Arrow> listArrow; /**< Liste des tuiles du niveau. */
    bool moving_left{}; /**< Flag indicating left movement. */
    bool moving_right{}; /**< Flag indicating right movement. */
    bool moving_up{}; /**< Flag indicating up movement. */
    bool moving_down{}; /**< Flag indicating down movement. */
    Position player_left_clips[9]{}; /**< Array of positions for left movement animation. */
    Position player_right_clips[9]{}; /**< Array of positions for right movement animation. */
    Position player_up_clips[9]{}; /**< Array of positions for up movement animation. */
    Position player_down_clips[9]{}; /**< Array of positions for down movement animation. */
    Position attackUp[13]{}; /**< Array of positions for attacking upwards animation. */
    Position attackLeft[13]{}; /**< Array of positions for attacking left animation. */
    Position attackDown[13]{}; /**< Array of positions for attacking downwards animation. */
    Position attackRight[13]{}; /**< Array of positions for attacking right animation. */
    Position PlayerHurtClips[7];
    void AttackInit(Position tabPos[], int index);
    void makeAnimation(int index, Position tabPos[]);
    void WalkingAnimation(Position tabPos[], int speed, int indexClips, int direction);
    void UP(int idxAtt);
    void LEFT(int idxAtt);
    void RIGHT(int idxAtt);
    void DOWN(int idxAtt);
    void updateArrowPos();
    char shootKey{} ;
    bool canShootNow = false;

    void Walk(Position tabPos[], int index);
    void loadClips();
public:
    /**
     * @brief Moves the player to the left on the specified map.
     * @param map The map on which the player moves.
     */
     void createArrow(int direct);
    void goLeft() const;

    /**
     * @brief Moves the player to the right on the specified map.
     * @param map The map on which the player moves.
     */
    void goRight() const;

    /**
     * @brief Moves the player upward on the specified map.
     * @param map The map on which the player moves.
     */
    void goUp() const;

    /**
     * @brief Moves the player downward on the specified map.
     * @param map The map on which the player moves.
     */
    void goDown() const;

    /**
     * @brief Gets the health points of the player.
     * @brief l'utilisation de [[nodiscard]] permet de signaler explicitement
     * que la valeur de retour d'une fonction est significative
     * et doit être prise en compte par le code appelan
     * @return The health points of the player.
     */
    [[nodiscard]] int getHealth() const;

    /**
     * @brief Sets the health points of the player.
     * @param _health The new health points.
     */
    void setHealth(int _health);

    /**
     * @brief Default constructor of the Player class.
     */
    Player();

    /**
     * @brief Destructor of the Player class.
     */
    ~Player();
};

// Inline function definitions

/**
 * @brief Gets the health points of the player.
 * @return The health points of the player.
 */
inline int Player::getHealth() const { return health; }

/**
 * @brief Sets the health points of the player.
 * @param _health The new health points.
 */
inline void Player::setHealth(int _health) { health = _health; }

#endif // HUNTERASSASSIN_PLAYER_H
