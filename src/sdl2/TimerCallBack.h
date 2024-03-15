/**
 * @file TimerCallback.h
 * @brief Définition de la classe TimerCallback pour gérer les rappels de minuterie.
 *
 * Ce fichier contient la définition de la classe TimerCallback, qui permet de créer
 * un rappel de minuterie pour déclencher un événement après un certain intervalle.
 */

#ifndef HUNTERASSASSIN_TIMERCALLBACK_H
#define HUNTERASSASSIN_TIMERCALLBACK_H

#include "SDLGame.h"

/**
 * @class TimerCallback
 * @brief Classe pour gérer les rappels de minuterie.
 *
 * La classe TimerCallback permet de créer un rappel de minuterie qui déclenchera
 * un événement après un certain intervalle de temps.
 */
struct Container {
    /**
     * @brief Fonction de rappel de minuterie.
     *
     * Cette fonction est appelée lorsque le temps spécifié dans l'intervalle est écoulé.
     * Elle génère un événement utilisateur pour indiquer que le temps est écoulé.
     *
     * @param interval L'intervalle de temps en millisecondes.
     * @param param Paramètre supplémentaire (non utilisé dans cet exemple).
     * @return Toujours 0 (valeur de retour requise par SDL_AddTimer).
     */
    static Uint32 TimerCallback(Uint32 interval, void* param) {
        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user.code = 42; // Code d'événement personnalisé
        SDL_PushEvent(&event); // Ajoute l'événement à la file d'attente
        return 0;
    }
};

#endif // HUNTERASSASSIN_TIMERCALLBACK_H
