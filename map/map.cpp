#include "map.h"

/*void map::drawMoquette(SDL_Renderer * renderer) {
    SDL_Surface* moquette_img = SDL_LoadBMP("../data/imgMap1/mapMoq.bmp");
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
    for(int i=0; i<58;i++){
        drawObstacle(renderer,imgPaths[i],recTab[i]);
    }
    //ouverture et fermeture des portes
    Uint8 time1 = SDL_GetTicks();
    openDoor();
    Uint8 time2 = SDL_GetTicks() - time1;
    if(time2>=1000){
        closeDoor();
    }
}

void Map::initPathMap1(){
    pathTexture(imgPaths,"../data/imgMap1/texture.bmp",1); // O moquette
    pathTexture(imgPaths,"../data/imgMap1/porte.bmp",1); // 1 porte
    pathTexture(imgPaths,"../data/imgMap1/mur-entree.bmp",2); // 2 3 mur
    pathTexture(imgPaths,"../data/imgMap1/porte jaune.bmp",6); // portes jaunes 4 5 6 7 8 9
    pathTexture(imgPaths,"../data/imgMap1/block.bmp",8); // bordure gauche 10, bordure haut 11, bordure droite 12, block 13,  piliers 14 15, block bas 16, block haut 17
    pathTexture(imgPaths,"../data/imgMap1/bas.bmp",3); // block bas cote gauche 18 19 20
    pathTexture(imgPaths,"../data/imgMap1/droite.bmp",3); // block droit cote gauche 21 22 23
    pathTexture(imgPaths,"../data/imgMap1/haut.bmp",3); // block haut cote gauche 24 25 26
    pathTexture(imgPaths,"../data/imgMap1/gauche.bmp",3); // block gauche coté gauche 27 28 29
    pathTexture(imgPaths,"../data/imgMap1/portesBlocks.bmp",3); // portes des blocks cote gauche 30 31 32
    pathTexture(imgPaths,"../data/imgMap1/bas.bmp",3); // block bas cote droit 33 34 35
    pathTexture(imgPaths,"../data/imgMap1/droite.bmp",3); // block droit cote droit 36 37 38
    pathTexture(imgPaths,"../data/imgMap1/haut.bmp",3); // block haut cote droit 39 40 41
    pathTexture(imgPaths,"../data/imgMap1/gauche.bmp",3); // block gauche coté droit 42 43 44
    pathTexture(imgPaths,"../data/imgMap1/portesBlocks.bmp",3); // portes des blocks cote droit 45 46 47
    pathTexture(imgPaths,"../data/imgMap1/block_H.bmp",2); // 48 50 obstacle gauche droite horizontal
    pathTexture(imgPaths,"../data/imgMap1/block_V.bmp",3); // 49 51 52 obstacle gauche droite vertical
    pathTexture(imgPaths,"../data/imgMap1/block_H.bmp",2); // 53 54 obstacle gauche horizontal
    pathTexture(imgPaths,"../data/imgMap1/clef.bmp",1); // 55 clef
    pathTexture(imgPaths,"../data/imgMap1/diamant.bmp",1); // 56 diamant
    pathTexture(imgPaths,"../data/imgMap1/block_Carre.bmp",1); // 57 block carre
}

//la deuxieme map
void Map::initPathMap2(){
    pathTexture(imgPaths,"../data/imgMap1/texture.bmp",1); // O moquette
    pathTexture(imgPaths,"../data/imgMap1/porte.bmp",1); // 1 porte
    pathTexture(imgPaths,"../data/imgMap1/mur-entree.bmp",2); // 2 3 mur
    pathTexture(imgPaths,"../data/imgMap1/porte jaune.bmp",6); // portes jaunes 4 5 6 7 8 9
    pathTexture(imgPaths,"../data/imgMap1/block.bmp",8); // bordure gauche 10, bordure haut 11, bordure droite 12, block 13,  piliers 14 15, block bas 16, block haut 17
    pathTexture(imgPaths,"../data/imgMap1/bas.bmp",3); // block bas cote gauche 18 19 20
    pathTexture(imgPaths,"../data/imgMap1/droite.bmp",3); // block droit cote gauche 21 22 23
    pathTexture(imgPaths,"../data/imgMap1/haut.bmp",3); // block haut cote gauche 24 25 26
    pathTexture(imgPaths,"../data/imgMap1/gauche.bmp",3); // block gauche coté gauche 27 28 29
    pathTexture(imgPaths,"../data/imgMap1/portesBlocks.bmp",3); // portes des blocks cote gauche 30 31 32
    pathTexture(imgPaths,"../data/imgMap1/bas.bmp",3); // block bas cote droit 33 34 35
    pathTexture(imgPaths,"../data/imgMap1/droite.bmp",3); // block droit cote droit 36 37 38
    pathTexture(imgPaths,"../data/imgMap1/haut.bmp",3); // block haut cote droit 39 40 41
    pathTexture(imgPaths,"../data/imgMap1/gauche.bmp",3); // block gauche coté droit 42 43 44
    pathTexture(imgPaths,"../data/imgMap1/portesBlocks.bmp",3); // portes des blocks cote droit 45 46 47
    pathTexture(imgPaths,"../data/imgMap1/block_H.bmp",2); // 48 50 obstacle gauche droite horizontal
    pathTexture(imgPaths,"../data/imgMap1/block_V.bmp",3); // 49 51 52 obstacle gauche droite vertical
    pathTexture(imgPaths,"../data/imgMap1/block_H.bmp",2); // 53 54 obstacle gauche horizontal
    pathTexture(imgPaths,"../data/imgMap1/clef.bmp",1); // 55 clef
    pathTexture(imgPaths,"../data/imgMap1/diamant.bmp",1); // 56 diamant
    pathTexture(imgPaths,"../data/imgMap1/block_Carre.bmp",1); // 57 block carre
}
//un probleme de concatenation à resoudre
void Map::initAllRectangle() {
    //destination
    const int tailleRecTab = 60;
    int recTabX[tailleRecTab] = {0,200,0,250,271,421,271,421,271,421,-25,0,675,270,270,395,270,270,70,70,70,170,170,170,70,70,70,70,70,70,70,70,70,500,500,500,603,603,603,500,500,500,500,500,500,500,500,500,70,150,490,450,210,80,500,645,640,560};
    int recTabY[tailleRecTab] = {0,900,900,900,799,799,480,480,130,130,0,-25,0,540,190,190,859,-3,190,509,800,70,389,680,70,389,680,70,389,680,140,459,750,190,509,800,70,389,680,70,389,680,70,389,680,140,459,750,335,285,295,260,680,590,590,35,860,840};
    int recTabW[tailleRecTab] = {700,50,200,450,20,19,19,19,19,19,50,700,50,170,45,45,170,170,130,130,130,30,30,30,130,130,130,30,30,30,20,20,20,130,130,130,30,30,30,130,130,130,30,30,30,20,20,20,100,50,90,40,50,120,120,30,40,50};
    int recTabH[tailleRecTab] = {950,50,50,50,60,60,60,60,60,60,910,50,910,260,295,295,43,135,30,30,30,149,149,149,30,30,30,70,70,70,50,50,50,30,30,30,149,149,149,30,30,30,70,70,70,50,50,50,50,100,40,80,110,40,40,30,40,50};
    for(int i=0; i<tailleRecTab; i++){
        recTab[i].x = recTabX[i];
        recTab[i].y = recTabY[i];
        recTab[i].w = recTabW[i];
        recTab[i].h = recTabH[i];
    }

    //chemin
    initPathMap1();
    //initPathMap2();

}

void Map::pathTexture(vector<char *> &imgPaths, char *image, int repetition) {
    for(int i=1; i<=repetition; i++){
        imgPaths.push_back(image);
    }
}

//ouverture portes
void Map::openDoor() {
    // porte principale
    if(recTab[1].x + recTab[1].w > recTab[1].x)
        recTab[1].w--;
    // portes jaunes
    for(int i=4; i<=9; i++){
        if(recTab[i].y + recTab[i].h > recTab[i].y)
            recTab[i].h--;
        sleep(1);
    }
    //isOpen = true;
}

//fermuture portes
void Map::closeDoor() {
    // porte principale
    if(recTab[1].x + recTab[1].w <= recTab[1].x)
        recTab[1].w++;
    // portes jaunes
    for(int i=4; i<=9; i++){
        if(recTab[i].h < 60)
            recTab[i].h ++;
    }
    //isOpen = false;
}
