#include "npc.h"

NPC::NPC(NpcType t, const std::string& name, int x, int y) : type(t), name(name), x(x), y(y) {}

NPC::NPC(NpcType type, std::istream& is) : type(type)
{
    is >> name >> x >> y;
}

int NPC::getX() const
{
    return x;
}

int NPC::getY() const
{
    return y;
}

NpcType& NPC::getType()
{
    return type;
}

std::string NPC::getName()
{
    return name;
}


void NPC::subscribe(const std::shared_ptr<IFightObserver>& observer)
{
    observers.push_back(observer);
}

void NPC::fightNotify(const std::shared_ptr<NPC>& defender, bool isWin)
{
    for (auto& observer : observers)
    {
        observer->inFight(shared_from_this(), defender, isWin);
    }
}

bool NPC::inRange(const std::shared_ptr<NPC>& other, size_t distance) const
{
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
    {
        return true;
    }
    return false;
}

void NPC::save(std::ostream& os)
{
    os << '$' << name << '\n' << x << '\n' << y << std::endl;
}

std::ostream& operator<<(std::ostream& os, NPC& npc)
{
    os << npc.name << " at (x: " << npc.x << ", y: " << npc.y << ')';
    return os;
}




