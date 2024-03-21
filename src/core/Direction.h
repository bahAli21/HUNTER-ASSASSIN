//
// Created by mamad on 21/03/2024.
//

#ifndef HUNTERASSASSIN_DIRECTION_H
#define HUNTERASSASSIN_DIRECTION_H

/**
 * @file Direction.h
 * @brief Defines directional constants for movement.
 */

/**
 * @brief Enumeration of directional constants.
 * NORTH represents upward movement.
 * WEST represents leftward movement.
 * EAST represents rightward movement.
 * SOUTH represents downward movement.
 */
enum {
    NORTH = 0, /**< Upward direction constant. */
    WEST = 1, /**< Leftward direction constant. */
    EAST = 3, /**< Rightward direction constant. */
    SOUTH = 2 /**< Downward direction constant. */
};

#endif //HUNTERASSASSIN_DIRECTION_H
