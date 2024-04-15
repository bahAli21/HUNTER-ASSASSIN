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
    textureTileCible = TextureLoader::loadTexture(renderer, "cible.bmp");
    // Initialisation des rectangles
    destMoq = {0, 0, 400, 600};
    destWallUp = {0, 0, 400, 30};
    destSmallWallUpLeft = {30, 115, 140, 20};
    destSmallWallUpRight = {400-170, 115, 150, 20};
    destWallDown = {0, 600-30, 400, 30};
    destWallLeft = {0, 30, 30, 600-66};
    destWallRight = {400 - 30, 30, 30, 600-66};
    destBlockGrisTopLeft = {100, 100, 50, 50};
    destBlockGrisTopRight = {400-150, 100, 50, 50};
    destBlockGrisMiddleLeft = {100, 250, 50, 50};
    destBlockGrisMiddleRight = {400-150, 250, 50, 50};
    destBlockGrisDownLeft = {100, 400, 50, 50};
    destBlockGrisDownRight = {400-150, 400, 50, 50};
    destKey = {50, 320, 50, 50};
    destDoorDown = {400/2 -20, 600-30, 40, 30};
    destDoorUp= {170, 117, 60, 12};

    destCube2= {40, 600-80, 80, 40};
    destCube3= {400-120, 600-80, 80, 40};
    destDiamant = {30, 145, 20, 20};

    //Footer
    cible = {10, WINDOW_H-77, 40, 40};
}

Level::~Level() = default;

void Level::draw(SDL_Renderer *renderer) {
    angle++;

    //SDL_RenderCopy(renderer, textureTileMoquette, nullptr, &destMoq);
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
    SDL_Point origine = {0,0};
    SDL_RenderCopyEx(renderer, textureTileDoorOne, nullptr, &destDoorUp, beta, &origine, SDL_FLIP_NONE);
    SDL_RenderCopy(renderer, textureTileCubeTwo, nullptr, &destCube2);
    SDL_RenderCopy(renderer, textureTileCubeTwo, nullptr, &destCube3);
    SDL_RenderCopyEx(renderer, textureTileDiamant, nullptr, &destDiamant, angle, nullptr,SDL_FLIP_NONE);
    SDL_RenderCopy(renderer, textureTileCible, nullptr, &cible);
}
