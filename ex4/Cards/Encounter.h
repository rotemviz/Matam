#ifndef ENCOUNTER
#define ENCOUNTER

#include "Card.h"
#include <string>
#include <vector>
#include <memory>


class Encounter : public Card {

protected:
    int m_power;
    int m_loot;
    int m_damage;

public:

    /**
     * C'tor of Card class.
     * @param monster - name of the monster.
     * @param power - power points of the monster.
     * @param loot - loot given by the monster if encounter is won.
     * @param damage - damage points of the monster.
     */
    Encounter(const std::string& monster, int power, int loot, int damage);

    /**
     * Copy constructor of Monster.
     */
    Encounter(const Encounter& encounter) = default;

    /**
     * Default Destructor.
     */
    virtual ~Encounter() = default;

    /**
     * Assignment operator override.
     * @param other - the Monster given to assign.
     * @return - the Monster post assignment.
     */
    Encounter& operator=(const Encounter& encounter) = default;

    /**
     * Gets the of power the encountered monster
     * 
     * @return - power points of monster
    */
    virtual int getPower() const;

    /**
     * Gets the amount of gold the player gets if monster encountered is defeated
     * 
     * @return - the amount of gold the player gets for winning in the current encounter
    */
    virtual int getLoot() const;

    /**
     * Gets the amount (in health points) of damage you recieve if losing in the encounter
     * 
     * @return - the damage to be taken upon losing against the encountered monster
    */
    virtual int getDamage() const;

    virtual string getCardName() const;

    virtual std::string getDescription() const override;

    virtual void applyCard(Player& player) override;
};


class Goblin : public Encounter {
    static const int POWER = 5;
    static const int LOOT = 2;
    static const int DAMAGE = 10;

public:

    Goblin();
    Goblin(const Goblin& goblin) = default;
    Goblin& operator=(const Goblin& goblin) = default;
    ~Goblin() = default;
};


class Giant : public Encounter {
    static const int POWER = 12;
    static const int LOOT = 5;
    static const int DAMAGE = 25;

public:

    Giant();
    Giant(const Giant& giant) = default;
    Giant& operator=(const Giant& giant) = default;
    ~Giant() = default;
};


class Dragon : public Encounter {
    static const int POWER = 17;
    static const int LOOT = 100;
    static const int DAMAGE = 9001;

public:

    Dragon();
    Dragon(const Dragon& dragon) = default;
    Dragon& operator=(const Dragon& dragon) = default;
    ~Dragon() = default;
};


class Gang : public Encounter {
    std::vector<std::unique_ptr<Encounter>> gangMonsters;
    
public:
    Gang(std::vector<std::unique_ptr<Encounter>>& monsters);
    ~Gang() = default;
    Gang(const Gang& other);
    Gang& operator=(const Gang& other);
    /* TODO: OPERATOR= AND COPY CONSTRUCTOR !!!  */

    std::string getDescription() const override;
};

#endif