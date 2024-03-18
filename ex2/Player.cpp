#include "Player.h"
#include "utilities.h"

Player::Player(const string& name, int maxHP, int force) : 
    m_name(name), m_maxHP(maxHP > 0 ? maxHP : DEFAULT_MAX_HP), m_force(force > 0 ? force : DEFAULT_FORCE),
    m_HP(m_maxHP), m_level(1), m_coins(0)
{}

void Player::printInfo() const {
    const char* name = m_name.c_str();
    printPlayerInfo(name, m_level, m_force, m_HP, m_coins);
}

void Player::levelUp() {
    if(m_level < GAME_MAX_LEVEL) {
        m_level++;
    }
}

int Player::getLevel() const {
    return m_level;
}

void Player::buff(int givenForce) {
    if(givenForce < 0) {
        return;
    }
    m_force += givenForce;
}

void Player::heal(int hp) {
    if(hp > 0) {
        int newHp = m_HP + hp;
        if(newHp >= m_maxHP) {
            m_HP = m_maxHP;
        }
        else {
            m_HP = newHp;
        }
    }
}

void Player::damage(int hpDamage) {
    if(hpDamage >= m_HP) {
        m_HP = 0;
    }
    else if(hpDamage > 0) {
        m_HP-=hpDamage;
    }
}

bool Player::isKnockedOut() const {
    if(m_HP == 0) {
        return true;
    }
    return false;
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

int Player::getAttackStrength() const {
    return (m_level + m_force);
}