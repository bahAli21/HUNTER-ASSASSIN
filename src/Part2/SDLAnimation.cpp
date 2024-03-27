#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, const char * path, const Player& _player): player(_player) {
    allAnimation.loadSpriteFile(path, renderer);
}

SDLAnimation::~SDLAnimation() = default;

void SDLAnimation::Walk() {
    for (int i = 0; i < 6; ++i) {
        player_down_clips[i].x = i * PLAYER_WIDTH;
        player_down_clips[i].y = PLAYER_HEIGHT * 10;
        player_right_clips[i].y = PLAYER_HEIGHT * 11;
        player_right_clips[i].x = i * PLAYER_WIDTH;
        player_left_clips[i].x = i*PLAYER_WIDTH;
        player_left_clips[i].y = PLAYER_HEIGHT * 9;
        player_up_clips[i].x = i*PLAYER_WIDTH;
        player_up_clips[i].y = PLAYER_HEIGHT * 8;
    }
}

void SDLAnimation::AttackInit(Position tabPos[], int index) {
    for (int i = 0; i < 7; ++i) {
        tabPos[i].x = (1 + 3*i) * (WIDTH_A);
        tabPos[i].y = HEIGHT_A * index;
    }
}

void SDLAnimation::makeAnimation(int index, Position tabPos[]) const {
    player.playerSource->x = tabPos[index].x;
    player.playerSource->y = tabPos[index].y;
    player.playerSource->w  = PLAYER_WIDTH*2;
    player.playerDest->w  = PLAYER_WIDTH*2;
}

//Je charge mon image source (pour en faire une animation video
void SDLAnimation::loadClips() {
    //WALK
    Walk();
    //UP
    //index=22 for normal attack
    AttackInit(attackUp, 22);
    //index =  34 for reverse attack
    AttackInit(attackUpReverse, 34);
    //index = 46 for stabbed Attack
    AttackInit(attackUpStabbed, 46);

    //LEFT
    //index=25 for normal attack
    AttackInit(attackLeft, 25);
    //index =  37 for reverse attack
    AttackInit(attackLeftReverse, 37);
    //index = 49 for stabbed Attack
    AttackInit(attackLeftStabbed, 49);

    //DOWN
    //index=28 for normal attack
    AttackInit(attackDown, 28);
    //index =  40 for reverse attack
    AttackInit(attackDownReverse, 40);
    //index = 52 for stabbed Attack
    AttackInit(attackDownStabbed, 52);

    //RIGHT
    //index=31 for normal attack
    AttackInit(attackRight, 31);
    //index =  43 for reverse attack
    AttackInit(attackRightReverse, 43);
    //index = 55 for stabbed Attack
    AttackInit(attackRightStabbed, 55);
}

//ALL ANIMATION SEQUENCE USE w , x and s
void SDLAnimation::UP(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackUp);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,attackUpReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,attackUpStabbed);
    }
}

void SDLAnimation::LEFT(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackLeft);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,attackLeftReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,attackLeftStabbed);
    }
}

void SDLAnimation::DOWN(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackDown);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,attackDownReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,attackDownStabbed);
    }
}

void SDLAnimation::RIGHT(int idxAtt, char c) {
    if(c == 'w') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackRight);
    }
    if(c == 'x') {
        //Animation Attack up reverse
        makeAnimation(idxAtt,attackRightReverse);
    }
    if (c == 's') {
        //Animation Attack up stabbed
        makeAnimation(idxAtt,attackRightStabbed);
    }
}

void SDLAnimation::handleInput() {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    moving_left = state[SDL_SCANCODE_LEFT] > 0;
    moving_right = state[SDL_SCANCODE_RIGHT] > 0;
    moving_up = state[SDL_SCANCODE_UP] > 0;
    moving_down = state[SDL_SCANCODE_DOWN] > 0;

    if(state[SDL_SCANCODE_Z] > 0)  //W on AZERTY KeyBoard
        keyBoard = 'w';
    if(state[SDL_SCANCODE_X] > 0)
        keyBoard = 'x';
    if (state[SDL_SCANCODE_S] > 0)
        keyBoard = 's';

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
    }
}

void SDLAnimation::walkingAnimation(Position tabPos[], int speed, int indexClips, int direction) {
    player.playerSource->w  = PLAYER_WIDTH;
    player.playerDest->w  = PLAYER_WIDTH;
    player.playerSource->x =  tabPos[indexClips].x;
    player.playerSource->y =  tabPos[indexClips].y;
    player.direction = direction;
    keyBoard ='_';
    if(direction == NORTH)
        player.dest->y += speed;
    if(direction == EAST)
        player.dest->x += speed;
    if(direction == WEST)
        player.dest->x += speed;
    if(direction == SOUTH)
        player.dest->y += speed;
}

void SDLAnimation::updatePlayer(int x , int y) {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 6;
    int idxAtt= animation_speed % 6;
    int vitesse=2;

    if (x==0 && y==-1) {
        walkingAnimation(player_up_clips, -vitesse, idx, NORTH);
    }
    if (x==-1 && y==0) {
        walkingAnimation(player_left_clips, -vitesse, idx, EAST);
    }
    if (x==0 && y==1) {
        walkingAnimation(player_down_clips, +vitesse, idx, SOUTH);
    }
    if (x==1 && y==0) {
        walkingAnimation(player_right_clips, +vitesse, idx, WEST);
    }

    //All Animation
    if(player.direction == NORTH) {
        UP(idxAtt,keyBoard);
    }

    if(player.direction == EAST) {
        LEFT(idxAtt,keyBoard);
    }

    if(player.direction == SOUTH) {
        DOWN(idxAtt,keyBoard);
    }
    if(player.direction == WEST) {
        RIGHT(idxAtt,keyBoard);
    }
    keyBoard = ' '; //don't repeat animation
}

void SDLAnimation::DrawAnimation(SDL_Renderer * renderer) const {
    SDL_RenderCopy(renderer,
                   allAnimation._texture,
                   reinterpret_cast<const SDL_Rect *>(player.playerSource),
                   reinterpret_cast<const SDL_Rect *>(player.playerDest));
}

