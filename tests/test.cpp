#include "gtest/gtest.h"
#include "Characters.hpp"
#include "Thing.hpp"
#include "Quests.hpp"
#include "Game.hpp"
#include "House.hpp"
#include "Menu.hpp"
#include "Location.hpp"
#include <memory>

// Mocking classes for testing

/**
 * @class QuestMock
 * @brief A mock class for testing the `Quest` class functionality.
 */
class QuestMock : public Quests {
public:
    QuestMock(const std::string& id, const std::string& name, const std::string& objective, const std::string& rewards)
        : Quests(id, name, objective, rewards) {}

    bool check_completion() const override {
        return progress >= 100;  // Quest is completed when progress reaches 100
    }

    void start_quest() override {
        status = false;
        progress = 0;
        std::cout << "Quest started: " << get_name() << std::endl;
    }

    void complete_quest() override {
        status = true;
        std::cout << "Quest completed: " << get_name() << std::endl;
        std::cout << "Rewards obtained: " << get_rewards() << std::endl;
    }

    void update_progress(int progress_increase) override {
        progress += progress_increase;
        if (progress >= 100) {
            complete_quest();
        }
        std::cout << "Quest progress updated: " << progress << std::endl;
    }

    int get_progress() const override {
        return progress;
    }

private:
    bool status = false;
    int progress = 0;
};
/**
 * @class MenuTest
 * @brief Tests for the `Menu` class.
 */
class MenuTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_shared<Player>();
        menu = std::make_unique<Menu>(player.get());

        quest1 = std::make_shared<QuestMock>("1", "Quest One", "Defeat monsters", "Gold");
        quest2 = std::make_shared<QuestMock>("2", "Quest Two", "Find treasure", "Items");

        // Add quests to the menu
        menu->add_quest(quest1);
        menu->add_quest(quest2);

        menu->start_quest("1");
        menu->start_quest("2");
    }

    std::shared_ptr<Player> player;
    std::unique_ptr<Menu> menu;
    std::shared_ptr<QuestMock> quest1, quest2;
};

TEST_F(MenuTest, StartQuestTest) {
    menu->start_quest("1");
    EXPECT_EQ(quest1->get_progress(), 0);  ///< Ensure progress hasn't changed.
}

TEST_F(MenuTest, CompleteQuestTest) {
    menu->start_quest("1");
    menu->update_quest_progress("1", 50);
    menu->update_quest_progress("1", 50);  // Progress should reach 100
    menu->complete_quest("1");
    EXPECT_EQ(quest1->check_completion(), true);
}

TEST_F(MenuTest, UpdateQuestProgressTest) {
    menu->start_quest("1");
    menu->update_quest_progress("1", 40);
    EXPECT_EQ(quest1->get_progress(), 40);

    menu->update_quest_progress("1", 60);
    EXPECT_EQ(quest1->get_progress(), 100);  ///< Quest should be completed.
    EXPECT_EQ(quest1->check_completion(), true);
}

/**
 * @class CharactersTest
 * @brief Tests for the `Characters` class.
 */
class CharactersTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_shared<Player>();
    }

    std::shared_ptr<Player> player;
};

/**
 * @test Test player's health restoration.
 */
TEST_F(CharactersTest, PlayerHealthRestoration) {
    player->take_damage(50);
    player->restore_hp();
    EXPECT_EQ(player->get_health(), 100);
}

/**
 * @test Test player's stamina management.
 */
TEST_F(CharactersTest, PlayerStaminaManagement) {
    player->attack(*player); // Attack self to reduce stamina
    EXPECT_LT(player->get_stamina(), 50);
}

/**
 * @class ThingTest
 * @brief Tests for the `Thing` class.
 */
class ThingTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_shared<Player>();
        bed = std::make_unique<Bed>("Bed");
        chest = std::make_unique<Chest>("Chest");
    }

    std::shared_ptr<Player> player;
    std::unique_ptr<Bed> bed;
    std::unique_ptr<Chest> chest;
};

/**
 * @test Test bed's interaction.
 */
TEST_F(ThingTest, BedInteraction) {
    player->take_damage(50);
    bed->restore(*player);
    EXPECT_EQ(player->get_health(), 100);
}

/**
 * @test Test chest's item management.
 */
TEST_F(ThingTest, ChestItemManagement) {
    auto item = std::make_shared<Drugs>("Health Potion", 20);
    chest->put_item(item);
    auto retrieved_item = chest->retrieve_item("Health Potion");
    EXPECT_NE(retrieved_item, nullptr);
    EXPECT_EQ(retrieved_item->get_name(), "Health Potion");
}

/**
 * @class LocationTest
 * @brief Tests for the `Location` class.
 */
class LocationTest : public ::testing::Test {
protected:
    void SetUp() override {
        location1 = std::make_unique<Location>("Forest", "A dense forest with tall trees.");
        location2 = std::make_unique<Location>("Cave", "A dark and damp cave.");
        location1->add_neighbor(location2.get());
    }

    std::unique_ptr<Location> location1;
    std::unique_ptr<Location> location2;
};

/**
 * @test Test entering a location.
 */
TEST_F(LocationTest, EnterLocationTest) {
    testing::internal::CaptureStdout();
    location1->enter_location();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Forest"), std::string::npos);
}

/**
 * @test Test moving to a neighboring location.
 */
TEST_F(LocationTest, MoveToNeighborTest) {
    testing::internal::CaptureStdout();
    bool moved = location1->move_to_neighbor("Cave");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(moved);
    EXPECT_NE(output.find("Cave"), std::string::npos);
}

/**
 * @class HouseTest
 * @brief Tests for the `House` class.
 */
class HouseTest : public ::testing::Test {
protected:
    void SetUp() override {
        house = std::make_unique<House>();
        auto chest = std::make_shared<Chest>("Treasure Chest");
        house->addThing(chest);
    }

    std::unique_ptr<House> house;
};

TEST_F(HouseTest, ChestManagementTest) {
    auto chest = house->getChest(0);
    EXPECT_NE(chest, nullptr);
    EXPECT_EQ(chest->get_name(), "Treasure Chest");
}

TEST_F(HouseTest, InteractWithThingTest) {
    testing::internal::CaptureStdout();
    house->interactWithThing("Treasure Chest");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Treasure Chest"), std::string::npos);
}
/**
 * @class GameTest
 * @brief Tests for the `Game` class.
 */
class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>();
    }

    std::unique_ptr<Game> game;
};

/**
 * @test Test starting the game.
 */
TEST_F(GameTest, StartGameTest) {
    testing::internal::CaptureStdout();
    game->start_game();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Starting Area"), std::string::npos);
}

/**
 * @test Test advancing the game turn.
 */
TEST_F(GameTest, AdvanceTurnTest) {
    testing::internal::CaptureStdout();
    game->advance_turn();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Turn Advanced"), std::string::npos);
}

/**
 * @test Test moving to a neighboring location in the game.
 */
TEST_F(GameTest, MoveToNeighborTest) {
    testing::internal::CaptureStdout();
    bool moved = game->move_to_neighbor("Forest");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(moved);
    EXPECT_NE(output.find("Forest"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
