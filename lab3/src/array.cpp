#include "array.h"

Array::Array()
{
    size = 0;
    capacity = 2;
    data = new Figure*[capacity];
}

Array::Array(size_t s)
{
    size = s;
    if (size > 0)
    {
        capacity = size * 2;
    }
    else
    {
        capacity = 2;
    }
    data = new Figure*[capacity];
}

Array::~Array()
{
    delete[] data;
    size = 0;
    capacity = 0;
    data = nullptr;
}

size_t Array::getSize()
{
    return size;
}

size_t Array::getCapacity()
{
    return capacity;
}

void Array::reallocate(size_t newCapacity)
{
    if (data == nullptr)
    {
        return;
    }
    Figure** newData = new Figure*[newCapacity];

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}

void Array::push_back(Figure* fig)
{
    if (size < capacity)
    {
        if (size == 0)
        {
            data[size] = fig;
            size = 1;
            return;
        }
        data[size++] = fig;
        return;
    }
    this->reallocate(capacity * 2);
    data[size++] = fig;
}

void Array::pop_back()
{
    if (size == 0)
    {
        return;
    }

    size--;
}

void Array::erase(size_t index)
{
    if (index >= size)
    {
        return;
    }

    for (size_t i = index + 1; i < size; ++i)
    {
        data[i - 1] = data[i];
    }

    size--;
}

Figure* Array::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index];
}

Point Array::figureCenter(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index]->center();
}

double Array::figureArea(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index]->area();
}

double Array::commonArea()
{
    double sum = 0;

    for (size_t i = 0; i < size; ++i)
    {
        sum += data[i]->area();
    }

    return sum;
}

std::ostream& operator<<(std::ostream& os, Array& arr)
{
    for (size_t i = 0; i < arr.getSize(); ++i)
    {
        os << arr[i]->getName();

        Point center = arr.figureCenter(i);
        os << " center: " << center;

        double area = arr.figureArea(i);
        os << " area: " << area <<  std::endl;
    }
    return os;
}






