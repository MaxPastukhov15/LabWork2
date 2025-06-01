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
#include <limits>
#include <algorithm>

// Template function to fight any enemy type
template<typename EnemyType>
void fight_enemy(Player& player, EnemyType& enemy) {
    std::cout << "\n=== Fight Started ===" << std::endl;
    enemy.display_info();

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
        while(!(std::cin >> choice) || choice < 1 || choice > 4){
        	std::cin.clear();
        	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        	std::cout << "Invalid choice! Please enter a number 1 and 4\n";
        }

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
                enemy.display_info();
                enemy.drop_loot(player);
                return;
            }
        }

        std::cout << "\nStatus: HP=" << player.get_health() 
                  << "/" << player.get_max_health()
                  << " ST=" << player.get_stamina()
                  << "/" << player.get_max_stamina() << "\n";
        std::cout << "Enemy HP=" << enemy.get_health() << "\n";
    }
}

int main() {
    // Initialize the game
    Game game;
    game.start_game();

    // Create a player
    Player player;

    // Create specific enemy types
    Goblin goblin(nullptr, "A nasty little Goblin");
    Skeleton skeleton(nullptr, "An ancient Skeleton");

    // Add loot to enemies
    std::shared_ptr<Drugs> gold(new Drugs("Gold Coin", 0));
    goblin.add_loot(gold);
    
    std::shared_ptr<Drugs> bone(new Drugs("Mysterious Bone", 0));
    skeleton.add_loot(bone);

    // Create a house with interactive objects
    House player_house;
    auto house_bed = std::make_shared<Bed>("Comfy Bed");
    auto house_chest = std::make_shared<Chest>("Storage Chest");
    house_chest->put_item(std::make_shared<Drugs>("Health Potion", 20));
    player_house.addThing(house_bed);
    player_house.addThing(house_chest);

    // Create quests
    auto quest1 = std::make_shared<Quests>("1", "Goblin Menace", "Defeat the goblin in the forest", "50 Gold");
    auto quest2 = std::make_shared<Quests>("2", "Skeleton Key", "Find the ancient skeleton in the cave", "Magic Bone");
    auto quest3 = std::make_shared<Quests>("3", "Home Comfort", "Rest in your house", "Full Restore");

    Menu menu(&player);
    menu.add_quest(quest1);
    menu.add_quest(quest2);
    menu.add_quest(quest3);

    // Start the first quest
    menu.start_quest("1");

    // Game locations
    std::map<std::string, std::vector<std::string>> locations = {
        {"Forest", {"Cave", "House"}},
        {"Cave", {"Forest", "Graveyard"}},
        {"Graveyard", {"Cave"}},
        {"House", {"Forest"}}
    };

    // Available interactions per location
    std::map<std::string, std::vector<std::string>> interactions = {
        {"Forest", {"Old Tree", "Broken Cart", "Goblin"}},
        {"Cave", {"Stalactites", "Strange Mushrooms", "Skeleton"}},
        {"Graveyard", {"Ancient Tombstone", "Weathered Statue"}},
        {"House", {"Bed", "Chest"}}
    };

    // Current location
    std::string current_location = "Forest";
    
    
    // Game loop
    while (true) {
        std::cout << "\n=== You are in " << current_location << " ===" << std::endl;
        std::cout << "Available interactions: ";
        for (const auto& item : interactions[current_location]) {
            std::cout << item << ", ";
        }
        std::cout << "\nNeighboring locations: ";
        for (const auto& loc : locations[current_location]) {
            std::cout << loc << ", ";
        }

        std::cout << "\n\n=== Game Menu ===" << std::endl;
        std::cout << "1. Interact with object" << std::endl;
        std::cout << "2. Move to new location" << std::endl;
        std::cout << "3. Check Quests" << std::endl;
        std::cout << "4. Visit House" << std::endl;
        std::cout << "5. Exit Game" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        while(!(std::cin >> choice) || choice < 1 || choice > 5){
        	std::cin.clear();
        	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        	std::cout << "Invalid choice! Please enter a number 1 and 5\n";
        }
        
        switch (choice) {
            case 1:{ 
                std::cout << "Choose object to interact with: ";
                std::string object;
                std::cin.ignore();
                std::getline(std::cin, object);

                if (current_location == "Forest" && object == "Goblin") {
                    fight_enemy<Goblin>(player, goblin);
                    if (goblin.get_health() <= 0) {
                        quest1->complete_quest();
                    }
                } 
                else if (current_location == "Cave" && object == "Skeleton") {
                    fight_enemy<Skeleton>(player, skeleton);
                    if (skeleton.get_health() <= 0) {
                        quest2->complete_quest();
                    }
                }
                else if (current_location == "House") {
                    player_house.interactWithThing(object);
                    if (object == "Bed") {
                    	house_bed->restore(player);
                        quest3->update_progress(100);
                        quest3->complete_quest();
                    }
                }
                
                else {
                    std::cout << "You examine the " << object << " but nothing interesting happens.\n";
                }
                break;
            }
            case 2:{ 
                std::cout << "Where do you want to go? ";
                std::string new_loc;
                std::cin >> new_loc;
                
                if (std::find(locations[current_location].begin(), 
                             locations[current_location].end(), new_loc) != locations[current_location].end()) {
                    current_location = new_loc;
                    std::cout << "You travel to " << new_loc << ".\n";
                } else {
                    std::cout << "You can't go there from here.\n";
                }
                break;
            }
            case 3:{ 
                std::cout << "\n=== Active Quests ===" << std::endl;
                quest1->display_info();
                quest2->display_info();
                quest3->display_info();
                break;
            }
            case 4:{ 
                current_location = "House";
                std::cout << "You return to your house.\n";
                break;
            }
            case 5:{ 
                std::cout << "Exiting the game. Goodbye!" << std::endl;
                return 0;
            }
            default: 
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            
        }

        // Advance the game turn
        game.advance_turn();
    }

    return 0;
}
