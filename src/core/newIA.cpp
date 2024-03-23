

#include "newIA.h"

AI::AI(Rect* squareRect, Rect* destRect) : squareRect(squareRect), destRect(destRect) {}

bool AI::estArrivee() {
    return (squareRect->x == destRect->x && squareRect->y == destRect->y);
}

AI::AI() = default;

bool AI::collision(const Rect& rect2) {
    // Je Calcul avant tout les coordonnées des bords des rectangles
    int rect1Left = squareRect->x;
    int rect1Right = squareRect->x + squareRect->w;
    int rect1Top = squareRect->y;
    int rect1Bottom = squareRect->y + squareRect->h;

    int rect2Left = rect2.x;
    int rect2Right = rect2.x + rect2.w;
    int rect2Top = rect2.y;
    int rect2Bottom = rect2.y + rect2.h;

    // Vérification sur les collisions
    if (rect1Right >= rect2Left && rect1Left <= rect2Right && rect1Bottom >= rect2Top && rect1Top <= rect2Bottom)
        return true;

    //if (rect1Left <0 || rect1Right >= WINDOW_W-20 || rect1Top <= 20 || rect1Bottom >= WINDOW_H-20)
    //return true; // Il y a collision avec la fenêtre

    return false;
}

void AI::moveAgain(int distanceX, int distanceY) {
    // je me Déplace sur l'axe y si la distance en y est non nulle
    if (distanceY != 0) {
        if (distanceY > 0) {
            squareRect->y++;
        } else if (distanceY < 0) {
            squareRect->y--;
        }
    } else if (distanceX != 0) { // Si la distance en y est nulle, je me déplace sur l'axe x
        if (distanceX > 0) {
            squareRect->x++;
        } else if (distanceX < 0) {
            squareRect->x--;
        }
    }
}

bool AI::destNotAvailable(const Rect &  rect1, const Rect & rect2) {
    // Je Calcul avant tout les coordonnées des bords des rectangles
    int rect1Left = rect1.x;
    int rect1Right = rect1.x + rect1.w;
    int rect1Top = rect1.y;
    int rect1Bottom = rect1.y + rect1.h;

    int rect2Left = rect2.x;
    int rect2Right = rect2.x + rect2.w;
    int rect2Top = rect2.y;
    int rect2Bottom = rect2.y + rect2.h;

    // Vérification sur les collisions
    if (rect1Right >= rect2Left && rect1Left <= rect2Right && rect1Bottom >= rect2Top && rect1Top <= rect2Bottom)
        return true;
    return false;
}

bool AI::freePixel(std::vector<Rect>& obstacles) {
    Rect rect= {destRect->x,destRect->y,SQUARE_SIZE,SQUARE_SIZE};
    for(const Rect& obstacle: obstacles) {
        if(destNotAvailable(rect, obstacle))
            return false;
    }
    return true;
}

void AI::contourObstacle(Rect obstacleRect) {
    // Calcule des deux itinéraires possibles
    int leftX = obstacleRect.x - squareRect->w; // Bord gauche de l'obstacle
    int rightX = obstacleRect.x + obstacleRect.w; // Bord droit de l'obstacle

    // Calcule de la distance de chaque itinéraire par rapport à la destination
    double leftDistance = sqrt(pow(destRect->x - leftX, 2) + pow(destRect->y - squareRect->y, 2));
    double rightDistance = sqrt(pow(destRect->x - rightX, 2) + pow(destRect->y - squareRect->y, 2));

    // Choisir l'itinéraire le plus court
    if (leftDistance < rightDistance) {
        squareRect->x--;
    } else {
        squareRect->x++;
    }
}

void AI::mov(std::vector<Rect> obstacleRect) {
    // Calcule  des distances sur les axes x et y
    int distanceX = destRect->x - squareRect->x;
    int distanceY = destRect->y - squareRect->y;

    // Si le carré n'est pas encore arrivé à sa destination
    if (distanceX != 0 || distanceY != 0) {
        // S'il y a collision, j'essaye de contourner l'obstacle
        if (collision(obstacleRect[0])) {
            contourObstacle(obstacleRect[0]);
        } else {
            // Ensuite, je continue le mouvement
            moveAgain(distanceX, distanceY);
        }
    }
}
