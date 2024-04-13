#include "Game.h"


Game::Game(int nbGardes): nbGardes(nbGardes){
    addGardeAndPlayers();
}

void Game::addGardeAndPlayers() {
    const char* pathSpriteGarde[6] = {
            "../data/garde1.bmp",
            "../data/garde2.bmp",
            "../data/garde3.bmp",
            "../data/garde4.bmp",
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
    Rect destPlayer = {300, 300, WIDTH_A, HEIGHT_A*2};
    Rect targetPlayer = {300,300};
    listeOfPlayers.emplace_back(&source, &destPlayer, 0, 100, "../data/player.bmp",&targetPlayer,3, "BAH", 1, 21, defaultNoeud);
     //init 2 gardes
     //dest

     //Garde 1
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 27, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(10+WIDTH_A,HEIGHT_A+20,WIDTH_A,HEIGHT_A*2);
     //Garde 2
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 23, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(WINDOW_W-WIDTH_A-10,HEIGHT_A+20,WIDTH_A,HEIGHT_A*2);
     //Garde 3
     tabRectSource.emplace_back(WIDTH_A / 2, HEIGHT_A * 25, WIDTH_A, HEIGHT_A * 2);
     tabRectDest.emplace_back(10+WIDTH_A,HEIGHT_A+20*4,WIDTH_A,HEIGHT_A*2);
     //noeud
     //Noeud garde 1 gauche vers la droite (le chemein)
     std::vector<Position> tabNoeud;
    tabNoeud.push_back({20, 20});        // Noeud 1
    tabNoeud.push_back({20 * 3, 20});    // Noeud 2
    tabNoeud.push_back({20 * 3, 20 * 3}); // Noeud 3
    tabNoeud.push_back({20 * 6, 20 * 3}); // Noeud 4
    tabNoeud.push_back({20 * 6, 20});    // Noeud 5
    tabNoeud.push_back({20 * 12, 20});   // Noeud 6

    //Noeud garde 2 droite vers la gauche a faire

     Rect pointTarget = {rand()%((WINDOW_W-WIDTH_A)- WIDTH_A +1) + WIDTH_A,
                         rand()%((WINDOW_H-HEIGHT_A)- HEIGHT_A +1) + HEIGHT_A
     };

     for (int i = 0; i < nbGardes; ++i) {
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
                                    tabNoeud);
     }

    /* Rect source = {WIDTH_A / 2, HEIGHT_A * 21, WIDTH_A, HEIGHT_A * 2};
     Rect destPlayer = {300, 300, WIDTH_A, HEIGHT_A*2};
     Rect targetPlayer = {300,300};
     listeOfPlayers.emplace_back(&source, &destPlayer, 0, 100, "../data/player.bmp",&targetPlayer,3, "BAH", 1, 21);
      // Boucle pour créer les gardes en fonction de nbGardes
      for (int i = 0; i < nbGardes; ++i) {
          int newX, newY;
          bool collision;
          do {
              collision = false;
              newX = rand() % ((WINDOW_W - WIDTH_A) - WIDTH_A + 1) + WIDTH_A;
              newY = rand() % ((WINDOW_H / 2) - HEIGHT_A + 1) + HEIGHT_A;

              // Vérifions s'il y a une collision avec un autre garde
              for (int j = 0; j < i; ++j) {
                  if (destGarde[j].x < newX + WIDTH_A &&
                      newX < destGarde[j].x + destGarde[j].w &&
                      destGarde[j].y < newY + HEIGHT_A &&
                      newY < destGarde[j].y + destGarde[j].h) {
                      collision = true;
                      break;
                  }
              }
          } while (collision);

          int gardeSpriteIdx = rand() % 4;
          destGarde[i] = {newX, newY, WIDTH_A, HEIGHT_A * 2};
          gardeName[i] = "Garde" + std::to_string(i + 1) + " ";
          Rect pointTarget = {rand()%((WINDOW_W-WIDTH_A)- WIDTH_A +1) + WIDTH_A,
                                  rand()%((WINDOW_H-HEIGHT_A)- HEIGHT_A +1) + HEIGHT_A
          };
          listeOfGardes.emplace_back(&source,
                                     &destGarde[i],
                                     i,
                                     (i + 1) * 10,
                                     pathSpriteGarde[i],
                                     &pointTarget,
                                     3,
                                     gardeName[i],
                                     i + 1,
                                     (i + 1) + 1);
      }*/
}