#include "SolarEclipse.h"
#include "../Players/Player.h"
#include "../Players/Behavior.h"

void SolarEclipse::applyEffects(Player& player, const Behavior& behavior) const {
    if (behavior.getBehavior() == "Sorcerer") {
        player.forceUp();
    } else if (behavior.getBehavior() == "Warrior") {
        player.forceDown();
    }
}