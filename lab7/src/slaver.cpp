#include "slaver.h"

#ifndef BOULDER_PAPER_SHEARS

bool SlaverVisitor::visit(const std::shared_ptr<Slaver>& defender) const
{
    return false;
}

bool SlaverVisitor::visit(const std::shared_ptr<Druid>& defender) const
{
    return true;
}

bool SlaverVisitor::visit(const std::shared_ptr<Orc>& defender) const
{
    return false;
}
#endif

#ifdef BOULDER_PAPER_SHEARS

bool SlaverVisitor::visit(const std::shared_ptr<Slaver>& defender) const
{
    return false;
}

bool SlaverVisitor::visit(const std::shared_ptr<Druid>& defender) const
{
    return true;
}

bool SlaverVisitor::visit(const std::shared_ptr<Orc>& defender) const
{
    return false;
}
#endif

Slaver::Slaver() : NPC(SlaverType, "Slaver", 0, 0)
{
    attackRange = 10;
    movementRange = 10;
}

Slaver::Slaver(std::string name, int x, int y) : NPC(SlaverType, name, x, y)
{
    attackRange = 10;
    movementRange = 10;
}

Slaver::Slaver(std::istream& is) : NPC(SlaverType, is)
{
    attackRange = 10;
    movementRange = 10;
}

void Slaver::save(std::ostream& out)
{
    out << SlaverType << std::endl;
    NPC::save(out);
}

bool Slaver::accept(const std::shared_ptr<NPC>& attacker) const
{
    auto attacker_visitor = VisitorFactory::create(attacker->getType());

    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Slaver> defender = std::dynamic_pointer_cast<Slaver>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& out, Slaver& slaver)
{
    out << "Slaver: " << *static_cast<NPC*>(&slaver) << std::endl;
    return out;
}

void Slaver::print()
{
    std::cout << *this;
}

