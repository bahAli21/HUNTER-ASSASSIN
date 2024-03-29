#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "./sdl2/SDLTtf.h"
#include "./sdl2/SDLSound.h"
#include "core/config.h"
#include "../map/map.h"
#include "core/AStarAlgorithm.h"

/*******************************************ANIMATION*********************************************/

//Mon joueur
struct Player {
    SDL_Texture* tex;
    SDL_Rect source;
    SDL_Rect dest;
    int direction ;

};

enum {
    NORTH = 0,
    WEST = 1,
    EAST = 3,
    SOUTH = 2
};

//Structure Point
/*struct Position {
    int x;
    int y;
};*/

//La structure qui regroupe toutes definition du jeux
struct Contenu {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music *music;
    Mix_Chunk * effect;
    int mouseX, mouseY;
    Player player;
    //Nombre de sprite a utilise 7 car on revien a la position de depart (1,2,3,4,5,6,1)
    Position player_left_clips[7];
    Position player_right_clips[7];
    Position player_up_clips[7];
    Position player_down_clips[7];
    //Normal and Reverse
    //UP
    Position attackUp[7];
    Position attackUpReverse[7];
    //LEFT
    Position attackLeft[7];
    Position attackLeftReverse[7];
    //DOWN
    Position attackDown[7];
    Position attackDownReverse[7];
    //RIGHT
    Position attackRight[7];
    Position attackRightReverse[7];

    //attack Stabbed = poignardé
    //UP
    Position attackUpStabbed[7];
    //LEFT
    Position attackLeftStabbed[7];
    //DOWN
    Position attackDownStabbed[7];
    //RIGHT
    Position attackRightStabbed[7];

    char keyBoard;
    bool moving_left;
    bool moving_right;
    bool moving_up;
    bool moving_down;
} contenu;

//Global
SDLSound sound(44100, MIX_DEFAULT_FORMAT, 2, 248);

void Walk() {
    for (int i = 0; i < 6; ++i) {
        contenu.player_down_clips[i].x = i * PLAYER_WIDTH;
        contenu.player_down_clips[i].y = PLAYER_HEIGHT * 10;
        contenu.player_right_clips[i].y = PLAYER_HEIGHT * 11;
        contenu.player_right_clips[i].x = i * PLAYER_WIDTH;
        contenu.player_left_clips[i].x = i*PLAYER_WIDTH;
        contenu.player_left_clips[i].y = PLAYER_HEIGHT * 9;
        contenu.player_up_clips[i].x = i*PLAYER_WIDTH;
        contenu.player_up_clips[i].y = PLAYER_HEIGHT * 8;
    }
}

void AttackInit(Position tabPos[], int index) {
    for (int i = 0; i < 7; ++i) {
        tabPos[i].x = (1 + 3*i) * (WIDTH_A);
        tabPos[i].y = HEIGHT_A * index;
    }
}

void makeAnimation(int index, Position tabPos[]) {
    contenu.player.source.x = tabPos[index].x;
    contenu.player.source.y = tabPos[index].y;
    contenu.player.source.w  = PLAYER_WIDTH*2;
    contenu.player.dest.w  = PLAYER_WIDTH*2;
}

//Je charge mon image source (pour en faire une animation video
void loadClips() {
    //WALK
    Walk();
    //UP
    //index=22 for normal attack
    AttackInit(contenu.attackUp, 22);
    //index =  34 for reverse attack
    AttackInit(contenu.attackUpReverse, 34);
    //index = 46 for stabbed Attack
    AttackInit(contenu.attackUpStabbed, 46);

    //LEFT
    //index=25 for normal attack
    AttackInit(contenu.attackLeft, 25);
    //index =  37 for reverse attack
    AttackInit(contenu.attackLeftReverse, 37);
    //index = 49 for stabbed Attack
    AttackInit(contenu.attackLeftStabbed, 49);

    //DOWN
    //index=28 for normal attack
    AttackInit(contenu.attackDown, 28);
    //index =  40 for reverse attack
    AttackInit(contenu.attackDownReverse, 40);
    //index = 52 for stabbed Attack
    AttackInit(contenu.attackDownStabbed, 52);

    //RIGHT
    //index=31 for normal attack
    AttackInit(contenu.attackRight, 31);
    //index =  43 for reverse attack
    AttackInit(contenu.attackRightReverse, 43);
    //index = 55 for stabbed Attack
    AttackInit(contenu.attackRightStabbed, 55);

}

//ALL ANIMATION SEQUENCE USE w , x and s
void UP(int idxAtt, char c) {
     if(c == 'w') {
         //Animation Attack up normal
         makeAnimation(idxAtt,contenu.attackUp);
     }
     if(c == 'x') {
         //Animation Attack up reverse
         makeAnimation(idxAtt,contenu.attackUpReverse);
     }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackUpStabbed);
    }
}

void LEFT(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackLeft);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackLeftReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackLeftStabbed);
    }
}

void DOWN(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackDown);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackDownReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackDownStabbed);
    }
}

void RIGHT(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackRight);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackRightReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackRightStabbed);
    }
}

void handleInput() {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    contenu.moving_left = state[SDL_SCANCODE_LEFT] > 0;
    contenu.moving_right = state[SDL_SCANCODE_RIGHT] > 0;
    contenu.moving_up = state[SDL_SCANCODE_UP] > 0;
    contenu.moving_down = state[SDL_SCANCODE_DOWN] > 0;

    if(state[SDL_SCANCODE_Z] > 0)  //W on AZERTY KeyBoard
        contenu.keyBoard = 'w';
    if(state[SDL_SCANCODE_X] > 0)
        contenu.keyBoard = 'x';
    if (state[SDL_SCANCODE_S] > 0)
        contenu.keyBoard = 's';

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_DestroyWindow(contenu.window);
            SDL_Quit();
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            // Vérifier si la touche 's' est enfoncée
            if (event.key.keysym.sym == SDLK_s) {
                // Lecture de l'effet sonore une fois
                sound.PlayChunk(contenu.effect);
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                 contenu.mouseX = event.button.x;
                 contenu.mouseY = event.button.y;
            }else{
                contenu.mouseX = contenu.player.dest.x;
                contenu.mouseY = contenu.player.dest.y;

         }
        }

    }
}

void walkingAnimation(Position tabPos[], float speed, int indexClips, int direction) {
    contenu.player.source.w  = PLAYER_WIDTH;
    contenu.player.dest.w  = PLAYER_WIDTH;
    contenu.player.source.x =  tabPos[indexClips].x;
    contenu.player.source.y =  tabPos[indexClips].y;
    contenu.player.direction = direction;
    contenu.keyBoard ='_';
    if(direction == NORTH)
        contenu.player.dest.y += speed;
    if(direction == EAST)
        contenu.player.dest.x += speed;
    if(direction == WEST)
        contenu.player.dest.x += speed;
    if(direction == SOUTH)
        contenu.player.dest.y += speed;
}

void updatePlayer() {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 6;
    int idxAtt= animation_speed % 6;
    float vitesse=2.4;

    if (contenu.moving_up) {
         walkingAnimation(contenu.player_up_clips, -vitesse, idx, NORTH);
    }
    if (contenu.moving_left) {
         walkingAnimation(contenu.player_left_clips, -vitesse, idx, EAST);
    }
    if (contenu.moving_down) {
        walkingAnimation(contenu.player_down_clips, +vitesse, idx, SOUTH);
    }
    if (contenu.moving_right) {
        walkingAnimation(contenu.player_right_clips, +vitesse, idx, WEST);
    }

    //All Animation
    if(contenu.player.direction == NORTH) {
        UP(idxAtt,contenu.keyBoard);
    }

    if(contenu.player.direction == EAST) {
        LEFT(idxAtt,contenu.keyBoard);
    }

    if(contenu.player.direction == SOUTH) {
        DOWN(idxAtt,contenu.keyBoard);
    }
    if(contenu.player.direction == WEST) {
        RIGHT(idxAtt,contenu.keyBoard);
    }
    contenu.keyBoard = ' '; //don't repeat animation
}

int main(int argc, char* args[]) {
    // Initialisation de la SDL avec le support vidéo et audio
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Création de la fenêtre
    contenu.window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    contenu.renderer = SDL_CreateRenderer(contenu.window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    // Chargement de l'image du joueur
    SDL_Surface* player_img = SDL_LoadBMP("../data/sprite_Player.bmp");
    contenu.player.tex = SDL_CreateTextureFromSurface(contenu.renderer, player_img);
    contenu.player.source = {0, PLAYER_HEIGHT*8, PLAYER_WIDTH, PLAYER_HEIGHT};
    contenu.player.dest = {100, 100, PLAYER_WIDTH , PLAYER_HEIGHT};
    SDL_FreeSurface(player_img);

    // Chargement des clips pour l'animation
    loadClips();

    // Initialisation de la carte du jeu
    Map mapGame;
    mapGame.initAllRectangle();

    // Instance de AStar::Generator
   // AStar::Generator generator;
    //generator.setWorldSize({WINDOW_W, WINDOW_H}); // Taille de la fenêtre
    //SDL_Rect obst1 = {WINDOW_W/2 -20, 60, 20, 140};
    //SDL_Rect obst2 = {WINDOW_W/2 -20, 280, 20, 140};
    //generator.addCollision({obst1.x, obst1.y}, 30, 150);
    //generator.addCollision({obst2.x, obst2.y}, 30, 150);

    // Chargement de la musique
    contenu.music = sound.LoadMusicFromFile("../data/audio/music_test.mp3");
    if (contenu.music == nullptr) {
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Chargement de l'effet sonore
    contenu.effect = sound.LoadChunkFromFile("../data/audio/son.wav");
    if (contenu.effect == nullptr) {
        Mix_FreeMusic(contenu.music);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    // Lecture de la musique en boucle
    sound.PlayMusic(contenu.music);
    SDLTtf affichageTxt;
    TTF_Font * fontScore = affichageTxt.loadFont("../data/font/scoreFont.ttf", 14);
    SDL_Color colorScore = {120,200, 16};
    SDL_Color colorNumber= {0,0, 0};
    SDLTtf affichageNumber;
    affichageTxt.loadFromFont(contenu.renderer, fontScore, "SCORE: ", colorScore);
    int nb = 0;
    //Comme en LIFSE
    char buf[LEN];
    affichageNumber.loadFromFont(contenu.renderer, fontScore, buf, colorNumber);
    // Boucle principale du jeu
    SDL_Event event;
    //AStar::CoordinateList path = {{200, 300}, {220,300},
                                  //{240,300}, {220,280}, {220,260},
                                  //{220,240}}

   // AStar::CoordinateList path ;
    AStar::Vec2i sourceTestPos ;

    while (true) {
        sourceTestPos = {contenu.player.dest.x, contenu.player.dest.y};

        // Trouver un chemin du rectangle (position actuelle) à la position du clic
        //path = generator.findPath(sourceTestPos, {contenu.mouseX, contenu.mouseY});
        //Radix represente la base dans la quelle j'affiche mes chiffres pour moi c'est la base 10
        itoa(nb, buf, 10);
        // Effacement de l'écran
        SDL_SetRenderDrawColor(contenu.renderer, 255,255,255, 255);
        SDL_RenderClear(contenu.renderer);

        // Gestion des entrées
        handleInput();

        // Mise à jour du joueur
        updatePlayer();
        // Déplacer le rectangle le long du chemin trouvé
        /*for (const auto& coordinate : path) {
            // Déplacez votre rectangle à la position (coordinate.x, coordinate.y)
            // Dessinez le rectangle à sa nouvelle position sur le rendu SDL
            SDL_SetRenderDrawColor(contenu.renderer, 0, 255, 0, 255); // Couleur rouge
            SDL_Rect rect = {coordinate.x-2, coordinate.y-2, 2, 2};
            SDL_RenderFillRect(contenu.renderer, &rect);
            //SDL_Delay(100);
        }*/

        //Draw obstacle

        SDL_SetRenderDrawColor(contenu.renderer, 255, 0, 0, 255); // Couleur rouge

        //SDL_RenderFillRect(contenu.renderer, &obst1);
        //SDL_RenderFillRect(contenu.renderer, &obst2);
        // Affichage de la carte et du joueur
        //
        // mapGame.makeMap(contenu.renderer);
        affichageNumber.loadFromFont(contenu.renderer, fontScore, buf, colorNumber);
        nb++;
        SDL_RenderCopy(contenu.renderer, contenu.player.tex, &contenu.player.source, &contenu.player.dest);
        affichageTxt.Draw(contenu.renderer, {5,5});
        //au debut il sont superposer il faut mettre nbCaractere du premier donc 'SCORE' * size de la police
        affichageNumber.Draw(contenu.renderer, {4*15, 5});
        // Affichage à l'écran
        SDL_RenderPresent(contenu.renderer);
    }

    // Libération de la mémoire et fermeture de la SDL
    Mix_FreeMusic(contenu.music);
    Mix_FreeChunk(contenu.effect);
    Mix_CloseAudio();
    SDL_DestroyWindow(contenu.window);
    SDL_DestroyRenderer(contenu.renderer);
    SDL_Quit();

    return 0;
}

