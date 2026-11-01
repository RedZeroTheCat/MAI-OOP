#ifndef OOP_ARRAY_H
#define OOP_ARRAY_H

#include "figure.h"

class Array
{
public:
    Array();
    Array(size_t);

    void push_back(Figure*);
    void pop_back();
    void erase(size_t);
    Figure* operator[](size_t);
    Point figureCenter(size_t);
    double figureArea(size_t);
    double commonArea();

    size_t getSize();
    size_t getCapacity();

    friend std::ostream& operator<<(std::ostream&, Array&);

    ~Array();

private:
    size_t size;
    size_t capacity;
    Figure** data;

    void reallocate(size_t);
};

#endif //OOP_ARRAY_H