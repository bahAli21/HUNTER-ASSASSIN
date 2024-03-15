#include <iostream>
#include <SDL.h>
#include <vector>
#include <string>
using namespace std;

#include "color.h"
#include "../src/config_Variable.h"
#include "time.h"
#include "math.h"
#include "stdlib.h"
#ifndef HUNTERASSASSIN_MAP_H
#define HUNTERASSASSIN_MAP_H


class map {
public:
    SDL_Rect recTab[20];
    //char * pathTab[20];
    vector<char*> imgPaths;
    char* PORTE = "../data/porte.bmp";
    char * defaultDirectory = "../data/";
    void initAllRectangle();
    void drawObstacle(SDL_Renderer * renderer, char * path, SDL_Rect destination);
    //void drawMoquette(SDL_Renderer * renderer);
    void makeMap(SDL_Renderer * renderer);
    void pathTexture(vector<char*> &imgPaths, char* image, int repetition);
};


#endif //HUNTERASSASSIN_MAP_H
