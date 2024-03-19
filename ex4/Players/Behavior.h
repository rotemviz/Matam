#ifndef BEHAVIORS
#define BEHAVIORS

#include "Player.h"

#include <string>
using std::string;

class Behavior
{
protected:
    string m_behavior;
public:
    Behavior(const string& behavior);
    
    ~Behavior() = default;
    Behavior(const Behavior& behavior) = default; // maybe will change
    Behavior& operator=(const Behavior& behavior) = default; // maybe will change

    string getBehavior() const;
    virtual void makePotionsMerchantMove(Player& player, int cost, int givenHP) = 0;
};


class Responsible : public Behavior {

public:
    Responsible(const string& behavior);
    ~Responsible() = default;
    Responsible(const Responsible& responsible) = default; // maybe will change
    Responsible& operator=(const Responsible& responsible) = default; // maybe will change

    void makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};


class RiskTaking : public Behavior {

public:
    RiskTaking(const string& behavior);
    ~RiskTaking() = default;
    RiskTaking(const RiskTaking& riskTaking) = default; // maybe will change
    RiskTaking& operator=(const RiskTaking& riskTaking) = default; // maybe will change

    void makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};

#endif