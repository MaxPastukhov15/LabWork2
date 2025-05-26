// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#include "Characters.hpp"
#include "Thing.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>

/**
 * @brief Generates a random number (0 or 1).
 * @return Random integer (0 or 1).
 */
int GetRNum() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(0, 1);
    return distrib(gen); 
}

/// Entity class implementation

/**
 * @brief Reduces the entity's health by the specified damage amount.
 * @param amount The amount of damage to take.
 * @return The entity's current health after taking damage.
 */
int Entity::take_damage(int amount) {
    current_hp -= amount;
    if (current_hp < 0) current_hp = 0;
    return current_hp;
}

/**
 * @brief Attacks a target entity.
 * @param target The entity to attack.
 * @return The total damage dealt.
 */
int Entity::attack(Entity& target) {
    if (current_stamina <= 0) {
        std::cout << "Not enough stamina to attack!\n";
        return 0;
    }
    int total_damage = base_damage;
    target.take_damage(total_damage);
    current_stamina -= 10;
    return total_damage;
}

/**
 * @brief Puts the entity in a defensive stance, increasing HP.
 */
void Entity::defend() {
    is_defending = true;
    current_stamina -= 5;
    current_hp += defense; 
    std::cout << "Bracing for impact!\n";
}

/// Player class implementation

/**
 * @brief Uses an item from the player's inventory.
 * @param item The item to use.
 */
void Player::use_item(std::shared_ptr<Item> item) {
    item->use(*this);
}

/**
 * @brief Equips a weapon to the player.
 * @param weapon The weapon to equip.
 */
void Player::equip_weapon(Weapon* weapon) {
    equipped_weapon = weapon;
    std::cout << "Equipped weapon: " << weapon->get_name() << std::endl;
}

/**
 * @brief Equips a shield to the player.
 * @param shield The shield to equip.
 */
void Player::equip_shield(Shield* shield) {
    equipped_shield = shield;
    defense += shield->get_defense();
    std::cout << "Equipped shield: " << shield->get_name() << std::endl;
}

/**
 * @brief Puts the player in a defensive stance with shield bonus if equipped.
 */
void Player::defend() {
    if (current_stamina >= 5) {
        Entity::defend();
        if (equipped_shield) {
            defense += equipped_shield->get_defense();
            std::cout << "Shield boosts your defense!\n";
        }
    } else {
        std::cout << "Not enough stamina to defend!\n";
    }
}

/**
 * @brief Adds an item to the player's inventory.
 * @param item The item to add.
 */
void Player::add_to_inventory(std::shared_ptr<Item> item) {
    inventory.push_back(item);
    std::cout << "Added " << item->get_name() << " to inventory.\n";
}

/// Enemy class implementation

/**
 * @brief Performs a random action (attack, defend, or flee) against the player.
 * @param player The player to target.
 */
void Enemy::action(Player& player) {
    int act = GetRNum();  ///< 0=attack, 1=defend
    switch (act) {
        case 0:  // Attack
            if (current_stamina >= 10) {
                this->attack(player);
                std::cout << "Enemy attacks you!\n";
            } else {
                std::cout << "Enemy is too tired to attack!\n";
            }
            break;
        case 1:  // Defend
            if (current_stamina >= 5) {
                this->defend();
                std::cout << "Enemy raises its guard!\n";
            }
            break;
        default:  // Flee
            if (player.get_health() > this->get_health() * 2 || 
                player.get_stamina() > 30) {
                std::cout << "Enemy flees in terror!\n";
                this->take_damage(this->get_health());
            } else {
                this->attack(player);
            }
            break;
    }
}

/**
 * @brief Drops loot for the player to collect.
 * @param player The player who receives the loot.
 */
void Enemy::drop_loot(Player& player) {
    if (!loot.empty()) {
        for (const auto& item : loot) {
            player.add_to_inventory(item);
            std::cout << "Enemy dropped: " << item->get_name() << std::endl;
        }
    } else {
        std::cout << "Enemy dropped nothing!\n";
    }
}

/**
 * @brief Adds an item to the enemy's loot table.
 * @param item The item to add.
 */
void Enemy::add_loot(std::shared_ptr<Item> item) {
    loot.push_back(item);
}

/// Specific enemy implementations

/**
 * @brief Displays Goblin's current health and stamina.
 */
void Goblin::display_info() {
    std::cout << "Goblin: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}

/**
 * @brief Displays Skeleton's current health and stamina.
 */
void Skeleton::display_info() {
    std::cout << "Skeleton: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}

/**
 * @brief Displays Boss's current health and stamina.
 */
void Boss::display_info() {
    std::cout << "Boss: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}
