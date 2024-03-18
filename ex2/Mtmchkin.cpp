#include "Mtmchkin.h"

Mtmchkin::Mtmchkin(const char* playerName, const Card* cardsArray, int numOfCards) :
    m_player(playerName), m_cardsArray(new Card[numOfCards]), m_numberOfCards(numOfCards), 
    m_status(GameStatus::MidGame), m_cardIndex(FIRST_CARD_INDEX)
{
    for(int i=0; i<numOfCards; i++) {
        m_cardsArray[i] = cardsArray[i];
    }
}

Mtmchkin::~Mtmchkin(){
    delete[] m_cardsArray;
}

Mtmchkin::Mtmchkin(const Mtmchkin& mtmchkin) :
    m_player(mtmchkin.m_player), m_cardsArray(new Card[mtmchkin.m_numberOfCards]), m_numberOfCards(mtmchkin.m_numberOfCards),
    m_status(mtmchkin.m_status), m_cardIndex(mtmchkin.m_cardIndex)
{
    for(int i=0; i<m_numberOfCards; i++) {
        m_cardsArray[i] = mtmchkin.m_cardsArray[i];
    }
}

Mtmchkin& Mtmchkin::operator=(const Mtmchkin& other) {
    if(this == &other) {
        return *this;
    }
    m_player = other.m_player;
    m_status = other.m_status;
    m_numberOfCards = other.m_numberOfCards;
    Card* tempArray = new Card[other.m_numberOfCards];
    delete[] m_cardsArray;
    m_cardsArray = tempArray;
    for(int i=0; i<m_numberOfCards; i++) {
        m_cardsArray[i] = other.m_cardsArray[i];
    }
    return *this;
}

void Mtmchkin::playNextCard() {
    m_cardsArray[m_cardIndex].printInfo();
    m_cardsArray[m_cardIndex].applyEncounter(m_player);
    m_player.printInfo();
    if (m_cardIndex == m_numberOfCards-1) {
        m_cardIndex = FIRST_CARD_INDEX;
    }
    else {
        m_cardIndex++;
    }
    if (m_player.getLevel() == GAME_MAX_LEVEL) {
        m_status = GameStatus::Win;
    }
    else if (m_player.isKnockedOut()) {
        m_status = GameStatus::Loss;
    }
}

bool Mtmchkin::isOver() const {
    if (m_status != GameStatus::MidGame) {
        return true;
    }
    return false;
}

GameStatus Mtmchkin::getGameStatus() const {
    return m_status;
}