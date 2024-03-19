#ifndef HUNTERASSASSIN_GAME_H
#define HUNTERASSASSIN_GAME_H

#include "Player.h"
#include "Rect.h"
#include "IA.h"
#include "Map.h"
#include "Garde.h"

/**
 * @brief Classe représentant le jeu.
 *
 * Cette classe gère les opérations liées au jeu, telles que l'initialisation du joueur,
 * de la map et des gardes.
 */
class Game {
public:
    int nbGardes; /**<Le nombre de garde */
    Player _player; /**< Instance du joueur. */
    Map _gameMap; /**< Instance de la map du jeu. */
    Garde * allGardes ;/**<Un pointeur sur tous les Gardes du jeu. */
public:
    std::vector<Rect> vecAllObstacles; /**< Vecteur contenant tous les obstacles du jeu. */
   // Rect dest; /**< Destination de L'IA. */
    Rect * gardesDest;
    Rect * gardesRect ;
   /* Rect playerRect = dest = { getConstPlayer().getPosition().x,
                               getConstPlayer().getPosition().y,
                               PLAYER_WIDTH,
                               PLAYER_HEIGHT}; */
    /*SDL_Rect source = { 0,
                         PLAYER_HEIGHT*8,
                         PLAYER_WIDTH,
                         PLAYER_HEIGHT};*/


    /**
     * @brief Constructeur par défaut de la classe Game.
     */
    Game(int nbGardes);

    /**
     * @brief Destructeur de la classe Game.
     */
    ~Game();

    /**
     * @brief Gère l'entrée du clavier.
     *
     * Cette fonction détermine l'action à entreprendre en fonction de la touche pressée.
     * Elle permet au joueur de se déplacer sur la carte et interagit avec les éléments du jeu.
     *
     * @param touche La touche pressée par le joueur.
     * @return true si le joueur a effectué une action, sinon false.
     */
    bool toucheClavier(const char touche);

    bool checkCollision(const Rect& rect1, const Rect& rect2);

    /**
     * @brief Obtient une référence constante vers l'objet Player.
     *
     * @return Une référence constante vers l'objet Player associé au jeu.
     */
    inline const Player &getConstPlayer() { return _player; }

    /**
     * @brief Obtient une référence constante vers l'objet Map.
     *
     * @return Une référence constante vers l'objet Map associé au jeu.
     */
    inline const Map &getConstMap() { return _gameMap; }

    /**
     * @brief Obtient un pointeur vers tous les gardes du jeu.
     *
     * @return Un pointeur vers les gardes du jeu.
     */
    inline const Garde* getAllGardes() { return allGardes; }

    /**
     * @brief Obtient le nombre de gardes dans le jeu.
     *
     * @return Le nombre de gardes.
     */
    inline int getNbGardes() const { return nbGardes; }

    /**
     * @brief Définit le nombre de gardes dans le jeu.
     *
     * @param nb Le nouveau nombre de gardes.
     */
    inline void setNbGardes(int nb) { nbGardes = nb; }
};

#endif //HUNTERASSASSIN_GAME_H
