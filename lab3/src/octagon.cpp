#include "octagon.h"

void Octagon::checkConstructor(const Figure& f) const
{
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point> points(8);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;
    points[3] = temp->d;
    points[4] = temp->e;
    points[5] = temp->f;
    points[6] = temp->g;
    points[7] = temp->h;

    for (int i = 0; i < 7; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of octagon are the same");
        }
    }

    std::vector<double> sides(8);
    for (int i = 0; i < 8; ++i)
    {
        if (i < 7)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of octagon are NOT the same");
        }
    }

    double diam = sides[0] * SIDE_TO_DIAM_MODIFIER;
    double diag;
    for (int i = 0; i < 4; ++i)
    {
        diag = Point::distance(points[i], points[i + 4]);
        if (std::fabs(diag - diam) > EPS)
        {
            throw std::logic_error("Angles of octagon are not the same");
        }
    }
}

void Octagon::checkPoints(const Point& a, const Point& b, const Point& c, const Point& d, const Point& e, const Point& f, const Point& g, const Point& h)
{
    std::vector<Point> points(8);
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    points[4] = e;
    points[5] = f;
    points[6] = g;
    points[7] = h;

    for (int i = 0; i < 7; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of octagon are the same");
        }
    }

    std::vector<double> sides(8);
    for (int i = 0; i < 8; ++i)
    {
        if (i < 7)
        {
            sides[i] = round(Point::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of octagon are NOT the same");
        }
    }

    double diam = sides[0] * SIDE_TO_DIAM_MODIFIER;
    double diag;
    for (int i = 0; i < 4; ++i)
    {
        diag = Point::distance(points[i], points[i + 4]);
        if (std::fabs(diag - diam) > EPS)
        {
            throw std::logic_error("Angles of octagon are not the same");
        }
    }
}

Octagon::Octagon() : Figure("Octagon") {}

Octagon::Octagon(const Point& a, const Point& b, const Point& c, const Point& d, const Point& e, const Point& f, const Point& g, const Point& h) : Figure("Octagon")
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
    this->f = f;
    this->g = g;
    this->h = h;
    checkConstructor(*this);
}

Octagon::Octagon(const Octagon& t) : Figure("Octagon")
{
    a = t.a;
    b = t.b;
    c = t.c;
    d = t.d;
    e = t.e;
    f = t.f;
    g = t.g;
    h = t.h;
}

Point Octagon::center() const
{
    double xCent = (a.getX() + b.getX() + c.getX() + d.getX() + e.getX() + f.getX() + g.getX() + h.getX()) / 8;
    double yCent = (a.getY() + b.getY() + c.getY() + d.getY() + e.getY() + f.getY() + g.getY() + h.getY()) / 8;
    Point center(xCent, yCent);
    return center;
}

double Octagon::area() const
{
    double ab = Point::distance(a, b);
    return ab * ab * 2 * (std::sqrt(2) + 1);
}

Octagon::operator double() const
{
    return this->area();
}

void Octagon::print(std::ostream& os)
{
    os << a << "\n";
    os << b << "\n";
    os << c << "\n";
    os << d << "\n";
    os << e << "\n";
    os << f << "\n";
    os << g << "\n";
    os << h << "\n";
}

void Octagon::input(std::istream& is)
{
    is >> a >> b >> c >> d >> e >> f >> g >> h;
    checkPoints(a, b, c, d, e, f, g, h);
}

std::ostream& operator<<(std::ostream& os, Octagon& t)
{
    t.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Octagon& t)
{
    t.input(is);
    return is;
}

Octagon& Octagon::operator=(const Octagon& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
        d = t.d;
        e = t.e;
        f = t.f;
        g = t.g;
        h = t.h;
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
        d = t.d;
        e = t.e;
        f = t.f;
        g = t.g;
        h = t.h;
    }
    return *this;
}

bool Octagon::operator==(const Figure& f) const
{
    if (name != f.getName())
    {
        return false;
    }

    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
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




