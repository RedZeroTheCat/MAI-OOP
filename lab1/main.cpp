#include <iostream>

#include "GCD.h"

int main()
{
    int a, b;
    std::cin >> a >> b;

    std::cout << gcd(a, b) << std::endl;
    return 0;
}