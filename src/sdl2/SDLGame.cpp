#include "SDLGame.h"

SDLGame::SDLGame() : game(1){

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
    SDLAnimation playerAnimation(renderer, game.listeOfPlayers[0]);
    // Déclarons un tableau pour stocker les animations des gardes
    SDLAnimation gardeAnimations[1] = {
            SDLAnimation(renderer, game.listeOfGardes[0]),
    };

    Uint32 lastGuardDestinationChangeTime = SDL_GetTicks();
    bool isOpen = true;
    game._player.loadClips();
    while (isOpen) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isOpen = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                if (event.button.button == SDL_BUTTON_LEFT) {
                    game.updatePlayerDest(event.button.x, event.button.y);
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
        playerAnimation.DrawAnimation(renderer);
        playerAnimation.updateCharacter();
        //game.movingPlayerByAI();
        //game.movingGuardByAI(lastGuardDestinationChangeTime);

        for (int i = 0; i < game.nbGardes; ++i) {
            gardeAnimations[i].handleInput(); // Gére les entrées pour les animations des gardes si nécessaire
            gardeAnimations[i].updateCharacter(); // Mettre à jour l'animation du garde
            gardeAnimations[i].DrawAnimation(renderer); // Dessine l'animation du garde

        }

        for (int i = 0; i < 6; ++i) {
            SDL_Log("noeud %d = {%d, %d} ", i, game.listeOfGardes[0].tabNoeud[i].x,
                    game.listeOfGardes[0].tabNoeud[i].y);
        }

        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }
}