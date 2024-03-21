#include "Card.h"

Card::Card(const std::string& name) : 
    m_cardName(name)
{}

std::string Card::getCardName() const {
    return m_cardName;
}