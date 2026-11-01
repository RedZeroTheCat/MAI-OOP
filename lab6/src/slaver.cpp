#include "slaver.h"

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

Slaver::Slaver() : NPC(SlaverType, "Slaver", 0, 0) {}

Slaver::Slaver(const std::string& name, int x, int y) : NPC(SlaverType, name, x, y) {}

Slaver::Slaver(std::istream& is) : NPC(SlaverType, is) {}

void Slaver::save(std::ostream& os)
{
    os << SlaverType << std::endl;
    NPC::save(os);
}

bool Slaver::accept(const std::shared_ptr<FightVisitor>& visitor, const std::shared_ptr<NPC>& attacker) const
{
    std::shared_ptr<const NPC> npcConstPtr = shared_from_this();
    std::shared_ptr<NPC> npcPtr = std::const_pointer_cast<NPC>(npcConstPtr);
    std::shared_ptr<Slaver> defender = std::dynamic_pointer_cast<Slaver>(npcPtr);

    bool result = visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& os, Slaver& slaver)
{
    os << "Slaver: " << *static_cast<NPC*>(&slaver) << std::endl;
    return os;
}

void Slaver::print()
{
    std::cout << *this;
}

