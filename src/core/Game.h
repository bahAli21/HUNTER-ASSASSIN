#pragma once

#include "Player.h"
#include "_Player.h"
#include "_Garde.h"
#include "Rect.h"
#include "IA.h"
#include "Garde.h"
#include <cstdlib>
#include <ctime>
/**
 * @brief Class representing the game.
 *
 * This class manages operations related to the game, such as player initialization,
 * map handling, and guard management.
 */
class Game {
public:
    int nbGardes; /**< The number of guards. */
    std::vector<_Garde> listeOfGardes; /**< List of guards in the game. */
    std::vector<_Player> listeOfPlayers; /**< List of players in the game. */

public:
    /**
     * @brief Default constructor of the Game class.
     *
     * @param nbGardes The number of guards.
     */
    Game(int nbGardes);

    /**
     * @brief Destructor of the Game class.
     */
    ~Game() = default;

    /**
     * @brief Adds guards and players to the game.
     *
     * This method initializes and adds guards and players to the game.
     * It sets up their initial positions, attributes, and behaviors.
     */
    void addGardeAndPlayers();

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

