#include "Thing.hpp"
#include "Location.hpp"
#include "Characters.hpp"
#include <iostream>

/**
 * @brief Enters through the door.
 */
void Door::enter() {
    std::cout << "You entered the door." << std::endl;
}

/**
 * @brief Exits through the door.
 */
void Door::exit() {
    std::cout << "You exited through the door." << std::endl;
}

/**
 * @brief Restores the player's stamina and health by sleeping.
 */
void Bed::restore(Player& player) {
    player.restore_hp();
    player.restore_stamina();
    std::cout << "You feel refreshed after sleeping." << std::endl;
}

/**
 * @brief Puts an item into the chest.
 */
void Chest::put_item(std::shared_ptr<Item> item) {
    items.push_back(item);
    std::cout << "Added " << item->get_name() << " to the chest." << std::endl;
}

/**
 * @brief Retrieves an item from the chest.
 */
std::shared_ptr<Item> Chest::retrieve_item(const std::string& item_name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->get_name() == item_name) {
            auto item = *it;
            items.erase(it);
            std::cout << "Retrieved " << item_name << " from the chest." << std::endl;
            return item;
        }
    }
    std::cout << "Item not found in the chest." << std::endl;
    return nullptr;
}

/**
 * @brief Lists all items in the chest.
 */
void Chest::list_items() const {
    for (const auto& item : items) {
        std::cout << "- " << item->get_name() << std::endl;
    }
}

/**
 * @brief Calculates final damage considering armor.
 */
int Damage::calculate_damage(int armor) const {
    int final_damage = damage - (armor / 2);
    return (final_damage > 0) ? final_damage : 1;
}

/**
 * @brief Uses the weapon.
 */
void Weapon::use(Player& player) {
    std::cout << "Using weapon: " << name << std::endl;
}

/**
 * @brief Uses the drug to heal the player.
 */
void Drugs::use(Player& player) {
    player.heal(restore_amount);
    std::cout << "Used " << name << ". Restored " << restore_amount << " HP." << std::endl;
}

/**
 * @brief Uses an artifact.
 */
void Artifact::use(Player& player) {
    std::cout << "Used " << name << ". Effect: " << effect << std::endl;
}

/**
 * @brief Adds an item to inventory.
 */
template<class T>
void Inventory<T>::add_item(std::shared_ptr<T> item) {
    items.push_back(item);
    std::cout << "Added " << item->get_name() << " to inventory." << std::endl;
}

/**
 * @brief Removes an item from inventory.
 */
template<class T>
void Inventory<T>::remove_item(const std::string& item_name) {
    auto it = std::remove_if(items.begin(), items.end(), [&](std::shared_ptr<T> item) {
        return item->get_name() == item_name;
    });

    if (it != items.end()) {
        std::cout << "Removed " << item_name << " from inventory." << std::endl;
        items.erase(it, items.end());
    } else {
        std::cout << item_name << " not found in inventory." << std::endl;
    }
}

/**
 * @brief Lists items in inventory.
 */
template<class T>
void Inventory<T>::list_items() const {
    for (const auto& item : items) {
        std::cout << "Item: " << item->get_name() << std::endl;
    }
}

