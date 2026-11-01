#ifndef OOP_FIGURE_H
#define OOP_FIGURE_H

#include <vector>

#include "point.h"

class Figure
{
protected:
    std::string name;

    virtual void print(std::ostream&) = 0;
    virtual void input(std::istream&) = 0;
    virtual void checkConstructor(const Figure&) const = 0;

public:
    Figure() = default;
    Figure(const std::string&);

    const std::string& getName() const;
    virtual Point center() const = 0;
    virtual double area() const = 0;

    virtual bool operator==(const Figure&) const = 0;
    explicit virtual operator double() const = 0;

    virtual ~Figure();
};

#endif //OOP_FIGURE_H