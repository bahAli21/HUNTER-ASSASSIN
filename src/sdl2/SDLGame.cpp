#include "SDLGame.h"

SDLGame::SDLGame() : game(2){

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
    //game.vecAllObstacles.push_back({WINDOW_W / 4 +20, 150, WINDOW_W / 4 - 25, SQUARE_SIZE+10});
    //game.vecAllObstacles.push_back({WINDOW_W / 4, 150, WINDOW_W / 4 - 25, SQUARE_SIZE});
    // TODO On choisi le chemein depuis executable bin (donc on remonte une fois et on passe dans data)
    const char *path = "../data/mur.bmp";
    //sp_player.loadSpriteFile(path, renderer);
    sp_garde.loadSpriteFile(path, renderer);
    camera = {0,0};
}

SDLGame::~SDLGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*void SDLGame::drawTheMap(const Map &map) const {
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
} */

void SDLGame::sdlDraw() {
    // Je Remplis l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    //Je dessine mon bloc
    //sp_player.draw(renderer, game._player.playerDest->x, game._player.playerDest->y, 20, 20);
    for (const Rect obstacle: game.vecAllObstacles) {
        sp_player.draw(renderer, obstacle.x, obstacle.y, obstacle.w, obstacle.h);
    }
    //Je dessine tous les gardes
    for (int i = 0; i < game.getNbGardes(); ++i) {
        sp_garde.draw(renderer, game.gardesRect[i].x, game.gardesRect[i].y, game.gardesRect[i].w, game.gardesRect[i].h);
    }
}

void SDLGame::runProject() {
    SDL_Event event;
    SDLAnimation playerAnimation(renderer, "../data/player_red.bmp", game._player);
    Uint32 lastGuardDestinationChangeTime = SDL_GetTicks();
    bool isOpen = true;
    playerAnimation.loadClips();
    while (isOpen) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isOpen = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                if (event.button.button == SDL_BUTTON_LEFT) {
                    //game.updatePlayerDest(event.button.x, event.button.y);
                }
        }
        /*if(playerAnimation.moving_up && camera.y>0)
            camera.y -=5;
        if(playerAnimation.moving_left && camera.x>0)
            camera.x -=5;
        if(playerAnimation.moving_down && camera.y<WINDOW_H)
            camera.y +=5;
        if(playerAnimation.moving_right && camera.x<WINDOW_W)
            camera.x +=5;*/
        //sdlDraw();
        SDL_RenderClear(renderer);
        playerAnimation.handleInput();
        playerAnimation.updatePlayer();
        playerAnimation.DrawAnimation(renderer);
       // playerAnimation.Arrow(renderer);
        //game.movingPlayerByAI();
        game.movingGuardByAI(lastGuardDestinationChangeTime);
        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }
}