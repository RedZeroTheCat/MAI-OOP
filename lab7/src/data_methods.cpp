#include "utils.h"
#include "data_methods.h"

void DataMethods::saveData(const set_t& array, const std::string& filename)
{
    std::ofstream fs(filename);

    fs << array.size() << std::endl;

    for (auto& elem : array)
    {
        elem->save(fs);
    }
    fs.flush();
    fs.close();
}

set_t DataMethods::loadData(const std::string& filename)
{
    set_t result;
    int count;
    int x, y;
    NpcType type;

    char temp;

    std::string npcCount;
    std::ifstream is(filename);

    if (!is.good() || !is.is_open())
    {
        throw std::invalid_argument("Failed to open file");
    }

    while (true)
    {
        is.get(temp);
        if (is.eof())
        {
            throw std::invalid_argument("File is empty");
        }
        if (temp == '\n')
        {
            break;
        }
        if (temp < '0' || temp > '9')
        {
            throw std::invalid_argument("Invalid characters in load-file");
        }

        npcCount += temp;
    }
    if (npcCount.empty())
    {
        throw std::invalid_argument("Wrong load-file structure: no npc count");
    }
    count = std::stoi(npcCount);
    npcCount.clear();

    for (int i = 0; i < count; ++i)
    {
        if (is.eof())
        {
            throw std::invalid_argument("Bad load-file structure:no type etc.");
        }
        if (is.eof())
        {
            throw std::invalid_argument("Wrong load-file structure: no npc type and after");
        }

        std::string xNum, yNum, npcType, name;

        // type
        while (true)
        {
            is.get(temp);
            if (is.eof())
            {
                throw std::invalid_argument("Wrong load-file structure: no npc type");
            }
            if (temp == '\n')
            {
                break;
            }
            if (temp < '0' || temp > '9')
            {
                throw std::invalid_argument("Invalid characters in load-file");
            }

            npcType += temp;
        }
        if (npcType.empty())
        {
            throw std::invalid_argument("Wrong load-file structure: no npc type");
        }
        type = NpcType(std::stoi(npcType));
        npcType.clear();
        // ~type

        if (is.eof())
        {
            throw std::invalid_argument("Wrong load-file structure: no name and after");
        }

        // name
        if (!is.get(temp) || temp != '$')
        {
            throw std::invalid_argument("Wrong load-file structure: marker '$' not found");
        }
        while (true)
        {
            is.get(temp);
            if (is.eof())
            {
                throw std::invalid_argument("Wrong load-file structure: no name");
            }
            if (temp == '\n')
            {
                break;
            }
            name += temp;
        }
        if (name.empty())
        {
            throw std::invalid_argument("Wrong load-file structure: no name");
        }
        // ~name

        if (is.eof())
        {
            throw std::invalid_argument("Wrong load-file structure: no x and y coords");
        }

        // x
        while(true)
        {
            is.get(temp);
            if (is.eof())
            {
                throw std::invalid_argument("Wrong load-file structure: no x and y coords");
            }
            if (temp == '\n')
            {
                break;
            }
            if (temp < '0' || temp > '9')
            {
                throw std::invalid_argument("Invalid characters in load-file");
            }
            xNum += temp;
        }
        if (xNum.empty())
        {
            throw std::invalid_argument("Bad load-file structure: no x number");
        }
        x = std::stoi(xNum);
        xNum.clear();
        // ~x

        if (is.eof())
        {
            throw std::invalid_argument("Bad load-file structure: no y");
        }

        // y
        while(true)
        {
            is.get(temp);
            if (is.eof() || temp == '\n')
            {
                break;
            }
            if (temp < '0' || temp > '9')
            {
                throw std::invalid_argument("Invalid characters in load-file");
            }
            yNum += temp;
        }
        if (yNum.empty())
        {
            throw std::invalid_argument("Wrong load-file structure: no y coord");
        }
        y = std::stoi(yNum);
        yNum.clear();
        // ~y

        result.insert(Factory::create(type, name, x, y));
    }
    is.close();

    return result;
}

std::ostream& operator<<(std::ostream& os, const set_t& array)
{
    for (auto& elem : array)
    {
        if (elem->isAlive())
        {
            elem->print();
        }
    }
    return os;
}