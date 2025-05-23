// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
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
        // Auto-flee if conditions are met
        if (player.get_health() < 20 || player.get_stamina() < 10) {
            std::cout << "You're too weak! Running away automatically...\n";
            return;
        }

        std::cout << "\n=== Combat Menu ===" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Defend" << std::endl;
        std::cout << "3. Use Item" << std::endl;
        std::cout << "4. Run Away" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {  // Attack
                int damage = player.attack(goblin);
                std::cout << "You attack for " << damage << " damage!\n";
                break;
            }
            case 2: {  // Defend
                player.defend();
                break;
            }
            case 3: {  // Use Item
                auto potion = std::make_shared<Drugs>("Health Potion", 20);
                if (player.get_health() < player.get_max_health()) {
                    player.use_item(potion);
                } else {
                    std::cout << "Health already full!\n";
                }
                break;
            }
            case 4: {  // Run
                std::cout << "You retreat from battle!\n";
                return;
            }
            default: {
                std::cout << "Invalid choice!\n";
                continue;
            }
        }

        // Enemy turn if still alive
        if (goblin.get_health() > 0) {
            goblin.action(player);
            if (goblin.get_health() <= 0) {
                std::cout << "You defeated the Goblin!\n";
                goblin.drop_loot(player);
                return;
            }
        }

        // Display status
        std::cout << "\nStatus: HP=" << player.get_health() 
                  << "/" << player.get_max_health()
                  << " ST=" << player.get_stamina()
                  << "/" << player.get_max_stamina() << "\n";
        std::cout << "Goblin: HP=" << goblin.get_health() << "\n";
    }
}

int main() {
    // Initialize the game
    Game game;
    game.start_game();

    // Create a player
    Player player;

   // Create a Goblin enemy with some loot
   Goblin goblin(nullptr, "A nasty little Goblin");
   auto gold = std::make_shared<Drugs>("Gold Coin", 0); // 0 healing since it's gold
   goblin.add_loot(gold);
   
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
