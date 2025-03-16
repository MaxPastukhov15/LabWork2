#include "Characters.hpp"
#include "Thing.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

void Player::use_item(std::shared_ptr<Item> item) {
    item->use(*this);
}

void Player::equip_weapon(Weapon* weapon) {
    equipped_weapon = weapon;
    std::cout << "Equipped weapon: " << weapon->get_name() << std::endl;
}

void Player::equip_shield(Shield* shield) {
    equipped_shield = shield;
    std::cout << "Equipped shield: " << shield->get_name() << std::endl;
}

void Player::add_to_inventory(std::shared_ptr<Item> item) {
    inventory.push_back(item);
    std::cout << "Added " << item->get_name() << " to inventory.\n";
}

void Enemy::drop_loot(Player& player) {
    for (const auto& item : loot) {
        player.add_to_inventory(item);
    }
    std::cout << "Enemy dropped loot!\n";
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
