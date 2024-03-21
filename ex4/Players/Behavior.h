#ifndef BEHAVIORS
#define BEHAVIORS

class Player;

#include <string>

class Behavior
{
protected:
    std::string m_behavior;
public:
    Behavior(const std::string& behavior);
    
    ~Behavior() = default;
    Behavior(const Behavior& behavior) = default; // maybe will change
    Behavior& operator=(const Behavior& behavior) = default; // maybe will change

    std::string getBehavior() const;
    virtual void makePotionsMerchantMove(Player& player, int cost, int givenHP) = 0;
};


class Responsible : public Behavior {

public:
    Responsible(const std::string& behavior);
    ~Responsible() = default;
    Responsible(const Responsible& responsible) = default; // maybe will change
    Responsible& operator=(const Responsible& responsible) = default; // maybe will change

    void makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};


class RiskTaking : public Behavior {

public:
    RiskTaking(const std::string& behavior);
    ~RiskTaking() = default;
    RiskTaking(const RiskTaking& riskTaking) = default; // maybe will change
    RiskTaking& operator=(const RiskTaking& riskTaking) = default; // maybe will change

    void makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};

#endif