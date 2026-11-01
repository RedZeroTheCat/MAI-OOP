#ifndef OOP_SQUARE_H
#define OOP_SQUARE_H

#include "figure.h"

template<numeric T>
class Square : public Figure<T>
{
public:
    Square();
    Square(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
    Square(const Square<T>&);

    virtual Point<T> center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    Square& operator=(const Square<T>&);
    Square& operator=(Square<T>&&);
    bool operator==(const Figure<T>&) const override;

    void print(std::ostream& out) const override
    {
        out << a << '\n';
        out << b << '\n';
        out << c << '\n';
        out << d << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, Square<T>& s) {
        s.print(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Square<T>& s) {
        in >> s.a >> s.b >> s.c >> s.d;
        s.checkPoints(s.a, s.b, s.c, s.d);
        return in;
    }

    virtual ~Square() = default;

private:
    Point<T> a;
    Point<T> b;
    Point<T> c;
    Point<T> d;

    void checkConstructor(const Figure<T>&) const override;
    void checkPoints(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&) const;
};

template<numeric T>
void Square<T>::checkConstructor(const Figure<T>& fig) const
{
    const Square* temp = dynamic_cast<const Square*>(&fig);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point<T>> points(4);
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
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of square are NOT the same");
        }
    }
    double ac = round(Point<T>::distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];

    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000)
    {
        throw std::logic_error("Angles of square are not 90 degrees");
    }
}

template<numeric T>
void Square<T>::checkPoints(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&) const
{
    std::vector<Point<T>> points(4);
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
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of square are NOT the same");
        }
    }
    double ac = round(Point<T>::distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];

    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000)
    {
        throw std::logic_error("Angles of square are not 90 degrees");
    }
}

template<numeric T>
Square<T>::Square() : Figure<T>("Square") {}

template<numeric T>
Square<T>::Square(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) : Figure<T>("Square")
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    checkConstructor(*this);
}

template<numeric T>
Square<T>::Square(const Square<T>& t) : Figure<T>("Square")
{
    a = t.a;
    b = t.b;
    c = t.c;
    d = t.d;
}

template<numeric T>
Point<T> Square<T>::center() const
{
    T xCent = (a.getX() + b.getX() + c.getX() + d.getX()) / 4;
    T yCent = (a.getY() + b.getY() + c.getY() + d.getY()) / 4;
    Point<T> center(xCent, yCent);
    return center;
}

template<numeric T>
double Square<T>::area() const
{
    double ab = Point<T>::distance(a, b);
    return ab * ab;
}

template<numeric T>
Square<T>::operator double() const
{
    return this->area();
}

template<numeric T>
Square<T>& Square<T>::operator=(const Square<T>& t)
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

template<numeric T>
Square<T>& Square<T>::operator=(Square<T>&& t)
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

template<numeric T>
bool Square<T>::operator==(const Figure<T>& f) const
{
    if (this->getName() != f.getName())
    {
        return false;
    }

    const Square<T>* temp = dynamic_cast<const Square<T>*>(&f);
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

#endif //OOP_SQUARE_H