#include "Level.h"

Level::Level(SDL_Renderer *renderer) {
    // Chargement des textures
    textureTileDoorOne   = TextureLoader::loadTexture(renderer, "doorOne.bmp");
    textureTileBlockGris = TextureLoader::loadTexture(renderer, "blockGris.bmp");
    textureTileCubeOne   = TextureLoader::loadTexture(renderer, "cubeOne.bmp");
    textureTileCubeTwo   = TextureLoader::loadTexture(renderer, "cubeTwo.bmp");
    textureTileDiamant   = TextureLoader::loadTexture(renderer, "diamant.bmp");
    textureTileDoorTwo   = TextureLoader::loadTexture(renderer, "doorTwo.bmp");
    textureTileKey       = TextureLoader::loadTexture(renderer, "key.bmp");
    textureTileWallOne   = TextureLoader::loadTexture(renderer, "wallTwoHorizontale.bmp");
    textureTileWallTwo   = TextureLoader::loadTexture(renderer, "wallTwo.bmp");

    // Initialisation des rectangles
    destMoq = {0, 0, WINDOW_W, WINDOW_H};
    destWallUp = {0, 0, WINDOW_W, 30};
    destSmallWallUpLeft = {30, 115, 150, 20};
    destSmallWallUpRight = {WINDOW_W-180, 115, 150, 20};
    destWallDown = {0, WINDOW_H-30, WINDOW_W, 30};
    destWallLeft = {0, 30, 30, WINDOW_H-59};
    destWallRight = {WINDOW_W - 30, 30, 30, WINDOW_H-59};
    destBlockGrisTopLeft = {100, 100, 50, 50};
    destBlockGrisTopRight = {WINDOW_W-150, 100, 50, 50};
    destBlockGrisMiddleLeft = {100, 250, 50, 50};
    destBlockGrisMiddleRight = {WINDOW_W-150, 250, 50, 50};
    destBlockGrisDownLeft = {100, 400, 50, 50};
    destBlockGrisDownRight = {WINDOW_W-150, 400, 50, 50};
    destKey = {50, 320, 50, 50};
    destDoorDown = {WINDOW_W/2 -20, WINDOW_H-30, 40, 30};
    destDoorUp= {180, 117, 40, 12};
    destCube1= {160, 330, 80, 40};
    destCube2= {40, WINDOW_H-80, 80, 40};
    destCube3= {WINDOW_W-120, WINDOW_H-80, 80, 40};
    destDiamant = {30, 145, 20, 20};
}

Level::~Level() = default;

void Level::draw(SDL_Renderer *renderer) {
    angle++;
    // Dessiner les textures en utilisant les rectangles
    SDL_RenderCopy(renderer, textureTileMoquette, nullptr, &destMoq);
    SDL_RenderCopy(renderer, textureTileWallOne, nullptr, &destWallUp);
    SDL_RenderCopy(renderer, textureTileWallOne, nullptr, &destSmallWallUpLeft);
    SDL_RenderCopy(renderer, textureTileWallOne, nullptr, &destSmallWallUpRight);
    SDL_RenderCopy(renderer, textureTileWallOne, nullptr, &destWallDown);
    SDL_RenderCopy(renderer, textureTileWallTwo, nullptr, &destWallLeft);
    SDL_RenderCopy(renderer, textureTileWallTwo, nullptr, &destWallRight);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisTopLeft);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisTopRight);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisMiddleLeft);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisMiddleRight);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisDownLeft);
    SDL_RenderCopy(renderer, textureTileBlockGris, nullptr, &destBlockGrisDownRight);
    SDL_RenderCopyEx(renderer, textureTileKey, nullptr, &destKey, angle, nullptr, SDL_FLIP_NONE);
    SDL_RenderCopy(renderer, textureTileDoorTwo, nullptr, &destDoorDown);
    SDL_RenderCopy(renderer, textureTileDoorOne, nullptr, &destDoorUp);
    SDL_RenderCopy(renderer, textureTileCubeOne, nullptr, &destCube1);
    SDL_RenderCopy(renderer, textureTileCubeTwo, nullptr, &destCube2);
    SDL_RenderCopy(renderer, textureTileCubeTwo, nullptr, &destCube3);
    SDL_RenderCopy(renderer, textureTileDiamant, nullptr, &destDiamant);
}
