#include "Game.h"

Game::Game(int nbGardes): _player(), nbGardes(nbGardes),
    PlayerAI(_player.playerDest, _player.dest) {

    allGardes = new Garde[nbGardes];
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
    addGardeAndPlayers();
}

void Game::addGardeAndPlayers() {
    srand(time(NULL));
    Rect source = {PLAYER_WIDTH/2, PLAYER_HEIGHT*21, PLAYER_WIDTH, PLAYER_HEIGHT*2};
    Rect dest = {WINDOW_W/2 -PLAYER_WIDTH,WINDOW_H - PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT};
    listeOfPlayers.emplace_back(&source, &dest, 0, 100,"../data/player.bmp", "BAH", 1, 21);
    const char * pathSpriteGarde;
    for (int i = 0; i < nbGardes; ++i) {
        int newX, newY;
        if (i == 0) {
            // Génération des coordonnées pour le garde 0
            newX = rand() % 91 + 10; // entre 10 et 100
            newY = rand() % 91 + 10; // entre 10 et 100
            pathSpriteGarde = "../data/garde1.bmp";
        } else if (i == 1) {
            // Génération des coordonnées pour le garde 1
            newX = rand() % 101 + 200; // entre 200 et 300
            newY = rand() % 101 + 200; // entre 200 et 300
            pathSpriteGarde = "../data/garde2.bmp";
        } else if (i == 2) {
            // Génération des coordonnées pour le garde 2
            newX = rand() % 91 + 100; // entre 100 et 200
            newY = rand() % (WINDOW_H / 2); // entre 0 et WINDOW_H/2
            pathSpriteGarde = "../data/garde3.bmp";
        } else {
            // Génération des coordonnées pour le garde 3
            newX = rand() % 91 + 10; // entre 10 et 100
            newY = rand() % (WINDOW_H / 2); // entre 0 et WINDOW_H/2
            pathSpriteGarde = "../data/garde4.bmp";
        }
        Rect dest = {newX, newY, PLAYER_WIDTH, PLAYER_HEIGHT*2};
        std::string gardeName = "Garde " + std::to_string(i + 1);
        listeOfGardes.emplace_back(&source, &dest, rand() % 3, (i+1)*10,pathSpriteGarde, gardeName, rand() % 5, rand() % 5);
    }
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