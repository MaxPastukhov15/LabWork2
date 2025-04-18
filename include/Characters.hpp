#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "Thing.hpp"
// Forward declarations
class Item;
class Weapon;
class Shield;

/**
 * @class Entity
 * @brief Base class for all game entities.
 */
class Entity {
protected:
    int max_hp;
    int current_hp;
    int max_stamina;
    int current_stamina;
    int base_damage;
    int defense;         
    bool is_defending;
public:
    Entity(int hp = 100, int stamina = 150, int dmg = 10, int def = 5)
        : max_hp(hp), current_hp(hp), max_stamina(stamina),current_stamina(stamina), base_damage(dmg), defense(def),is_defending(false) {}

    virtual int take_damage(int amount);

    virtual int attack(Entity& target);
    
    virtual void defend();
    
    int get_health() const { return current_hp; }
    
    int get_max_health() const { return max_hp; }
       
    int get_max_stamina() const { return max_stamina; }
};

/**
 * @class Player
 * @brief Represents the player character.
 */
class Player : public Entity {
    std::vector<std::shared_ptr<Item>> inventory;
    Weapon* equipped_weapon;
    Shield* equipped_shield;
    friend class Bed;

public:
    Player() : Entity(100, 50, 10), equipped_weapon(nullptr), equipped_shield(nullptr) {}

    void use_item(std::shared_ptr<Item> item);

    void equip_weapon(Weapon* weapon);

    void equip_shield(Shield* shield);
    
    void defend() override;

    void restore_hp() {
        current_hp = max_hp;
        std::cout << "HP restored to " << current_hp << std::endl;
    }

    void restore_stamina() {
        current_stamina = max_stamina;
        std::cout << "Stamina restored to " << current_stamina << std::endl;
    }

    void heal(int amount) {
        current_hp += amount;
        if (current_hp > max_hp) current_hp = max_hp;
        std::cout << "Healed " << amount << " HP. Current HP: " << current_hp << std::endl;
    }

    void add_to_inventory(std::shared_ptr<Item> item);

    
    int get_stamina() const { return current_stamina; }
    
    
};

/**
 * @class Enemy
 * @brief Base class for enemies.
 */
class Enemy : public Entity {
protected:
    std::vector<std::shared_ptr<Item>> loot;

public:
    Enemy(int hp, int stamina, int dmg) : Entity(hp, stamina, dmg) {}
    
    void action(Player& player);
    void drop_loot(Player& player);
    void add_loot(std::shared_ptr<Item> item); 
};

/**
 * @class Goblin
 */
class Goblin : public Enemy {
    Weapon* weapon;
    std::string info;

public:
    Goblin(Weapon* weapon, const std::string& info)
        : Enemy(20, 20, 5), weapon(weapon), info(info) {}

    void display_info();
     
};

/**
 * @class Skeleton
 */
class Skeleton : public Enemy {
    Weapon* weapon;
    std::string info;

public:
    Skeleton(Weapon* weapon, const std::string& info)
        : Enemy(70, 30, 7), weapon(weapon), info(info) {}

    void display_info();
    
};

/**
 * @class Boss
 */
class Boss : public Enemy {
    Weapon* weapon;
    std::string info;

public:
    Boss(Weapon* weapon, const std::string& info)
        : Enemy(150, 50, 15), weapon(weapon), info(info) {}

    Boss(Boss& obj) = delete;
    void display_info();
    
};

#endif // CHARACTERS_HPP
