#ifndef OOP_DATA_METHODS_H
#define OOP_DATA_METHODS_H

#include "npc.h"
#include "druid.h"
#include "orc.h"
#include "slaver.h"
#include "factory.h"
#include "utils.h"

class DataMethods
{
public:
    static void saveData(const std::set<std::shared_ptr<NPC>>& data, const std::string& filename);
    static set_t loadData(const std::string& filename);
};

std::ostream& operator<<(std::ostream& os, const set_t& array);

#endif //OOP_DATA_METHODS_H