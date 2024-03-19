#ifndef MONSTER
#define MONSTER

enum class monsterType {Goblin, Giant, Dragon, Gang};

class Monster {
    int m_power;
    int m_loot;
    int m_damage;

public:
    Monster();
};

#endif