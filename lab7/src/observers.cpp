#include "observers.h"

std::shared_ptr<IFightObserver> TextObserver::get()
{
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::inFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool isWin)
{
    if (isWin)
    {
        std::cout << std::endl << "-- Murder --" << std::endl;
        attacker->print();
        defender->print();
    }
}

std::string FileObserver::NPCgetType(const NpcType& type)
{
    std::string ans;
    switch (type)
    {
    case SlaverType:
        ans = "Slaver";
        return ans;
    case DruidType:
        ans = "Druid";
        return ans;
    case OrcType:
        ans = "Orc";
        return ans;
    default:
        throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<IFightObserver> FileObserver::get()
{
    static FileObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void FileObserver::inFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool isWin)
{
    if (isWin)
    {
        if (!fs.is_open())
        {
            fs.open("log.txt");
        }
        auto [attackerX, attackerY] = attacker->getPos();
        auto [defenderX, defenderY] = defender->getPos();

        auto attackerName = attacker->getName();
        auto defenderName = defender->getName();

        fs << std::endl << "-- Murder --" << std::endl;
        fs << NPCgetType(attacker->getType()) << ' ' << attackerName << ": ";
        fs << "(x:" << attackerX << ", y:" << attackerY << ")" << std::endl;
        fs << NPCgetType(defender->getType()) << ' ' << defenderName << ": ";
        fs << "(x:" << defenderX << ", y:" << defenderY << ")" << std::endl;
    }
}

