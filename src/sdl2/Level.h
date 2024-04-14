#pragma once
#include "SDL.h"
#include "TextureLoader.h"
#include "../core/config.h"
class Level {
public:

    int angle = 0;

    /**
   * @brief Constructeur de la classe Level.
   *
   * @param renderer Pointeur vers le renderer SDL.
   */
    Level(SDL_Renderer* renderer);

    ~Level();

    /**
     * @brief Dessine le niveau.
     *
     * @param renderer Pointeur vers le renderer SDL.
     */
    void draw(SDL_Renderer* renderer);

    // Textures des tuiles
    SDL_Texture* textureTileWallOne = nullptr;
    SDL_Texture* textureTileDoorOne = nullptr;
    SDL_Texture* textureTileCubeOne = nullptr;
    SDL_Texture* textureTileDoorTwo = nullptr;
    SDL_Texture* textureTileWallTwo = nullptr;
    SDL_Texture* textureTileKey = nullptr;
    SDL_Texture* textureTileBlockGris = nullptr;
    SDL_Texture* textureTileDiamant = nullptr;
    SDL_Texture* textureTileMoquette = nullptr;
    SDL_Texture* textureTileCubeTwo = nullptr;

    SDL_Rect destMoq;
    SDL_Rect destWallUp;
    SDL_Rect destSmallWallUpLeft;
    SDL_Rect destSmallWallUpRight;
    SDL_Rect destWallDown;
    SDL_Rect destWallLeft;
    SDL_Rect destWallRight;
    SDL_Rect destBlockGrisTopLeft;
    SDL_Rect destBlockGrisTopRight;
    SDL_Rect destBlockGrisMiddleLeft;
    SDL_Rect destBlockGrisMiddleRight;
    SDL_Rect destBlockGrisDownLeft;
    SDL_Rect destBlockGrisDownRight;
    SDL_Rect destKey;
    SDL_Rect destDoorDown;
    SDL_Rect destDoorUp;
    SDL_Rect destCube1;
    SDL_Rect destCube2;
    SDL_Rect destCube3;
    SDL_Rect destDiamant;
};

