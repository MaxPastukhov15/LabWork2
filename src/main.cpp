/**
 * @file main.cpp
 * @brief Main game implementation with combat system and quest management.
 */

#include "Game.hpp"
#include "Characters.hpp"
#include "Quests.hpp"
#include "Thing.hpp"
#include "House.hpp"
#include "Menu.hpp"
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

// Forward declarations
template<typename T>
void fight(Player& player, T& enemy, std::shared_ptr<Quests> quest = nullptr);
void display_encounter_message(const Entity& enemy);
void initialize_game(Game& game, Player& player, Menu& menu);
void display_main_menu();

/**
 * @brief Generic combat function that handles player vs enemy battles
 * @tparam T The enemy type (must inherit from Entity)
 * @param player Reference to the Player object
 * @param enemy Reference to the Enemy object
 * @param quest Optional quest to update upon victory
 */
template<typename T>
void fight(Player& player, T& enemy, std::shared_ptr<Quests> quest) {
    std::cout << "\n=== Fight Started ===" << std::endl;
    display_encounter_message(enemy);

    while (player.get_health() > 0 && enemy.get_health() > 0) {
        // Auto-flee if player is too weak
        if (player.get_health() < 20 || player.get_stamina() < 10) {
            std::cout << "You're too weak! Running away automatically...\n";
            return;
        }

        // Combat menu
        std::cout << "\n=== Combat Menu ===" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Defend" << std::endl;
        std::cout << "3. Use Health Potion" << std::endl;
        std::cout << "4. Run Away" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {  // Attack
                int damage = player.attack(enemy);
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

        // Enemy's turn if still alive
        if (enemy.get_health() > 0) {
            enemy.action(player);
            if (enemy.get_health() <= 0) {
                std::cout << "\nYou defeated the " << typeid(enemy).name() << "!\n";
                enemy.drop_loot(player);
                
                if (quest && !quest->check_completion()) {
                    quest->complete_quest();
                }
                return;
            }
        }

        // Display combat status
        std::cout << "\n=== Status ===" << std::endl;
        std::cout << "Player: HP=" << player.get_health() 
                  << "/" << player.get_max_health()
                  << " ST=" << player.get_stamina()
                  << "/" << player.get_max_stamina() << std::endl;
        std::cout << "Enemy: HP=" << enemy.get_health() << std::endl;
    }
}

/**
 * @brief Displays enemy-specific encounter message
 * @param enemy Reference to the encountered enemy
 */
void display_encounter_message(const Entity& enemy) {
    if (dynamic_cast<const Goblin*>(&enemy)) {
        std::cout << "A nasty goblin jumps out from the bushes!\n";
    } 
    else if (dynamic_cast<const Skeleton*>(&enemy)) {
        std::cout << "Bones rattle as an ancient skeleton rises from the ground!\n";
    } 
    else if (dynamic_cast<const Boss*>(&enemy)) {
        std::cout << "The ground shakes as the mighty boss appears!\n";
    }
    std::cout << "Prepare for battle!\n";
}

/**
 * @brief Initializes game objects and quests
 * @param game Reference to the Game object
 * @param player Reference to the Player object
 * @param menu Reference to the Menu object
 */
void initialize_game(Game& game, Player& player, Menu& menu) {
    game.start_game();
    
    // Create quests
    auto goblinQuest = std::make_shared<Quests>(
        "Q1", 
        "Goblin Extermination", 
        "Defeat 3 goblins in the forest",
        "100 Gold"
    );
    
    auto skeletonQuest = std::make_shared<Quests>(
        "Q2", 
        "Ancient Bones", 
        "Defeat the skeleton warrior in the crypt",
        "Mystic Bone"
    );
    
    auto bossQuest = std::make_shared<Quests>(
        "Q3", 
        "Final Challenge", 
        "Defeat the Dragon Lord",
        "Dragon Artifact and 500 Gold"
    );

    // Add quests to menu
    menu.add_quest(goblinQuest);
    menu.add_quest(skeletonQuest);
    menu.add_quest(bossQuest);
    
    // Start initial quest
    menu.start_quest("Q1");
}

/**
 * @brief Displays the main game menu
 */
void display_main_menu() {
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. Forest (Goblins)" << std::endl;
    std::cout << "2. Crypt (Skeletons)" << std::endl;
    std::cout << "3. Dragon's Lair (Boss)" << std::endl;
    std::cout << "4. View Quests" << std::endl;
    std::cout << "5. Player Status" << std::endl;
    std::cout << "6. Exit Game" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    // Initialize game systems
    Game game;
    Player player;  // Using default constructor
    Menu menu(&player);
    
    // Create enemies
    Goblin goblin1(nullptr, "Green Goblin");
    Goblin goblin2(nullptr, "Red Goblin");
    Goblin goblin3(nullptr, "Goblin Chief");
    
    Skeleton skeleton(nullptr, "Ancient Skeleton");
    Boss boss(nullptr, "Dragon Lord");
    
    // Add loot to enemies
    auto gold = std::make_shared<Drugs>("Gold", 0);
    auto potion = std::make_shared<Drugs>("Health Potion", 20);
    auto bone = std::make_shared<Drugs>("Mystic Bone", 0);
    auto artifact = std::make_shared<Drugs>("Dragon Artifact", 0);
    
    goblin1.add_loot(gold);
    goblin2.add_loot(potion);
    goblin3.add_loot(gold);
    skeleton.add_loot(bone);
    boss.add_loot(artifact);
    
    // Initialize game state
    initialize_game(game, player, menu);
    
    // Game loop
    bool running = true;
    int goblinsDefeated = 0;
    
    while (running && player.get_health() > 0) {
        display_main_menu();
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {  // Forest - Goblins
                Goblin* currentGoblin = nullptr;
                if (goblinsDefeated == 0) currentGoblin = &goblin1;
                else if (goblinsDefeated == 1) currentGoblin = &goblin2;
                else currentGoblin = &goblin3;
                
                fight(player, *currentGoblin, nullptr);  // Removed quest parameter
                if (currentGoblin->get_health() <= 0) {
                    goblinsDefeated++;
                    if (goblinsDefeated >= 3) {
                        menu.update_quest_progress("Q1", 100);
                    }
                }
                break;
            }
            case 2: {  // Crypt - Skeleton
                fight(player, skeleton, nullptr);  // Removed quest parameter
                break;
            }
            case 3: {  // Boss
                // Simplified boss fight without quest dependency
                fight(player, boss, nullptr);  // Removed quest parameter
                break;
            }
            case 4: {  // View Quests
                // Removed quest display since we don't have get_quests()
                std::cout << "Quest feature not fully implemented yet.\n";
                break;
            }
            case 5: {  // Player Status
                std::cout << "\n=== Player Status ===" << std::endl;
                std::cout << "HP: " << player.get_health() 
                          << "/" << player.get_max_health() << std::endl;
                std::cout << "Stamina: " << player.get_stamina()
                          << "/" << player.get_max_stamina() << std::endl;
                break;
            }
            case 6: {  // Exit
                running = false;
                std::cout << "Thanks for playing!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice!\n";
                break;
            }
        }
        
        // Advance game state
        game.advance_turn();
        // Removed stamina recovery since the method doesn't exist
    }
    
    if (player.get_health() <= 0) {
        std::cout << "\n=== GAME OVER ===\n";
        std::cout << "You have been defeated...\n";
    }
    
    return 0;
}
