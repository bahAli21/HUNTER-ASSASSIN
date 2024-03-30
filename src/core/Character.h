#pragma once
#include "point.h"
#include "config.h"
#include <cassert>
#include "Rect.h"

#include <iostream>
#include "vector"
#include "Arrow.h"
#include "Direction.h"

class Character{

public:

    Character(Rect * source, Rect * dest, int direction, int health, const char * theSpritePath);
    ~Character();
    int health; ///< Health points of the player.
    Rect * dest; ///< Destination of the player.
    Rect * source; ///< Source of the player.
    int direction{}; /**< Direction indicators of the player.*/
    std::vector<Arrow> listArrow; /**< Liste des tuiles du niveau. */
    char shootKey;

    const char * theSpritePath;
    //Walking clips
    Position player_left_clips[9]{}; /**< Array of positions for left movement animation. */
    Position player_right_clips[9]{}; /**< Array of positions for right movement animation. */
    Position player_up_clips[9]{}; /**< Array of positions for up movement animation. */
    Position player_down_clips[9]{}; /**< Array of positions for down movement animation. */

    //Shoot clips
    Position attackUp[13]{}; /**< Array of positions for attacking upwards animation. */
    Position attackLeft[13]{}; /**< Array of positions for attacking left animation. */
    Position attackDown[13]{}; /**< Array of positions for attacking downwards animation. */
    Position attackRight[13]{}; /**< Array of positions for attacking right animation. */

    //Dead clips
    Position PlayerHurtClips[7];

public:
    static void AttackInit(Position tabPos[], int index);
    void makeAnimation(int index, Position tabPos[]) const;
    void WalkingAnimation(Position tabPos[], int speed, int indexClips, int direction) const;
    void UP(int idxAtt);
    void LEFT(int idxAtt);
    void RIGHT(int idxAtt);
    void DOWN(int idxAtt);
    void updateArrowPos();
    bool canShootNow = false;
    static void Walk(Position tabPos[], int index);
    void loadClips();
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

};


// Inline function definitions

/**
 * @brief Gets the health points of the player.
 * @return The health points of the player.
 */
inline int Character::getHealth() const { return health; }

/**
 * @brief Sets the health points of the player.
 * @param _health The new health points.
 */
inline void Character::setHealth(int _health) { health = _health;}
