#include "npc.h"

NPC::NPC(NpcType type, std::string name, int x, int y) : type(type), name(name), x(x), y(y) {}

NPC::NPC(NpcType type, std::istream& in) : type(type)
{
    in >> name;
    in >> x;
    in >> y;
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

std::string NPC::getName()
{
    std::lock_guard<std::mutex> lck(mtx);
    return name;
}

std::pair<int, int> NPC::getPos()
{
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};
}

bool NPC::inRange(const std::shared_ptr<NPC>& other)
{
    auto [otherX, otherY] = other->getPos();

    std::lock_guard<std::mutex> lck(mtx);
    if (std::pow(x - otherX, 2) + std::pow(y - otherY, 2) <= std::pow(attackRange, 2))
    {
        return true;
    }
    return false;
}

NpcType& NPC::getType()
{
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

void NPC::save(std::ostream& os)
{
    os << '$' << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

int NPC::getMovementRange()
{
    std::lock_guard<std::mutex> lck(mtx);
    return movementRange;
}

void NPC::move(int shiftX, int shiftY, int maxX, int maxY)
{
    std::lock_guard<std::mutex> lck(mtx);

    if (shiftX > movementRange || shiftY > movementRange)
    {
        throw std::invalid_argument("Max move distance is " + std::to_string(movementRange));
    }

    if ((x + shiftX >= 0) && (x + shiftX <= maxX))
    {
        x += shiftX;
    }

    if ((y + shiftY >= 0) && (y + shiftY <= maxY))
    {
        y += shiftY;
    }
}

bool NPC::isAlive()
{
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::mustDie()
{
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

int NPC::diceRoll()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    return dis(gen) % 6 + 1;
}

std::ostream& operator<<(std::ostream& os, NPC& npc)
{
    os << npc.name << " at (x:" << npc.x << ", y:" << npc.y << ")";
    return os;
}

