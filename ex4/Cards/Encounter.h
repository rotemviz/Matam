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
     * @return - A new instance of Encounter
     */
    Encounter(const std::string& monster, int power, int loot, int damage);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Encounter(const Encounter& encounter) = default;
    Encounter& operator=(const Encounter& encounter) = default;
    virtual ~Encounter() = default;

    /**
     * Gets the of power the encountered monster
     * 
     * @return - power points of monster
    */
    int getPower() const;

    /**
     * Gets the amount of coins the encountered monster has
     * 
     * @return - The amount of coins the encountered monster has
    */
    int getLoot() const;

    /**
     * Gets the damage of the monster, in health points
     * 
     * @return - the damage to be taken upon losing against the encountered monster
    */
    int getDamage() const;

    /**
     * Gets the description of the encounter
     * 
     * @return - The player on whom the encounter will be applied on
    */
    virtual std::string getDescription() const override;

    /**
     * applies the encounter on the player
     * 
     * @param player - the player to be applied on
     * @return - void
    */
    void applyCard(Player& player) override;
};


class Goblin : public Encounter {
    static const int POWER = 5;
    static const int LOOT = 2;
    static const int DAMAGE = 10;

public:

    /**
     * C'tor of Card class.
     * @return - A new instance of Goblin
     */
    Goblin();

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Goblin(const Goblin& goblin) = default;
    Goblin& operator=(const Goblin& goblin) = default;
    ~Goblin() = default;
};


class Giant : public Encounter {
    static const int POWER = 12;
    static const int LOOT = 5;
    static const int DAMAGE = 25;

public:

    /**
     * C'tor of Card class.
     * @return - A new instance of Giant
     */
    Giant();

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Giant(const Giant& giant) = default;
    Giant& operator=(const Giant& giant) = default;
    ~Giant() = default;
};


class Dragon : public Encounter {
    static const int POWER = 17;
    static const int LOOT = 100;
    static const int DAMAGE = 9001;

public:

    /**
     * C'tor of Card class.
     * @return - A new instance of Dragon
     */
    Dragon();

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    Dragon(const Dragon& dragon) = default;
    Dragon& operator=(const Dragon& dragon) = default;
    ~Dragon() = default;
};


class Gang : public Encounter {
    std::vector<std::unique_ptr<Encounter>> gangMonsters;
    
public:

    /**
     * C'tor of Gang class
     * 
     * @param monsters - The monsters in the Gang
     * @return - A new instance of Gang
    */
    Gang(std::vector<std::unique_ptr<Encounter>>& monsters);

    /**
     * Copy Constructor of Gang class
     * 
     * @param other - the gang to be copied
     * @return - A new instance of Gang
    */
    Gang(const Gang& other);

    /**
     * Assignment operator of Gang class
     * 
     * @param other - the gang to be assigned
     * @return - the gang post the assignment
    */
    Gang& operator=(const Gang& other);

    /**
     * Explicitly telling the compiler to use the defualt method of destructor
    */
    ~Gang() = default;

     /**
     * Gets the description of the gang
     * 
     * @return - the description of the gang
    */
    std::string getDescription() const override;
};

#endif