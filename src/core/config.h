
#ifndef HUNTERASSASSIN_CONFIG_H
#define HUNTERASSASSIN_CONFIG_H
#include "SDL.h"

/// \file config.h
/// \brief Constantes du projet

/// \def WINDOW_TITLE
/// Titre de la fenêtre du jeu.
#define WINDOW_TITLE "Hunter Assassin"

/// \def WINDOW_X
/// Position horizontale de la fenêtre.
#define WINDOW_X SDL_WINDOWPOS_UNDEFINED

/// \def WINDOW_Y
/// Position verticale de la fenêtre.
#define WINDOW_Y SDL_WINDOWPOS_UNDEFINED

/// \def WINDOW_W
/// Largeur de la fenêtre.
#define WINDOW_W 900 // 550 chez Gold

/// \def CLIPS_SIZE
/// Taille du tableau de sprite a utiliser pour l'animation.
#define CLIPS_SIZE = 6
/// \def WINDOW_H
/// Hauteur de la fenêtre.
#define WINDOW_H 400 // 850 chez Gold

/// \def PLAYER_WIDTH
/// Largeur du joueur.
#define PLAYER_WIDTH 64  //Ne le change jamais Gold

/// \def PLAYER_HEIGHT
/// Hauteur du joueur.
#define PLAYER_HEIGHT 64 //Ne le change jamais Gold

#endif // HUNTERASSASSIN_CONFIG_H
