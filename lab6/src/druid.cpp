#include "druid.h"

bool DruidVisitor::visit(const std::shared_ptr<Slaver>& defender) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Druid>& defender) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Orc>& defender) const
{
    return false;
}

Druid::Druid() : NPC(DruidType, "Druid", 0, 0) {}

Druid::Druid(const std::string& name, int x, int y) : NPC(DruidType, name, x, y) {}

Druid::Druid(std::istream& is) : NPC(DruidType, is) {}

void Druid::save(std::ostream& os)
{
    os << DruidType << std::endl;
    NPC::save(os);
}

bool Druid::accept(const std::shared_ptr<FightVisitor>& visitor, const std::shared_ptr<NPC>& attacker) const
{
    std::shared_ptr<const NPC> npcConstPtr = shared_from_this();
    std::shared_ptr<NPC> npcPtr = std::const_pointer_cast<NPC>(npcConstPtr);
    std::shared_ptr<Druid> defender = std::dynamic_pointer_cast<Druid>(npcPtr);

    bool result = visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& os, Druid& druid)
{
    os << "Druid: " << *static_cast<NPC*>(&druid) << std::endl;
    return os;
}

void Druid::print()
{
    std::cout << *this;
}

