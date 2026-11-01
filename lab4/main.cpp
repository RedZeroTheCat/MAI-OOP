#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"

int main()
{
    Array<Figure<double>*> arr(0);
    Octagon<double> o
    (
        {10, 0},
        {7.07, 7.07},
        {0, 10},
        {-7.07, 7.07},
        {-10, 0},
        {-7.07, -7.07},
        {0, -10},
        {7.07, -7.07}
    )
    ;
    Triangle<double> t
    (
        {0, 10},
        {-8.66, -5},
        {8.66, -5}
    )
    ;
    Square<double> s
    (
        {10, 0},
        {0, 10},
        {-10, 0},
        {0, -10}
    )
    ;

    //std::cin >> s;
    arr.push_back(&s);

    //std::cin >> t;
    arr.push_back(&t);

    //std::cin >> o;
    arr.push_back(&o);

    for (int i = 0; i < arr.getSize(); ++i)
    {
        std::cout << arr[i]->getName() << " area: " << arr[i]->area() << " center: " << arr[i]->center() << '\n';
        std::cout << "Vertices:\n";
        arr[i]->print(std::cout);
    }
    std::cout << "Common area: " << arr.commonArea() << "\n";
    std::cout << '\n';

    arr.erase(1);
    for (int i = 0; i < arr.getSize(); ++i)
    {
        std::cout << arr[i]->getName() << " area: " << arr.figureArea(i) << " center: " << arr.figureCenter(i) << '\n';
    }
    std::cout << "Common area: " << arr.commonArea() << "\n";
    std::cout << '\n';

    arr.pop_back();
    for (int i = 0; i < arr.getSize(); ++i)
    {
        std::cout << arr[i]->getName() << " area: " << arr[i]->area() << " center: " << arr[i]->center() << '\n';
    }
    std::cout << "Common area: " << arr.commonArea() << "\n";
    std::cout << '\n';

    Array<Figure<int>*> otherArr;
    Square<int> otherS
    (
        {5, 0},
        {0, 5},
        {-5, 0},
        {0, -5}
    )
    ;
    //std::cin >> other_s;
    otherArr.push_back(&otherS);
    for (int i = 0; i < otherArr.getSize(); ++i)
    {
        std::cout << otherArr[i]->getName() << " area: " << otherArr[i]->area() << " center: " << otherArr[i]->center() << '\n';
    }
    std::cout << "Common area: " << otherArr.commonArea() << "\n";
    std::cout << '\n';

    return 0;
}