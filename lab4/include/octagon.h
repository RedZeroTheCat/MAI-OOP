#ifndef OOP_OCTAGON_H
#define OOP_OCTAGON_H

#include "figure.h"

const double SIDE_TO_DIAM_MODIFIER = 2 / std::sqrt(2 - std::sqrt(2)); // trigonometry

template<numeric T>
class Octagon :public Figure<T>
{
public:
    Octagon();
    Octagon(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
    Octagon(const Octagon&);

    virtual Point<T> center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    Octagon<T>& operator=(const Octagon<T>&);
    Octagon<T>& operator=(Octagon<T>&&);
    bool operator==(const Figure<T>&) const override;

    void print(std::ostream& out) const override
    {
        out << a << '\n';
        out << b << '\n';
        out << c << '\n';
        out << d << '\n';
        out << e << '\n';
        out << f << '\n';
        out << g << '\n';
        out << h << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, Octagon<T>& o) {
        o.print(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Octagon<T>& o) {
        in >> o.a >> o.b >> o.c >> o.d >> o.e >> o.f >> o.g >> o.h;
        o.checkPoints(o.a, o.b, o.c, o.d, o.e, o.f, o.g, o.h);
        return in;
    }

    virtual ~Octagon() = default;

private:
    Point<T> a;
    Point<T> b;
    Point<T> c;
    Point<T> d;
    Point<T> e;
    Point<T> f;
    Point<T> g;
    Point<T> h;

    void checkConstructor(const Figure<T>&) const override;
    void checkPoints(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
};

template<numeric T>
void Octagon<T>::checkConstructor(const Figure<T>& f) const
{
    const Octagon<T>* temp = dynamic_cast<const Octagon*>(&f);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point<T>> points(8);
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
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
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
        diag = Point<T>::distance(points[i], points[i + 4]);
        if (std::fabs(diag - diam) > EPS)
        {
            throw std::logic_error("Angles of octagon are not the same");
        }
    }
}

template<numeric T>
void Octagon<T>::checkPoints(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, const Point<T>& e, const Point<T>& f, const Point<T>& g, const Point<T>& h)
{
    std::vector<Point<T>> points(8);
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
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
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
        diag = Point<T>::distance(points[i], points[i + 4]);
        if (std::fabs(diag - diam) > EPS)
        {
            throw std::logic_error("Angles of octagon are not the same");
        }
    }
}

template<numeric T>
Octagon<T>::Octagon() : Figure<T>("Octagon") {}

template<numeric T>
Octagon<T>::Octagon(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, const Point<T>& e, const Point<T>& f, const Point<T>& g, const Point<T>& h) : Figure<T>("Octagon")
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

template<numeric T>
Octagon<T>::Octagon(const Octagon& t) : Figure<T>("Octagon")
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

template<numeric T>
Point<T> Octagon<T>::center() const
{
    T xCent = (a.getX() + b.getX() + c.getX() + d.getX() + e.getX() + f.getX() + g.getX() + h.getX()) / 8;
    T yCent = (a.getY() + b.getY() + c.getY() + d.getY() + e.getY() + f.getY() + g.getY() + h.getY()) / 8;
    Point<T> center(xCent, yCent);
    return center;
}

template<numeric T>
double Octagon<T>::area() const
{
    double ab = Point<T>::distance(a, b);
    return ab * ab * 2 * (std::sqrt(2) + 1);
}

template<numeric T>
Octagon<T>::operator double() const
{
    return this->area();
}

template<numeric T>
Octagon<T>& Octagon<T>::operator=(const Octagon<T>& t)
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

template<numeric T>
Octagon<T>& Octagon<T>::operator=(Octagon<T>&& t)
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

template<numeric T>
bool Octagon<T>::operator==(const Figure<T>& f) const
{
    if (this->getName() != f.getName())
    {
        return false;
    }

    const Octagon<T>* temp = dynamic_cast<const Octagon<T>*>(&f);
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

#endif //OOP_OCTAGON_H