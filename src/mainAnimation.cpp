#include <iostream>
#include <SDL.h>
#include "core/config.h"
#include "../map/map.h"
//Mon joueur
struct Player {
    SDL_Texture* tex;
    SDL_Rect source;
    SDL_Rect dest;
    int direction ;

};

//Structure Point
struct Position {
    int x;
    int y;
};

//La structure qui regroupe toutes definition du jeux
struct Contenu {
    SDL_Window* window;
    SDL_Renderer* renderer;
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
    bool attack;
} contenu;

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
        tabPos[i].x = (1 + 3*i) * WIDTH_A;
        tabPos[i].y = HEIGHT_A * index;
    }
}

void makeAnimation(int index, Position tabPos[], int posLargeSprite[]) {
    contenu.player.source.x = tabPos[index].x;
    contenu.player.source.y = tabPos[index].y;
    if( index == posLargeSprite[0] || index == posLargeSprite[1]) {
        contenu.player.source.w  = PLAYER_WIDTH*2;
        contenu.player.dest.w  = PLAYER_WIDTH*2;
    } else {
        contenu.player.source.w  = PLAYER_WIDTH;
        contenu.player.dest.w  = PLAYER_WIDTH;

    }
}

void AttackUpReverse() {
    for (int i = 0; i < 7; ++i) {
        contenu.attackUpReverse[i].x = (1 + 3*i) * WIDTH_A;
        contenu.attackUpReverse[i].y = HEIGHT_A * 34;
    }
}

void AttackUp() {
    //up first Animation
    for (int i = 0; i < 7; ++i) {
            contenu.attackUp[i].x = (1 + 3*i) * WIDTH_A;
            contenu.attackUp[i].y = HEIGHT_A * 22;
    }
}

//Je charge mon image source (pour en faire une animation video
void loadClips() {
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
void UP(int idxAtt, int tab1[], int tab2[], int tab3[], char c) {
     if(c == 'w') {
         //Animation Attack up normal
         makeAnimation(idxAtt,contenu.attackUp, tab1);
     }
     if(c == 'x') {
         //Animation Attack up reverse
         makeAnimation(idxAtt,contenu.attackUpReverse, tab2);
     }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackUpStabbed, tab3);
    }
}

void LEFT(int idxAtt, int tab1[], int tab2[], int tab3[], char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackLeft, tab1);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackLeftReverse, tab2);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackLeftStabbed, tab3);
    }
}

void DOWN(int idxAtt, int tab1[], int tab2[], int tab3[], char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackDown, tab1);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackDownReverse, tab2);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackDownStabbed, tab3);
    }
}

void RIGHT(int idxAtt, int tab1[], int tab2[], int tab3[], char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,contenu.attackRight, tab1);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,contenu.attackRightReverse, tab2);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,contenu.attackRightStabbed, tab3);
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
        }
    }
}

void animationUp(int idxAtt) {
    contenu.player.source.x = contenu.attackUp[idxAtt].x;
    contenu.player.source.y = contenu.attackUp[idxAtt].y;
    if( idxAtt == 5 || idxAtt == 6) {
        contenu.player.source.w  = PLAYER_WIDTH*2;
        contenu.player.dest.w  = PLAYER_WIDTH*2;
    } else {
        contenu.player.source.w  = PLAYER_WIDTH;
        contenu.player.dest.w  = PLAYER_WIDTH;

    }
}

void animationUpReverse(int idxAtt) {
    contenu.player.source.x = contenu.attackUpReverse[idxAtt].x;
    contenu.player.source.y = contenu.attackUpReverse[idxAtt].y;
    if( idxAtt == 0 || idxAtt == 1) {
        contenu.player.source.w  = PLAYER_WIDTH*2;
        contenu.player.dest.w  = PLAYER_WIDTH*2;
    } else {
        contenu.player.source.w  = PLAYER_WIDTH;
        contenu.player.dest.w  = PLAYER_WIDTH;
    }
}

void updatePlayer() {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 6;
    int idxAtt= animation_speed % 6;
    float vitesse=2.4;

    if ( contenu.moving_up) {
         contenu.player.source.x =  contenu.player_up_clips[idx].x;
         contenu.player.source.y =  contenu.player_up_clips[idx].y;
         contenu.player.dest.y -= vitesse;
         contenu.player.direction = 0;
    }
    if ( contenu.moving_left) {

         contenu.player.source.x =  contenu.player_left_clips[idx].x;
         contenu.player.source.y =  contenu.player_left_clips[idx].y;
         contenu.player.dest.x -= vitesse;
        contenu.player.direction = 3;

    }
    if ( contenu.moving_down) {
        contenu.player.source.x = contenu.player_down_clips[idx].x;
        contenu.player.source.y = contenu.player_down_clips[idx].y;
        contenu.player.dest.y += vitesse;
        contenu.player.direction= 2;

    }
    if ( contenu.moving_right) {
        contenu.player.source.x = contenu.player_right_clips[idx].x;
        contenu.player.source.y = contenu.player_right_clips[idx].y;
        contenu.player.dest.x += vitesse;
        contenu.player.direction = 1;
    }

    if(contenu.player.direction == 0 && contenu.attack) {
        //animationUpReverse(idxAtt);
        //animationUp(idxAtt);
        int tab1[] = {5,6};
        int tab2[] = {0,1};
        int tab3[] = {1, 2};
        UP(idxAtt,tab1, tab2, tab3, contenu.keyBoard);

    }



}


int main(int argc, char* args[]) {
     SDL_Init(SDL_INIT_VIDEO);

     contenu.window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
     contenu.renderer = SDL_CreateRenderer( contenu.window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

     SDL_Surface* player_img = SDL_LoadBMP("../data/sprite_Player.bmp");

     contenu.player.tex = SDL_CreateTextureFromSurface( contenu.renderer, player_img);
     contenu.player.source = {0, PLAYER_HEIGHT*8, PLAYER_WIDTH, PLAYER_HEIGHT};
     contenu.player.dest = {100, 100, PLAYER_WIDTH , PLAYER_HEIGHT};
     SDL_FreeSurface(player_img);

    loadClips();
    Map mapGame;
    mapGame.initAllRectangle();

    while (true) {
        SDL_SetRenderDrawColor(contenu.renderer, 255,255,255, 255);
        SDL_RenderClear(contenu.renderer);
        handleInput();
        updatePlayer();
        SDL_RenderClear(contenu.renderer);
        //mapGame.makeMap(contenu.renderer);
        SDL_RenderCopy( contenu.renderer,  contenu.player.tex, & contenu.player.source, & contenu.player.dest);
        SDL_RenderPresent( contenu.renderer);
    }

    SDL_DestroyWindow( contenu.window);
    SDL_DestroyRenderer( contenu.renderer);
    SDL_Quit();


    return 0;
}
