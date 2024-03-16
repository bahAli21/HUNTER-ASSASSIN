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
    for(int i=0; i<9;i++){
        drawObstacle(renderer,imgPaths[i],recTab[i]);
    }
}
//un probleme de concatenation à resoudre
void Map::initAllRectangle() {
    //destination

    const int tailleRecTab = 10;
    int recTabX[tailleRecTab] = {0,150,0,200,201,380,201,380,200};
    int recTabY[tailleRecTab] = {0,900,900,900,809,809,510,510,540};
    int recTabW[tailleRecTab] = {600,50,150,400,20,19,20,19,200};
    int recTabH[tailleRecTab] = {950,50,50,50,30,30,30,30,270};
    for(int i=0; i<tailleRecTab; i++){
        recTab[i].x = recTabX[i];
        recTab[i].y = recTabY[i];
        recTab[i].w = recTabW[i];
        recTab[i].h = recTabH[i];
    }
    //chemin
    pathTexture(imgPaths,"../data/texture.bmp",1);
    pathTexture(imgPaths,"../data/porte.bmp",1);
    pathTexture(imgPaths,"../data/mur-entree.bmp",2);
    pathTexture(imgPaths,"../data/porte jaune.bmp",4);
    pathTexture(imgPaths,"../data/block.bmp",1);
    /*
    pathTexture(imgPaths,"../data/moquette-blanc.bmp",2);
    pathTexture(imgPaths,"../data/mur.bmp",1);
    pathTexture(imgPaths,"../data/mur-bas.bmp",1);
    pathTexture(imgPaths,"../data/mur-horizontal.bmp",1);
    pathTexture(imgPaths,"../data/mur-horizontal-gauche.bmp",1);
    pathTexture(imgPaths,"../data/bordureKakiBasDroite.bmp",1);
    pathTexture(imgPaths,"../data/blockMilieu.bmp",6);
    //pathTexture(imgPaths,"../data/portes.bmp",1);*/
//porte
    /*recTab[0].x = 120;
    recTab[0].y = 850;
    recTab[0].w = 50;
    recTab[0].h = 50;
    //mur gauche
    recTab[1].x = 0;
    recTab[1].y = 850;
    recTab[1].w = 120;
    recTab[1].h = 50;
    //mur droit
    recTab[2].x = 170;
    recTab[2].y = 850;
    recTab[2].w = 380;
    recTab[2].h = 50;
    //texture bas
    /*recTab[3].x = 0;
    recTab[3].y = 510;
    recTab[3].w = 550;
    recTab[3].h = 305;
    //texture haut gauche
    recTab[4].x = 0;
    recTab[4].y = 0;
    recTab[4].w = 190;
    recTab[4].h = 510;
    //texture droit
    recTab[5].x = 190;
    recTab[5].y = 0;
    recTab[5].w = 368;
    recTab[5].h = 510;
    //bordure kaki gauche
    recTab[7].x = 190;
    recTab[7].y = 200;
    recTab[7].w = 40;
    recTab[7].h = 310;
    //bordure kaki haut
    recTab[8].x = 190;
    recTab[8].y = 0;
    recTab[8].w = 40;
    recTab[8].h = 80;
    //bordure kaki bas gauche
    recTab[9].x = 230;
    recTab[9].y = 470;
    recTab[9].w = 90;
    recTab[9].h = 40;
    //gros block bas
    recTab[6].x = 175;
    recTab[6].y = 580;
    recTab[6].w = 185;
    recTab[6].h = 167;
    //bordure kaki droite
    recTab[10].x = 530;
    recTab[10].y = -5;
    recTab[10].w = 40;
    recTab[10].h = 510;
    //bordure kaki bas droite
    recTab[11].x = 450;
    recTab[11].y = 470;
    recTab[11].w = 100;
    recTab[11].h = 40;
    //petits blocks milieu texture kaki
    recTab[12].x = 280;
    recTab[12].y = 50;
    recTab[12].w = 50;
    recTab[12].h = 50;

    recTab[13].x = 280;
    recTab[13].y = 190;
    recTab[13].w = 50;
    recTab[13].h = 50;

    recTab[14].x = 280;
    recTab[14].y = 330;
    recTab[14].w = 50;
    recTab[14].h = 50;

    recTab[15].x = 415;
    recTab[15].y = 50;
    recTab[15].w = 50;
    recTab[15].h = 50;

    recTab[16].x = 415;
    recTab[16].y = 190;
    recTab[16].w = 50;
    recTab[16].h = 50;

    recTab[17].x = 415;
    recTab[17].y = 330;
    recTab[17].w = 50;
    recTab[17].h = 50;
     */
}

void Map::pathTexture(vector<char *> &imgPaths, char *image, int repetition) {
    for(int i=1; i<=repetition; i++){
        imgPaths.push_back(image);
    }
}