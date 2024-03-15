/**
 * @file MySleep.h
 * @brief Définition de la fonction MySleep pour attendre un certain nombre de millisecondes sans bloquer le programme.
 *
 * Ce fichier contient la définition de la fonction MySleep, qui permet d'attendre un intervalle de temps
 * sans bloquer l'exécution du programme en utilisant un rappel de minuterie.
 */

#ifndef HUNTERASSASSIN_MYSLEEP_H
#define HUNTERASSASSIN_MYSLEEP_H
#include "SDL.h"
//#include "TimerCallback.h"

/**
 * @brief Attend un certain nombre de millisecondes sans bloquer le programme.
 *
 * Cette fonction ajoute un timer qui déclenchera un événement après l'intervalle spécifié.
 * Elle attend ensuite l'événement utilisateur pour indiquer que le temps est écoulé.
 *
 * @param interval L'intervalle de temps en millisecondes.
 */
void MySleep(Uint32 interval) {
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

    // J'ajoute un timer qui déclenchera l'événement après l'intervalle spécifié
    SDL_AddTimer(interval, Container::TimerCallback, NULL);

    // J'attends l'événement utilisateur
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_USEREVENT && event.user.code == 42)
            break;
    }
}

#endif // HUNTERASSASSIN_MYSLEEP_H
