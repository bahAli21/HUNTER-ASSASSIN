#include "SDLGame.h"

SDLGame::SDLGame() : game(4), sound(44100, MIX_DEFAULT_FORMAT, 2, 248), menu(){

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

    //Par Defaut la Camera est au centre du monde
    camera = {0,0};
}

SDLGame::~SDLGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// fonction qui verifie la collision de deux rectangle
bool checkCollision(Rect rectA,Rect & rectB) {

    int leftA = rectA.x;
    int rightA = rectA.x + rectA.w;
    int topA = rectA.y;
    int bottomA = rectA.y + rectA.h;

    int leftB = rectB.x;
    int rightB = rectB.x + rectB.w;
    int topB = rectB.y;
    int bottomB = rectB.y + rectB.h;

    // Check for no collision
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }
    // Collision detected
    return true;
}

void shoot(int direction) {

}
void SDLGame::runGame() {
    SDL_Event e;
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
    SDLTtf myTtfKilled, myTtfSlash, myTtfNbGarde, myTtfWelcom, myTtfGameOver;
    TTF_Font * font = SDLTtf::loadFont("../data/font/scoreFont.ttf", 24);
    myTtfKilled.loadFromFont(renderer, font, "0", {255,255, 255});
    myTtfSlash.loadFromFont(renderer, font, "/", {255,255, 255});
    myTtfNbGarde.loadFromFont(renderer, font, "4", {255, 255, 255});
    myTtfWelcom.loadFromFont(renderer, font, "< / >", {193, 55, 25});
    myTtfGameOver.loadFromFont(renderer, font, "GAME-OVER", {193, 55, 25});
    gameMusic = SDLSound::LoadMusicFromFile("../data/audio/musicGame.mp3");
    SDLSound::PlayMusic(gameMusic);
    Position mouseMotion, mouseClicked;
    menu.initRectangles();
    while (isOpen) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                isOpen = false;
                SDL_Quit();
            }
                // Mouse event
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int x = e.button.x;
                    int y = e.button.y;
                    mouseClicked = {x, y};
                    std::cout << "Left mouse button clicked at: (" << x << ", " << y << ")" << std::endl;
                }
            }
            else if (e.type == SDL_MOUSEMOTION) {
                int x = e.motion.x;
                int y = e.motion.y;
                mouseMotion = {x, y};
                std::cout << "Mouse moved at: (" << x << ", " << y << ")" << std::endl;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);
        switch (menu.detecteClic(mouseClicked)) {
            case -1:
                menu.makeMenu(renderer, mouseMotion);
                break;
            case 220: //Start indice
                if(playerAnimation.character.health >0){
                    myTtfKilled.Draw(renderer, {60, WINDOW_H-70});
                    myTtfSlash.Draw(renderer, {80, WINDOW_H-70});
                    myTtfNbGarde.Draw(renderer, {90, WINDOW_H-70});
                    myTtfWelcom.Draw(renderer, {120, WINDOW_H-70});
                    myTtfWelcom.AnimationText();
                    level1.draw(renderer);
                    playerAnimation.handleInput();
                    playerAnimation.DrawAnimation(renderer);
                    playerAnimation.updateCharacter(-1, level1); //index -1 pour un joueur
                    for (int i = 0; i < game.nbGardes; ++i) {
                        gardeAnimations[i].handleInput(); // Gére les entrées pour les animations des gardes si nécessaire
                        gardeAnimations[i].updateCharacter(i, level1); // Mettre à jour l'animation du garde
                        gardeAnimations[i].DrawAnimation(renderer); // Dessine l'animation du garde
                        for(auto arrow : playerAnimation.character.listArrow){
                            SDL_Rect tmp = {
                                    arrow.arrowPos.x,
                                    arrow.arrowPos.y,
                                    50,
                                    5
                            };
                            gardeAnimations[i].makeSmallRectCollision(); //Ce rectangle(smallRect) permet de savoir si un garde est toucher

                            //C'etait pour debugger
                            //SDL_SetRenderDrawColor(renderer, 0,255,0,255);
                            //SDL_RenderDrawRect(renderer, &gardeAnimations[i].character.smallRect);
                            if(playerAnimation.checkCollision(tmp, gardeAnimations[i].character.smallRect)){
                                gardeAnimations[i].character.isDead = true; //Le garde est eliminé
                            }
                        }
                        SDL_Rect ChampDeTir[4][4];

                        //UP
                        ChampDeTir[i][0] = {
                                gardeAnimations[i].character.dest->x,
                                gardeAnimations[i].character.dest->y - 80,
                                gardeAnimations[i].character.dest->w,
                                80
                        };

                        //RIGHT
                        ChampDeTir[i][1] = {
                                gardeAnimations[i].character.dest->x+gardeAnimations[i].character.dest->w,
                                gardeAnimations[i].character.dest->y,
                                80,
                                gardeAnimations[i].character.dest->h
                        };

                        //LEFT
                        ChampDeTir[i][2] = {
                                gardeAnimations[i].character.dest->x-80,
                                gardeAnimations[i].character.dest->y,
                                80,
                                gardeAnimations[i].character.dest->h
                        };

                        //DOWN
                        ChampDeTir[i][3] = {
                                gardeAnimations[i].character.dest->x,
                                gardeAnimations[i].character.dest->y + gardeAnimations[i].character.dest->h,
                                gardeAnimations[i].character.dest->w,
                                80
                        };

                        //Dessinons pour debugger
                        //SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                        //UP
                        if(gardeAnimations[i].character.direction == 0) {
                            Rect coordTir = {ChampDeTir[i][0].x, ChampDeTir[i][0].y, ChampDeTir[i][0].w, ChampDeTir[i][0].h};
                            Rect playerPos = {playerAnimation.character.dest->x,
                                              playerAnimation.character.dest->y,
                                              playerAnimation.character.dest->w,
                                              playerAnimation.character.dest->h
                            };

                            if(checkCollision(coordTir, playerPos)){
                                gardeAnimations[i].character.shootKey = 's';
                            } else
                                gardeAnimations[i].character.shootKey = ' ';


                        }
                        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                        SDL_RenderDrawRect(renderer, &ChampDeTir[1][0]);

                        //RIGHT
                        if(gardeAnimations[i].character.direction == 1) {
                            Rect coordTir = {ChampDeTir[i][1].x, ChampDeTir[i][1].y, ChampDeTir[i][1].w, ChampDeTir[i][1].h};
                            Rect playerPos = {playerAnimation.character.dest->x,
                                              playerAnimation.character.dest->y,
                                              playerAnimation.character.dest->w,
                                              playerAnimation.character.dest->h
                            };

                            if(checkCollision(coordTir, playerPos)){
                                gardeAnimations[i].character.shootKey = 's';
                            } else
                                gardeAnimations[i].character.shootKey = ' ';


                        }
                        //Right
                        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                        SDL_RenderDrawRect(renderer, &ChampDeTir[1][1]);

                        //LEFT
                        if(gardeAnimations[i].character.direction == 3) {
                            Rect coordTir = {ChampDeTir[i][2].x, ChampDeTir[i][2].y, ChampDeTir[i][2].w, ChampDeTir[i][2].h};
                            Rect playerPos = {playerAnimation.character.dest->x,
                                              playerAnimation.character.dest->y,
                                              playerAnimation.character.dest->w,
                                              playerAnimation.character.dest->h
                            };

                            if(checkCollision(coordTir, playerPos)){
                                gardeAnimations[i].character.shootKey = 's';
                            } else
                                gardeAnimations[i].character.shootKey = ' ';


                        }
                        //Right

                        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                        SDL_RenderDrawRect(renderer, &ChampDeTir[1][2]);

                        //DOWN
                        if(gardeAnimations[i].character.direction == 2) {
                            Rect coordTir = {ChampDeTir[i][3].x, ChampDeTir[i][3].y, ChampDeTir[i][3].w, ChampDeTir[i][3].h};
                            Rect playerPos = {playerAnimation.character.dest->x,
                                              playerAnimation.character.dest->y,
                                              playerAnimation.character.dest->w,
                                              playerAnimation.character.dest->h
                            };

                            if(checkCollision(coordTir, playerPos)){
                                gardeAnimations[i].character.shootKey = 's';
                            } else
                                gardeAnimations[i].character.shootKey = ' ';


                        }
                        //Right
                        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                        SDL_RenderDrawRect(renderer, &ChampDeTir[1][3]);

                        //GAME-OVERRRRRRRRRRRRRRRR
                        for(auto arrow : gardeAnimations[i].character.listArrow){
                            Rect tmp = {
                                    arrow.arrowPos.x,
                                    arrow.arrowPos.y,
                                    50,
                                    5
                            };

                            Rect playerPos = {playerAnimation.character.dest->x,
                                              playerAnimation.character.dest->y,
                                              playerAnimation.character.dest->w,
                                              playerAnimation.character.dest->h
                            };

                            playerAnimation.makeSmallRectCollision(); //Ce rectangle(smallRect) permet de savoir si un garde est toucher

                            //C'etait pour debugger
                            //SDL_SetRenderDrawColor(renderer, 0,255,0,255);
                            //SDL_RenderDrawRect(renderer, &gardeAnimations[i].character.smallRect);
                            if(checkCollision(tmp, playerPos)){
                                playerAnimation.character.health -=100;
                            }
                        }

                        if(playerAnimation.character.health <= 0){
                            playerAnimation.character.isDead = true; //Le garde est eliminé
                        }
                    }

                    SDL_Delay(25);
                } else{
                    myTtfGameOver.Draw(renderer, {WINDOW_W/2 - 70, WINDOW_H/2 - 40});
                    
                }


                break;
            case 420:
                //isOpen = false;
                SDL_Quit();
                break;
        }
        SDL_RenderPresent(renderer);
    }
}