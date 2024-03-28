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

int Responsible::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int playerMaxHP = player.getMaxHP();
    int potionsAmount = 0;
    while(player.getHealthPoints() < playerMaxHP && player.pay(cost)) {
        player.heal(givenHP);
        potionsAmount++;
    }
    return potionsAmount;
}

RiskTaking::RiskTaking(const std::string& behavior) : 
    Behavior(behavior)
{}

int RiskTaking::makePotionsMerchantMove(Player& player, int cost, int givenHP) {
    int currentHP = player.getHealthPoints();
    int playerMaxHP = player.getMaxHP();
    if(currentHP < (playerMaxHP/2) && player.pay(cost)) {
        player.heal(givenHP);
        return 1;
    }
    return 0;
}