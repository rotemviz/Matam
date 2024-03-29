#include "Encounter.h"
#include "./utilities.h"
#include <iostream>

std::vector<std::unique_ptr<Encounter>> copyGangMonsters(const std::vector<std::unique_ptr<Encounter>>& gangMonsters);

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

string Encounter::getCardName() const {
    return m_cardName;
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

Gang::Gang(const Gang& other) : 
    Encounter(other.m_cardName, other.m_power, other.m_loot, other.m_damage), gangMonsters(copyGangMonsters(other.gangMonsters))
{}

Gang& Gang::operator=(const Gang& other) {
    if(this == &other) {
        return *this;
    }
    std::vector<std::unique_ptr<Encounter>> copiedOtherGangMonsters(copyGangMonsters(other.gangMonsters));
    while(!gangMonsters.empty()) {
        gangMonsters.pop_back();
    }
    for(auto iterator = copiedOtherGangMonsters.begin(); iterator != copiedOtherGangMonsters.end(); ++iterator) {
        gangMonsters.push_back(std::unique_ptr<Encounter>(std::move(*iterator)));
    }
    m_power = other.m_power;
    m_loot = other.m_loot;
    m_damage = other.m_damage;
    return *this;
}

std::string Gang::getDescription() const {
    return "Gang of " + std::to_string(gangMonsters.size()) + " members (power " + std::to_string(m_power) + ", loot " 
    + std::to_string(m_loot) + ", damage " + std::to_string(m_damage) + ")";
}

std::vector<std::unique_ptr<Encounter>> copyGangMonsters(const std::vector<std::unique_ptr<Encounter>>& gangMonsters) {
    std::vector<std::unique_ptr<Encounter>> copiedGangMonsters;
    for(auto iterator = gangMonsters.begin(); iterator != gangMonsters.end(); ++iterator) {
        if(Encounter* encounterPointer = dynamic_cast<Encounter*>(iterator->get())) {
            copiedGangMonsters.push_back(std::unique_ptr<Encounter>(new Encounter(*encounterPointer)));
        }
    }
    return copiedGangMonsters;
}