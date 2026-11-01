#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}


Point::Point(const Point& p)
{
    x = p.x;
    y = p.y;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX(double newX)
{
    x = newX;
}

void Point::setY(double newY)
{
    y = newY;
}


bool Point::operator==(const Point& p) const
{
    if (distance(*this, p) <= EPS)
    {
        return true;
    }
    return false;
}

bool Point::operator!=(const Point& p) const
{
    return !(*this == p);
}

Point& Point::operator=(const Point& p)
{
    if (this != &p)
    {
        x = p.x;
        y = p.y;
    }
    return *this;
}

Point& Point::operator=(Point&& p)
{
    if (this != &p)
    {
        x = p.x;
        y = p.y;

        p.x = 0;
        p.y = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(x: " << p.getX() << ", y: " << p.getY() << ')';

    return os;
}

std::istream& operator>>(std::istream& is, Point& p)
{
    double tempX, tempY;
    is >> tempX >> tempY;
    p.setX(tempX);
    p.setY(tempY);

    return is;
}

double Point::distance(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}




