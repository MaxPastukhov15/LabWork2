// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Location.hpp"

/**
 * @class Game
 * @brief Represents the main game class, tracking progress and managing the game loop.
 * 
 * The Game class manages the player’s current location and allows for interaction with the environment,
 * advancement of turns, and checking the game's progress, including moving between locations.
 */
class Game {
private:
    Location* current_location; ///< The current location of the player.
    int available_quests;       ///< The number of available quests in the game.
    int turn_count;             ///< The current turn count.

public:
    /**
     * @brief Constructs a new Game instance.
     */
    Game();

    /**
     * @brief Starts the game and initializes variables.
     */
    void start_game();

    /**
     * @brief Advances the game by increasing the turn count.
     */
    void advance_turn();

    /**
     * @brief Allows the player to interact with the environment.
     */
    void interact_with_environment();

    /**
     * @brief Allows the player to move to a neighboring location.
     * @param neighbor_name The name of the neighboring location to move to.
     * @return True if movement is successful, false otherwise.
     */
    bool move_to_neighbor(const std::string& neighbor_name);

    /**
     * @brief Checks if the game has ended based on quest availability.
     */
    void check_game_over();
};

#endif

