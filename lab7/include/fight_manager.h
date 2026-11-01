#ifndef OOP_FIGHT_MANAGER_H
#define OOP_FIGHT_MANAGER_H

#include "npc.h"
#include "druid.h"
#include "orc.h"
#include "slaver.h"

inline const int MAX_TIME = 30;

inline int timer = 0;

struct FightEvent
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager
{
public:

    static FightManager& get();
    void addEvent(FightEvent&& event);
    void operator()();

    ~FightManager() = default;

private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() = default;
};

#endif //OOP_FIGHT_MANAGER_H