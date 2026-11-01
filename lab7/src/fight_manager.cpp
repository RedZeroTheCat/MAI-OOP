#include "fight_manager.h"

FightManager& FightManager::get()
{
    static FightManager instance;
    return instance;
}

void FightManager::addEvent(FightEvent&& event)
{
    std::lock_guard<std::shared_mutex> lock(mtx);
    events.push(event);
}

void FightManager::operator()()
{
    while (true)
    {
        {
            if (timer == MAX_TIME)
            {
                return;
            }
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mtx);
                if (!events.empty())
                {
                    event = events.front();
                    events.pop();
                }
            }
            if (event)
            {
                if (event->attacker->isAlive()
                    && event->defender->isAlive()
                    && event->attacker->diceRoll() > event->defender->diceRoll()
                    && event->defender->accept(event->attacker))
                {
                    event->defender->mustDie();
                }
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
}
