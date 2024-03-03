#ifndef HEALTH_POINTS
#define HEALTH_POINTS

#include <ostream>
using std::ostream;

class HealthPoints {

    int m_maxHP;
    int m_hp;
    static const int DEFAULT_MAX_HP = 100;

public:
    HealthPoints(int maxHP = DEFAULT_MAX_HP);
    ~HealthPoints() = default;
    HealthPoints(const HealthPoints& healthPoints) = default;
    int getHP() const;
    int getMaxHP() const;
    HealthPoints& operator+=(int hp);
    HealthPoints& operator-=(int hp);

    class InvalidArgument{};
};


HealthPoints operator+(const HealthPoints& healthPoints, int hp);
HealthPoints operator+(int hp, const HealthPoints& healthPoints);
HealthPoints operator-(const HealthPoints& healthPoints, int hp);
HealthPoints operator-(int hp, const HealthPoints& healthPoints);
bool operator==(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
bool operator!=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
bool operator>(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
bool operator<(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
bool operator<=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
bool operator>=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);
ostream& operator<<(ostream& os, const HealthPoints& healthPoints);

#endif