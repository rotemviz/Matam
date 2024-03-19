#include "Player.h"

Player::Player(const string& name, Behavior* behavior) : 
    m_name(name), m_level(START_LEVEL), m_force(START_FORCE), m_hp(), m_coins(START_COINS), m_behavior(behavior)
{}

Player::~Player() {
    delete m_behavior;
}

int Player::getLevel() const {
    return m_level;
}

string Player::getName() const {
    return m_name;
}

int Player::getForce() const {
    return m_force;
}

int Player::getHealthPoints() const {
    return m_hp.getHP();
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

Warrior::Warrior(const string& name, Behavior* behavior, const string& job) : 
    Player(name, behavior), m_job(job)
{}

int Warrior::getCombatPower() const {
    return (this->getForce()*2 + this->getLevel());
}

string Warrior::getDescription() const {
    return (this->getName() + ", " + m_job + " with " + m_behavior->getBehavior() + " behavior (level " 
    + std::to_string(this->getLevel()) + ", force " + std::to_string(this->getForce()) + ")");
}

Sorcerer::Sorcerer(const string& name, Behavior* behavior, const string& job) :
    Player(name, behavior), m_job(job)
{}

string Sorcerer::getDescription() const {
    return (this->getName() + ", " + m_job + " with " + m_behavior->getBehavior() + " behavior (level " 
    + std::to_string(this->getLevel()) + ", force " + std::to_string(this->getForce()) + ")");
}