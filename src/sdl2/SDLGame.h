#ifndef HUNTERASSASSIN_SDLGAME_H
#define HUNTERASSASSIN_SDLGAME_H

#include "SDLSprite.h"
#include "../core/Game.h"
#include "SDL.h"
#include "../core/config.h"
/**
 * @brief La classe gérant le jeu avec un affichage SDL.
 */
class SDLGame {
private:
    Game game; /**< Instance de la classe Game. */
    SDL_Window * window; /**< Fenêtre SDL pour l'affichage. */
    SDL_Renderer * renderer; /**< Rendu SDL pour l'affichage. */

    SDLSprite sp_player; /**< Sprite SDL pour le joueur. */
    SDLSprite sp_garde; /**< Sprite SDL pour les gardes. */
    SDLSprite sp_greyBoxe; // representer par 'g'
    SDLSprite sp_redBoxe1;// representer par 'i'
    SDLSprite sp_redBoxe2;// representer par 'j'
    SDLSprite sp_redBoxe3;// representer par 'k'
    SDLSprite sp_redBoxe4;// representer par 'l'
    SDLSprite sp_door; // representer par '|'
    SDLSprite sp_smallBoxe; // representer par 'b'
    SDLSprite sp_blueDoor; // representer par 'd'
    SDLSprite sp_wall1; // representer par '#'
    SDLSprite sp_wall2;// representer par 'p'
    SDLSprite sp_moqGrey;// representer par '_'
    SDLSprite sp_moqBlack;// representer par '.'

public:
    void drawTheMap(const Map & map) const;
    /**
     * @brief Constructeur par défaut de la classe SDLGame.
     */
    SDLGame ();

    /**
     * @brief Destructeur de la classe SDLGame.
     */
    ~SDLGame ();

    /**
     * @brief Méthode principale pour exécuter le jeu.
     */
    void runProject();

    /**
     * @brief Méthode pour dessiner le jeu avec SDL.
     */
    void sdlDraw();

    /**
     * @brief Méthode pour obtenir le temps.
     * @return Le temps écoulé depuis le début du jeu.
     */
    float temps();

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
};

#endif //HUNTERASSASSIN_SDLGAME_H
