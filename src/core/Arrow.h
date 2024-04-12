#pragma once

#include "point.h"

/**
 * @brief Structure representing an arrow in the game.
 *
 * This structure holds information about the direction, position, rotation angle,
 * and speed of an arrow projectile in the game.
 */
struct Arrow {
    int direction; /**< Direction of the arrow. */
    Rect arrowPos; /**< Position and size of the arrow. */
    double angleRotate; /**< Rotation angle of the arrow. */
    int speed; /**< Speed of the arrow. */
};

