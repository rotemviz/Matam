#ifndef EVENT
#define EVENT

#include "Card.h"
#include "../utilities.h"

class SolarEclipse : public Card {

public:
    SolarEclipse(const std::string& cardName);
    SolarEclipse(const SolarEclipse& other) = default;
    SolarEclipse& operator=(const SolarEclipse& other) = default;
    ~SolarEclipse() = default;

    void applyCard(Player& player) override;

};

class PotionsMerchant : public Card {
    static const int POTION_PRICE = 5;
    static const int GIVEN_HP = 10;

public:
    PotionsMerchant(const std::string& cardName);
    PotionsMerchant(const PotionsMerchant& other) = default;
    PotionsMerchant& operator=(const PotionsMerchant& other) = default;
    ~PotionsMerchant() = default;

    void applyCard(Player& player) override;

};

#endif