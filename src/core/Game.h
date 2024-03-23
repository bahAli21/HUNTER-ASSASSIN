#ifndef HUNTERASSASSIN_GAME_H
#define HUNTERASSASSIN_GAME_H

#include "Player.h"
#include "Rect.h"
#include "newIA.h"
#include "Garde.h"

/**
 * @brief Class representing the game.
 *
 * This class manages operations related to the game, such as player initialization,
 * map handling, and guard management.
 */
class Game {
public:
    int nbGardes; /**< The number of guards. */
    Player _player; /**< Instance of the player. */
    Map _gameMap; /**< Instance of the game map. */
    Garde *allGardes; /**< Pointer to all guards in the game. */
    Rect *gardesDest; /**< Pointer to all guards in the game. */
    Rect *gardesRect; /**< Pointer to all guards in the game. */
    AI PlayerAI; /**< AI object for player. */
    AI *guardAI; /**< Pointer to AI objects for guards. */

public:
    std::vector<Rect> vecAllObstacles; /**< Vector containing all obstacles in the game. */

    /**
     * @brief Default constructor of the Game class.
     *
     * @param nbGardes The number of guards.
     */
    Game(int nbGardes);

    /**
     * @brief Moves the guards based on AI decisions.
     *
     * @param lastGuardDestinationChangeTime Time of the last guard destination change.
     */
    void movingGuardByAI(Uint32 lastGuardDestinationChangeTime);

    /**
     * @brief Moves the player based on AI decisions.
     */
    void movingPlayerByAI();

    /**
     * @brief Updates player destination coordinates.
     *
     * @param x New x-coordinate of player destination.
     * @param y New y-coordinate of player destination.
     */
    void updatePlayerDest(int x, int y);

    /**
     * @brief Destructor of the Game class.
     */
    ~Game();

    /**
     * @brief Handles keyboard input.
     *
     * This function determines the action to take based on the pressed key.
     * It allows the player to move on the map and interact with game elements.
     *
     * @param touche The key pressed by the player.
     * @return true if the player performed an action, false otherwise.
     */
    bool toucheClavier(const char touche);

    /**
     * @brief Checks for collision between two rectangles.
     *
     * @param rect1 The first rectangle.
     * @param rect2 The second rectangle.
     * @return true if the rectangles collide, false otherwise.
     */
    bool checkCollision(const Rect& rect1, const Rect& rect2);

    /**
     * @brief Gets a constant reference to the Player object.
     *
     * @return A constant reference to the Player object associated with the game.
     */
    inline const Player& getConstPlayer() { return _player; }

    /**
     * @brief Gets a constant reference to the Map object.
     *
     * @return A constant reference to the Map object associated with the game.
     */
    inline const Map& getConstMap() { return _gameMap; }

    /**
     * @brief Gets a pointer to all guards in the game.
     *
     * @return A pointer to the guards in the game.
     */
    inline const Garde* getAllGardes() { return allGardes; }

    /**
     * @brief Gets the number of guards in the game.
     *
     * @return The number of guards.
     */
    inline int getNbGardes() const { return nbGardes; }

    /**
     * @brief Sets the number of guards in the game.
     *
     * @param nb The new number of guards.
     */
    inline void setNbGardes(int nb) { nbGardes = nb; }
};

#endif // HUNTERASSASSIN_GAME_H
