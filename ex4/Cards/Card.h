#ifndef Card_H
#define Card_H

#pragma once
#include "../Players/Player.h"
#include "../utilities.h"
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
     * Ordering the compiler to use default methods.
     */
    Card(const Card& card) = default;


    /**
     * Default C'tor.
     */
    virtual ~Card() = default;

    /**
     * Assignment operator override.
     * @param other - the Card given to assign.
     * @return - the card post assignment.
     */
    Card& operator=(const Card& other) = default;

    /**
     * Gets the name of the card
     * 
     * @return - the name of the card
    */
    std::string getCardName() const;

    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual std::string getDescription() const = 0;

}; 
#endif // Card_H
