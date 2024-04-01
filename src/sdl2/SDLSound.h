//
// Created by mamad on 21/03/2024.
//

#ifndef HUNTERASSASSIN_SDLSOUND_H
#define HUNTERASSASSIN_SDLSOUND_H

#include "SDL_mixer.h"
#include "SDL.h"

/**
 * @brief The SDLSound class provides functionality to work with sound in SDL.
 */
class SDLSound {
public:
    /**
     * @brief Constructs an SDLSound object with specified audio parameters.
     *
     * @param frequency The audio frequency in samples per second.
     * @param format    The audio format.
     * @param channels  The number of audio channels.
     * @param chunksize The size of audio chunks.
     */
    SDLSound(int frequency, Uint16 format, int channels, int chunksize);
    SDLSound() = default;
    /**
     * @brief Destroys the SDLSound object.
     */
    ~SDLSound();

    /**
     * @brief Loads a sound chunk from a file.
     *
     * @param pathChunk The path to the sound chunk file.
     * @return A pointer to the loaded sound chunk.
     */
    static Mix_Chunk* LoadChunkFromFile(const char* pathChunk);

    /**
     * @brief Loads music from a file.
     *
     * @param pathMusic The path to the music file.
     * @return A pointer to the loaded music.
     */
    static Mix_Music* LoadMusicFromFile(const char* pathMusic);

    /**
     * @brief Plays a sound chunk.
     *
     * @param chunk A pointer to the sound chunk to be played.
     */
    static void PlayChunk(Mix_Chunk* chunk);

    /**
     * @brief Plays music.
     *
     * @param music A pointer to the music to be played.
     */
    static void PlayMusic(Mix_Music* music);
};

#endif //HUNTERASSASSIN_SDLSOUND_H
