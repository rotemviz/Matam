
#pragma once

#include "HealthPoints.h"
#include "Behavior.h"
#include <memory>
#include <string>

using std::string;


class Player {
    std::string m_name;
    int m_level;
    int m_force;
    HealthPoints m_hp;
    int m_coins;
    static const int START_LEVEL = 1;
    static const int START_COINS = 10;
    static const int START_FORCE = 5;
    static const int GAME_MAX_LEVEL = 10;

protected:
    std::unique_ptr<Behavior> m_behavior;

public:
    /**
     * C'tor of Player class
     *
     * @param name - The name of the player.
     * @return - A new instance of Player.
    */
    Player(const std::string& name, const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    Player(const Player& player) = delete;
    Player& operator=(const Player& player) = delete;
    virtual ~Player() = default;

    /**
     * Gets the name of the player
     * 
     * @return - name of the player
    */
    std::string getName() const;

    /**
     * Gets the current level of the player
     * 
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     * 
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     * 
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     * 
     * @return - coins of the player
    */
    int getCoins() const;

    /**
     * Raises the player's level by one, unless his level is the max level:
     *
     * @return
     *      void
    */
    void levelUp();

    /**
     * Checks if the player got to the max level:
     *
     * @return
     *      True if the player's level is the max level in the game, which is ten
     *      False otherwise
    */
    bool isMaxLevel() const;

    /**
     * Increases the player's coins by a given amount of coins:
     *
     * @param givenCoins - The amount of coins which the player's coins increases by.
     * @return
     *      void
    */
    void addCoins(int givenCoins);

    /**
     * Decreases the player's amount of coins by a given amount of coins, unless the given amount is bigger than the player's amount of coins:
     *
     * @param amount - The amount of coins which the player's coins decreases by.
     * @return
     *      True if the player's coins have decreased
     *      False otherwise
    */
    bool pay(int amount);

    /**
     * Decreases the player's health points by a given health points, at most to zero:
     *
     * @param hpDamage - The amount of health points which the player's health points dencreases by.
     * @return
     *      void
    */
    void damage(int hpDamage);

    /**
     * Checks if the player is knocked out
     *
     * @return
     *      True if the player's health points are zero
     *      False otherwise
    */
    bool isKnockedOut() const;

    /**
     * Increases the player's health points by a given amount of health points, at most to the player's maximum health points:
     *
     * 
     * @param hp - The amount of health points which the player's health points increases by.
     * @return
     *      void
    */
    void heal(int hp);

    /**
     * Raises the player's force by one:
     *
     * @return
     *      void
    */
    void forceUp();

    /**
     * Lowers the player's force by one:
     *
     * @return
     *      void
    */
    void forceDown();

    /**
     * Gets the Max HP (Health Points) of the player
     *
     * @return - Max HP of the player
    */
    int getMaxHP() const;

    /**
     * Applies the method makePotionsMerchantMove on a player
     *
     * @param cost - The cost of a single potion
     * @param givenHP - The HP given to a player by a single potion
     * @return - the amount of potions bought by the player
    */
    int usePotionsMerchantMove(int cost, int givenHP);

    /**
     * Applies the effect of the card SolarEclipse;
     * If player's job is Sorcerer - increases player's force by 1
     * If player's job is Warrior - decrease player's force by 1 (to a minimum of 0)
     *
     * @return - the amount of force points increased (can be negative if decreased)
    */
    virtual int solarEclipseEffect();

    /**
     * Gets the combat power of a player
     *
     * @return - The combat power of a player
    */
    virtual int getCombatPower() const;

    /**
     * Gets the description of the player
     * 
     * @return - Description of the player
    */
    virtual std::string getDescription() const = 0;

    /**
     * Gets the job of the player
     * 
     * @return - Job of the player
    */
    virtual const std::string& getJob() const = 0;
};


class Warrior : public Player {
    std::string m_job;

public:

    /**
     * C'tor of Warrior class
     *
     * @param name - The name of the warrior.
     * @param behavior - The behavior of the warrior.
     * @return - A new instance of Warrior.
    */
    Warrior(const std::string& name, const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default method for the destructor, deleting the copy constructor and operator=
    */
    Warrior(const Warrior& other) = delete;
    Warrior& operator=(const Warrior& other) = delete;
    ~Warrior() = default;

    /**
     * Gets the description of the warrior
     * 
     * @return - Description of the warrior
    */
    std::string getDescription() const override;

    /**
     * Gets the combat power of a warrior
     *
     * @return - The combat power of the warrior
    */
    int getCombatPower() const override;

    /**
     * Gets the job of the Warrior
     * 
     * @return - Job of the Warrior
    */
    const std::string& getJob() const override;
};


class Sorcerer : public Player {
    std::string m_job;

public:

    /**
     * C'tor of Sorcerer class
     *
     * @param name - The name of the sorcerer.
     * @param behavior - The behavior of the sorcerer.
     * @return - A new instance of Sorcerer.
    */
    Sorcerer(const std::string& name, const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default method for the destructor, deleting the copy constructor and operator=
    */
    Sorcerer(const Sorcerer& other) = delete;
    Sorcerer& operator=(const Sorcerer& other) = delete;
    ~Sorcerer() = default;

    /**
     * Applies the effect of the card SolarEclipse;
     * If player's job is Sorcerer - increases player's force by 1
     * If player's job is Warrior - decrease player's force by 1 (to a minimum of 0)
     *
     * @return - the amount of force points increased (1)
    */
    virtual int solarEclipseEffect() override;
    
    /**
     * Gets the description of the sorcerer
     * 
     * @return - Description of the sorcerer
    */
    std::string getDescription() const override;

    /**
     * Gets the job of the sorcerer
     * 
     * @return - Job of the sorcerer
    */
    const std::string& getJob() const override;
};