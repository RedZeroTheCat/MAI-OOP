#include "triangle.h"

void Triangle::checkConstructor(const Figure& fig) const
{
    const Triangle* temp = dynamic_cast<const Triangle*>(&fig);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point> points(3);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;

    for (int i = 0; i < 2; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of triangle are the same");
        }
    }

    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i)
    {
        if (i < 2)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of triangle are NOT the same");
        }
    }
}

void Triangle::checkPoints(const Point& a, const Point& b, const Point& c)
{
    std::vector<Point> points(3);
    points[0] = a;
    points[1] = b;
    points[2] = c;

    for (int i = 0; i < 2; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of triangle are the same");
        }
    }
    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i)
    {
        if (i < 2)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of triangle are NOT the same");
        }
    }
}

Triangle::Triangle() : Figure("Triangle") {}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : Figure("Triangle")
{
    this->a = a;
    this->b = b;
    this->c = c;
    checkConstructor(*this);
}

Triangle::Triangle(const Triangle& t) : Figure("Triangle")
{
    a = t.a;
    b = t.b;
    c = t.c;
}

Point Triangle::center() const
{
    double xCent = (a.getX() + b.getX() + c.getX()) / 3;
    double yCent = (a.getY() + b.getY() + c.getY()) / 3;
    Point center(xCent, yCent);
    return center;
}

double Triangle::area() const
{
    double ab = Point::distance(a, b);
    return ab * ab * 0.25 * std::sqrt(3);
}

Triangle::operator double() const
{
    return this->area();
}

void Triangle::print(std::ostream& os)
{
    os << a << "\n";
    os << b << "\n";
    os << c << "\n";
}

void Triangle::input(std::istream& is)
{
    is >> a >> b >> c;
    checkPoints(a, b, c);
}

std::ostream& operator<<(std::ostream& os, Triangle& t)
{
    t.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& t)
{
    t.input(is);
    return is;
}

Triangle& Triangle::operator=(const Triangle& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

bool Triangle::operator==(const Figure& f) const
{
    if (name != f.getName())
    {
        return false;
    }

    const Triangle* temp = dynamic_cast<const Triangle*>(&f);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed to cast");
    }

    if (this->area() == temp->area())
    {
        return true;
    }

    return false;
}

