#include "npc.h"
#include "slaver.h"
#include "druid.h"
#include "orc.h"
#include "utils.h"
#include "factory.h"
#include "observers.h"
#include "data_methods.h"
#include "fight_manager.h"

std::mutex print_mutex;

const int countOrcs = 6;
const int countDruids = 22;
const int countSlavers = 22;
const int countTotal = countOrcs + countDruids + countSlavers;

int main()
{
    const int maxX = 100;
    const int maxY = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    set_t combatants;

    std::cout << "Generating combatants" << std::endl;
    for (size_t i = 0; i < countTotal; ++i)
    {
        NpcType currentType;
        if (i < countOrcs)
        {
            currentType = OrcType;
        }
        else if (i - countOrcs < countDruids)
        {
            currentType = DruidType;
        }
        else if (i - countOrcs - countDruids < countSlavers)
        {
            currentType = SlaverType;
        }
        combatants.insert(Factory::create(
            currentType,
            "Bob " + toRoman(i + 1),
            dis(gen) % maxX,
            dis(gen) % maxY));
    }

    std::cout << "Saving combatants" << std::endl;
    DataMethods::saveData(combatants, "npc.txt");

    std::cout << "Loading combatants" << std::endl;
    combatants = DataMethods::loadData("npc.txt");

    std::cout << "Initial combatants:" << std::endl << combatants;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&combatants, maxX, maxY, &dis, &gen]()
    {
        while(true)
        {
            if (timer == MAX_TIME)
            {
                break;
            }
            for (const std::shared_ptr<NPC>& npc : combatants)
            {
                if (npc->isAlive())
                {
                    int deltaX = dis(gen) % (npc->getMovementRange() * 2) - npc->getMovementRange();
                    int deltaY = dis(gen) % (npc->getMovementRange() * 2) - npc->getMovementRange();
                    npc->move(deltaX, deltaY, maxX, maxY);
                }
            }
            for (const std::shared_ptr<NPC>& npc : combatants)
            {
                for (const std::shared_ptr<NPC>& other : combatants)
                {
                    if (other != npc && npc->isAlive() && other->isAlive() && npc->inRange(other))
                    {
                        FightManager::get().addEvent({npc, other});
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    std::cout << "Rolling initiative... Fight!" << std::endl;

    while(true)
    {
        if (timer == MAX_TIME)
        {
            break;
        }
        const int grid = 20,
        stepX = maxX / grid,
        stepY = maxY / grid;
        {
            std::array<char, grid* grid> battlefield{0};
            for (const std::shared_ptr<NPC>& npc : combatants)
            {
                auto [x, y] = npc->getPos();
                int i = x / stepX;
                int j = y / stepY;

                if (npc->isAlive())
                {
                    switch (npc->getType())
                    {
                        case DruidType:
                            battlefield[i + grid * j] = 'D';
                            break;
                        case OrcType:
                            battlefield[i + grid * j] = 'O';
                            break;
                        case SlaverType:
                            battlefield[i + grid * j] = 'S';
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    battlefield[i + grid * j] = '_';
                }
            }

            std::lock_guard<std::mutex> lck(print_mutex);

            std::cout << "Round " << timer << std::endl;
            for (int j = 0; j < grid; ++j)
            {
                for (int i = 0; i < grid; ++i)
                {
                    char c = battlefield[i + j * grid];
                    if (c != 0)
                    {
                        std::cout << "[" << c << "]";
                    }
                    else
                    {
                        std:: cout << "[ ]";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++timer;
    }

    move_thread.join();
    fight_thread.join();

    std::cout << "Survivors:" << std::endl << combatants;

    return 0;
}
