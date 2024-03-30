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
    Behavior(const Behavior& behavior) = default;
    Behavior& operator=(const Behavior& behavior) = default;

    virtual ~Behavior() = default;

    std::string getBehavior() const;
    virtual int makePotionsMerchantMove(Player& player, int cost, int givenHP) = 0;
};


class Responsible : public Behavior {

public:
    Responsible(const std::string& behavior);
    Responsible(const Responsible& responsible) = default;
    Responsible& operator=(const Responsible& responsible) = default;

    ~Responsible() = default;

    int makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};


class RiskTaking : public Behavior {

public:
    RiskTaking(const std::string& behavior);
    RiskTaking(const RiskTaking& riskTaking) = default;
    RiskTaking& operator=(const RiskTaking& riskTaking) = default;

    ~RiskTaking() = default;

    int makePotionsMerchantMove(Player& player, int cost, int givenHP) override;

};

#endif