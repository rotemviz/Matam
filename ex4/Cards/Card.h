
#pragma once

#include "../Players/Player.h"
#include "Monster.h"

class Card {
    string m_cardName;

public:
    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual string getDescription() const = 0;
};

class Encounter : public Card {
    Monster* m_monster;
    
public:
    virtual void applyEncounter(Player& player) = 0;

};
