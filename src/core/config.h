#ifndef HUNTERASSASSIN_CONFIG_H
#define HUNTERASSASSIN_CONFIG_H

#include "SDL.h"

/**
 * @file config.h
 * @brief Project constants
 */

/// @def WINDOW_TITLE
/// Title of the game window.
#define WINDOW_TITLE "Hunter Assassin"

/// @def WINDOW_X
/// Horizontal position of the window.
#define WINDOW_X SDL_WINDOWPOS_UNDEFINED

/// @def WINDOW_Y
/// Vertical position of the window.
#define WINDOW_Y SDL_WINDOWPOS_UNDEFINED

/// @def WINDOW_W
/// Width of the window.
#define WINDOW_W 700 // 700 for Gold, 500 for Aliou

/// @def WINDOW_H
/// Height of the window.
#define WINDOW_H 450 // 950 for Gold, 600 for Aliou

/// @def PLAYER_WIDTH
/// Width of the player.
#define PLAYER_WIDTH 64 // Never change for Gold

/// @def PLAYER_HEIGHT
/// Height of the player.
#define PLAYER_HEIGHT 64 // Never change for Gold

/// @def WIDTH_A
/// Width of the sprite.
#define WIDTH_A 64

/// @def HEIGHT_A
/// Height of the sprite.
#define HEIGHT_A 64

/// @def LEN
/// Size of buffer.
#define LEN 44
#define ARR_SPEED 6
#endif // HUNTERASSASSIN_CONFIG_H
