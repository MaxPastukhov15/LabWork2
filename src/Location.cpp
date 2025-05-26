// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#include "Quests.hpp"
#include "Location.hpp"
#include <iostream>

/**
 * @brief Constructs a new Location object.
 * @param name The name of the location.
 * @param description The description of the location.
 * @param quests The number of available quests (default: 1).
 * @param enemies The enemies present in the location (default: "").
 */
Location::Location(const std::string& name, const std::string& description, int quests, const std::string& enemies)
    : name(name), description(description), available_quests(quests), enemies(enemies) {}

/**
 * @brief Simulates the player entering the location.
 */
void Location::enter_location() {
    std::cout << "=== Entered Location ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    if (!enemies.empty()) {
        std::cout << "Enemies: " << enemies << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

/**
 * @brief Simulates the player interacting with an object in the location.
 * @param object_name The name of the object to interact with.
 */
void Location::interact_with_object(const std::string& object_name) {
    std::cout << "Interacting with " << object_name << " in " << name << "." << std::endl;
}

/**
 * @brief Lists the available quests in the location.
 * @return A Quests object representing the available quests.
 */
Quests Location::list_available_quests() {
    std::cout << "Available quests in " << name << ": " << available_quests << std::endl;
    return Quests();
}

/**
 * @brief Displays information about the location.
 */
void Location::display_info() {
    std::cout << "=== Location Information ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Available Quests: " << available_quests << std::endl;
    if (!enemies.empty()) {
        std::cout << "Enemies: " << enemies << std::endl;
    }
    std::cout << "===========================" << std::endl;
}

/**
 * @brief Adds a neighboring location to this location.
 * @param neighbor A pointer to the neighboring location.
 */
void Location::add_neighbor(Location* neighbor) {
    neighboring_locations.push_back(neighbor);
}

/**
 * @brief Moves the player to a neighboring location.
 * @param neighbor_name The name of the neighboring location to move to.
 * @return True if movement is successful, false if the location is not found.
 */
bool Location::move_to_neighbor(const std::string& neighbor_name) {
    for (Location* neighbor : neighboring_locations) {
        if (neighbor->name == neighbor_name) {
            std::cout << "Moving to " << neighbor_name << "." << std::endl;
            neighbor->enter_location();
            return true;
        }
    }
    std::cout << "Neighboring location " << neighbor_name << " not found." << std::endl;
    return false;
}

