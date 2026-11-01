#include "GCD.h"

int gcd(const int a, const int b)
{
    int absA = std::abs(a);
    int absB = std::abs(b);

    if (absA == 0 || absB == 0)
    {
        return absA > absB ? absA : absB;
    }

    while (absB != 0)
    {
        int temp = absB;
        absB = absA % absB;
        absA = temp;
    }

    return absA;
}
