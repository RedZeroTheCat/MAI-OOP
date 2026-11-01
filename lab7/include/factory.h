#ifndef OOP_FACTORY_H
#define OOP_FACTORY_H

#include "npc.h"
#include "druid.h"
#include "orc.h"
#include "slaver.h"
#include "observers.h"

class Factory
{
public:
    static std::shared_ptr<NPC> create(const NpcType& type, std::string name, int x, int y);
};

class VisitorFactory
{
public:
    static std::shared_ptr<FightVisitor> create(const NpcType& type);
};

#endif //OOP_FACTORY_H