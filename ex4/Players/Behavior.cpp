#include "Behavior.h"
#include "Player.h"


Behavior::Behavior(const std::string& behavior) : 
    m_behavior(behavior)
{}

std::string Behavior::getBehavior() const {
    return m_behavior;
}

Responsible::Responsible(const std::string& behavior) : 
    Behavior(behavior)
{}

void Responsible::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int playerMaxHP = player.getMaxHP();
    while(player.pay(cost) && player.getHealthPoints() < playerMaxHP) {
        player.heal(givenHP);
    }
}

RiskTaking::RiskTaking(const std::string& behavior) : 
    Behavior(behavior)
{}

void RiskTaking::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int currentHP = player.getHealthPoints();
    int playerMaxHP = player.getMaxHP();
    if(currentHP < (playerMaxHP/2) && player.pay(cost)) {
        player.heal(givenHP);
    }
}