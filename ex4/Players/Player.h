
#pragma once

#include "HealthPoints.h"
#include "Behavior.h"
#include <memory>
#include <string>



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
    /*
     * C'tor of Player class
     *
     * @param name - The name of the player.
     * @return
     *      A new instance of Player.
    */
    Player(const std::string& name, const std::string& behavior);

    virtual ~Player() = default;

    /*
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;

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

    /*
     * Raises the player's level by one, unless his level is the max level:
     *
     * @return
     *      void
    */
    void levelUp();

    /*
     * Checks if the player got to the max level:
     *
     * @return
     *      True if the player's level is the max level in the game, which is ten
     *      False otherwise
    */
    bool isTopLevel() const;

    /*
     * Increases the player's coins by a given amount of coins:
     *
     * @param givenCoins - The amount of coins which the player's coins increases by.
     * @return
     *      void
    */
    void addCoins(int givenCoins);

    /*
     * Decreases the player's amount of coins by a given amount of coins, unless the given amount is bigger than the player's amount of coins:
     *
     * @param amount - The amount of coins which the player's coins decreases by.
     * @return
     *      True if the player's coins have decreased
     *      False otherwise
    */
    bool pay(int amount);

    /*
     * Decreases the player's health points by a given health points, at most to zero:
     *
     * @param hpDamage - The amount of health points which the player's health points dencreases by.
     * @return
     *      void
    */
    void damage(int hpDamage);

    /*
     * Checks if the player is knocked out
     *
     * @return
     *      True if the player's health points are zero
     *      False otherwise
    */
    bool isKnockedOut() const;

    /*
     * Increases the player's health points by a given amount of health points, at most to the player's maximum health points:
     *
     * 
     * @param hp - The amount of health points which the player's health points increases by.
     * @return
     *      void
    */
    void heal(int hp);

    /*
     * Raises the player's force by one:
     *
     * @return
     *      void
    */
    void forceUp();

    /*
     * Lowers the player's force by one:
     *
     * @return
     *      void
    */
    void forceDown();

    int getMaxHP() const;

    virtual int getCombatPower() const;

    /**
     * Gets the description of the player
     * 
     * @return - description of the player
    */
    virtual std::string getDescription() const = 0;
};


class Warrior : public Player {
    std::string m_job;

public:
    Warrior(const std::string& name, const std::string& behavior, const std::string& job);

    std::string getDescription() const override;
    int getCombatPower() const override;
};


class Sorcerer : public Player {
    std::string m_job;

public:

    Sorcerer(const std::string& name, const std::string& behavior, const std::string& job);
    std::string getDescription() const override;
};