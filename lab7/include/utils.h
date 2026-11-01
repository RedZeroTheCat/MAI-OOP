#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include "npc.h"
#include "slaver.h"
#include "druid.h"
#include "orc.h"

using set_t = std::set<std::shared_ptr<NPC>>;

std::string toRoman(int number);

#endif //OOP_UTILS_H