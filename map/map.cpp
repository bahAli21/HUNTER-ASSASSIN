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
void map::drawObstacle(SDL_Renderer * renderer, char * path, SDL_Rect destination) {
    SDL_Surface* obstacle = SDL_LoadBMP(path);
    SDL_Texture * tex = SDL_CreateTextureFromSurface( renderer,obstacle);
    SDL_FreeSurface(obstacle);
    SDL_RenderCopy( renderer,  tex,  NULL, & destination);
}

void map::makeMap(SDL_Renderer * renderer) {
    //drawMoquette(renderer);
    for(int i=0; i<=17;i++){
        drawObstacle(renderer,imgPaths[i],recTab[i]);
    }
}
//un probleme de concatenation à resoudre
void map::initAllRectangle() {
    //destination
    //porte
    /*recTab[0].x = 225;
    recTab[0].y = 823;
    recTab[0].w = 100;
    recTab[0].h = 33;
    //mur gauche
    recTab[1].x = 0;
    recTab[1].y = 800;
    recTab[1].w = 225;
    recTab[1].h = 50;
    //mur droit
    recTab[2].x = 325;
    recTab[2].y = 800;
    recTab[2].w = 225;
    recTab[2].h = 50;
    //texture bas
    recTab[3].x = 0;
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
    recTab[17].h = 50;*/
    const int tailleRecTab = 20;
    int recTabX[tailleRecTab] = {225, 0, 325, 0, 0, 190, 175, 190, 190, 230, 530, 450, 280, 280, 280, 415, 415, 415};
    int recTabY[tailleRecTab] = {823, 800, 800, 510, 0, 0, 580, 200, 0, 470, -5, 470, 50, 190, 330, 50, 190, 330};
    int recTabW[tailleRecTab] = {100, 225, 225, 550, 190, 368, 185, 40, 40, 90, 40, 100, 50, 50, 50, 50, 50, 50};
    int recTabH[tailleRecTab] = {33, 50, 50, 305, 510, 510, 167, 310, 80, 40, 510, 40, 50, 50, 50, 50, 50, 50};
    for(int i=0; i<tailleRecTab; i++){
        recTab[i].x = recTabX[i];
        recTab[i].y = recTabY[i];
        recTab[i].w = recTabW[i];
        recTab[i].h = recTabH[i];
    }
   //chemin
    /*pathTab[0] = "../data/porte.bmp";
    for(int i=1; i<3; i++){
        pathTab[i]= "../data/mur.bmp";
    }
    for(int i=3; i<5; i++){
        pathTab[i]= "../data/textureBlanc.bmp";
    }
    pathTab[5] = "../data/textureKaki.bmp";
    pathTab[6] = "../data/grosBlockBas.bmp";
    for(int i=7; i<=8; i++){
        pathTab[i]= "../data/bordureTextureKaki.bmp";
    }
    pathTab[9] = "../data/bordureKakiBas.bmp";
    pathTab[10]= "../data/bordureTextureKaki.bmp";
    pathTab[11] = "../data/bordureKakiBasDroite.bmp";
    for(int i=12; i<=17; i++){
        pathTab[i]= "../data/blockMilieu.bmp";
    }*/
    pathTexture(imgPaths,PORTE,1);
    pathTexture(imgPaths,"../data/mur.bmp",2);
    pathTexture(imgPaths,"../data/textureBlanc.bmp",2);
    pathTexture(imgPaths,"../data/textureKaki.bmp",1);
    pathTexture(imgPaths,"../data/grosBlockBas.bmp",1);
    pathTexture(imgPaths,"../data/bordureTextureKaki.bmp",2);
    pathTexture(imgPaths,"../data/bordureKakiBas.bmp",1);
    pathTexture(imgPaths,"../data/bordureTextureKaki.bmp",1);
    pathTexture(imgPaths,"../data/bordureKakiBasDroite.bmp",1);
    pathTexture(imgPaths,"../data/blockMilieu.bmp",6);
}

void map::pathTexture(vector<char *> &imgPaths, char *image, int repetition) {
    for(int i=1; i<=repetition; i++){
        imgPaths.push_back(image);
    }
}