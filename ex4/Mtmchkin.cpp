
#include "Mtmchkin.h"

#include "utilities.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>


bool rankComparator(std::shared_ptr<Player> playerOne, std::shared_ptr<Player> playerTwo);

Gang* Mtmchkin::createGang(int& index, vector<string>& givenWords, vector<std::unique_ptr<Encounter>>& monstersInGang, int numberOfWords) {
    int sizeOfGang = std::stoi(givenWords[index]);
    int givenIndex = index;
    if(sizeOfGang > numberOfWords - (givenIndex+1)) {
        throw std::runtime_error("Invalid Cards File");
    }
    ++index;
    for(; index!=(givenIndex + sizeOfGang + 1); ++index) {
        if(givenWords[index] == "Goblin") {
            monstersInGang.push_back(std::unique_ptr<Encounter>(new Goblin()));
        } 
        else if(givenWords[index] == "Giant") {
            monstersInGang.push_back(std::unique_ptr<Encounter>(new Giant()));
        }
        else if(givenWords[index] == "Dragon") {
            monstersInGang.push_back(std::unique_ptr<Encounter>(new Dragon()));
        }
        else if(givenWords[index] == "Gang") {
            vector<std::unique_ptr<Encounter>> monstersInOtherGang;
            monstersInGang.push_back(std::unique_ptr<Encounter>(createGang(++index, givenWords, monstersInOtherGang, numberOfWords)));
            givenIndex = index;
        }
        else {
            throw std::runtime_error("Invalid Cards File");
        }
    }
    return new Gang(monstersInGang);
}

Mtmchkin::Mtmchkin(const string& deckPath, const string& playersPath) : m_numberOfPlayers(0) 
{
    string word;
    vector<string> wordsInDeckFile;

    /*===== TODO: Open and read cards file =====*/

    std::ifstream deckFile(deckPath);
    if(!deckFile.is_open()) {
        throw std::runtime_error("Invalid Cards File");
    }
    int countWords = 0;
    while(deckFile >> word) {
        wordsInDeckFile.push_back(word);
        countWords++;
    }
    for(int i=0; i<countWords; i++) {
        if(wordsInDeckFile[i] == "Goblin") {
            m_cards.push_back(std::unique_ptr<Card>(new Goblin()));
        } 
        else if(wordsInDeckFile[i] == "Giant") {
            m_cards.push_back(std::unique_ptr<Card>(new Giant()));
        }
        else if(wordsInDeckFile[i] == "Dragon") {
            m_cards.push_back(std::unique_ptr<Card>(new Dragon()));
        }
        else if(wordsInDeckFile[i] == "Gang") {
            vector<std::unique_ptr<Encounter>> monstersInGang;
            m_cards.push_back(std::unique_ptr<Card>(createGang(++i, wordsInDeckFile, monstersInGang, countWords)));
            --i;
        }
        else if(wordsInDeckFile[i] == "SolarEclipse") {
            m_cards.push_back(std::unique_ptr<Card>(new SolarEclipse(wordsInDeckFile[i])));
        }
        else if(wordsInDeckFile[i] == "PotionsMerchant") {
            m_cards.push_back(std::unique_ptr<Card>(new PotionsMerchant(wordsInDeckFile[i])));
        }
        else {
            throw std::runtime_error("Invalid Cards File");
        }
    }
    if(m_cards.size() < 2) {
        throw std::runtime_error("Invalid Cards File"); 
    }

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    
    std::ifstream playersFile(playersPath);
    if(!playersFile.is_open()) {
        throw std::runtime_error("Invalid Players File");
    }
    string line;
    while(std::getline(playersFile, line)) {
        vector<string> wordsInLine;
        std::istringstream stringStream(line);
        while(stringStream >> word) {
            wordsInLine.push_back(word);
        }
        if(wordsInLine.size() != 3 || wordsInLine[0].length() < 3 || wordsInLine[0].length() > 15) {
            throw std::runtime_error("Invalid Players File");
        }
        if(wordsInLine[1] == "Warrior") {
            m_players.push_back(shared_ptr<Player>(new Warrior(wordsInLine[0], wordsInLine[2])));
            m_leaderBoard.push_back(shared_ptr<Player>(m_players.back()));
            m_numberOfPlayers++;
        }
        else if(wordsInLine[1] == "Sorcerer") {
            m_players.push_back(shared_ptr<Player>(new Sorcerer(wordsInLine[0], wordsInLine[2])));
            m_leaderBoard.push_back(shared_ptr<Player>(m_players.back()));
            m_numberOfPlayers++;
        }
        else {
            throw std::runtime_error("Invalid Players File");
        }
    }
    if(m_players.size() < 2 || m_players.size() > 6) {
        throw std::runtime_error("Invalid Players File");
    }

    /*============================================*/

    this->m_turnIndex = 1;
}

void Mtmchkin::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Draw a card from the deck
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the card
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    Card& currentCard = *m_cards.front();
    printTurnDetails(m_turnIndex, player, currentCard);
    currentCard.applyCard(player); //includes outcome print
    m_cards.push_back(std::unique_ptr<Card>(std::move(m_cards.front())));
    m_cards.pop_front();

    m_turnIndex++;
}

void Mtmchkin::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {    
        if(!(*iterator)->isKnockedOut()) {
            playTurn(**iterator);
        }
    }

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();
    
    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    std::sort(m_leaderBoard.begin(), m_leaderBoard.end(), rankComparator);

    for(int i = 0; i < m_numberOfPlayers; i++) {
        printLeaderBoardEntry(i+1, *m_leaderBoard[i]);
    }

    /*=======================================================================================*/

    printBarrier();
}

bool Mtmchkin::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/

    int count = 0;
    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {
        if(!(*iterator)->isKnockedOut()) {
            break;
        }
        count++;
    }
    if(count == m_numberOfPlayers) {
        return true;
    }
    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {
        if((*iterator)->isMaxLevel()) {
            return true;
        }
    }
    return false;

    /*===================================================*/
}

void Mtmchkin::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    int count = 1;
    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {
        printStartPlayerEntry(count, **iterator);
        count++;
    }
    
    /*=========================================================================================*/
    
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    if(m_leaderBoard[0]->isMaxLevel()) {
        printWinner(*m_leaderBoard[0]);
        return;
    }
    printNoWinners();

    /*========================================================================*/
}

bool rankComparator(std::shared_ptr<Player> playerOne, std::shared_ptr<Player> playerTwo) {
    if(playerOne->getLevel() > playerTwo->getLevel()) {
        return true;
    }
    else if(playerOne->getLevel() < playerTwo->getLevel()) {
        return false;
    }
    else {
        if(playerOne->getCoins() > playerTwo->getCoins()) {
            return true;
        }
        else if(playerOne->getCoins() < playerTwo->getCoins()) {
            return false;
        }
        else {
            return playerOne->getName() < playerTwo->getName();
        }
    }   
}

