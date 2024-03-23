#ifndef SolarEclipse_H
#define SolarEclipse_H

#include "Card.h"
#include "../Players/Player.h"
#include "../Players/Behavior.h"

class SolarEclipse : public Card {
public:
    SolarEclipse() : Card("SolarEclipse") {}

    virtual std::string getDescription() const override {
        return "Event:Solar Eclipse - a Solar Eclipse occurs and affects each character differently based on their Job.";
    }

    void applyEffects(Player& player, const Behavior& behavior) const;
};

#endif // SolarEclipse_H