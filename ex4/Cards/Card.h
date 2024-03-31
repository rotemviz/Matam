#pragma once

#include "../Players/Player.h"
#include <string>

class Card {

    std::string m_cardName;

public:

    /**
     * C'tor of Card class.
     * @param cardName - the name of the card.
     */
    Card(const std::string& cardName);


    /**
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
     */
    Card(const Card& card) = default;
    virtual ~Card() = default;
    Card& operator=(const Card& other) = default;
    
    /**
     * Gets the name of the card
     * 
     * @return - the name of the card
    */
    string getCardName() const;

    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual std::string getDescription() const;

    virtual void applyCard(Player& player) = 0;

};
