#include "PotionsMerchant.h"
#include "../Players/Player.h"
#include "../Players/Behavior.h"

void PotionsMerchant::applyEffects(Player& player, Behavior& behavior) const {
    behavior.makePotionsMerchantMove(player, 5, 10);
}
