#include "hex.h"

int main()
{
    Hex a("11f3");
    Hex b("10F4");

    a -= b;
    std::cout << a << " Size: " << a.getSize() << std::endl;

    return 0;
}