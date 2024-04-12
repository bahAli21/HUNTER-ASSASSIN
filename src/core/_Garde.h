#pragma once
#include "Character.h"
#include <string>
#include <utility>

/**
 * @brief The Player class represents a player in the game.
 *
 * It inherits from Character class and extends it by adding
 * attributes such as name, level, and identifier.
 */
class _Garde : public Character {
    using Character::Character;
private:
    std::string name;       ///< The name of the player.
    int level;              ///< The level of the player.
    int id;         ///< The identifier of the player.

public:
    /**
     * @brief Constructs a new Player object.
     *
     * @param source The source rectangle.
     * @param dest The destination rectangle.
     * @param direction The initial direction of the player.
     * @param health The initial health of the player.
     * @param _name The name of the player.
     * @param _level The level of the player.
     * @param _identifier The identifier of the player.
     */


    _Garde(Rect* source, Rect* dest, int direction, int health,const char * pathSprite,Rect * targetPos,int _speed, std::string  _name, int _level, int _id, std::vector<Position> tabNoeud)
            : Character(source, dest, direction, health, pathSprite, targetPos, _speed, tabNoeud), name(std::move(_name)), level(_level), id(_id) {}

            // Getters and setters for name, level, and identifier

    ~_Garde() = default;
    /**
     * @brief Gets the name of the player.
     *
     * @return The name of the player.
     */
    [[nodiscard]] const std::string& getName() const { return name; }

    /**
     * @brief Sets the name of the player.
     *
     * @param _name The new name of the player.
     */
    void setName(const std::string& _name) { name = _name; }

    /**
     * @brief Gets the level of the player.
     *
     * @return The level of the player.
     */
    [[nodiscard]] int getLevel() const { return level; }

    /**
     * @brief Sets the level of the player.
     *
     * @param _level The new level of the player.
     */
    void setLevel(int _level) { level = _level; }

    /**
     * @brief Gets the identifier of the player.
     *
     * @return The identifier of the player.
     */
    [[nodiscard]] int getIdentifier() const { return id; }

    /**
     * @brief Sets the identifier of the player.
     *
     * @param _identifier The new identifier of the player.
     */
    void setIdentifier(int _id) { id = _id; }


};
