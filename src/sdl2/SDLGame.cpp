#include "SDLGame.h"

SDLGame::SDLGame() : game(4), sound(44100, MIX_DEFAULT_FORMAT, 2, 248){

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

    camera = {0,0};
}

SDLGame::~SDLGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLGame::runProject() {
    SDL_Event event;
    Level level1(renderer);
    SDLAnimation playerAnimation(renderer, game.listeOfPlayers[0]);
    // Déclarons un tableau pour stocker les animations des gardes
    SDLAnimation gardeAnimations[4] = {
            SDLAnimation(renderer, game.listeOfGardes[0]),
            SDLAnimation(renderer, game.listeOfGardes[1]),
            SDLAnimation(renderer, game.listeOfGardes[2]),
            SDLAnimation(renderer, game.listeOfGardes[3]),
    };

    Uint32 lastGuardDestinationChangeTime = SDL_GetTicks();
    bool isOpen = true;
    SDLTtf myTtfKilled, myTtfSlash, myTtfNbGarde, myTtfWelcom;
    TTF_Font * font = SDLTtf::loadFont("../data/font/scoreFont.ttf", 24);
    myTtfKilled.loadFromFont(renderer, font, "0", {255,255, 255});
    myTtfSlash.loadFromFont(renderer, font, "/", {255,255, 255});
    myTtfNbGarde.loadFromFont(renderer, font, "4", {255, 255, 255});
    myTtfWelcom.loadFromFont(renderer, font, "BIENVENUE </> H-A", {193, 55, 25});
    gameMusic = SDLSound::LoadMusicFromFile("../data/audio/musicGame.mp3");
    SDLSound::PlayMusic(gameMusic);
    while (isOpen) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isOpen = false;
        }

        /*if(playerAnimation.moving_up && camera.y>0)
            camera.y -=5;
        if(playerAnimation.moving_left && camera.x>0)
            camera.x -=5;
        if(playerAnimation.moving_down && camera.y<WINDOW_H)
            camera.y +=5;
        if(playerAnimation.moving_right && camera.x<WINDOW_W)
            camera.x +=5;*/

        SDL_RenderClear(renderer);
        myTtfKilled.Draw(renderer, {60, WINDOW_H-70});
        myTtfSlash.Draw(renderer, {80, WINDOW_H-70});
        myTtfNbGarde.Draw(renderer, {90, WINDOW_H-70});
        myTtfWelcom.Draw(renderer, {120, WINDOW_H-70});
        myTtfWelcom.AnimationText();
        level1.draw(renderer);
        playerAnimation.handleInput();
        playerAnimation.DrawAnimation(renderer);
        playerAnimation.updateCharacter(0, level1); //index 0 pour un joueur

        for (int i = 0; i < game.nbGardes; ++i) {
            gardeAnimations[i].handleInput(); // Gére les entrées pour les animations des gardes si nécessaire
            gardeAnimations[i].updateCharacter(1, level1); // Mettre à jour l'animation du garde
            gardeAnimations[i].DrawAnimation(renderer); // Dessine l'animation du garde
        }

        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }
}