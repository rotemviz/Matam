#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;

class Player {
    
    string m_name;
    int m_maxHP;
    int m_force;
    int m_HP;
    int m_level;
    int m_coins;
    static const int DEFAULT_FORCE = 5;
    static const int DEFAULT_MAX_HP = 100;
    static const int GAME_MAX_LEVEL = 10;

public:
    /*
     * C'tor of Player class
     *
     * @param name - The name of the player.
     * @param maxHP - The maximum health points a player can have.
     * @param force - The force of the player.
     * @return
     *      A new instance of Player.
    */
    Player(const string& name, int maxHP = DEFAULT_MAX_HP, int force = DEFAULT_FORCE);

    /*
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    Player(const Player& player) = default;
    ~Player() = default;
    Player& operator=(const Player& player) = default;

    /*
     * Prints the player info:
     *
     * @return
     *      void
    */
    void printInfo() const;

    /*
     * Raises the player's level by one, unless his level is the max level:
     *
     * @return
     *      void
    */
    void levelUp();

    /*
     * Get the player's level:
     *
     * @return
     *      The level of the player
    */
    int getLevel() const;

    /*
     * Increases the player's force by a given force:
     * 
     * @param givenForce - The amount of force which the player's force increases by.
     * @return
     *      void
    */
    void buff(int givenForce);

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
     * Get the player's attack strength:
     *
     * @return
     *     The attack strength of the player
    */
    int getAttackStrength() const;
};

#endif //PLAYER_H