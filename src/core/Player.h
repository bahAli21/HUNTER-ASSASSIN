#ifndef HUNTERASSASSIN_PLAYER_H
#define HUNTERASSASSIN_PLAYER_H

#include "point.h"
#include "config.h"
#include <cassert>
#include "Rect.h"
#include "Map.h"
#include <iostream>

/**
 * @brief Class representing the player in the game.
 */
class Player {
public:
    Position pos; ///< Current position of the player.
    bool left, right, up, down; ///< Direction indicators of the player.
    int health; ///< Health points of the player.
    Rect playerDest; ///< Destination of the player.
    Rect playerSource; ///< Source of the player.
    Rect dest; /**< Destination of the AI. */

public:
    /**
     * @brief Moves the player to the left on the specified map.
     * @param map The map on which the player moves.
     */
    void goLeft(const Map &map);

    /**
     * @brief Moves the player to the right on the specified map.
     * @param map The map on which the player moves.
     */
    void goRight(const Map &map);

    /**
     * @brief Moves the player upward on the specified map.
     * @param map The map on which the player moves.
     */
    void goUp(const Map &map);

    /**
     * @brief Moves the player downward on the specified map.
     * @param map The map on which the player moves.
     */
    void goDown(const Map &map);

    /**
     * @brief Gets the current position of the player.
     * @return The current position of the player.
     */
    Position getPosition() const;

    /**
     * @brief Sets the horizontal position of the player.
     * @param _x The new horizontal position.
     */
    void setPositionX(int _x);

    /**
     * @brief Sets the vertical position of the player.
     * @param _y The new vertical position.
     */
    void setPositionY(int _y);

    /**
     * @brief Gets the health points of the player.
     * @return The health points of the player.
     */
    int getHealth() const;

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

    /**
     * @brief Regression testing method.
     * Used to test the functionalities of the Player class.
     */
    static void testRegression();
};

// Inline function definitions

/**
 * @brief Gets the current position of the player.
 * @return The current position of the player.
 */
inline Position Player::getPosition() const { return pos; }

/**
 * @brief Sets the horizontal position of the player.
 * @param _x The new horizontal position.
 */
inline void Player::setPositionX(int _x) { pos.x = _x; }

/**
 * @brief Sets the vertical position of the player.
 * @param _y The new vertical position.
 */
inline void Player::setPositionY(int _y) { pos.y = _y; }

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
