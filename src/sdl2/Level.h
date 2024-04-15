#pragma once
#include "SDL.h"
#include "TextureLoader.h"
#include "../core/config.h"
#include "../core/point.h"

/**
 * @brief Class representing the game level.
 *
 * This class handles the drawing of the game level and manages the textures of various tiles.
 */
class Level {
public:
    int angle = 0; /**< Angle of rotation for the door (default: horizontal). */
    int beta = 0; /**< Angle of pivot for the door (default: horizontal). */
    /**
     * @brief Constructor for the Level class.
     *
     * @param renderer Pointer to the SDL renderer.
     */
    Level(SDL_Renderer* renderer);

    /**
     * @brief Destructor for the Level class.
     */
    ~Level();

    /**
     * @brief Draws the level.
     *
     * This function draws the game level on the specified renderer.
     *
     * @param renderer Pointer to the SDL renderer.
     */
    void draw(SDL_Renderer* renderer);

    // Tile textures
    SDL_Texture* textureTileWallOne = nullptr; /**< Texture for wall tile type 1. */
    SDL_Texture* textureTileDoorOne = nullptr; /**< Texture for door tile type 1. */
    SDL_Texture* textureTileCubeOne = nullptr; /**< Texture for cube tile type 1. */
    SDL_Texture* textureTileDoorTwo = nullptr; /**< Texture for door tile type 2. */
    SDL_Texture* textureTileWallTwo = nullptr; /**< Texture for wall tile type 2. */
    SDL_Texture* textureTileKey = nullptr; /**< Texture for key tile. */
    SDL_Texture* textureTileBlockGris = nullptr; /**< Texture for gray block tile. */
    SDL_Texture* textureTileDiamant = nullptr; /**< Texture for diamond tile. */
    SDL_Texture* textureTileMoquette = nullptr; /**< Texture for carpet tile. */
    SDL_Texture* textureTileCubeTwo = nullptr; /**< Texture for cube tile type 2. */
    SDL_Texture* textureTileCible = nullptr; /**< Texture for target tile. */

    // Destination rectangles for various tiles
    SDL_Rect destMoq; /**< Destination rectangle for carpet tile. */
    SDL_Rect destWallUp; /**< Destination rectangle for upper wall tile. */
    SDL_Rect destSmallWallUpLeft; /**< Destination rectangle for small upper left wall tile. */
    SDL_Rect destSmallWallUpRight; /**< Destination rectangle for small upper right wall tile. */
    SDL_Rect destWallDown; /**< Destination rectangle for lower wall tile. */
    SDL_Rect destWallLeft; /**< Destination rectangle for left wall tile. */
    SDL_Rect destWallRight; /**< Destination rectangle for right wall tile. */
    SDL_Rect destBlockGrisTopLeft; /**< Destination rectangle for top left gray block tile. */
    SDL_Rect destBlockGrisTopRight; /**< Destination rectangle for top right gray block tile. */
    SDL_Rect destBlockGrisMiddleLeft; /**< Destination rectangle for middle left gray block tile. */
    SDL_Rect destBlockGrisMiddleRight; /**< Destination rectangle for middle right gray block tile. */
    SDL_Rect destBlockGrisDownLeft; /**< Destination rectangle for bottom left gray block tile. */
    SDL_Rect destBlockGrisDownRight; /**< Destination rectangle for bottom right gray block tile. */
    SDL_Rect destKey; /**< Destination rectangle for key tile. */
    SDL_Rect destDoorDown; /**< Destination rectangle for downward door tile. */
    SDL_Rect destDoorUp; /**< Destination rectangle for upward door tile. */
    SDL_Rect destCube1; /**< Destination rectangle for cube tile 1. */
    SDL_Rect destCube2; /**< Destination rectangle for cube tile 2. */
    SDL_Rect destCube3; /**< Destination rectangle for cube tile 3. */
    SDL_Rect destDiamant; /**< Destination rectangle for diamond tile. */

    // Footer
    SDL_Rect cible; /**< Destination rectangle for target tile. */
};

