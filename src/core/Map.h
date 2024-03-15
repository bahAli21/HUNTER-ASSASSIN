//
// Created by mamad on 14/03/2024.
//

#ifndef HUNTERASSASSIN_MAP_H
#define HUNTERASSASSIN_MAP_H

#include <cassert>

/**
 * @brief Classe représentant une carte dans le jeu.
 */
class Map {
private:
    /**
     * @brief Enumération des valeurs possibles pour chaque case de la carte.
     */
    enum caseValue {
        UNDERSCORE = '_', /**< Case vide */
        WALL = '#',       /**< Mur */
        DOOR = '|'        /**< Porte */
    };

    int _dimX; /**< Largeur de la carte */
    int _dimY; /**< Hauteur de la carte */

    caseValue myMap[150][150]; /**< Tableau représentant la carte */
public:
    /**
     * @brief Constructeur par défaut de la classe Map.
     */
    Map();

    /**
     * @brief Vérifie si la case aux coordonnées spécifiées est libre.
     * @param _x Abscisse de la case.
     * @param _y Ordonnée de la case.
     * @return True si la case est libre, sinon False.
     */
    bool freePixel(const int _x, const int _y) const;

    /**
     * @brief Ouvre la porte à la position spécifiée.
     * @param _x Abscisse de la porte.
     * @param _y Ordonnée de la porte.
     */
    void openTheDoor(const int _x, const int _y);

    /**
     * @brief Renvoie le type d'objet se trouvant au coordonnées spécifiées.
     * @param _x Abscisse de la case.
     * @param _y Ordonnée de la case.
     * @return Type d'objet (#, _ ou |).
     */
    caseValue getObject(const int _x, const int _y) const;

    /**
     * @brief Renvoie le caractère représentant le type d'objet se trouvant aux coordonnées spécifiées.
     * @param _x Abscisse de la case.
     * @param _y Ordonnée de la case.
     * @return Caractère représentant le type d'objet (#, _ ou |).
     */
    unsigned char getObjectChar(const int _x, const int _y) const;

    /**
     * @brief Renvoie la largeur de la carte.
     * @return La largeur de la carte.
     */
    int getDimX() const;

    /**
     * @brief Renvoie la hauteur de la carte.
     * @return La hauteur de la carte.
     */
    int getDimY() const;

};

/**
 * @brief Renvoie la largeur de la carte.
 * @return La largeur de la carte.
 */
inline int Map::getDimX() const { return _dimX; }

/**
 * @brief Renvoie la hauteur de la carte.
 * @return La hauteur de la carte.
 */
inline int Map::getDimY() const { return _dimY; }

/**
 * @brief Renvoie le type d'objet se trouvant au coordonnées spécifiées.
 * @param _x Abscisse de la case.
 * @param _y Ordonnée de la case.
 * @return Type d'objet (#, _ ou |).
 */
inline Map::caseValue Map::getObject(const int _x, const int _y) const {
    assert(_x >= 0);
    assert(_y >= 0);
    assert(_x < _dimX);
    assert(_y < _dimY);
    return myMap[_x][_y];
}

/**
 * @brief Renvoie le caractère représentant le type d'objet se trouvant aux coordonnées spécifiées.
 * @param _x Abscisse de la case.
 * @param _y Ordonnée de la case.
 * @return Caractère représentant le type d'objet (#, _ ou |).
 */
inline unsigned char Map::getObjectChar(const int _x, const int _y) const {
    assert(_x >= 0);
    assert(_y >= 0);
    assert(_x < _dimX);
    assert(_y < _dimY);
    return (char) myMap[_x][_y];
}


#endif //HUNTERASSASSIN_MAP_H