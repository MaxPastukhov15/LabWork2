/**
 * @file Quests.hpp
 * @brief Header for the Quests class which manages game quests.
 */

#ifndef QUESTS_HPP
#define QUESTS_HPP

#include <string>

/**
 * @class Quests
 * @brief Represents a quest in the game with objectives and rewards.
 */
class Quests {
private:
    std::string id;         ///< Unique identifier for the quest.
    std::string name;       ///< Name of the quest.
    std::string objectives; ///< Quest objectives description.
    std::string rewards;    ///< Rewards for completing the quest.
    bool status;           ///< Completion status (true if completed).
    int progress;          ///< Current progress percentage (0-100).

public:
    /**
     * @brief Constructs a Quests object.
     * @param id Quest identifier (default: "Q1").
     * @param name Quest name (default: "First Quest").
     * @param objectives Quest objectives (default: "Find the hidden key").
     * @param rewards Quest rewards (default: "Artifact").
     */
    Quests(const std::string& id = "Q1", const std::string& name = "First Quest",
           const std::string& objectives = "Find the hidden key",
           const std::string& rewards = "Artifact")
        : id(id), name(name), objectives(objectives), rewards(rewards), status(false), progress(0) {}

    virtual ~Quests() = default;  

    /**
     * @brief Starts the quest.
     */
    virtual void start_quest();
    
    /**
     * @brief Updates quest progress.
     * @param progress_increase Amount to increase progress by.
     */
    virtual void update_progress(int progress_increase);
    
    /**
     * @brief Checks if quest is completed.
     * @return True if completed, false otherwise.
     */
    virtual bool check_completion() const;
    
    /**
     * @brief Completes the quest and awards rewards.
     */
    virtual void complete_quest();
    
    /**
     * @brief Gets current quest progress.
     * @return Current progress percentage.
     */
    virtual int get_progress() const;  
    
    /**
     * @brief Displays quest status.
     */
    void get_status();
    
    /**
     * @brief Displays detailed quest information.
     */
    void display_info();

    /**
     * @brief Gets quest ID.
     * @return The quest ID.
     */
    std::string get_id() const { return id; } 
    
    /**
     * @brief Gets quest name.
     * @return The quest name.
     */
    std::string get_name() const { return name; }  
    
    /**
     * @brief Gets quest rewards.
     * @return The quest rewards.
     */
    std::string get_rewards() const { return rewards; }  
};

#endif
