#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <string>
#include <vector>
#include <memory>
#include "Thing.hpp"
#include "Menu.hpp"

class House {
private:
    std::vector<std::shared_ptr<Thing>> things;  ///< List of things (objects) in the house.

public:
    /**
     * @brief Adds an interactive object (thing) to the house.
     * @param thing The object to add.
     */
    void addThing(std::shared_ptr<Thing> thing) {
        things.push_back(thing);
    }

    /**
     * @brief Retrieves a chest object by its index in the house.
     * @param index The index of the chest.
     * @return A shared pointer to the chest object, or nullptr if not found.
     */
    std::shared_ptr<Chest> getChest(int index) {
        if (index >= 0 && static_cast<size_t>(index) < things.size()) {
            return std::dynamic_pointer_cast<Chest>(things[index]);
        }
        return nullptr;
    }

    /**
     * @brief Lists all objects in the house.
     */
    void listThings() {
        std::cout << "The house contains the following objects:\n";
        for (auto& thing : things) {
            std::cout << "- " << thing->get_name() << "\n";
        }
    }
    
    /**
     * @brief Interacts with a specified thing in the house by name.
     * @param thing_name The name of the object to interact with.
     */
    void interactWithThing(const std::string& thing_name) {
        for (auto& thing : things) {
            if (thing->get_name() == thing_name) {
                thing->interact();
                return;
            }
        }
        std::cout << "No such object in the house.\n";
    }
};

#endif
