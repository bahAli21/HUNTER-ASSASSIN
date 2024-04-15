#include "Game.h"


Game::Game(int nbGardes): nbGardes(nbGardes){
    addGardeAndPlayers();
}

void Game::addGardeAndPlayers() {
    const char* pathSpriteGarde[6] = {
            "../data/garde1.bmp",
            "../data/garde2.bmp",
            "../data/garde3.bmp",
            "../data/garde6.bmp",
            "../data/garde5.bmp",
            "../data/garde6.bmp"
    };
    Rect destGarde[8];
    std::string gardeName[8];
    srand(time(NULL));
    std::vector<Rect> tabRectSource;
    std::vector<Rect> tabRectDest;
     //std::vector<Rect> tabRectTarget;

    std::vector<Position> defaultNoeud{{-1, -1}};
    Rect source = {WIDTH_A / 2, HEIGHT_A * 21, WIDTH_A, HEIGHT_A * 2};
    Rect destPlayer = {WINDOW_W/2 - WIDTH_A + 30, WINDOW_H - HEIGHT_A*3-20, WIDTH_A, HEIGHT_A*2};
    Rect targetPlayer = {300,300};
    listeOfPlayers.emplace_back(&source, &destPlayer, 0, 100, "../data/player.bmp",&targetPlayer,3, "BAH", 1, 21, defaultNoeud);
     //dest

    //garde 1 Left Up [0]
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 27, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(12,-25,WIDTH_A,HEIGHT_A*2);
     //Garde 2 Right UP [1]
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 23, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(WINDOW_W-WIDTH_A-22,HEIGHT_A+30,WIDTH_A,HEIGHT_A*2 - 10);

     //Garde 3 Left Down [2]
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 25, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(12,HEIGHT_A+60,WIDTH_A,HEIGHT_A*2);

     //Garde 4 Right Down [3] (coiffure bizarre rouge)
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 25, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(WINDOW_W-WIDTH_A-62,HEIGHT_A*3 ,WIDTH_A,HEIGHT_A*2);

     //noeud garde 1 UP LEFT

     tabNoeud[0][0] = {12, -25};
     tabNoeud[0][1] = {WINDOW_W-WIDTH_A-62, -25};
     tabNoeud[0][2] = {WINDOW_W-WIDTH_A-62, -25 +45};

     //noeud garde 2 UP RIGHT

     tabNoeud[1][0] = {WINDOW_W-WIDTH_A-52,HEIGHT_A+30};
     tabNoeud[1][1] = {WINDOW_W/2-80,HEIGHT_A+30};
     tabNoeud[1][2] = {WINDOW_W/2,HEIGHT_A+150};

     //noeud garde 3 DOWN LEFT

     tabNoeud[2][0] = {12,HEIGHT_A+60};
     tabNoeud[2][1] = {12, WINDOW_H - HEIGHT_A*4 -40};
     tabNoeud[2][2] = {WINDOW_W/2 - WIDTH_A + 30, WINDOW_H - HEIGHT_A*4 -40};

     //noeud garde 4 DOWN RIGHT

     tabNoeud[3][0] = {WINDOW_W-WIDTH_A-62,HEIGHT_A*3};
     tabNoeud[3][1] = {WINDOW_W-WIDTH_A-62,HEIGHT_A*5-20};
     tabNoeud[3][2] = {20,HEIGHT_A*5-20};

    //Noeud garde 2 droite vers la gauche a faire

     Rect pointTarget = {rand()%((WINDOW_W-WIDTH_A)- WIDTH_A +1) + WIDTH_A,
                         rand()%((WINDOW_H-HEIGHT_A)- HEIGHT_A +1) + HEIGHT_A
     };

     for (int i = 0; i < nbGardes; ++i) {
         std::vector<Position> tmpNoeud{};
         for (int j = 0; j < 3; ++j) {
             tmpNoeud.push_back(tabNoeud[i][j]);
         }
         listeOfGardes.emplace_back(&tabRectSource[i],
                                    &tabRectDest[i],
                                    i,
                                    (i + 1) * 10,
                                    pathSpriteGarde[i],
                                    &pointTarget,
                                    3,
                                    gardeName[i],
                                    i + 1,
                                    (i + 1) + 1,
                                    tmpNoeud);
     }

}

