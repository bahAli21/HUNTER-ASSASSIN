
#ifndef HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H
#define HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H

#include <iostream>
#include <cmath>
#include "config.h"
#include "Rect.h"
#include <vector>

/**
 * @brief Taille du carré contrôlé par l'IA.
 */
const int SQUARE_SIZE = 20;

/**
 * @class AI
 * @brief Classe définissant l'intelligence artificielle pour le jeu.
 */
class AI {
public:
    /**
     * @brief Constructeur de la classe AI.
     * @param squareRect Pointeur vers le rectangle représentant le carré contrôlé par l'IA.
     * @param destRect Pointeur vers le rectangle représentant la destination du carré.
     */
    AI(Rect* squareRect, Rect* destRect);
    AI();

    /**
     * @brief Vérifie si le carré est arrivé à sa destination.
     * @return True si le carré est arrivé à sa destination, sinon False.
     */
    bool estArrivee();

    /**
     * @brief Gère le mouvement du carré contrôlé par l'IA.
     * @param obstacleRect Rectangle représentant un obstacle à éviter.
     */
    void mov(std::vector<Rect> obstacleRect);

    /**
     * @brief Vérifie s'il y a une collision entre deux rectangles.
     * @param rect2 Rectangle avec lequel vérifier la collision.
     * @return True s'il y a une collision, sinon False.
     */
    bool collision(const Rect& rect2);

    /**
     * @brief Contourne un obstacle en choisissant le chemin le plus court.
     * @param obstacleRect Rectangle représentant l'obstacle à contourner.
     */
    void contourObstacle(Rect obstacleRect);

    /**
     * @brief Déplace le carré contrôlé par l'IA en fonction des distances spécifiées sur les axes x et y.
     * @param distanceX Distance sur l'axe x.
     * @param distanceY Distance sur l'axe y.
     */
    void moveAgain(int distanceX, int distanceY);
    bool freePixel(std::vector<Rect>& obstacles);
    bool destNotAvailable(const Rect &  rect1, const Rect & rect2);

private:
    Rect* squareRect; ///< Pointeur vers le rectangle représentant le carré contrôlé par l'IA.
    Rect* destRect; ///< Pointeur vers le rectangle représentant la destination du carré.
};

#endif //HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H
