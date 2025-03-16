#include "Game.hpp"
#include "Location.hpp"
#include <iostream>

/**
 * @brief Constructs a new Game instance.
 * Initializes the game with a starting location and basic game settings.
 */
Game::Game() {
    Location* starting_area = new Location("Starting Area", "You are in a small village.");
    Location* forest = new Location("Forest", "A dense, dark forest filled with danger.");
    Location* town = new Location("Town", "A bustling town with shops and inns.");
    
    starting_area->add_neighbor(forest);
    starting_area->add_neighbor(town);
    
    current_location = starting_area;
    available_quests = 1;
    turn_count = 0;
}

/**
 * @brief Starts the game and initializes variables.
 */
void Game::start_game() {
    current_location->enter_location();
    std::cout << "=== Game Started ===" << std::endl;
    std::cout << "Welcome to the game! You are in the " << current_location->get_name() << "." << std::endl;
    std::cout << "====================" << std::endl;
}

/**
 * @brief Advances the game by increasing the turn count.
 */
void Game::advance_turn() {
    turn_count++;
    std::cout << "=== Turn Advanced ===" << std::endl;
    std::cout << "Current Turn: " << turn_count << std::endl;
    std::cout << "====================" << std::endl;
}

/**
 * @brief Allows the player to interact with the environment.
 */
void Game::interact_with_environment() {
    std::cout << "=== Interacting with Environment ===" << std::endl;
    current_location->display_info();
    std::cout << "===================================" << std::endl;
}

/**
 * @brief Allows the player to move to a neighboring location.
 * @param neighbor_name The name of the neighboring location to move to.
 * @return True if movement is successful, false otherwise.
 */
bool Game::move_to_neighbor(const std::string& neighbor_name) {
    return current_location->move_to_neighbor(neighbor_name);
}

/**
 * @brief Checks if the game has ended based on quest availability.
 */
void Game::check_game_over() {
    if (available_quests <= 0) {
        std::cout << "=== Game Over ===" << std::endl;
        std::cout << "Congratulations! You have completed all quests." << std::endl;
        std::cout << "=================" << std::endl;
    } else {
        std::cout << "Quests remaining: " << available_quests << std::endl;
    }
}
