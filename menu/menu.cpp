#include "menu.h"

/*void map::drawMoquette(SDL_Renderer * renderer) {
    SDL_Surface* moquette_img = SDL_LoadBMP("../data/imgMap1/mapMoq.bmp");
    SDL_Texture * tex = SDL_CreateTextureFromSurface( renderer, moquette_img);
    SDL_Rect source = {275, 0, 275,350};
    //SDL_Rect dest = {100, 100, PLAYER_WIDTH * 2, PLAYER_HEIGHT * 2};
    SDL_FreeSurface(moquette_img);
    SDL_RenderCopy( renderer,  tex, & source, NULL);
}*/

// on prend une image et on la place dans un rectangle destination qui est deja placee sur le rendu
void Menu::drawItem(SDL_Renderer * renderer, char * path, SDL_Rect destination) {
    SDL_Surface* obstacle = SDL_LoadBMP(path);
    SDL_Texture * tex = SDL_CreateTextureFromSurface( renderer,obstacle);
    SDL_FreeSurface(obstacle);
    SDL_RenderCopy( renderer,  tex,  NULL, & destination);
}

void Menu::makeMenu(SDL_Renderer * renderer, Position mouse) {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);

    SDL_RenderDrawRect(renderer, &rect);
    for(int i=0; i<5;i++){
        drawItem(renderer,imgPaths[i],recTab[i]);
    }
    SDL_SetRenderDrawColor(renderer, 255,112,100,255);
    SDL_RenderDrawRect(renderer, &recTab[4]);
    SDL_RenderDrawRect(renderer, &recTab[3]);
    int clickY;
    if((clickY = detecteClic(recTab,mouse)) != -1){
        for(int i=0; i<3;i++){
            if(clickY == recTab[i].y)
                SDL_RenderDrawRect(renderer, &recTab[i]);
        }
    }
}

int Menu::detecteClic(SDL_Rect *recTab, Position mouse) {
    for(int i=0; i<3; i++){
        if((mouse.x >= recTab[i].x && mouse.x <= recTab[i].x + recTab[i].w) && (mouse.y >= recTab[i].y && mouse.y <= recTab[i].y + recTab[i].h)){
            return recTab[i].y;
        }
    }
    return -1;
}

void Menu::initPathMenu(){
    pathTexture(imgPaths,"../data/menu/debut.bmp",1);
    pathTexture(imgPaths,"../data/menu/recommencer.bmp",1);
    pathTexture(imgPaths,"../data/menu/quitter.bmp",1);
    pathTexture(imgPaths,"../data/menu/initial.bmp",1);
    pathTexture(imgPaths,"../data/menu/titre.bmp",1);
}

void Menu::initRectangles() {
    //destination
    rect = {50,100, WINDOW_W-(2*50), WINDOW_H-(2*100)};
    const int tailleRecTab = 5;
    int recTabX[tailleRecTab] = {rect.x + rect.w/2 -80,rect.x + rect.w/2 -80,rect.x + rect.w/2 -80,rect.x + 3, rect.x + 60}; //Start indice 0 , Restart indice 1, Quit indice 3
    int recTabY[tailleRecTab] = {220,320,420,rect.y + rect.h - 43,85};
    int recTabW[tailleRecTab] = {150,150,150,rect.w - 6,180};
    int recTabH[tailleRecTab] = {40,40,40,40,30};
    /*recTab[0].x = recTabX[0];
    recTab[0].y = recTabY[0];
    recTab[0].w = recTabW[0];
    recTab[0].h = recTabH[0];*/
    for(int i=0; i<tailleRecTab; i++){
        recTab[i].x = recTabX[i];
        recTab[i].y = recTabY[i];
        recTab[i].w = recTabW[i];
        recTab[i].h = recTabH[i];
    }

    //chemin
    initPathMenu();

}

void Menu::pathTexture(vector<char *> &imgPaths, char *image, int repetition) {
    for(int i=1; i<=repetition; i++){
        imgPaths.push_back(image);
    }
}
