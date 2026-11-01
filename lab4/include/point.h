#ifndef OOP_POINT_H
#define OOP_POINT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <exception>
#include <concepts>
#include <type_traits>

const double EPS = 0.01;

template<typename T>
concept numeric = std::is_arithmetic_v<T>;

template<numeric T>
class Point
{
public:
    Point();
    Point(const T&, const T&);
    Point(const Point<T>&);

    T getX() const;
    T getY() const;

    bool operator==(const Point<T>&) const;
    bool operator!=(const Point<T>&) const;
    Point<T>& operator=(const Point<T>&);
    Point<T>& operator=(Point<T>&&);

    static double distance(const Point<T>&, const Point<T>&);

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p)
    {
        os << "(x: " << p.getX() << ",\t y: " << p.getY() << ')';
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Point<T>& p)
    {
        is >> p.x >> p.y;
        return is;
    }

    ~Point() = default;

private:
    T x;
    T y;
};

template<numeric T>
Point<T>::Point() {
    x = 0;
    y = 0;
}

template<numeric T>
Point<T>::Point(const T& x, const T& y) {
    this->x = x;
    this->y = y;
}

template<numeric T>
Point<T>::Point(const Point<T>& p) {
    x = p.x;
    y = p.y;
}

template <numeric T>
T Point<T>::getX() const
{
    return x;
}

template <numeric T>
T Point<T>::getY() const
{
    return y;
}

template<numeric T>
double Point<T>::distance(const Point<T>& l, const Point<T>& r)
{
    return std::sqrt((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y));
}

template<numeric T>
bool Point<T>::operator==(const Point<T>& p) const
{
    if (distance(*this, p) <= 0.01)
    {
        return true;
    }
    return false;
}

template<numeric T>
bool Point<T>::operator!=(const Point<T>& p) const
{
    return !(*this == p);
}

template<numeric T>
Point<T>& Point<T>::operator=(const Point<T>& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<numeric T>
Point<T>& Point<T>::operator=(Point<T>&& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;

        other.x = 0;
        other.y = 0;
    }
    return *this;
}

#endif //OOP_POINT_H