
#include "Mtmchkin.h"
#include "utilities.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>


Gang* createGang(int& index, vector<string>& givenWords, vector<std::unique_ptr<Encounter>>& monstersInGang, int numberOfWords);
bool rankComparator(std::shared_ptr<Player> playerOne, std::shared_ptr<Player> playerTwo);
bool isAlphaString(const string& string);



Mtmchkin::Mtmchkin(const string& deckPath, const string& playersPath) : m_numberOfPlayers(0) 
{
    string word;
    vector<string> wordsInDeckFile;

    /*===== Open and read cards file =====*/

    int countEncounters = 0;
    std::ifstream deckFile(deckPath);
    if(!deckFile.is_open()) {
        throw std::runtime_error("Invalid Cards File");
    }
    while(deckFile >> word) {
        wordsInDeckFile.push_back(word);
    }
    int numberOfWords = std::distance(wordsInDeckFile.begin(), wordsInDeckFile.end());
    for(int i=0; i<numberOfWords; i++) {
        if(wordsInDeckFile[i] == "Goblin") {
            m_cards.push_back(std::unique_ptr<Card>(new Goblin()));
            countEncounters++;
        } 
        else if(wordsInDeckFile[i] == "Giant") {
            m_cards.push_back(std::unique_ptr<Card>(new Giant()));
            countEncounters++;
        }
        else if(wordsInDeckFile[i] == "Dragon") {
            m_cards.push_back(std::unique_ptr<Card>(new Dragon()));
            countEncounters++;
        }
        else if(wordsInDeckFile[i] == "Gang") {
            vector<std::unique_ptr<Encounter>> monstersInGang;
            m_cards.push_back(std::unique_ptr<Card>(createGang(++i, wordsInDeckFile, monstersInGang, numberOfWords)));
            countEncounters++;
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
    if(m_cards.size() < 2 || countEncounters == 0) {
        throw std::runtime_error("Invalid Cards File");
    }

    /*==========================================*/


    /*===== Open and Read players file =====*/
    
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
        if(wordsInLine.size() != 3 || !isAlphaString(wordsInLine[0]) || wordsInLine[0].length() < 3 || wordsInLine[0].length() > 15) {
            throw std::runtime_error("Invalid Players File");
        }
        if(wordsInLine[1] == "Warrior" || wordsInLine[1] == "Sorcerer") {
            m_players.push_back(shared_ptr<Player>(new Player(wordsInLine[0], wordsInLine[2], wordsInLine[1])));
            m_leaderBoard.push_back(shared_ptr<Player>(m_players.back()));
        }
        else {
            throw std::runtime_error("Invalid Players File");
        }
    }
    m_numberOfPlayers = std::distance(m_players.begin(), m_players.end());
    if(m_players.size() < 2 || m_players.size() > 6) {
        throw std::runtime_error("Invalid Players File");
    }

    /*============================================*/

    this->m_turnIndex = 1;
}

void Mtmchkin::playTurn(Player& player) {

    Card& currentCard = *m_cards.front();
    printTurnDetails(m_turnIndex, player, currentCard);
    currentCard.applyCard(player); //includes outcome print
    m_cards.push_back(std::unique_ptr<Card>(std::move(m_cards.front())));
    m_cards.pop_front();

    m_turnIndex++;
}

void Mtmchkin::playRound() {

    printRoundStart();

    /*===== Play a turn for each player =====*/

    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {    
        if(!(*iterator)->isKnockedOut()) {
            playTurn(**iterator);
        }
    }

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();
    
    /*===== Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    std::sort(m_leaderBoard.begin(), m_leaderBoard.end(), rankComparator);

    for(int i = 0; i < m_numberOfPlayers; i++) {
        printLeaderBoardEntry(i+1, *m_leaderBoard[i]);
    }

    /*=======================================================================================*/

    printBarrier();
}

bool Mtmchkin::isGameOver() const {
    /*===== Implement the game over condition =====*/

    int countKnockedOut = 0;
    for(auto iterator = m_players.begin(); iterator != m_players.end(); ++iterator) {
        if(!(*iterator)->isKnockedOut()) {
            break;
        }
        countKnockedOut++;
    }
    if(countKnockedOut == m_numberOfPlayers) {
        return true;
    }
    // Checks if at least one player has reached Max Level
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
    /*===== Print start message entry for each player using "printStartPlayerEntry" =====*/

    for(int i=0; i < m_numberOfPlayers; i++) {
        printStartPlayerEntry(i+1, *m_players[i]);
    }
    
    /*=========================================================================================*/
    
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    /*===== Print either a "winner" message or "no winner" message =====*/

    if(m_leaderBoard[0]->isMaxLevel()) {
        printWinner(*m_leaderBoard[0]);
        return;
    }
    printNoWinners();

    /*========================================================================*/
}

Gang* createGang(int& index, vector<string>& givenWords, vector<std::unique_ptr<Encounter>>& monstersInGang, int numberOfWords) {
    int sizeOfGang = std::stoi(givenWords[index]);
    int countEncounters = 1;
    if(sizeOfGang < 2 || sizeOfGang > numberOfWords - (index+1)) {
        throw std::runtime_error("Invalid Cards File");
    }
    ++index;
    while(countEncounters <= sizeOfGang) {
        if(index >= numberOfWords) {
            throw std::runtime_error("Invalid Cards File");
        }
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
            ++index;
            vector<std::unique_ptr<Encounter>> monstersInOtherGang;
            monstersInGang.push_back(std::unique_ptr<Encounter>(createGang(index, givenWords, monstersInOtherGang, numberOfWords)));
        }
        else {
            throw std::runtime_error("Invalid Cards File");
        }
        ++countEncounters;
        ++index;
    }
    --index;
    return new Gang(monstersInGang);
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
            return playerOne->getName() <= playerTwo->getName();
        }
    }   
}

bool isAlphaString(const string& givenString) {
    for(char character : givenString) { // The Character to be checked
        if(!std::isalpha(character)) {
            return false;
        }
    }
    return true;
}
