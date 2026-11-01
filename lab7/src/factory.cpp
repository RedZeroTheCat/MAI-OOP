#include "factory.h"

std::shared_ptr<NPC> Factory::create(const NpcType& type, std::string name, int x, int y)
{
    std::shared_ptr<NPC> result;
    switch(type)
    {
    case SlaverType:
        result = std::make_shared<Slaver>(name, x, y);
        break;
    case DruidType:
        result = std::make_shared<Druid>(name, x, y);
        break;
    case OrcType:
        result = std::make_shared<Orc>(name, x, y);
        break;
    default:
        throw std::invalid_argument("Unknown type of NPC:");
    }

    if (result)
    {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}

std::shared_ptr<FightVisitor> VisitorFactory::create(const NpcType& type)
{
    std::shared_ptr<FightVisitor> result;
    switch (type)
    {
    case DruidType:
        result = std::static_pointer_cast<FightVisitor>(std::make_shared<DruidVisitor>());
        break;

    case OrcType:
        result = std::static_pointer_cast<FightVisitor>(std::make_shared<OrcVisitor>());
        break;

    case SlaverType:
        result = std::static_pointer_cast<FightVisitor>(std::make_shared<SlaverVisitor>());
        break;

    default:
        throw std::invalid_argument("Unknown type of Npc and Npc visitor");
    }

    return result;
}