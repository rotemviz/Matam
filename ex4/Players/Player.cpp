#include "Player.h"


Behavior* createPlayerBehavior(const string& behavior);
Job* createPlayerJob(const string& job);

Player::Player(const string& name, const string& behavior, const string& job) : 
    m_name(name), m_level(START_LEVEL), m_force(START_FORCE), m_hp(), 
    m_coins(START_COINS), m_behavior(createPlayerBehavior(behavior)), m_job(createPlayerJob(job))
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

bool Player::isMaxLevel() const {
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
    return m_job->getCombatPower(*this);
}

string Player::getDescription() const {
    return (this->getName() + ", " + m_job->getJob() + " with " + m_behavior->getBehavior() + " behavior (level " 
    + std::to_string(this->getLevel()) + ", force " + std::to_string(this->getForce()) + ")");
}

string Player::getJob() const {
    return m_job->getJob();
}

int Player::solarEclipseEffect() {
    return m_job->solarEclipse(*this);
}

int Player::usePotionsMerchantMove(int cost, int givenHP) {
    return m_behavior->makePotionsMerchantMove(*this, cost, givenHP);
}

Behavior* createPlayerBehavior(const std::string& behavior) {
    if(behavior == "Responsible") {
        return new Responsible(behavior);
    }
    else if(behavior == "RiskTaking") {
        return new RiskTaking(behavior);
    }
    throw std::runtime_error("Invalid Player File");
}

Job* createPlayerJob(const string& job) {
    if(job == "Warrior") {
        return new Warrior(job);
    }
    else if(job == "Sorcerer") {
        return new Sorcerer(job);
    }
    throw std::runtime_error("Invalid Player File");
}