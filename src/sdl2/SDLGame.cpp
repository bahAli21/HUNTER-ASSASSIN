#include "SDLGame.h"

//J'ai converti le temps en second
float SDLGame::temps() { return float(SDL_GetTicks()) / CLOCKS_PER_SEC; }

SDLGame::SDLGame() : game(2) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
        // Quitter le programme
        exit(EXIT_FAILURE);
    }

    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // je Gère l'erreur si la création de la fenêtre a échoué
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // je Gère l'erreur si la création du renderer a échoué
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

//Une petite map ;
// Remplissage du vecteur avec les obstacles du tableau
    game.vecAllObstacles.push_back({WINDOW_W / 2 - 80, 50, WINDOW_W / 2 - 25, SQUARE_SIZE});
    game.vecAllObstacles.push_back({WINDOW_W / 4, WINDOW_H / 2 - 20, 25, WINDOW_W / 2 - 25});
    game.vecAllObstacles.push_back({WINDOW_W / 2 + 20, WINDOW_H / 2 - 20, 25, WINDOW_W / 2 - 25});
    game.vecAllObstacles.push_back({WINDOW_W / 2 - 80, WINDOW_H - 70, WINDOW_W / 2 - 25, SQUARE_SIZE});

    // Initialisation de tous les sprites
    //pour l'instant que le joueur
    // TODO On choisi le chemein depuis executable bin (donc on remonte une fois et on passe dans data)
    const char *path = "../data/mur.bmp";
    sp_player.loadSpriteFile(path, renderer);
    sp_garde.loadSpriteFile(path, renderer);
}

SDLGame::~SDLGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLGame::drawTheMap(const Map &map) const {
    for (int i = 0; i < map.getDimX(); ++i) {
        for (int j = 0; j < map.getDimY(); ++j) {
            // je dessine le sprite approprié en fonction de l'objet de la carte
            switch (map.getObject(i, j)) {
                case '#': // Mur
                    sp_wall1.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case '|': // Porte
                    sp_door.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'g': // Boîte grise
                    sp_greyBoxe.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'i': // Boîte rouge 1
                    sp_redBoxe1.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'j': // Boîte rouge 2
                    sp_redBoxe2.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'k': // Boîte rouge 3
                    sp_redBoxe3.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'l': // Boîte rouge 4
                    sp_redBoxe4.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'b': // Petite boîte
                    sp_smallBoxe.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'd': // Porte bleue
                    sp_blueDoor.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case 'p': // Mur 2
                    sp_wall2.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case '_': // Grille gris clair
                    sp_moqGrey.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                case '.': // Grille noire
                    sp_moqBlack.draw(renderer, i * PLAYER_WIDTH, j * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                    break;
                default:
                    // Si l'objet n'est pas reconnu, ne me dessine R
                    break;
            }
        }
    }
}

void SDLGame::sdlDraw() {
    // Je Remplis l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    const Player &m_player = game.getConstPlayer();
    const Garde *m_gardes = game.getAllGardes();
    const Map &m_map = game.getConstMap();

    //Je dessine ma map. pas encore complet, j'attends plus que golden
    drawTheMap(m_map);
    //Je dessine mon joueur
    sp_player.draw(renderer, game.playerRect.x, game.playerRect.y, PLAYER_WIDTH, PLAYER_HEIGHT);
    //Je dessine mon bloc
    for (const Rect obstacle: game.vecAllObstacles) {
        sp_player.draw(renderer, obstacle.x, obstacle.y, obstacle.w, obstacle.h);
    }
    //Je dessine tous les gardes
    for (int i = 0; i < game.getNbGardes(); ++i) {
        sp_garde.draw(renderer, game.gardesRect[i].x, game.gardesRect[i].y, game.gardesRect[i].w, game.gardesRect[i].h);
    }
}
#include <thread>
#include <vector>

void SDLGame::runProject() {
    SDL_Event event;

    AI myAI(&game.playerRect, &game.dest);
    AI *guardAI = new AI[game.getNbGardes()];
    for (int i = 0; i < game.getNbGardes(); ++i) {
        // Initialiser les gardes avec leurs positions
        guardAI[i] = AI(&game.gardesRect[i], &game.gardesDest[i]); // Créer une instance de l'IA pour chaque garde
    }
    Uint32 lastGuardDestinationChangeTime = SDL_GetTicks();
    bool isOpen = true;
    while (isOpen) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isOpen = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Mettre à jour la position de destination avec les coordonnées du clic
                    game.dest.x = event.button.x;
                    game.dest.y = event.button.y;
                }

        }
        sdlDraw();

        if (!myAI.estArrivee())
            myAI.mov(game.vecAllObstacles);

//Garde 0
        if (!guardAI[0].estArrivee()) {
            guardAI[0].mov(game.vecAllObstacles);
        } else {
            Uint32 currentTime = SDL_GetTicks();
            if(currentTime - lastGuardDestinationChangeTime >= 3000) {
                int newGuardX, newGuardY;
                do {
                    newGuardX = rand() % (WINDOW_W - PLAYER_WIDTH - 10);
                    newGuardY = rand() % (WINDOW_H - PLAYER_HEIGHT - 10);
                    game.gardesDest[0].x = newGuardX;
                    game.gardesDest[0].y = newGuardY;
                } while (!guardAI[0].freePixel(game.vecAllObstacles));
                lastGuardDestinationChangeTime = currentTime;
            }

        }
        //Garde 1



        /*for (int i = 0; i < game.getNbGardes(); ++i) {
            if (!guardAI[i].estArrivee()) {
                guardAI[i].mov(game.vecAllObstacles);
            } else {
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - lastGuardDestinationChangeTime >= 3000) {
                    int newGuardX, newGuardY;
                    do {
                        newGuardX = rand() % (WINDOW_W - PLAYER_WIDTH - 10);
                        newGuardY = rand() % (WINDOW_H - PLAYER_HEIGHT - 10);
                        game.gardesDest[i].x = newGuardX;
                        game.gardesDest[i].y = newGuardY;
                    } while (!guardAI[i].freePixel(game.vecAllObstacles));
                    lastGuardDestinationChangeTime = currentTime;
                }

            }
        }*/
        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }
}