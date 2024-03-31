#include "Game.h"

Game::Game(int nbGardes): _player(), nbGardes(nbGardes),
    PlayerAI(_player.playerDest, _player.dest) {

   /* allGardes = new Garde[nbGardes];
    gardesDest = new Rect[nbGardes];
    gardesRect = new Rect[nbGardes];
    guardAI = new AI[getNbGardes()];
    for (int i = 0; i < getNbGardes(); ++i) {
        // Initialiser les gardes avec leurs positions
        guardAI[i] = AI(&gardesRect[i], &gardesDest[i]); // Créer une instance de l'IA pour chaque garde
    }
    srand(time(NULL));
    for(int i = 0; i < nbGardes; ++i){
        int X, Y;
        bool collision;
        do {
            X = rand() %(WINDOW_W-PLAYER_WIDTH-10);
            Y = rand() %((WINDOW_H/2)-30);
            collision = false;

            Rect rectTmp = {X, Y, 30,30};
            // Je vérifie la collision avec les obstacles
            for (const auto& obstacle : vecAllObstacles) {
                if (checkCollision(rectTmp, obstacle)) {
                    collision = true;
                    break;
                }
            }
            // Je vérifie la collision avec les gardes déjà générés
            for (int j = 0; j < i; ++j) {
                Rect rect= {allGardes[j].getPosition().x, allGardes[j].getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT};
                if (checkCollision(rectTmp, rect)) {
                    collision = true;
                    break;
                }
            }
        } while (collision);

        allGardes[i].setPositionX(X);
        allGardes[i].setPositionY(Y);
        gardesDest[i] = {allGardes[i].getPosition().x,
                        allGardes[i].getPosition().y,
                    PLAYER_WIDTH-40,
                    PLAYER_HEIGHT-40};
        gardesRect[i] = {allGardes[i].getPosition().x,
                       allGardes[i].getPosition().y,
                       PLAYER_WIDTH-40,
                       PLAYER_HEIGHT-40};
    }
    vecAllObstacles.push_back({WINDOW_W / 4 +20, 150, WINDOW_W / 4 - 25, SQUARE_SIZE});
    vecAllObstacles.push_back({WINDOW_W / 4, 150, WINDOW_W / 4 - 25, SQUARE_SIZE});
    */
    addGardeAndPlayers();
}

void Game::addGardeAndPlayers() {
    const char * pathSpriteGarde[8];
    Rect destGarde[8];
    std::string gardeName[8];
    srand(time(NULL));

    Rect source = {WIDTH_A/2, HEIGHT_A*21, WIDTH_A, HEIGHT_A*2};
    Rect destPlayer = {WINDOW_W/2 -WIDTH_A,WINDOW_H - HEIGHT_A*2, WIDTH_A, HEIGHT_A};
    listeOfPlayers.emplace_back(&source, &destPlayer, 0, 100,"../data/player.bmp", "BAH", 1, 21);

    int newX[8], newY[8];
    newX[0] = WIDTH_A*(+2);
    newY[0] = 10;
    newX[1] = WIDTH_A*(+3);
    newY[1] = 10;
    newX[2] = WIDTH_A*(+4);
    newY[2] = 10;
    newX[3] = WIDTH_A*(+5);
    newY[3] = 10;
    pathSpriteGarde[0] = "../data/garde1.bmp";
    pathSpriteGarde[1] = "../data/garde2.bmp";
    pathSpriteGarde[2] = "../data/garde3.bmp";
    pathSpriteGarde[3] = "../data/garde4.bmp";

    destGarde[0] = {newX[0], newY[0], WIDTH_A, HEIGHT_A*2};
    destGarde[1] = {newX[1], newY[1], WIDTH_A, HEIGHT_A*2};
    destGarde[2] = {newX[2], newY[2], WIDTH_A, HEIGHT_A*2};
    destGarde[3] = {newX[3], newY[3], WIDTH_A, HEIGHT_A*2};

    gardeName[0] = "Garde1 ";
    gardeName[1] = "Garde2 ";
    gardeName[2] = "Garde3 ";
    gardeName[3] = "Garde4 ";

    listeOfGardes.emplace_back(&source, &destGarde[0], 1, (1+1)*10,pathSpriteGarde[0], gardeName[0], 1, (1+1));
    listeOfGardes.emplace_back(&source, &destGarde[1], 2, (1+2)*10,pathSpriteGarde[1], gardeName[1], 2, (1+2));
    listeOfGardes.emplace_back(&source, &destGarde[2], 3, (1+3)*10,pathSpriteGarde[2], gardeName[2], 3, (1+3));
    listeOfGardes.emplace_back(&source, &destGarde[3], 4, (1+4)*10,pathSpriteGarde[3], gardeName[3], 4, (1+4));
}

// Méthode pour vérifier la collision entre deux rectangles
bool Game::checkCollision(const Rect& rect1, const Rect& rect2) {
    int rect1Left = rect1.x;
    int rect1Right = rect1.x + rect1.w;
    int rect1Top = rect1.y;
    int rect1Bottom = rect1.y + rect1.h;

    int rect2Left = rect2.x;
    int rect2Right = rect2.x + rect2.w;
    int rect2Top = rect2.y;
    int rect2Bottom = rect2.y + rect2.h;

    // Vérification sur les collisions
    return (rect1Right >= rect2Left && rect1Left <= rect2Right && rect1Bottom >= rect2Top && rect1Top <= rect2Bottom);
}


Game::~Game() {
    delete [] allGardes;
    allGardes = nullptr;
}

bool Game::toucheClavier(const char touche)
{
    switch (touche)
    {
        case 'z':
            _player.goUp();
            break;
        case 'q':
            _player.goLeft();
            break;
        case 's':
            _player.goDown();
            break;
        case 'd':
            _player.goRight();
            break;
    }

    return false;
}

void Game::movingGuardByAI(Uint32 lastGuardDestinationChangeTime) {
    for (int i = 0; i < getNbGardes(); ++i) {
        if (!guardAI[i].estArrivee()) {
            guardAI[i].mov(vecAllObstacles);
        } else {
            Uint32 currentTime = SDL_GetTicks();
            if(currentTime - lastGuardDestinationChangeTime >= 3000) {
                int newGuardX, newGuardY;
                do {
                    newGuardX = rand() % (WINDOW_W - PLAYER_WIDTH - 10);
                    newGuardY = rand() % (WINDOW_H - PLAYER_HEIGHT - 10);
                    gardesDest[i].x = newGuardX;
                    gardesDest[i].y = newGuardY;
                } while (!guardAI[i].freePixel(vecAllObstacles));
                lastGuardDestinationChangeTime = currentTime;
            }

        }
    }
}

void Game::movingPlayerByAI() {
    if (!PlayerAI.estArrivee())
        PlayerAI.mov(vecAllObstacles);
}

void Game::updatePlayerDest(int x, int y) {
    // Mettre à jour la position de destination avec les coordonnées du clic
    _player.dest->x = x;
    _player.dest->y = y;
}