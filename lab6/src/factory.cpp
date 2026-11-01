#include "factory.h"

std::shared_ptr<NPC> Factory::create(const NpcType& type, const std::string& name, int x, int y)
{
    std::shared_ptr<NPC> result = nullptr;
    switch (type)
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
        throw std::invalid_argument("Unknown NPC type");
    }

    if (result)
    {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}
