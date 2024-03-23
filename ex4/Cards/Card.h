#ifndef Card_H
#define Card_H

#pragma once
#include "../Players/Player.h"
#include "../utilities.h"
#include <string>

class Card {

protected:
    std::string m_cardName;

public:

    /**
     * C'tor of Card class.
     * @param cardName - the name of the card.
     */
    Card(const std::string& cardName);


    /**
     * Ordering the compiler to use default methods.
     */
    Card(const Card& card) = default;


    /**
     * Default Destructor.
     */
    virtual ~Card() = default;

    /**
     * Assignment operator override.
     * @param other - the Card given to assign.
     * @return - the card post assignment.
     */
    Card& operator=(const Card& other) = default;

    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual std::string getDescription() const;

    virtual void applyCard(Player& player) = 0;

}; 
#endif // Card_H
