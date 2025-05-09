#include "HealthPoints.h"

HealthPoints::HealthPoints(int hp) : 
    m_maxHP(DEFAULT_MAX_HP), m_hp(hp)
{}

HealthPoints& HealthPoints::operator+=(const int hp) {
    if(hp >= 0) {
        int newHp = m_hp + hp;
        if (newHp >= m_maxHP) {
            m_hp = m_maxHP;
        }
        else {
            m_hp = newHp;
        }
        return *this;
    }
    *this-=(-1*hp);
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int hp) {
    if(hp >= 0) {
        int newHp = m_hp - hp;
        if(newHp <= 0) {
            m_hp = 0;
        }
        else {
            m_hp = newHp;
        }
        return *this;
    }
    *this+=(-1*hp);
    return *this;
}

int HealthPoints::getHP() const {
    return m_hp;
}

int HealthPoints::getMaxHP() const {
    return m_maxHP;
}

HealthPoints operator+(const HealthPoints& healthPoints, const int hp) {
    return HealthPoints(healthPoints)+=hp;
}

HealthPoints operator+(const int hp, const HealthPoints& healthPoints) {
    return HealthPoints(healthPoints)+=hp;
}

HealthPoints HealthPoints::operator-(const int hp) const { 
    return HealthPoints(*this)-=hp;
}

bool operator==(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    int hpOne = healthPointsOne.getHP();
    int hpTwo = healthPointsTwo.getHP();
    return hpOne == hpTwo;
}

bool operator!=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    return !(healthPointsOne == healthPointsTwo);
}

bool operator>(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    int hpOne = healthPointsOne.getHP();
    int hpTwo = healthPointsTwo.getHP();
    return hpOne > hpTwo;
}

bool operator<(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    return !(healthPointsOne > healthPointsTwo || healthPointsOne == healthPointsTwo);
}

bool operator<=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    return !(healthPointsOne > healthPointsTwo);
}

bool operator>=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo) {
    return !(healthPointsOne < healthPointsTwo);
}

ostream& operator<<(ostream& os, const HealthPoints& healthPoints) {
    return os << healthPoints.getHP() << "(" << healthPoints.getMaxHP() << ")";
}