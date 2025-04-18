#include "Quests.hpp"
#include <iostream>

/**
 * @brief Starts the quest, resetting progress and status.
 */
void Quests::start_quest() {
    status = false;
    progress = 0;
    std::cout << "Quest started: " << name << std::endl;
}

/**
 * @brief Updates the quest progress.
 * @param progress_increase The amount to increase progress by.
 */
void Quests::update_progress(int progress_increase) {
    progress += progress_increase;
    std::cout << "Quest progress updated: " << progress << std::endl;

    if (progress >= 100) {  
        complete_quest();
    }
}

/**
 * @brief Checks if the quest is completed.
 * @return True if completed, false otherwise.
 */
bool Quests::check_completion() const {
    return status;
}

/**
 * @brief Completes the quest and awards rewards.
 */
void Quests::complete_quest() {
    status = true;
    std::cout << "Quest completed: " << name << std::endl;
    std::cout << "Rewards obtained: " << rewards << std::endl;
}

/**
 * @brief Gets the current quest progress.
 * @return The current progress percentage.
 */
int Quests::get_progress() const {
    return progress;
}

/**
 * @brief Displays the quest's current status.
 */
void Quests::get_status() {
    std::cout << "Quest: " << name 
              << ", Status: " << (status ? "Completed" : "Incomplete") << std::endl;
}

/**
 * @brief Displays detailed information about the quest.
 */
void Quests::display_info() {
    std::cout << "=== Quest Information ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Objectives: " << objectives << std::endl;
    std::cout << "Rewards: " << rewards << std::endl;
    std::cout << "Status: " << (status ? "Completed" : "Incomplete") << std::endl;
    std::cout << "=========================" << std::endl;
}
