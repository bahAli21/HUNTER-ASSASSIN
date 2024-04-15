#pragma once
#include "point.h"
#include "config.h"
#include <cassert>
#include "Rect.h"

#include <iostream>
#include "vector"
#include "Arrow.h"
#include "Direction.h"

/**
 * @brief Class representing a character in the game.
 *
 * This class encapsulates the properties and behaviors of a character,
 * such as movement, animation, health, and attacking.
 */
class Character{
public:
    /**
     * @brief Constructor for the Character class.
     *
     * Initializes a character with the specified attributes.
     *
     * @param source The source rectangle for rendering.
     * @param dest The destination rectangle for rendering.
     * @param direction The initial direction of the character.
     * @param health The initial health points of the character.
     * @param theSpritePath The path to the sprite image file.
     * @param _targetPos The target position for the character.
     * @param _speed The movement speed of the character.
     * @param _tabNoeud The vector of positions for character pathfinding.
     */
    Character(Rect * source, Rect * dest, int direction, int health, const char * theSpritePath, Rect * _targetPos,  int _speed, std::vector<Position> _tabNoeud);

    /**
     * @brief Default constructor for the Character class.
     */
    Character() = default;

    /**
     * @brief Destructor for the Character class.
     */
    ~Character();

    int health; ///< Health points of the character.
    Rect * dest; ///< Destination rectangle for rendering.
    Rect * source; ///< Source rectangle for rendering.
    Rect * targetPos; ///< Target position for the character.
    int direction{}; /**< Direction indicators of the character.*/
    std::vector<Arrow> listArrow; /**< List of arrows associated with the character. */
    char shootKey; ///< Key used for shooting.
    int speed; ///< Movement speed of the character.
    const char * theSpritePath; ///< Path to the sprite image file.
    std::vector<Position> tabNoeud; ///< Vector of positions for character pathfinding.
    bool isDead{false}; ///<Checks if the character is dead.
    SDL_Rect smallRect; /**< SDL_Rect structure for small rectangle. */
    // Walking clips
    Position player_left_clips[9]{}; /**< Array of positions for left movement animation. */
    Position player_right_clips[9]{}; /**< Array of positions for right movement animation. */
    Position player_up_clips[9]{}; /**< Array of positions for up movement animation. */
    Position player_down_clips[9]{}; /**< Array of positions for down movement animation. */

    // Shoot clips
    Position attackUp[13]{}; /**< Array of positions for attacking upwards animation. */
    Position attackLeft[13]{}; /**< Array of positions for attacking left animation. */
    Position attackDown[13]{}; /**< Array of positions for attacking downwards animation. */
    Position attackRight[13]{}; /**< Array of positions for attacking right animation. */
    bool hasKey = {false};
    // Dead clips
    Position PlayerHurtClips[7]; /**< Array of positions for the hurt animation. */
    bool Retour{false}, Aller{true};
public:
    static void AttackInit(Position tabPos[], int index);
    void makeAnimation(int index, Position tabPos[]) const;
    void WalkingAnimation(Position tabPos[], int speed, int indexClips, int direction);
    void UP(int idxAtt);
    void LEFT(int idxAtt);
    void RIGHT(int idxAtt);
    void DOWN(int idxAtt);
    void updateArrowPos();
    bool canShootNow = false;
    static void Walk(Position tabPos[], int index);
    void loadClips();
    /**
     * @brief Moves the player to the left on the specified map.
     * @param map The map on which the player moves.
     */
    void createArrow(int direct);
    void goLeft() const;

    /**
     * @brief Moves the player to the right on the specified map.
     * @param map The map on which the player moves.
     */
    void goRight() const;

    /**
     * @brief Moves the player upward on the specified map.
     * @param map The map on which the player moves.
     */
    void goUp() const;

    /**
     * @brief Moves the player downward on the specified map.
     * @param map The map on which the player moves.
     */
    void goDown() const;

    /**
     * @brief Gets the health points of the player.
     * @brief l'utilisation de [[nodiscard]] permet de signaler explicitement
     * que la valeur de retour d'une fonction est significative
     * et doit être prise en compte par le code appelan
     * @return The health points of the player.
     */
    [[nodiscard]] int getHealth() const;

    /**
     * @brief Sets the health points of the player.
     * @param _health The new health points.
     */
    void setHealth(int _health);

};


// Inline function definitions

/**
 * @brief Gets the health points of the player.
 * @return The health points of the player.
 */
inline int Character::getHealth() const { return health; }

/**
 * @brief Sets the health points of the player.
 * @param _health The new health points.
 */
inline void Character::setHealth(int _health) { health = _health;}
