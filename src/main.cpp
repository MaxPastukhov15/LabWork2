// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#include "Game.hpp"
#include "Characters.hpp"
#include "Quests.hpp"
#include "Thing.hpp"
#include "House.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>
#include <map>

// Function to simulate a fight between the player and an enemy
void fight_enemy(Player& player, Enemy& enemy) {
    std::cout << "\n=== Fight Started ===" << std::endl;
    std::cout << "You are fighting a " << enemy.get_name() << "!" << std::endl;

    while (player.get_health() > 0 && enemy.get_health() > 0) {
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
            case 1: {
                int damage = player.attack(enemy);
                std::cout << "You attack for " << damage << " damage!\n";
                break;
            }
            case 2: {
                player.defend();
                break;
            }
            case 3: {
                std::shared_ptr<Drugs> potion(new Drugs("Health Potion", 20));
                if (player.get_health() < player.get_max_health()) {
                    player.use_item(potion);
                } else {
                    std::cout << "Health already full!\n";
                }
                break;
            }
            case 4: {
                std::cout << "You retreat from battle!\n";
                return;
            }
            default: {
                std::cout << "Invalid choice!\n";
                continue;
            }
        }

        if (enemy.get_health() > 0) {
            enemy.action(player);
            if (enemy.get_health() <= 0) {
                std::cout << "You defeated the enemy!\n";
                enemy.drop_loot(player);
                return;
            }
        }

        std::cout << "\nStatus: HP=" << player.get_health() 
                  << "/" << player.get_max_health()
                  << " ST=" << player.get_stamina()
                  << "/" << player.get_max_stamina() << "\n";
        std::cout << "Enemy: HP=" << enemy.get_health() << "\n";
    }
}

int main() {
    // Initialize the game
    Game game;
    game.start_game();

    // Create a player
    Player player;

    // Create enemies using vector
    std::vector<std::shared_ptr<Enemy>> enemies;
    enemies.push_back(std::shared_ptr<Enemy>(new Goblin(nullptr, "A nasty little Goblin")));
    enemies.push_back(std::shared_ptr<Enemy>(new Skeleton(nullptr, "An ancient Skeleton")));
    
    // Add loot to enemies
    std::shared_ptr<Drugs> gold(new Drugs("Gold Coin", 0));
    enemies[0]->add_loot(gold);
    
    std::shared_ptr<Drugs> bone(new Drugs("Mysterious Bone", 0));
    enemies[1]->add_loot(bone);

    // Create a house with interactive objects using vector
    House player_house;
    std::vector<std::shared_ptr<Thing>> house_objects;
    house_objects.push_back(std::shared_ptr<Thing>(new Bed("Comfy Bed")));
    house_objects.push_back(std::shared_ptr<Thing>(new Chest("Storage Chest")));
    
    std::dynamic_pointer_cast<Chest>(house_objects[1])->put_item(std::shared_ptr<Drugs>(new Drugs("Health Potion", 20)));
    
    for (auto& obj : house_objects) {
        player_house.addThing(obj);
    }

    // Create quests using vector
    std::vector<std::shared_ptr<Quests>> quests;
    quests.push_back(std::shared_ptr<Quests>(new Quests("1", "Goblin Menace", "Defeat the goblin in the forest", "50 Gold")));
    quests.push_back(std::shared_ptr<Quests>(new Quests("2", "Skeleton Key", "Find the ancient skeleton in the cave", "Magic Bone")));
    quests.push_back(std::shared_ptr<Quests>(new Quests("3", "Home Comfort", "Rest in your house", "Full Restore")));

    Menu menu(&player);
    for (auto& quest : quests) {
        menu.add_quest(quest);
    }

    // Start the first quest
    menu.start_quest("1");

    // Game locations
    std::map<std::string, std::vector<std::string>> locations;
    locations["Forest"].push_back("Cave");
    locations["Forest"].push_back("House");
    locations["Cave"].push_back("Forest");
    locations["Cave"].push_back("Graveyard");
    locations["Graveyard"].push_back("Cave");
    locations["House"].push_back("Forest");

    // Available interactions per location
    std::map<std::string, std::vector<std::string>> interactions;
    interactions["Forest"].push_back("Old Tree");
    interactions["Forest"].push_back("Broken Cart");
    interactions["Forest"].push_back("Goblin");
    interactions["Cave"].push_back("Stalactites");
    interactions["Cave"].push_back("Strange Mushrooms");
    interactions["Cave"].push_back("Skeleton");
    interactions["Graveyard"].push_back("Ancient Tombstone");
    interactions["Graveyard"].push_back("Weathered Statue");
    interactions["House"].push_back("Bed");
    interactions["House"].push_back("Chest");

    // Current location
    std::string current_location = "Forest";

    // Game loop
    while (true) {
        std::cout << "\n=== You are in " << current_location << " ===" << std::endl;
        std::cout << "Available interactions: ";
        for (size_t i = 0; i < interactions[current_location].size(); ++i) {
            std::cout << interactions[current_location][i];
            if (i != interactions[current_location].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\nNeighboring locations: ";
        for (size_t i = 0; i < locations[current_location].size(); ++i) {
            std::cout << locations[current_location][i];
            if (i != locations[current_location].size() - 1) {
                std::cout << ", ";
            }
        }

        std::cout << "\n\n=== Game Menu ===" << std::endl;
        std::cout << "1. Interact with object" << std::endl;
        std::cout << "2. Move to new location" << std::endl;
        std::cout << "3. Check Quests" << std::endl;
        std::cout << "4. Visit House" << std::endl;
        std::cout << "5. Exit Game" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Choose object to interact with: ";
                std::string object;
                std::cin.ignore();
                std::getline(std::cin, object);

                if (current_location == "Forest" && object == "Goblin") {
                    fight_enemy(player, *enemies[0]);
                    if (enemies[0]->get_health() <= 0) {
                        quests[0]->complete_quest();
                    }
                } 
                else if (current_location == "Cave" && object == "Skeleton") {
                    fight_enemy(player, *enemies[1]);
                    if (enemies[1]->get_health() <= 0) {
                        quests[1]->complete_quest();
                    }
                }
                else if (current_location == "House") {
                    player_house.interactWithThing(object);
                    if (object == "Bed") {
                        quests[2]->update_progress(100);
                        quests[2]->complete_quest();
                    }
                }
                else {
                    std::cout << "You examine the " << object << " but nothing interesting happens.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Where do you want to go? ";
                std::string new_loc;
                std::cin >> new_loc;
                
                bool found = false;
                for (const auto& loc : locations[current_location]) {
                    if (loc == new_loc) {
                        found = true;
                        break;
                    }
                }
                
                if (found) {
                    current_location = new_loc;
                    std::cout << "You travel to " << new_loc << ".\n";
                } else {
                    std::cout << "You can't go there from here.\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n=== Active Quests ===" << std::endl;
                for (auto& quest : quests) {
                    quest->display_info();
                }
                break;
            }
            case 4: {
                current_location = "House";
                std::cout << "You return to your house.\n";
                break;
            }
            case 5: {
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
