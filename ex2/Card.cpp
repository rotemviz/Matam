#include "Card.h"

Card::Card(CardType type, const CardStats &stats) :
    m_effect(type), m_stats(stats)
{}

void Card::applyEncounter(Player& player) const{
    switch (m_effect) {
        case CardType::Treasure:
            player.addCoins(m_stats.loot);
            break;        
        case CardType::Battle:
            if(player.getAttackStrength() >= m_stats.force){
                player.addCoins(m_stats.loot);
                player.levelUp();
                printBattleResult(true);
            }
            else{
                player.damage(m_stats.hpLossOnDefeat);
                printBattleResult(false);
            }
            break;
        case CardType::Buff:
            if(player.pay(m_stats.cost)){
                player.buff(m_stats.buff);
            }
            break;
        case CardType::Heal:
            if(player.pay(m_stats.cost)){
                player.heal(m_stats.heal);
            }
            break;
    }
}
void Card::printInfo() const{
    switch (m_effect) {
        case CardType::Treasure:
            printTreasureCardInfo(m_stats);
            break;
        case CardType::Battle:
            printBattleCardInfo(m_stats);
            break;
        case CardType::Buff:
            printBuffCardInfo(m_stats);
            break;
        case CardType::Heal:
            printHealCardInfo(m_stats);
            break;
    }
}

