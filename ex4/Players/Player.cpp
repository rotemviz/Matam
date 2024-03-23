#include "Player.h"
#include "../Cards/SolarEclipse.h"

Behavior* createPlayerBehavior(const std::string& behavior) {
    if(behavior == "Responsible") {
        return new Responsible(behavior);
    }
    else if(behavior == "RiskTaking") {
        return new RiskTaking(behavior);
    }
    throw std::runtime_error("Invalid Player File");
}

Player::Player(const std::string& name, const std::string& behavior) : 
    m_name(name), m_level(START_LEVEL), m_force(START_FORCE), m_hp(), 
    m_coins(START_COINS), m_behavior(createPlayerBehavior(behavior))
{}

int Player::getLevel() const {
    return m_level;
}

std::string Player::getName() const {
    return m_name;
}

int Player::getForce() const {
    return m_force;
}

int Player::getHealthPoints() const {
    return m_hp.getHP();
}

int Player::getCoins() const {
    return m_coins;
}

void Player::levelUp() {
    if(m_level < GAME_MAX_LEVEL) {
        m_level++;
    }
}

bool Player::isTopLevel() const {
    return m_level == GAME_MAX_LEVEL;
}

void Player::addCoins(int givenCoins) {
    if(givenCoins > 0) {
        m_coins+=givenCoins;
    }
}

bool Player::pay(int amount) {
    if(amount < 0 || amount > m_coins) {
        return false;
    }
    m_coins-=amount;
    return true;
}

void Player::damage(int hpDamage) {
    m_hp-=hpDamage;
}

bool Player::isKnockedOut() const {
    if(m_hp == 0) {
        return true;
    }
    return false;
}

void Player::heal(int hp) {
    int maxHp = m_hp.getMaxHP();
    if(hp > 0) {
        HealthPoints newHP = m_hp + hp;
        if(newHP >= maxHp) {
            m_hp = maxHp;
        }
        else {
            m_hp = newHP;
        }
    }
}

void Player::forceUp() {
    ++m_force;
}

void Player::forceDown() {
    if(m_force > 0) {
        --m_force;
    }
}

int Player::getMaxHP() const {
    return m_hp.getMaxHP();
}

int Player::getCombatPower() const {
    return (this->getForce() + this->getLevel());
}

void applySolarEclipse(Player& player) {
    if (player.getJob() == Job::Sorcerer) {
        player.forceUp(); // Sorcerers gain 1 Force point
    } else if (player.getJob() == Job::Warrior) {
        player.forceDown(); // Non-Sorcerers lose 1 Force point
    }
}

int Player::solarEclipseEffect() {
    forceDown();
    return -1;
}

int Player::usePotionsMerchantMove(int cost, int givenHP) {
    return m_behavior->makePotionsMerchantMove(*this, cost, givenHP);
}

Warrior::Warrior(const std::string& name, const std::string& behavior) : 
    Player(name, behavior), m_job("Warrior")
{}

int Warrior::getCombatPower() const {
    return (this->getForce()*2 + this->getLevel());
}

std::string Warrior::getDescription() const {
    return (this->getName() + ", " + m_job + " with " + m_behavior->getBehavior() + " behavior (level " 
    + std::to_string(this->getLevel()) + ", force " + std::to_string(this->getForce()) + ")");
}

const std::string& Warrior::getJob() const {
    return m_job;
}

Sorcerer::Sorcerer(const std::string& name, const std::string& behavior) :
    Player(name, behavior), m_job("Sorcerer")
{}

int Sorcerer::solarEclipseEffect() {
    forceUp();
    return 1;
}

std::string Sorcerer::getDescription() const {
    return (this->getName() + ", " + m_job + " with " + m_behavior->getBehavior() + " behavior (level " 
    + std::to_string(this->getLevel()) + ", force " + std::to_string(this->getForce()) + ")");
}

const std::string& Sorcerer::getJob() const {
    return m_job;
}