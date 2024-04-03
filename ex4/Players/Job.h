#ifndef JOB
#define JOB

#include <string>
class Player;


class Job {
    std::string m_job;

public:
    /**
     * C'tor of class Job
     *
     * @param job - The name of the job.
     * @return - A new instance of Job.
    */
    Job(const std::string& job);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    ~Job() = default;
    Job(const Job& other) = default;
    Job& operator=(const Job& other) = default;

    /**
     * Gets the job's name
     * 
     * @return - The job's name
    */
    std::string getJob() const;

    /**
     * Gets the combat power of a player
     *
     * @param player - The player
     * @return - The combat power of the player
    */
    virtual int getCombatPower(const Player& player) const;

    /**
     * Applies the effect of the card SolarEclipse on a player:
     * Decrease player's force by 1 (to a minimum of 0)
     *
     * @param player - the player
     * @return - the amount of force points decreased
    */
    virtual int solarEclipse(Player& player);
};

class Warrior : public Job {

public:
    /**
     * C'tor of class Warrior
     *
     * @param job - The name of the job(warrior).
     * @return - A new instance of Warrior.
    */
    Warrior(const std::string& job);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Warrior(const Warrior& other) = default;
    Warrior& operator=(const Warrior& other) = default;
    ~Warrior() = default;

    /**
     * Gets the combat power of a player which his job is warrior
     *
     * @param player - The player
     * @return - The combat power of the player
    */
    int getCombatPower(const Player& player) const override;
};


class Sorcerer : public Job {

public:
    /**
     * C'tor of class Sorcerer
     *
     * @param job - The name of the job(sorcerer).
     * @return - A new instance of Sorcerer.
    */
    Sorcerer(const std::string& job);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Sorcerer(const Sorcerer& other) = default;
    Sorcerer& operator=(const Sorcerer& other) = default;
    ~Sorcerer() = default;

    /**
     * Applies the effect of the card SolarEclipse on a player:
     * Icrease player's force by 1
     *
     * @param player - the player
     * @return - the amount of force points decreased
    */
    int solarEclipse(Player& player) override;
};

#endif