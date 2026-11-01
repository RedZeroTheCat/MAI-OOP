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
    std::string name;
    switch (type)
    {
    case SlaverType:
        name = "Slaver";
        return name;
    case DruidType:
        name = "Druid";
        return name;
    case OrcType:
        name = "Orc";
        return name;
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
        if (!file.is_open())
        {
            file.open("log.txt");
        }
        file << std::endl << "-- Murder --" << std::endl;
        file << NPCgetType(attacker->getType()) << std::endl;
        file << "(x: " << attacker->getX() << ", y: " << attacker->getY() << ")" << std::endl;
        file << NPCgetType(defender->getType()) << std::endl;
        file << "(X: " << defender->getX() << ", y: " << defender->getY() << ")" << std::endl;
    }
}



