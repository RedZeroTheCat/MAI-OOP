#include "array.h"
#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"

int main()
{
    Array arr(0);

    //              Heresy...
    Triangle t
    (
        {0, 10},
        {-8.66, -5},
        {8.66, -5}
    )
    ;
    Square s
    (
        {10, 0},
        {0, 10},
        {-10, 0},
        {0, -10}
    )
    ;
    Octagon o
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

    //std::cin >> s;
    arr.push_back(&s);

    //std::cin >> t;
    arr.push_back(&t);

    //std::cin >> o;
    arr.push_back(&o);

    std::cout << "Square area: " << s.area() << " center: " << s.center() << '\n';
    std::cout << "Triangle area: " << t.area() << " center: " << t.center() << '\n';
    std::cout << "Octagon area: " << arr.figureArea(2) << " center: " << arr.figureCenter(2) << '\n';
    std::cout << '\n';

    std::cout << arr;
    std::cout << "Common area: " << arr.commonArea() << '\n';
    std::cout << '\n';

    arr.erase(1);
    std::cout << arr;
    std::cout << "Common area: " << arr.commonArea() << '\n';
    std::cout << '\n';

    arr.pop_back();
    std::cout << arr;
    std::cout << "Common area: " << arr.commonArea() << '\n';

    arr.push_back(&s);

    o = {Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1)};
    std::cout << "Octagon area: " << o.area() << " center: " << o.center() << '\n';
    std::cout << "Vertices:\n" << o << '\n';

    std::cout << arr;
    std::cout << "Common area: " << arr.commonArea() << std::endl;

    return 0;
}