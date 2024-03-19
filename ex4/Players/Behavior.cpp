#include "Behavior.h"

Behavior::Behavior(const string& behavior) : 
    m_behavior(behavior)
{}

string Behavior::getBehavior() const {
    return m_behavior;
}

Responsible::Responsible(const string& behavior) : 
    Behavior(behavior)
{}

void Responsible::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int playerMaxHP = player.getMaxHP();
    while(player.pay(cost) && player.getHealthPoints() < playerMaxHP) {
        player.heal(givenHP);
    }
}

RiskTaking::RiskTaking(const string& behavior) : 
    Behavior(behavior)
{}

void RiskTaking::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int currentHP = player.getHealthPoints();
    int playerMaxHP = player.getMaxHP();
    if(currentHP < (playerMaxHP/2) && player.pay(cost)) {
        player.heal(givenHP);
    }
}