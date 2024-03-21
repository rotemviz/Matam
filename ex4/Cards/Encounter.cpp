#include "Encounter.h"


Encounter::Encounter(const std::string& monster, int power, int loot, int damage) :
    Card("Encounter"), m_monsterName(monster), m_power(power), m_loot(loot), m_damage(damage)
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
    return m_monsterName + " (power " + std::to_string(m_power) + ", loot " + std::to_string(m_loot) + ", damage " 
    + std::to_string(m_damage) + ")";
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

void Gang::addMonster(const std::string& monster) {
    if(monster == "Goblin") {
        gangMonsters.push_back(std::unique_ptr<Encounter>(new Goblin()));
    }
    else if(monster == "Giant") {
        gangMonsters.push_back(std::unique_ptr<Encounter>(new Giant()));
    }
    else if(monster == "Dragon") {
        gangMonsters.push_back(std::unique_ptr<Encounter>(new Dragon()));
    }
    m_power+=gangMonsters.back()->getPower();
    m_loot+=gangMonsters.back()->getLoot();
    m_damage+=gangMonsters.back()->getDamage();
}

Gang::Gang() : 
    Encounter("Gang", 0, 0, 0), gangMonsters()
{}

std::string Gang::getDescription() const {
    return "Gang of " + std::to_string(gangMonsters.size()) + "members (power " + std::to_string(m_power) + ", loot " 
    + std::to_string(m_loot) + ", damage " + std::to_string(m_damage);
}