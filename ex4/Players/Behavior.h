#ifndef BEHAVIORS
#define BEHAVIORS

class Player;

#include <string>

class Behavior
{
protected:
    std::string m_behavior;
    
public:
    /**
     * C'tor of Behavior class
     *
     * @param behavior - The player's behavior
     * @return - A new instance of Behavior
    */
    Behavior(const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    Behavior(const Behavior& behavior) = default;
    Behavior& operator=(const Behavior& behavior) = default;
    virtual ~Behavior() = default;

    /**
     * Gets the behavior of the player
     * 
     * @return - behavior of the player
    */
    std::string getBehavior() const;

    /**
     * Applies the effect of the card PotionsMerhant;
     * If player is Responsible - buys potions until health is at MaxHP or until player does not have enough coins for another potion
     * If player is RiskTaking - only buys 1 potion if player is below half of his max health and has enough coins
     *
     * @param player - The player to be applied on
     * @param cost - The cost of a single potion
     * @param givenHP - The HP given to a player by a single potion
     * @return - the amount of potions bought by the player
    */
    virtual int makePotionsMerchantMove(Player& player, int cost, int givenHP) = 0;
};


class Responsible : public Behavior {

public:
    /**
     * C'tor of Responsible class
     *
     * @param behavior - The player's behavior
     * @return - A new instance of Responsible
    */
    Responsible(const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    Responsible(const Responsible& responsible) = default;
    Responsible& operator=(const Responsible& responsible) = default;
    ~Responsible() = default;

    /**
     * Applies the effect of the card PotionsMerhant;
     * Buys potions until health is at MaxHP or until player does not have enough coins for another potion
     *
     * @param player - The Responsible player to be applied on
     * @param cost - The cost of a single potion
     * @param givenHP - The HP given to a player by a single potion
     * @return - the amount of potions bought by the player
    */
    int makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};


class RiskTaking : public Behavior {

public:
    /**
     * C'tor of RiskTaking class
     *
     * @param behavior - The player's behavior
     * @return - A new instance of RiskTaking
    */
    RiskTaking(const std::string& behavior);

    /**
     * Explicitly telling the compiler to use the default methods of copy constructor, destructor, and operator=
    */
    RiskTaking(const RiskTaking& riskTaking) = default;
    RiskTaking& operator=(const RiskTaking& riskTaking) = default;
    ~RiskTaking() = default;

    /**
     * Applies the effect of the card PotionsMerhant;
     * Only buys 1 potion if player is below half of his max health and has enough coins
     *
     * @param player - The RiskTaking player to be applied on
     * @param cost - The cost of a single potion
     * @param givenHP - The HP given to a player by a single potion
     * @return - the amount of potions bought by the player
    */
    int makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};

#endif