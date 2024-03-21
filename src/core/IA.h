#ifndef HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H
#define HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H

#include "Rect.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "config.h"

const int SQUARE_SIZE = 20;

/**
 * @class AI
 * @brief Class defining the artificial intelligence for the game.
 */
class AI {
public:
    /**
     * @brief Constructor of the AI class.
     * @param squareRect Pointer to the rectangle representing the square controlled by the AI.
     * @param destRect Pointer to the rectangle representing the destination of the square.
     */
    AI(Rect* squareRect, Rect* destRect);

    /**
     * @brief Default constructor of the AI class.
     */
    AI();

    bool left{}, right{}, down{}, up{}; /**< Direction indicators for AI-controlled movement. */

    /**
     * @brief Checks if the square has reached its destination.
     * @return True if the square has reached its destination, otherwise False.
     */
    bool estArrivee();

    /**
     * @brief Handles the movement of the square controlled by the AI.
     * @param obstacles Vector of all rectangles representing obstacles to avoid.
     */
    void mov(std::vector<Rect>& obstacles);

    /**
     * @brief Checks for collision between two rectangles.
     * @param rect2 Rectangle to check collision with.
     * @return True if there is a collision, otherwise False.
     */
    bool collision(const Rect& rect2);

    /**
     * @brief Bypasses an obstacle by choosing the shortest path.
     * @param obstacleRect Rectangle representing the obstacle to bypass.
     */
    void contourObstacle(Rect obstacleRect);

    /**
     * @brief Moves the square controlled by the AI based on the specified distances on the x and y axes.
     * @param distanceX Distance on the x-axis.
     * @param distanceY Distance on the y-axis.
     * @param obstacle Rectangle representing the obstacle to bypass.
     */
    void moveAgain(int distanceX, int distanceY, Rect obstacle);

    /**
     * @brief Checks if the pixel is free.
     * @param obstacles Vector of all rectangles representing obstacles to avoid.
     * @return True if the pixel is free, otherwise False.
     */
    bool freePixel(std::vector<Rect>& obstacles);

    /**
     * @brief Checks if the destination is available.
     * @param rect1 Rectangle representing the current position.
     * @param rect2 Rectangle representing the destination.
     * @return True if the destination is available, otherwise False.
     */
    static bool destNotAvailable(const Rect &rect1, const Rect &rect2);

private:
    Rect* squareRect{}; /**< Pointer to the rectangle representing the square controlled by the AI. */
    Rect* destRect{}; /**< Pointer to the rectangle representing the destination of the square. */
};

#endif // HUNTERASSASSIN_ARTIFICIALINTELLIGENCE_H
