#include "orc.h"

#ifndef BOULDER_PAPER_SHEARS

bool OrcVisitor::visit(const std::shared_ptr<Slaver>& defender) const
{
    return true;
}

bool OrcVisitor::visit(const std::shared_ptr<Druid>& defender) const
{
    return true;
}

bool OrcVisitor::visit(const std::shared_ptr<Orc>& defender) const
{
    return true;
}
#endif

#ifdef BOULDER_PAPER_SHEARS

bool OrcVisitor::visit(const std::shared_ptr<Slaver>& defender) const
{
    return true;
}

bool OrcVisitor::visit(const std::shared_ptr<Druid>& defender) const
{
    return false;
}

bool OrcVisitor::visit(const std::shared_ptr<Orc>& defender) const
{
    return false;
}
#endif

Orc::Orc() : NPC(OrcType,"Orc", 0, 0)
{
    attackRange = 10, movementRange = 20;
}

Orc::Orc(std::string name, int x, int y) : NPC(OrcType, name, x, y)
{
    attackRange = 10, movementRange = 20;
}

Orc::Orc(std::istream& in) : NPC(OrcType, in)
{
    attackRange = 10, movementRange = 20;
}

void Orc::save(std::ostream& out)
{
    out << OrcType << std::endl;
    NPC::save(out);
}

bool Orc::accept(const std::shared_ptr<NPC>& attacker) const
{
    auto attacker_visitor = VisitorFactory::create(attacker->getType());

    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Orc> defender = std::dynamic_pointer_cast<Orc>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& out, Orc& orc)
{
    out << "Orc: " << *static_cast<NPC*>(&orc) << std::endl;
    return out;
}

void Orc::print()
{
    std::cout << *this;
}
