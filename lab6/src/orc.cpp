#include "orc.h"

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

Orc::Orc() : NPC(OrcType, "Orc", 0, 0) {}

Orc::Orc(const std::string& name, int x, int y) : NPC(OrcType, name, x, y) {}

Orc::Orc(std::istream& is) : NPC(OrcType, is) {}

void Orc::save(std::ostream& os)
{
    os << OrcType << std::endl;
    NPC::save(os);
}

bool Orc::accept(const std::shared_ptr<FightVisitor>& visitor, const std::shared_ptr<NPC>& attacker) const
{
    std::shared_ptr<const NPC> npcConstPtr = shared_from_this();
    std::shared_ptr<NPC> npcPtr = std::const_pointer_cast<NPC>(npcConstPtr);
    std::shared_ptr<Orc> defender = std::dynamic_pointer_cast<Orc>(npcPtr);

    bool result = visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}

std::ostream& operator<<(std::ostream& os, Orc& orc)
{
    os << "Orc: " << *static_cast<NPC*>(&orc) << std::endl;
    return os;
}

void Orc::print()
{
    std::cout << *this;
}
