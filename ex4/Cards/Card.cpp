#include "Card.h"

Card::Card(const std::string& name) : 
    m_cardName(name)
{}

string Card::getCardName() const {
    return m_cardName;
}

std::string Card::getDescription() const {
    return m_cardName;
}