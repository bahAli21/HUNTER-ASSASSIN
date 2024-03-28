#include "SDLAnimation.h"

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, const char * path, const Player& _player): player(_player),
sound(44100, MIX_DEFAULT_FORMAT, 2, 248){
    allAnimation.loadSpriteFile(path, renderer);
    fireArrow.loadSpriteFile("../data/imgAnimation/fire-arrow.bmp", renderer);
    shootEffect = SDLSound::LoadChunkFromFile("../data/audio/shootEffect.wav");
    ptrStop = new int;
    *ptrStop = 0;
}

SDLAnimation::~SDLAnimation() = default;

void SDLAnimation::Walk(Position tabPos[], int index) {
    for (int i = 0; i < 8; ++i) {
        tabPos[i].x = (i*2) * (WIDTH_A);
        tabPos[i].y = HEIGHT_A * index;
    }
}

void SDLAnimation::AttackInit(Position tabPos[], int index) {
    for (int i = 0; i <=12; ++i) {
        tabPos[i].x = (i)*(WIDTH_A);
        tabPos[i].y = (HEIGHT_A) * index;
    }
}

void SDLAnimation::makeAnimation(int index, Position tabPos[]) const {
    player.playerSource->x = tabPos[index].x;
    player.playerSource->y = tabPos[index].y;
    player.playerSource->w = WIDTH_A;
    player.playerDest->w = WIDTH_A;
    player.playerSource->h = HEIGHT_A;
    player.playerDest->h = HEIGHT_A;
}

//Je charge mon image source (pour en faire une animation video)
void SDLAnimation::loadClips() {
    //WALKING UP
    Walk(player_up_clips, 21);
    //WALKING LEFT
    Walk(player_left_clips, 23);
    //WALKING DOWN
    Walk(player_down_clips, 25);
    //WALKING RIGHT
    Walk(player_right_clips, 27);
    //UP
    AttackInit(attackUp, 16);

    //LEFT
    AttackInit(attackLeft, 17);

    //DOWN

    AttackInit(attackDown, 18);

    //RIGHT
    AttackInit(attackRight, 19);

    //Player Dead
    AttackInit(PlayerHurtClips, 20);

}

//ALL ANIMATION SEQUENCE USE w , x and s
void SDLAnimation::UP(int idxAtt, char c) {
    if(c == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackUp);
    }
}

void SDLAnimation::LEFT(int idxAtt, char c) {
    if(c == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackLeft);
    }
}

void SDLAnimation::DOWN(int idxAtt, char c) {
    if(c == 's') { //shoot
        //Animation Attack up normal
        makeAnimation(idxAtt,attackDown);
    }
}

void SDLAnimation::RIGHT(int idxAtt, char c) {
    if(c == 's') {
        //Animation Attack up normal
        makeAnimation(idxAtt,attackRight);
    }
}

void SDLAnimation::handleInput() {
    state = SDL_GetKeyboardState(nullptr);

    moving_left = state[SDL_SCANCODE_LEFT] > 0;
    moving_right = state[SDL_SCANCODE_RIGHT] > 0;
    moving_up = state[SDL_SCANCODE_UP] > 0;
    moving_down = state[SDL_SCANCODE_DOWN] > 0;

    if(state[SDL_SCANCODE_K] > 0)
        keyBoardK = 'k';

    if (state[SDL_SCANCODE_S] > 0)
        keyBoard = 's';

    /*while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
    }*/
}


void SDLAnimation::walkingAnimation(Position tabPos[], int speed, int indexClips, int direction) {

    player.playerSource->x =  tabPos[indexClips].x;
    player.playerSource->y =  tabPos[indexClips].y;
    player.playerSource->w = WIDTH_A*2;
    player.playerDest->w = WIDTH_A*2;
    player.playerSource->h = HEIGHT_A*2;
    player.playerDest->h = HEIGHT_A*2;
    player.direction = direction;
    keyBoard ='_';
    if(direction == NORTH)
        player.playerDest->y += speed;
    if(direction == EAST)
        player.playerDest->x += speed;
    if(direction == WEST)
        player.playerDest->x += speed;
    if(direction == SOUTH)
        player.playerDest->y += speed;
}

void SDLAnimation::updateArrowPos() {
    for (auto& arrow: player.listArrow) {
        if(arrow.direction == EAST || arrow.direction == WEST)
            arrow.arrowPos.x += arrow.speed;
        if(arrow.direction == NORTH || arrow.direction == SOUTH)
            arrow.arrowPos.y += arrow.speed;
    }
}

void SDLAnimation::Arrow(SDL_Renderer * renderer) const {

    //Angle -90 (up) 0 ou 360 (right) 180(left) et 90(down)
    for (auto arrow: player.listArrow){
        SDL_Rect tmp = {arrow.arrowPos.x,
                        arrow.arrowPos.y,
                        50,
                        fireArrow._surface->h-20};

        SDL_RenderCopyEx(renderer,
                         fireArrow._texture,
                         nullptr,
                         &tmp,
                         arrow.angleRotate,
                         nullptr,
                         SDL_FLIP_NONE);

    }
}

void SDLAnimation::updatePlayer() {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 7;//for walking frame
    int idxAtt= animation_speed % 13; //for animation frame
    int  idxDead = animation_speed % 5;
    int vitesse=2;

    //idxAtt = 8; //Ne touche jamais gold //Maitennt on tire la fleche si idxAtt = 8


    if (moving_up) {
        player.direction = NORTH;
        walkingAnimation(player_up_clips, -vitesse, idx, NORTH);
    }
    if (moving_left) {
        player.direction = EAST;
        walkingAnimation(player_left_clips, -vitesse, idx, EAST);
    }
    if (moving_down) {
        player.direction = SOUTH;
        walkingAnimation(player_down_clips, +vitesse, idx, SOUTH);
    }
    if (moving_right) {
        player.direction = WEST;
        walkingAnimation(player_right_clips, +vitesse, idx, WEST);
    }

    if(state[SDL_SCANCODE_S] > 0 && idxAtt==8) {
        player.createArrow();
        // Lecture de l'effet sonore une fois
        SDLSound::PlayChunk(shootEffect);
    }
    updateArrowPos();
    if (idxAtt>5)
        *ptrStop = 1;
    if(keyBoardK == 'k' && *ptrStop==0)
         makeAnimation(idxDead, PlayerHurtClips);


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

    Arrow(renderer);
    SDL_RenderCopy(renderer,
                   allAnimation._texture,
                   reinterpret_cast<const SDL_Rect *>(player.playerSource),
                   reinterpret_cast<const SDL_Rect *>(player.playerDest));


}



