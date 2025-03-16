#ifndef THING_HPP
#define THING_HPP

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

// Forward declarations
class Player;
class Item;

/**
 * @class Thing
 * @brief Base class for all interactive objects in the game.
 */
class Thing {
protected:
    std::string thing; ///< Name of the thing.
public:
    explicit Thing(const std::string& name) : thing(name) {}
    virtual ~Thing() = default;
    virtual std::string get_name() const { return thing; }
    virtual void interact() = 0;  // Pure virtual function
};

/**
 * @class Door
 * @brief Represents a door that the player can enter or exit.
 */
class Door : public Thing {
public:
    explicit Door(const std::string& name) : Thing(name) {}
    void enter();
    void exit();
    void interact() override {
        std::cout << "You see a door labeled " << thing << "." << std::endl;
    }
};

/**
 * @class Bed
 * @brief Represents a bed that the player can use to restore stamina and HP.
 */
class Bed : public Thing {
public:
    explicit Bed(const std::string& name) : Thing(name) {}
    void restore(Player& player);
    void interact() override {
        std::cout << "A comfortable-looking bed is here." << std::endl;
    }
};

/**
 * @class Item
 * @brief Base class for all items.
 */
class Item {
protected:
    std::string name;
public:
    explicit Item(const std::string& name): name(name) {}
    virtual ~Item() = default;
    virtual void use(Player& player) = 0;
    virtual std::string get_name() const { return name; }
};

/**
 * @class Chest
 * @brief Represents a chest that stores items.
 */
class Chest : public Thing {
private:
    std::vector<std::shared_ptr<Item>> items; ///< List of items.
public:
    explicit Chest(const std::string& name) : Thing(name) {}

    void put_item(std::shared_ptr<Item> item);
    std::shared_ptr<Item> retrieve_item(const std::string& item_name);
    void list_items() const;
    void interact() override {
        std::cout << "You see a chest labeled " << get_name() << ". Maybe there's something inside?" << std::endl;
    }
};

/**
 * @class Damage
 * @brief Handles damage mechanics.
 */
class Damage {
protected:
    int damage;
public:
    explicit Damage(int dmg) : damage(dmg) {}
    virtual int calculate_damage(int armor) const;
};

/**
 * @class Weapon
 * @brief Represents a weapon.
 */
class Weapon : public Item {
private:
    int damage;
public:
    Weapon(const std::string& name, int dmg) : Item(name), damage(dmg) {}
    void use(Player& player) override;
    int get_damage() const { return damage; }
    std::string get_name() const { return name; }
};

/**
 * @class Drugs
 * @brief Represents a healing item.
 */
class Drugs : public Item {
private:
    int restore_amount;
public:
    Drugs(const std::string& name, int amount) : Item(name), restore_amount(amount) {}
    void use(Player& player) override;
};

/**
 * @class Artifact
 * @brief Special game item.
 */
class Artifact : public Item {
private:
    std::string effect;
public:
    Artifact(const std::string& name, const std::string& effect) : Item(name), effect(effect) {}
    void use(Player& player) override;
};

/**
 * @class Shield
 * @brief Represents a shield for defense.
 */
class Shield : public Item {
private:
    int defense_value;
public:
    explicit Shield(const std::string& name, int defense) : Item(name), defense_value(defense) {}
    int get_defense() const { return defense_value; }
    std::string get_name() const  {return name;}
};

/**
 * @class Inventory
 * @brief Manages player items.
 */
template<class T>
class Inventory {
private:
    std::vector<std::shared_ptr<T>> items;
public:
    void add_item(std::shared_ptr<T> item);
    void remove_item(const std::string& item_name);
    void list_items() const;
};

#endif // THING_HPP
