#include "Quests.hpp"
#include <iostream>

void Quests::start_quest() {
    status = false;
    progress = 0;
    std::cout << "Quest started: " << name << std::endl;
}

void Quests::update_progress(int progress_increase) {
    progress += progress_increase;
    std::cout << "Quest progress updated: " << progress << std::endl;

    if (progress >= 100) {  
        complete_quest();
    }
}

bool Quests::check_completion() const {
    return status;
}

void Quests::complete_quest() {
    status = true;
    std::cout << "Quest completed: " << name << std::endl;
    std::cout << "Rewards obtained: " << rewards << std::endl;
}

int Quests::get_progress() const {
    return progress;
}

void Quests::get_status() {
    std::cout << "Quest: " << name 
              << ", Status: " << (status ? "Completed" : "Incomplete") << std::endl;
}

void Quests::display_info() {
    std::cout << "=== Quest Information ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Objectives: " << objectives << std::endl;
    std::cout << "Rewards: " << rewards << std::endl;
    std::cout << "Status: " << (status ? "Completed" : "Incomplete") << std::endl;
    std::cout << "=========================" << std::endl;
}
