#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <memory>
#include "Characters.hpp"
#include "Quests.hpp"

class Menu {
private:
    std::string options;        ///< String containing the menu options.
    int current_selection;      ///< Currently selected menu option.
    Player* player;             ///< Pointer to the player for stamina and health management.
    std::vector<std::shared_ptr<Quests>> quests; ///< List of active quests for the player.

public:
    Menu(Player* player, const std::string& opts = "1. Inventory\n2. Quests\n3. Status\n4. Exit")
        : options(opts), current_selection(0), player(player) {}

    void display_menu() {
        std::cout << options << std::endl;
    }

    int select_option(int index) {
        current_selection = index;
        return current_selection;
    }

    void open_inventory() {
        std::cout << "Opening inventory..." << std::endl;
    }

    void open_quests() {
        std::cout << "Opening quest log..." << std::endl;
    }

    void show_player_status() {
        std::cout << "Player HP: " << player->get_health() << ", Stamina: " << player->get_stamina() << std::endl;
    }

    void exit_game() {
        std::cout << "Exiting game..." << std::endl;
    }

    int handle_input(int index) {
        return select_option(index);
    }

    bool check_stamina() {
        return player->get_stamina() > 0;
    }

    void add_quest(std::shared_ptr<Quests> quest) {
        quests.push_back(quest);
    }

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

    void update_quest_progress(const std::string& quest_id, int progress_increase) {
        for (auto& quest : quests) {
            if (quest->get_id() == quest_id) {
                quest->update_progress(progress_increase);
                return;
            }
        }
        std::cout << "Quest not found!" << std::endl;
    }

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
