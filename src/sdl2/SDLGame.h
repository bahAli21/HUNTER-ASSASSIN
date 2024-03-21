#ifndef HUNTERASSASSIN_SDLGAME_H
#define HUNTERASSASSIN_SDLGAME_H

#include "SDLAnimation.h" //inclu SDLSprite.h
#include "../core/Game.h"
#include "SDL.h"
//#include ""
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
    SDLSprite sourceAnimation;
    char * animImg;
    //Sprite pour la map
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

} ;

#endif //HUNTERASSASSIN_SDLGAME_H
