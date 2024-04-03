#include "Game.h"

// Constructeur de la classe Game avec par defaut le mode 1(Ajout des murs)
GameAstar::GameAstar(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) :
placementModeCurrent(PlacementMode::wall), g(6),
level(renderer, windowWidth, windowHeight) {

    // Initialisation du jeu
    if (window != nullptr && renderer != nullptr) {
        // Chargement de la texture d'overlay
        textureOverlay = TextureLoader::loadTexture(renderer, "Overlay.bmp");
        if(textureOverlay == nullptr) {
            // Affichage d'une erreur si le chargement de la texture échoue
            SDL_Log("Erreur lors du chargement de la texture : %s", SDL_GetError());
        }

        // Stockage du temps actuel pour le temps écoulé
        auto time1 = std::chrono::system_clock::now();
        //auto time2 = std::chrono::system_clock::now();

        // Temps pour chaque frame (80 fps)
        const float dT = 1.0f / 100.0f;

        //debut
        // Afficher les informations de la liste sur la console


        //fin
        // Je Cree une instance de SDLAnimation pour chaque Joueur
        SDLAnimation playerAnimation(renderer, g.listeOfPlayers[0]);

        // Déclarons un tableau pour stocker les animations des gardes
        SDLAnimation gardeAnimations[6] = {
                SDLAnimation(renderer, g.listeOfGardes[0]),
                SDLAnimation(renderer, g.listeOfGardes[1]),
                SDLAnimation(renderer, g.listeOfGardes[2]),
                SDLAnimation(renderer, g.listeOfGardes[3]),
                SDLAnimation(renderer, g.listeOfGardes[4]),
                SDLAnimation(renderer, g.listeOfGardes[5])
        };


        Vector2D playerPosTuile((float)g._player.playerDest->x/tileSize, (float)g._player.playerDest->y/tileSize );
        addUnit(renderer, playerPosTuile);
        // Boucle principale du jeu
        bool running = true;
        while (running) {
            // Calcul du temps écoulé depuis la dernière frame
            auto time2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();

            // Si suffisamment de temps s'est écoulé, je génère la prochaine frame
            if (timeDeltaFloat >= dT) {
                // Mise à jour du temps pour la prochaine frame
                time1 = time2;
                // Traitement des événements, mise à jour et dessin du jeu
                processEvents(renderer, running);
                SDL_RenderClear(renderer);
                draw(renderer);


                //updateGardes(dT);
                playerAnimation.handleInput();
                playerAnimation.updateCharacter(g.listeOfPlayers[0].direction);
                //playerAnimation.DrawAnimation(renderer);
                updatePlayer(dT, playerAnimation);

                /*for (int i = 0; i < g.nbGardes; ++i) {
                    gardeAnimations[i].handleInput(); // Gére les entrées pour les animations des gardes si nécessaire
                    gardeAnimations[i].updateCharacter(g.listeOfGardes[i].direction); // Mettre à jour l'animation du garde
                    gardeAnimations[i].DrawAnimation(renderer); // Dessine l'animation du garde
                }*/
                SDL_Delay(5);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

// Destructeur de la classe Game
GameAstar::~GameAstar() {
    // Nettoyage des ressources
    TextureLoader::deallocateTextures(); // Libère toutes les textures
}

// Traitement des événements du jeu
void GameAstar::processEvents(SDL_Renderer* renderer, bool& running) {
    // Variables pour le suivi du clic de souris
    bool mouseDownThisFrame = false;

    // Traitement des événements SDL
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // Arrête le jeu si l'utilisateur ferme la fenêtre
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Gére les clics de souris
                mouseDownThisFrame = (mouseDownStatus == 0);
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseDownStatus = SDL_BUTTON_LEFT;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseDownStatus = SDL_BUTTON_RIGHT;
                break;
            case SDL_MOUSEBUTTONUP:
                // Réinitialisons le statut du clic de souris
                mouseDownStatus = 0;
                break;
            case SDL_KEYDOWN:
                // Gére les pressions de touche
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        // Quitte le jeu en appuyant sur la touche Echap
                        running = false;
                        break;
                    case SDL_SCANCODE_1:
                        // Change le mode de placement en mur
                        placementModeCurrent = PlacementMode::wall;
                        break;
                    case SDL_SCANCODE_2:
                        // Change le mode de placement en unités
                        placementModeCurrent = PlacementMode::units;
                        break;
                    case SDL_SCANCODE_H:
                        // Affiche/masque l'overlay en appuyant sur la touche H
                        overlayVisible = !overlayVisible;
                        break;
                }
        }
    }

    // Obtenir la position de la souris
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    //for (auto unitSelected: listUnits) {
      /* if((int)listUnits[0].pos.x== (int)level.getTargetPos().x && (int)listUnits[0].pos.y== (int)level.getTargetPos().y){
                g.listeOfPlayers[0].targetPos = new Position{rand()%((WINDOW_W-WIDTH_A)- WIDTH_A +1) + WIDTH_A,
                                                rand()%((WINDOW_H-HEIGHT_A)- HEIGHT_A +1) + HEIGHT_A};
        }*/
   /* if((int)g.listeOfPlayers[0].dest->x == (int)level.getTargetPos().x * tileSize && (int)g.listeOfPlayers[0].dest->y== (int)level.getTargetPos().y *tileSize){
        g.listeOfPlayers[0].targetPos = new Position{rand()%((WINDOW_W-WIDTH_A)- WIDTH_A +1) + WIDTH_A,
                                                     rand()%((WINDOW_H-HEIGHT_A)- HEIGHT_A +1) + HEIGHT_A};
    }*/
    //}



    //Player Move pos
    //Demain il faut faire bouger les garde independament
    Vector2D posMouse((float)g.listeOfPlayers[0].targetPos->x / tileSize,
                      (float)g.listeOfPlayers[0].targetPos->y / tileSize);
    level.setTargetAndCalculateFlowField((int)mouseX/ tileSize, (int)mouseY/ tileSize);

    // Gére l'action du clic de souris
    if (mouseDownStatus > 0) {
        switch (mouseDownStatus) {
            case SDL_BUTTON_LEFT:
                // Gére le clic gauche de la souris
                switch (placementModeCurrent) {
                    case PlacementMode::wall:
                        // Ajoute un mur à la position de la souris
                        level.setTileWall((int)posMouse.x, (int)posMouse.y, true);
                        break;
                    case PlacementMode::units:
                        // Ajoute une unité à la position de la souris
                        if (mouseDownThisFrame) //Si cette ligne est commenter on aura plusieur Enemy d'un coup
                            addUnit(renderer, posMouse);
                        break;
                }
                break;
            case SDL_BUTTON_RIGHT:
                // Gére le clic droit de la souris
                // Supprime un mur ou une unité à la position de la souris
                level.setTileWall((int)posMouse.x, (int)posMouse.y, false);
                removeUnitsAtMousePosition(posMouse);
                break;
        }
    }
}

// Mettre à jour l'état du jeu
void GameAstar::updatePlayer(float dT, SDLAnimation playerAnimation) {
    // Mettre à jour les unités
    for (auto & unitSelected : listUnits)
         unitSelected.update(dT, level, listUnits, g.listeOfPlayers[0]);
    //playerAnimation.updateTest(dT, level);
}

// Mettre à jour l'état du jeu
void GameAstar::updateGardes(float dT) {
    for (auto & unitSelected : listUnits) {
        for (int i = 0; i < g.nbGardes; ++i) {
            unitSelected.update(dT, level, listUnits, g.listeOfGardes[i]);
        }
    }


}

// Dessine le contenu du jeu
void GameAstar::draw(SDL_Renderer* renderer) {
    // Efface l'écran
    SDL_SetRenderDrawColor(renderer, 57, 51, 82, 0.37);

    //SDLAnimation playerAnimation(renderer, "../data/sprite_Player.bmp", _player);
    //playerAnimation.loadClips();
    // Dessine le niveau
    level.draw(renderer, tileSize);

    // Dessine les unités
    for (auto& unitSelected : listUnits)
        unitSelected.draw(renderer, tileSize, g.listeOfPlayers[0]);

    // Dessine l'overlay si visible
    if (textureOverlay != nullptr && overlayVisible) {
        int w = 0, h = 0;
        SDL_QueryTexture(textureOverlay, NULL, NULL, &w, &h);
        SDL_Rect rect = { 40, 40, w, h };
        SDL_RenderCopy(renderer, textureOverlay, NULL, &rect);
    }


}

// Ajoute une unités/Enemy à la position donnée
void GameAstar::addUnit(SDL_Renderer* renderer, Vector2D posMouse) {
    listUnits.push_back(Unit(renderer, posMouse));
}

// Supprime les unités/Enemy à la position de la souris
void GameAstar::removeUnitsAtMousePosition(Vector2D posMouse) {
    for (int i = 0; i < listUnits.size(); i++) {
        auto& unitSelected = listUnits[i];
        if (unitSelected.checkOverlap(posMouse, 0.0f)) {
            listUnits.erase(listUnits.begin() + i);
            i--;
        }
    }
}


