#ifndef PotionsMerchant_H
#define PotionsMerchant_H

#include "Card.h"
#include "../Players/Player.h"
#include "../Players/Behavior.h"

class PotionsMerchant : public Card {
public:
    PotionsMerchant() : Card("Potions Merchant") {}

    virtual std::string getDescription() const override {
        return "Event:Potions Merchant - A merchant offering health potions for sale.";
    }

    void applyEffects(Player& player, Behavior& behavior) const;
};

#endif // PotionsMerchant_H
