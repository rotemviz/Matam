#include "Event.h"

SolarEclipse::SolarEclipse(const std::string& cardName) : 
    Card(cardName)
{}

void SolarEclipse::applyCard(Player& player) {
    int outcome = player.solarEclipseEffect();
    printTurnOutcome(getSolarEclipseMessage(player, outcome));
}

PotionsMerchant::PotionsMerchant(const std::string& cardName) : 
    Card(cardName)
{}

void PotionsMerchant::applyCard(Player& player) {
    int outCome = player.usePotionsMerchantMove(POTION_PRICE, GIVEN_HP);
    printTurnOutcome(getPotionsPurchaseMessage(player, outCome));
}