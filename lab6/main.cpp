#include "npc.h"
#include "slaver.h"
#include "druid.h"
#include "orc.h"
#include "utils.h"
#include "factory.h"
#include "observers.h"
#include "data_methods.h"


const int orcAmount = 2;
const int druidAmount = 24;
const int slaverAmount = 24;
const int totalAmount = orcAmount + druidAmount + slaverAmount;


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 500);

    set_t combatants;

    std::cout << "Generating combatants" << std::endl;

    for (size_t i = 0; i < totalAmount; ++i)
    {
        int currentType = 0;
        if (i < orcAmount)
        {
            currentType = 2;
        }
        else if (i >= orcAmount && i < druidAmount + orcAmount)
        {
            currentType = 1;
        }
        else if (i >= druidAmount + orcAmount && i < totalAmount)
        {
            currentType = 0;
        }
        combatants.insert(Factory::create(NpcType(currentType),
                        "Bob "+toRoman(i+1),
                        distrib(gen),
                        distrib(gen)));
    }

    std::cout << "Saving combatants" << std::endl;
    DataMethods::saveData(combatants, "npc.txt");

    std::cout << "Loading combatants" << std::endl;
    combatants = DataMethods::loadData("npc.txt");

    std::cout << combatants << std::endl;

    std::cout << "Rolling initiative... Fight!" << std::endl << combatants;
    for (size_t distance = 20; distance <= 500 && !combatants.empty(); distance += 80)
    {
        auto kia = fight(combatants, distance);
        for (auto& killed : kia)
        {
            combatants.erase(killed);
        }

        std::cout << "--- Combat stats --- \n distance: " << distance << "\n killed: " << kia.size() << std::endl;
        std::cout << std::endl << std::endl;
    }

    std::cout << "Survivors:\n" << combatants << std::endl;

    return 0;
}