// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Quests.hpp"
#include <string>
#include <vector>

/**
 * @class Location
 * @brief Represents a game location where the player can explore, interact, and complete quests.
 * 
 * The Location class encapsulates all the necessary details about a game location, such as its name,
 * description, available quests, and enemies. It also supports interaction with objects and movement between locations.
 */
class Location {
private:
    std::string name;               ///< Name of the location.
    std::string description;        ///< Description of the location.
    int available_quests;           ///< Number of available quests in the location.
    std::string enemies;            ///< Enemies present in the location.
    std::vector<Location*> neighboring_locations; ///< List of neighboring locations for movement.

public:
    /**
     * @brief Constructs a new Location object.
     * @param name The name of the location.
     * @param description The description of the location.
     * @param quests The number of available quests (default: 1).
     * @param enemies The enemies present in the location (default: "").
     */
    Location(const std::string& name, const std::string& description, int quests = 1, const std::string& enemies = "");

    /**
     * @brief Simulates the player entering the location.
     */
    void enter_location();

    /**
     * @brief Simulates the player interacting with an object in the location.
     * @param object_name The name of the object to interact with.
     */
    void interact_with_object(const std::string& object_name);

    /**
     * @brief Lists the available quests in the location.
     * @return A Quests object representing the available quests.
     */
    Quests list_available_quests();

    /**
     * @brief Displays information about the location.
     */
    void display_info();

    /**
     * @brief Adds a neighboring location to this location.
     * @param neighbor A pointer to the neighboring location.
     */
    void add_neighbor(Location* neighbor);

    /**
     * @brief Moves the player to a neighboring location.
     * @param neighbor_name The name of the neighboring location to move to.
     * @return True if movement is successful, false if the location is not found.
     */
    bool move_to_neighbor(const std::string& neighbor_name);

    /**
     * @brief Gets the name of the location.
     * @return The name of the location.
     */
    std::string get_name() const {
        return name;
    }
};

#endif
