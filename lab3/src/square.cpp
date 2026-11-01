#include "square.h"

void Square::checkConstructor(const Figure& fig) const
{
    const Square* temp = dynamic_cast<const Square*>(&fig);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point> points(4);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;
    points[3] = temp->d;

    for (int i = 0; i < 3; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of square are the same");
        }
    }

    std::vector<double> sides(4);
    for (int i = 0; i < 4; ++i)
    {
        if (i < 3)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of square are NOT the same");
        }
    }
    double ac = round(Point::distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];

    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000)
    {
        throw std::logic_error("Angles of square are not 90 degrees");
    }
}

void Square::checkPoints(const Point&, const Point&, const Point&, const Point&)
{
    std::vector<Point> points(4);
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    for (int i = 0; i < 4; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of square are the same");
        }
    }

    std::vector<double> sides(4);
    for (int i = 0; i < 4; ++i)
    {
        if (i < 3)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of square are NOT the same");
        }
    }
    double ac = round(Point::distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];

    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000)
    {
        throw std::logic_error("Angles of square are not 90 degrees");
    }
}

Square::Square() : Figure("Square") {}

Square::Square(const Point& a, const Point& b, const Point& c, const Point& d) : Figure("Square")
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    checkConstructor(*this);
}

Square::Square(const Square& t) : Figure("Square")
{
    a = t.a;
    b = t.b;
    c = t.c;
    d = t.d;
}

Point Square::center() const
{
    double xCent = (a.getX() + b.getX() + c.getX() + d.getX()) / 4;
    double yCent = (a.getY() + b.getY() + c.getY() + d.getY()) / 4;
    Point center(xCent, yCent);
    return center;
}

double Square::area() const
{
    double ab = Point::distance(a, b);
    return ab * ab;
}

Square::operator double() const
{
    return this->area();
}

void Square::print(std::ostream& os)
{
    os << a << "\n";
    os << b << "\n";
    os << c << "\n";
    os << d << "\n";
}

void Square::input(std::istream& is)
{
    is >> a >> b >> c >> d;
    checkPoints(a, b, c, d);
}

std::ostream& operator<<(std::ostream& os, Square& t)
{
    t.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Square& t)
{
    t.input(is);
    return is;
}

Square& Square::operator=(const Square& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
        d = t.d;
    }
    return *this;
}

Square& Square::operator=(Square&& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
        d = t.d;
    }
    return *this;
}

bool Square::operator==(const Figure& f) const
{
    if (name != f.getName())
    {
        return false;
    }

    const Square* temp = dynamic_cast<const Square*>(&f);
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







