#include <iostream>
#include <SDL.h>
#include <vector>
#include <string>

using namespace std;

#include "../src/core/config.h"
#include "../src/core/point.h"
#include "unistd.h"
#ifndef HUNTERASSASSIN_MENU_H
#define HUNTERASSASSIN_MENU_H


class Menu {
public:
    SDL_Rect rect;
    SDL_Rect recTab[10];
    vector<char*> imgPaths;
    void initRectangles();
    void initPathMenu();
    void drawItem(SDL_Renderer * renderer, char * path, SDL_Rect destination);
    void pathTexture(vector<char*> &imgPaths, char* image, int repetition);
    void makeMenu(SDL_Renderer * renderer, Position mouse);
    int detecteClic(Position mouse, int value=0);
};


#endif //HUNTERASSASSIN_MENU_H
