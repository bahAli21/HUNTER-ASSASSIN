#include "map.h"

/*void map::drawMoquette(SDL_Renderer * renderer) {
    SDL_Surface* moquette_img = SDL_LoadBMP("../data/mapMoq.bmp");
    SDL_Texture * tex = SDL_CreateTextureFromSurface( renderer, moquette_img);
    SDL_Rect source = {275, 0, 275,350};
    //SDL_Rect dest = {100, 100, PLAYER_WIDTH * 2, PLAYER_HEIGHT * 2};
    SDL_FreeSurface(moquette_img);
    SDL_RenderCopy( renderer,  tex, & source, NULL);
}*/

// on prend une image et on la place dans un rectangle destination qui est deja placee sur le rendu
void Map::drawObstacle(SDL_Renderer * renderer, char * path, SDL_Rect destination) {
    SDL_Surface* obstacle = SDL_LoadBMP(path);
    SDL_Texture * tex = SDL_CreateTextureFromSurface( renderer,obstacle);
    SDL_FreeSurface(obstacle);
    SDL_RenderCopy( renderer,  tex,  NULL, & destination);
}

void Map::makeMap(SDL_Renderer * renderer) {
    //drawMoquette(renderer);
    for(int i=0; i<48;i++){
        drawObstacle(renderer,imgPaths[i],recTab[i]);
    }
}
//un probleme de concatenation à resoudre
void Map::initAllRectangle() {
    //destination
    const int tailleRecTab = 50;
    int recTabX[tailleRecTab] = {0,200,0,250,271,421,271,421,271,421,-25,0,675,270,270,395,270,270,70,70,70,170,170,170,70,70,70,70,70,70,70,70,70,500,500,500,603,603,603,500,500,500,500,500,500,500,500,500};
    int recTabY[tailleRecTab] = {0,900,900,900,799,799,480,480,130,130,0,-25,0,540,190,190,859,-3,190,509,800,70,389,680,70,389,680,70,389,680,140,459,750,190,509,800,70,389,680,70,389,680,70,389,680,140,459,750};
    int recTabW[tailleRecTab] = {700,50,200,450,20,19,19,19,19,19,50,700,50,170,45,45,170,170,130,130,130,30,30,30,130,130,130,30,30,30,20,20,20,130,130,130,30,30,30,130,130,130,30,30,30,20,20,20};
    int recTabH[tailleRecTab] = {950,50,50,50,60,60,60,60,60,60,910,50,910,260,295,295,43,135,30,30,30,149,149,149,30,30,30,70,70,70,50,50,50,30,30,30,149,149,149,30,30,30,70,70,70,50,50,50};
    for(int i=0; i<tailleRecTab; i++){
        recTab[i].x = recTabX[i];
        recTab[i].y = recTabY[i];
        recTab[i].w = recTabW[i];
        recTab[i].h = recTabH[i];
    }

    //chemin
    pathTexture(imgPaths,"../data/texture.bmp",1); // O moquette
    pathTexture(imgPaths,"../data/porte.bmp",1); // 1 porte
    pathTexture(imgPaths,"../data/mur-entree.bmp",2); // 2 3 mur
    pathTexture(imgPaths,"../data/porte jaune.bmp",6); // 4 5 6 7 8 9
    pathTexture(imgPaths,"../data/block.bmp",8); //
    pathTexture(imgPaths,"../data/bas.bmp",3);
    pathTexture(imgPaths,"../data/droite.bmp",3);
    pathTexture(imgPaths,"../data/haut.bmp",3);
    pathTexture(imgPaths,"../data/gauche.bmp",3);
    pathTexture(imgPaths,"../data/portesBlocks.bmp",3);
    pathTexture(imgPaths,"../data/bas.bmp",3);
    pathTexture(imgPaths,"../data/droite.bmp",3);
    pathTexture(imgPaths,"../data/haut.bmp",3);
    pathTexture(imgPaths,"../data/gauche.bmp",3);
    pathTexture(imgPaths,"../data/portesBlocks.bmp",3);

}

void Map::pathTexture(vector<char *> &imgPaths, char *image, int repetition) {
    for(int i=1; i<=repetition; i++){
        imgPaths.push_back(image);
    }
}