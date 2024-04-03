
#pragma once

#include "HealthPoints.h"
#include "Behavior.h"
#include "Job.h"
#include <memory>
#include <string>

using std::string;


class Player {
    std::string m_name;
    int m_level;
    int m_force;
    HealthPoints m_hp;
    int m_coins;
    std::unique_ptr<Behavior> m_behavior;
    std::unique_ptr<Job> m_job;
    static const int START_LEVEL = 1;
    static const int START_COINS = 10;
    static const int START_FORCE = 5;
    static const int GAME_MAX_LEVEL = 10;

public:
    /**
     * C'tor of Player class
     *
     * @param name - The name of the player.
     * @param behavior - The behavior of the player
     * @param job - The job of the player
     * @return - A new instance of Player.
    */
    Player(const string& name, const string& behavior, const string& job);

    /**
     * Explicitly telling the compiler to use the default methods of copy constructor
    */
    ~Player() = default;

    /**
     * Deleting the copy constructor and operator=
    */
    Player(const Player& player) = delete;
    Player& operator=(const Player& player) = delete;

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
     * Gets the force points of the player
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
     * Checks if the player has reached max level:
     *
     * @return
     *      True if the player's level is the max level in the game, which is 10
     *      False otherwise
    */
    bool isMaxLevel() const;

    /**
     * Increases the player's coins by a given amount of coins:
     *
     * @param givenCoins - The amount of coins which the player's coins will be increased by.
     * @return
     *      void
    */
    void addCoins(int givenCoins);

    /**
     * Decreases the player's coins by a given amount, unless the given amount is bigger than the player's amount of coins:
     *
     * @param amount - The amount of coins which the player's coins will be decreased by.
     * @return
     *      True if the player's coins has decreased
     *      False otherwise
    */
    bool pay(int amount);

    /**
     * Decreases the player's health points by a given amount, to a minimum of 0:
     *
     * @param hpDamage - The amount of health points which the player's health points will be decreased by.
     * @return
     *      void
    */
    void damage(int hpDamage);

    /**
     * Checks if the player is knocked out
     *
     * @return
     *      True if the player's health points are at zero
     *      False otherwise
    */
    bool isKnockedOut() const;

    /**
     * Increases the player's health points by a given amount, at most to the player's maximum health points:
     *
     * 
     * @param hp - The amount of health points which the player's health points will be increased by.
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
     * Decrease player's force by 1 (to a minimum of 0)
     *
     * @return - the amount of force points decreased
    */
    int solarEclipseEffect();

    /**
     * Gets the combat power of a player
     *
     * @return - The combat power of a player
    */
    int getCombatPower() const;

    string getDescription() const;

    string getJob() const;
};