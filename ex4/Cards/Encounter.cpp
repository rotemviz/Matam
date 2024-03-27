#include "Encounter.h"
#include "../utilities.h"
#include <iostream>


Encounter::Encounter(const std::string& monster, int power, int loot, int damage) :
    Card(monster), m_power(power), m_loot(loot), m_damage(damage)
{}

int Encounter::getPower() const {
    return m_power;
}

int Encounter::getLoot() const {
    return m_loot;
}

int Encounter::getDamage() const {
    return m_damage;
}

std::string Encounter::getDescription() const {
    return m_cardName + " (power " + std::to_string(m_power) + ", loot " + std::to_string(m_loot) + ", damage " 
    + std::to_string(m_damage) + ")";
}

void Encounter::applyCard(Player& player) {
    int playerCombatPower = player.getCombatPower();
    if(playerCombatPower > getPower()) {
        player.levelUp();
        player.addCoins(m_loot);
        printTurnOutcome(getEncounterWonMessage(player, m_loot));
    }
    else {
        player.damage(m_damage);
        printTurnOutcome(getEncounterLostMessage(player, m_damage));
    }
}

Goblin::Goblin() : 
    Encounter("Goblin", POWER, LOOT, DAMAGE)
{}

Giant::Giant() : 
    Encounter("Giant", POWER, LOOT, DAMAGE)
{}

Dragon::Dragon() : 
    Encounter("Dragon", POWER, LOOT, DAMAGE)
{}

Gang::Gang(std::vector<std::unique_ptr<Encounter>>& monsters) : 
    Encounter("Gang", 0, 0, 0), gangMonsters()
{
    for(auto iterator = monsters.begin(); iterator != monsters.end(); ++iterator) {
        
        gangMonsters.push_back(std::move(*iterator));
        m_damage+=gangMonsters.back()->getDamage();
        m_loot+=gangMonsters.back()->getLoot();
        m_power+=gangMonsters.back()->getPower();
    }
}

std::string Gang::getDescription() const {
    return "Gang of " + std::to_string(gangMonsters.size()) + " members (power " + std::to_string(m_power) + ", loot " 
    + std::to_string(m_loot) + ", damage " + std::to_string(m_damage) + ")";
}