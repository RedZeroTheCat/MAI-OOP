#ifndef OOP_FIGURE_H
#define OOP_FIGURE_H

#include "point.h"

template<numeric T>
class Figure
{
public:
    Figure() = default;
    Figure(const std::string&);

    const std::string& getName() const;
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;

    virtual bool operator==(const Figure&) const = 0;
    explicit virtual operator double() const = 0;

    virtual void print(std::ostream& os) const = 0;

    virtual ~Figure() = default;

protected:
    std::string name;

    virtual void checkConstructor(const Figure<T>&) const = 0;
};

template<numeric T>
Figure<T>::Figure(const std::string& name)
{
    this->name = name;
}

template<numeric T>
const std::string& Figure<T>::getName() const
{
    return name;
}

#endif //OOP_FIGURE_H