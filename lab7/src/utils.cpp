#include "utils.h"

std::string toRoman(int number)
{
    const std::vector<std::pair<int, std::string>> romanBase = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    std::string result;
    for (const auto& segmentum : romanBase)
    {
        while (number >= segmentum.first)
        {
            result += segmentum.second;
            number -= segmentum.first;
        }
    }
    return result;
}