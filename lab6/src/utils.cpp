#include "utils.h"


std::unordered_map<NpcType, std::shared_ptr<FightVisitor>> visitors = {
    {SlaverType, std::make_shared<SlaverVisitor>()},
    {DruidType, std::make_shared<DruidVisitor>()},
    {OrcType, std::make_shared<OrcVisitor>()}
};


set_t fight(const set_t& combatants, size_t distance)
{
    set_t kia;

    for (const auto& attacker : combatants)
    {
        for (const auto& defender : combatants)
        {
            if (attacker != defender
                && attacker->inRange(defender, distance)
                && kia.find(defender) == kia.end())
            {
                bool attackerWin = defender->accept(visitors[attacker->getType()], attacker);
                if (attackerWin)
                {
                    kia.insert(defender);
                }
            }
        }
    }

    return kia;
}

std::string toRoman(int number)
{
    const std::vector<std::pair<int, std::string>> romanBase = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    std::string result;
    for (const auto& segmentum : romanBase)
    {
        while (number >= segmentum.first)
        {
            result += segmentum.second;
            number -= segmentum.first;
        }
    }
    return result;
}

