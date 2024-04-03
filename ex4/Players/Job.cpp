#include "Job.h"
#include "Player.h"

Job::Job(const std::string& job) : m_job(job)
{}

std::string Job::getJob() const {
    return m_job;
}

int Job::getCombatPower(const Player& player) const {
    return (player.getForce() + player.getLevel());
}

int Job::solarEclipse(Player& player) {
    if(player.getForce() == 0) {
        return 0;
    }
    player.forceDown();
    return -1;
}

Warrior::Warrior(const std::string& job) : Job(job)
{}

int Warrior::getCombatPower(const Player& player) const {
    return (2*player.getForce() + player.getLevel());
}

Sorcerer::Sorcerer(const std::string& job) : Job(job)
{}

int Sorcerer::solarEclipse(Player& player) {
    player.forceUp();
    return 1;
}