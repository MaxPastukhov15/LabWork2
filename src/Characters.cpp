#include "Characters.hpp"
#include "Thing.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>


void Player::use_item(std::shared_ptr<Item> item) {
    item->use(*this);
}

void Player::equip_weapon(Weapon* weapon) {
    equipped_weapon = weapon;
    std::cout << "Equipped weapon: " << weapon->get_name() << std::endl;
}

void Player::equip_shield(Shield* shield) {
    equipped_shield = shield;
    defense += shield->get_defense(); // Add shield defense to base
    std::cout << "Equipped shield: " << shield->get_name() << std::endl;
}

void Player::add_to_inventory(std::shared_ptr<Item> item) {
    inventory.push_back(item);
    std::cout << "Added " << item->get_name() << " to inventory.\n";
}

void Enemy::action(Player& player) {
    int act = rand() % 2;  // 0=attack, 1=defend
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
        default:  // Special or flee
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

void Enemy::add_loot(std::shared_ptr<Item> item) {
    loot.push_back(item);
}

void Goblin::display_info() {
    std::cout << "Goblin: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}

void Skeleton::display_info() {
    std::cout << "Skeleton: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}

void Boss::display_info() {
    std::cout << "Boss: HP=" << current_hp << ", Stamina=" << current_stamina << std::endl;
}
