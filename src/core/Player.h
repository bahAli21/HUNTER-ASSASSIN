#ifndef HUNTERASSASSIN_PLAYER_H
#define HUNTERASSASSIN_PLAYER_H

#include "point.h"
#include "config.h"
#include <cassert>
#include "Map.h"
#include <iostream>

/**
 * @brief Classe représentant le joueur dans le jeu.
 */
class Player {
private:
    Position pos; ///< Position actuelle du joueur.
    bool left, right, up, down; ///< Indicateurs de direction du joueur.
    int health; ///< Nombre de vies du joueur.

public:
    /**
     * @brief Déplace le joueur vers la gauche sur la carte spécifiée.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void goLeft(const Map &map);

    /**
     * @brief Déplace le joueur vers la droite sur la carte spécifiée.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void goRight(const Map &map);

    /**
     * @brief Déplace le joueur vers le haut sur la carte spécifiée.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void goUp(const Map &map);

    /**
     * @brief Déplace le joueur vers le bas sur la carte spécifiée.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void goDown(const Map &map);

    /**
     * @brief Obtient la position actuelle du joueur.
     * @return La position actuelle du joueur.
     */
    Position getPosition() const;

    /**
     * @brief Définit la position horizontale du joueur.
     * @param _x La nouvelle position horizontale.
     */
    void setPositionX(int _x);

    /**
     * @brief Définit la position verticale du joueur.
     * @param _y La nouvelle position verticale.
     */
    void setPositionY(int _y);

    /**
     * @brief Obtient le nombre de vies du joueur.
     * @return Le nombre de vies du joueur.
     */
    int getHealth() const;

    /**
     * @brief Définit le nombre de vies du joueur.
     * @param _health Le nouveau nombre de vies.
     */
    void setHealth(int _health);

    /**
     * @brief Constructeur par défaut de la classe Player.
     */
    Player();

    /**
     * @brief Destructeur de la classe Player.
     */
    ~Player();

    /**
     * @brief Méthode de test pour la régression.
     * Utilisée pour tester les fonctionnalités de la classe Player.
     */
    static void testRegression();
};

// Définition des fonctions inline

/**
 * @brief Obtient la position actuelle du joueur.
 * @return La position actuelle du joueur.
 */
inline Position Player::getPosition() const { return pos; }

/**
 * @brief Définit la position horizontale du joueur.
 * @param _x La nouvelle position horizontale.
 */
inline void Player::setPositionX(int _x) { pos.x = _x; }

/**
 * @brief Définit la position verticale du joueur.
 * @param _y La nouvelle position verticale.
 */
inline void Player::setPositionY(int _y) { pos.y = _y; }

/**
 * @brief Obtient le nombre de vies du joueur.
 * @return Le nombre de vies du joueur.
 */
inline int Player::getHealth() const { return health; }

/**
 * @brief Définit le nombre de vies du joueur.
 * @param _health Le nouveau nombre de vies.
 */
inline void Player::setHealth(int _health) { health = _health; }

#endif //HUNTERASSASSIN_PLAYER_H
