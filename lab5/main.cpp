#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

#include "Vector.h"

int factorial(int n);


int main()
{
    srand(time(nullptr));

    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 5000>> testTask;

    for (int i = 1; i < 10; i++)
    {
        testTask[i] = factorial(i);
    }

    for (auto it = testTask.begin(); it != testTask.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;


    Vector<int, Allocator<int, 5000>> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(factorial(i));
    }

    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    const size_t allocatedBlocks = 20000;
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, allocatedBlocks>> testSelf;

    int count = rand() % allocatedBlocks;
    if (count < 1000)
    {
        count = 1000;
    }

    for (int i = 0; i < count; ++i)
    {
        int randKey = rand();
        int randValue = rand();
        int eraseValue = rand();
        testSelf.emplace(randKey, randValue);

        auto it = testSelf.find(eraseValue);
        if (it != testSelf.end())
        {
            testSelf.erase(it);
        }
    }

    return 0;
}

int factorial(int n)
{
    int result = 1;

    // if (n > 11)
    // {
    //     std::cout << "Number is too big for this task" << std::endl;
    //     return -1;
    // }

    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }
    return result;

}