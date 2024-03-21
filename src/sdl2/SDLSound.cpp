#include "SDLSound.h"

SDLSound::SDLSound(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL_mixer : ");
        SDL_Quit();
        return;
    }
}

SDLSound::~SDLSound() {}

Mix_Chunk *SDLSound::LoadChunkFromFile(const char *pathChunk) {
    Mix_Chunk* effect = Mix_LoadWAV(pathChunk);
    if (effect == nullptr) {
        SDL_Log("Erreur lors du chargement de l'effet sonore");
    }
    return effect;
}

Mix_Music *SDLSound::LoadMusicFromFile(const char *pathMusic) {
    Mix_Music* music = Mix_LoadMUS(pathMusic);
    if (music == nullptr) {
        SDL_Log("Erreur lors du chargement de la musique : ");
    }
    return music;
}

void SDLSound::PlayChunk(Mix_Chunk *chunk) {
    /**@param channel, chunk and loop*/
    Mix_PlayChannel(-1, chunk, 0);
}

void SDLSound::PlayMusic(Mix_Music *music) {
    Mix_PlayMusic(music, -1);
}

