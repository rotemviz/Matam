#ifndef EVENT
#define EVENT

#include "Card.h"
#include "utilities.h"

class SolarEclipse : public Card {

public:

    /**
     * C'tor of Card class.
     * 
     * @param cardName - name of the event card
     * @return - A new instance of SolarEclipse
     */
    SolarEclipse(const std::string& cardName);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    SolarEclipse(const SolarEclipse& other) = default;
    SolarEclipse& operator=(const SolarEclipse& other) = default;
    ~SolarEclipse() = default;

    /**
     * applies solar eclipse on the player
     * 
     * @param player - the player to be applied on
     * @return - void
    */
    void applyCard(Player& player) override;

};

class PotionsMerchant : public Card {
    static const int POTION_PRICE = 5;
    static const int GIVEN_HP = 10;

public:

    /**
     * C'tor of Card class.
     * 
     * @param cardName - name of the event card
     * @return - A new instance of PotionsMerchant
     */
    PotionsMerchant(const std::string& cardName);

    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    PotionsMerchant(const PotionsMerchant& other) = default;
    PotionsMerchant& operator=(const PotionsMerchant& other) = default;
    ~PotionsMerchant() = default;

    /**
     * applies the potion merchant on the player
     * 
     * @param player - the player to be applied on
     * @return - void
    */
    void applyCard(Player& player) override;
};

#endif