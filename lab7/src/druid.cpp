#include "druid.h"

#ifndef BOULDER_PAPER_SHEARS

bool DruidVisitor::visit(const std::shared_ptr<Slaver>& attacker) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Druid>& attacker) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Orc>& attacker) const
{
    return false;
}
#endif

#ifdef BOULDER_PAPER_SHEARS

bool DruidVisitor::visit(const std::shared_ptr<Slaver>& attacker) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Druid>& attacker) const
{
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Orc>& attacker) const
{
    return true;
}

#endif

Druid::Druid() : NPC(DruidType, "Druid", 0, 0)
{
    attackRange = 10, movementRange = 10;
}

Druid::Druid(std::string name, int x, int y) : NPC(DruidType, name, x, y)
{
    attackRange = 10, movementRange = 10;
}

Druid::Druid(std::istream& is) : NPC(DruidType, is)
{
    attackRange = 10, movementRange = 10;
}

void Druid::save(std::ostream& os)
{
    os << DruidType << std::endl;
    NPC::save(os);
}

bool Druid::accept(const std::shared_ptr<NPC>& attacker) const
{
    auto attacker_visitor = VisitorFactory::create(attacker->getType());

    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Druid> defender = std::dynamic_pointer_cast<Druid>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& out, Druid& druid)
{
    out << "Druid: " << *static_cast<NPC*>(&druid) << std::endl;
    return out;
}

void Druid::print()
{
    std::cout << *this;
}
