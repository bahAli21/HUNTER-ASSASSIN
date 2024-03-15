#ifndef HUNTERASSASSIN_Garde_H
#define HUNTERASSASSIN_Garde_H

#include "point.h"
#include "config.h"
#include <cassert>
#include "Map.h"
#include <iostream>

/**
 * @brief Classe représentant le Garde dans le jeu.
 */
class Garde {
private:
    Position pos; ///< Position actuelle du Garde.
    bool left, right, up, down; ///< Indicateurs de direction du Garde.
    int health; ///< Nombre de vies du Garde.

public:
    /**
     * @brief Déplace le Garde vers la gauche sur la carte spécifiée.
     * @param map La carte sur laquelle le Garde se déplace.
     */
    void goLeft(const Map &map);

    /**
     * @brief Déplace le Garde vers la droite sur la carte spécifiée.
     * @param map La carte sur laquelle le Garde se déplace.
     */
    void goRight(const Map &map);

    /**
     * @brief Déplace le Garde vers le haut sur la carte spécifiée.
     * @param map La carte sur laquelle le Garde se déplace.
     */
    void goUp(const Map &map);

    /**
     * @brief Déplace le Garde vers le bas sur la carte spécifiée.
     * @param map La carte sur laquelle le Garde se déplace.
     */
    void goDown(const Map &map);

    /**
     * @brief Obtient la position actuelle du Garde.
     * @return La position actuelle du Garde.
     */
    Position getPosition() const;

    /**
     * @brief Définit la position horizontale du Garde.
     * @param _x La nouvelle position horizontale.
     */
    void setPositionX(int _x);

    /**
     * @brief Définit la position verticale du Garde.
     * @param _y La nouvelle position verticale.
     */
    void setPositionY(int _y);

    /**
     * @brief Obtient le nombre de vies du Garde.
     * @return Le nombre de vies du Garde.
     */
    int getHealth() const;

    /**
     * @brief Définit le nombre de vies du Garde.
     * @param _health Le nouveau nombre de vies.
     */
    void setHealth(int _health);

    /**
     * @brief Constructeur par défaut de la classe Garde.
     */
    Garde();

    /**
     * @brief Destructeur de la classe Garde.
     */
    ~Garde();

    /**
     * @brief Méthode de test pour la régression.
     * Utilisée pour tester les fonctionnalités de la classe Garde.
     */
    static void testRegression();
};

// Définition des fonctions inline

/**
 * @brief Obtient la position actuelle du Garde.
 * @return La position actuelle du Garde.
 */
inline Position Garde::getPosition() const { return pos; }

/**
 * @brief Définit la position horizontale du Garde.
 * @param _x La nouvelle position horizontale.
 */
inline void Garde::setPositionX(int _x) { pos.x = _x; }

/**
 * @brief Définit la position verticale du Garde.
 * @param _y La nouvelle position verticale.
 */
inline void Garde::setPositionY(int _y) { pos.y = _y; }

/**
 * @brief Obtient le nombre de vies du Garde.
 * @return Le nombre de vies du Garde.
 */
inline int Garde::getHealth() const { return health; }

/**
 * @brief Définit le nombre de vies du Garde.
 * @param _health Le nouveau nombre de vies.
 */
inline void Garde::setHealth(int _health) { health = _health; }

#endif //HUNTERASSASSIN_Garde_H
