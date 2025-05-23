// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <memory>
#include "Characters.hpp"
#include "Quests.hpp"

/**
 * @class Menu
 * @brief Handles game menu navigation and player interactions.
 */
class Menu {
private:
    std::string options;        ///< String containing the menu options.
    int current_selection;      ///< Currently selected menu option.
    Player* player;             ///< Pointer to the player for stamina and health management.
    std::vector<std::shared_ptr<Quests>> quests; ///< List of active quests for the player.

public:
    /**
     * @brief Constructs a Menu object.
     * @param player Pointer to the player object.
     * @param opts String containing menu options (default provided).
     */
    Menu(Player* player, const std::string& opts = "1. Inventory\n2. Quests\n3. Status\n4. Exit")
        : options(opts), current_selection(0), player(player) {}

    /**
     * @brief Displays the menu options.
     */
    void display_menu() {
        std::cout << options << std::endl;
    }

    /**
     * @brief Selects a menu option.
     * @param index The index of the option to select.
     * @return The selected index.
     */
    int select_option(int index) {
        current_selection = index;
        return current_selection;
    }

    /**
     * @brief Opens the inventory menu.
     */
    void open_inventory() {
        std::cout << "Opening inventory..." << std::endl;
    }

    /**
     * @brief Opens the quest log.
     */
    void open_quests() {
        std::cout << "Opening quest log..." << std::endl;
    }

    /**
     * @brief Displays the player's current health and stamina.
     */
    void show_player_status() {
        std::cout << "Player HP: " << player->get_health() << ", Stamina: " << player->get_stamina() << std::endl;
    }

    /**
     * @brief Exits the game.
     */
    void exit_game() {
        std::cout << "Exiting game..." << std::endl;
    }

    /**
     * @brief Handles menu input selection.
     * @param index The selected menu index.
     * @return The selected index.
     */
    int handle_input(int index) {
        return select_option(index);
    }

    /**
     * @brief Checks if the player has stamina remaining.
     * @return True if stamina > 0, false otherwise.
     */
    bool check_stamina() {
        return player->get_stamina() > 0;
    }

    /**
     * @brief Adds a quest to the player's quest log.
     * @param quest The quest to add.
     */
    void add_quest(std::shared_ptr<Quests> quest) {
        quests.push_back(quest);
    }

    /**
     * @brief Starts a quest if not already completed.
     * @param quest_id The ID of the quest to start.
     */
    void start_quest(const std::string& quest_id) {
        for (auto& quest : quests) {
            if (quest->get_id() == quest_id && !quest->check_completion()) {
                quest->start_quest();
                std::cout << "Started quest: " << quest->get_name() << std::endl;
                return;
            }
        }
        std::cout << "Quest not found or already completed!" << std::endl;
    }

    /**
     * @brief Updates progress for a specific quest.
     * @param quest_id The ID of the quest to update.
     * @param progress_increase The amount to increase progress by.
     */
    void update_quest_progress(const std::string& quest_id, int progress_increase) {
        for (auto& quest : quests) {
            if (quest->get_id() == quest_id) {
                quest->update_progress(progress_increase);
                return;
            }
        }
        std::cout << "Quest not found!" << std::endl;
    }

    /**
     * @brief Completes a quest if requirements are met.
     * @param quest_id The ID of the quest to complete.
     */
    void complete_quest(const std::string& quest_id) {
        for (auto& quest : quests) {
            if (quest->get_id() == quest_id && quest->check_completion()) {
                quest->complete_quest();
                std::cout << "Quest completed: " << quest->get_name() << std::endl;
                return;
            }
        }
        std::cout << "Quest not found or not completed!" << std::endl;
    }
};

#endif
