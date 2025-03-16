#include "Game.hpp"
#include "Characters.hpp"
#include "Quests.hpp"
#include "Thing.hpp"
#include "House.hpp"
#include "Menu.hpp"
#include <iostream>

// Function to simulate a fight between the player and a Goblin
void fight_goblin(Player& player, Goblin& goblin) {
    std::cout << "\n=== Fight Started ===" << std::endl;
    std::cout << "You are fighting a Goblin!" << std::endl;

    while (player.get_health() > 0 && goblin.get_health() > 0) {
        std::cout << "\n=== Combat Menu ===" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Use Health Potion" << std::endl;
        std::cout << "3. Run Away" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Player attacks the Goblin
                int damage = player.attack(goblin);
                std::cout << "You attacked the Goblin for " << damage << " damage!" << std::endl;
                if (goblin.get_health() <= 0) {
                    std::cout << "You defeated the Goblin!" << std::endl;
                    return;
                }
                break;
            }
            case 2: {
                // Player uses a health potion
                auto potion = std::make_shared<Drugs>("Health Potion", 20);
                if (player.get_health() < 100) {
                    player.use_item(potion);
                    std::cout << "You used a Health Potion and restored 20 HP." << std::endl;
                } else {
                    std::cout << "Your health is already full!" << std::endl;
                }
                break;
            }
            case 3: {
                // Player runs away
                std::cout << "You ran away from the fight!" << std::endl;
                return;
            }
            default: {
                std::cout << "Invalid choice. Try again!" << std::endl;
                break;
            }
        }

        // Goblin attacks the player
        if (goblin.get_health() > 0) {
            int damage = goblin.attack(player);
            std::cout << "The Goblin attacked you for " << damage << " damage!" << std::endl;
            if (player.get_health() <= 0) {
                std::cout << "You were defeated by the Goblin!" << std::endl;
                return;
            }
        }
    }
}

int main() {
    // Initialize the game
    Game game;
    game.start_game();

    // Create a player
    Player player;

    // Create a Goblin enemy
    Goblin goblin(nullptr, "A nasty little Goblin");

    // Create a quest
    auto quest = std::make_shared<Quests>("1", "Defeat the Goblin", "Defeat the goblin in the forest", "Gold and Experience");
    Menu menu(&player);
    menu.add_quest(quest);

    // Start the quest
    menu.start_quest("1");

    // Simulate game loop
    int choice;
    while (true) {
        std::cout << "\n=== Game Menu ===" << std::endl;
        std::cout << "1. Explore Location" << std::endl;
        std::cout << "2. Interact with Environment" << std::endl;
        std::cout << "3. Check Quests" << std::endl;
        std::cout << "4. Move to Neighbor Location" << std::endl;
        std::cout << "5. Fight Goblin" << std::endl;
        std::cout << "6. Exit Game" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Explore the current location
                game.interact_with_environment();
                break;
            }
            case 2: {
                // Interact with an object in the location
                std::string object_name;
                std::cout << "Enter the name of the object to interact with: ";
                std::cin >> object_name;
                // Simulate interaction (e.g., opening a chest)
                if (object_name == "chest") {
                    auto chest = std::make_shared<Chest>("Treasure Chest");
                    auto potion = std::make_shared<Drugs>("Health Potion", 20);
                    chest->put_item(potion);
                    chest->interact();
                    auto item = chest->retrieve_item("Health Potion");
                    if (item) {
                        player.add_to_inventory(item);
                    }
                } else {
                    std::cout << "No such object in the location." << std::endl;
                }
                break;
            }
            case 3: {
                // Check quests
                quest->display_info();
                if (!quest->check_completion()) {
                    std::cout << "Updating quest progress..." << std::endl;
                    menu.update_quest_progress("1", 50); // Simulate progress
                    menu.update_quest_progress("1", 50); // Complete the quest
                }
                break;
            }
            case 4: {
                // Move to a neighboring location
                std::string neighbor_name;
                std::cout << "Enter the name of the neighboring location to move to: ";
                std::cin >> neighbor_name;
                if (!game.move_to_neighbor(neighbor_name)) {
                    std::cout << "Failed to move to " << neighbor_name << "." << std::endl;
                }
                break;
            }
            case 5: {
                // Fight the Goblin
                fight_goblin(player, goblin);
                if (goblin.get_health() <= 0) {
                    quest->complete_quest();
                    std::cout << "Quest completed: Defeat the Goblin" << std::endl;
                }
                break;
            }
            case 6: {
                // Exit the game
                std::cout << "Exiting the game. Goodbye!" << std::endl;
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }

        // Advance the game turn
        game.advance_turn();
    }

    return 0;
}
