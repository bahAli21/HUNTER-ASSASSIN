#ifndef HUNTERASSASSIN_Garde_H
#define HUNTERASSASSIN_Garde_H

#include "point.h"
#include "config.h"
#include <cassert>
#include <iostream>

/**
 * @brief Class representing the Guard in the game.
 */
class Garde {
private:
    Position pos; ///< Current position of the Guard.
    bool left, right, up, down; ///< Direction indicators of the Guard.
    int health; ///< Health points of the Guard.

public:
    /**
     * @brief Moves the Guard to the left on the specified map.
     * @param map The map on which the Guard moves.
     */
    void goLeft();

    /**
     * @brief Moves the Guard to the right on the specified map.
     * @param map The map on which the Guard moves.
     */
    void goRight();

    /**
     * @brief Moves the Guard upward on the specified map.
     * @param map The map on which the Guard moves.
     */
    void goUp();

    /**
     * @brief Moves the Guard downward on the specified map.
     * @param map The map on which the Guard moves.
     */
    void goDown();

    /**
     * @brief Gets the current position of the Guard.
     * @return The current position of the Guard.
     */
    Position getPosition() const;

    /**
     * @brief Sets the horizontal position of the Guard.
     * @param _x The new horizontal position.
     */
    void setPositionX(int _x);

    /**
     * @brief Sets the vertical position of the Guard.
     * @param _y The new vertical position.
     */
    void setPositionY(int _y);

    /**
     * @brief Gets the health points of the Guard.
     * @return The health points of the Guard.
     */
    int getHealth() const;

    /**
     * @brief Sets the health points of the Guard.
     * @param _health The new health points.
     */
    void setHealth(int _health);

    /**
     * @brief Default constructor of the Guard class.
     */
    Garde();

    /**
     * @brief Destructor of the Guard class.
     */
    ~Garde();

    /**
     * @brief Regression testing method.
     * Used to test the functionalities of the Guard class.
     */
    static void testRegression();
};

// Inline function definitions

/**
 * @brief Gets the current position of the Guard.
 * @return The current position of the Guard.
 */
inline Position Garde::getPosition() const { return pos; }

/**
 * @brief Sets the horizontal position of the Guard.
 * @param _x The new horizontal position.
 */
inline void Garde::setPositionX(int _x) { pos.x = _x; }

/**
 * @brief Sets the vertical position of the Guard.
 * @param _y The new vertical position.
 */
inline void Garde::setPositionY(int _y) { pos.y = _y; }

/**
 * @brief Gets the health points of the Guard.
 * @return The health points of the Guard.
 */
inline int Garde::getHealth() const { return health; }

/**
 * @brief Sets the health points of the Guard.
 * @param _health The new health points.
 */
inline void Garde::setHealth(int _health) { health = _health; }

#endif // HUNTERASSASSIN_Garde_H
