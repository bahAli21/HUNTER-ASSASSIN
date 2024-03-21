//
// Created by mamad on 21/03/2024.
//

#ifndef HUNTERASSASSIN_SDLSOUND_H
#define HUNTERASSASSIN_SDLSOUND_H
#include "SDL_mixer.h"
#include "SDL.h"
class SDLSound {
public:
    SDLSound(int frequency, Uint16 format, int channels, int chunksize);
    ~SDLSound();
    Mix_Chunk* LoadChunkFromFile(const char * pathChunk);
    Mix_Music* LoadMusicFromFile(const char * pathMusic);
    void PlayeChunk(Mix_Chunk* chunk);
    void PlayeMusic(Mix_Music* music);
};


#endif //HUNTERASSASSIN_SDLSOUND_H
