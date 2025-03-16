#ifndef QUESTS_HPP
#define QUESTS_HPP

#include <string>

/**
 * @class Quests
 * @brief Represents a quest in the game.
 */
class Quests {
private:
    std::string id;
    std::string name;
    std::string objectives;
    std::string rewards;
    bool status;  
    int progress;  

public:
    Quests(const std::string& id = "Q1", const std::string& name = "First Quest",
           const std::string& objectives = "Find the hidden key",
           const std::string& rewards = "Artifact")
        : id(id), name(name), objectives(objectives), rewards(rewards), status(false), progress(0) {}

    virtual ~Quests() = default;  // Add a virtual destructor

    virtual void start_quest();
    virtual void update_progress(int progress_increase);
    virtual bool check_completion() const;
    virtual void complete_quest();
    virtual int get_progress() const;  // Add this method
    void get_status();
    void display_info();

    std::string get_id() const { return id; } 
    std::string get_name() const { return name; }  
    std::string get_rewards() const { return rewards; }  // Add accessor for rewards
};

#endif
