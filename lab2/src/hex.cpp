#include "hex.h"

bool isHex(unsigned char c)
{
    if (!( (c >= '0' && c <= '9')
         ||(c >= 'a' && c <= 'f')
         ||(c >= 'A' && c <= 'F')))
    {
        return false;
    }
    return true;
}

int hexCharToInt(unsigned char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    throw std::invalid_argument("Not a valid hex character");
}

char intToHexChar(int c)
{
    if (c >= 0 && c <= 9)
    {
        return '0' + c;
    }
    else if (c >= 10 && c <= 15)
    {
        return 'A' + c - 10;
    }
    throw std::invalid_argument("Not a valid hex integer");
}

void Hex::reallocate(const size_t &newCapacity)
{
    unsigned char *newData = new unsigned char[newCapacity];
    capacity = newCapacity;
    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}



size_t Hex::getSize() const noexcept
{
    return size;
}

unsigned char* Hex::getData() const noexcept
{
    return data;
}



Hex::Hex() : size(0), capacity(0), data(nullptr) {}

Hex::Hex(const size_t& n, unsigned char t)
{
    if (!isHex(t))
    {
        throw std::invalid_argument("This number does not belong to hex system");
    }

    size = n;
    capacity = size * 2;
    data = new unsigned char[capacity];


    if (t == '0' && size > 0)
    {
        data[0] = '0';
        size = 1;
    }
    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = t;
        }
    }
}

Hex::Hex(const std::initializer_list<unsigned char>& t)
{
    size = t.size();
    capacity = size * 2;
    data = new unsigned char[capacity];

    size_t index = size - 1;
    size_t insignificantZeros = 0;
    bool validZero = false;

    for (const auto elem : t)
    {
        if (!isHex(elem))
        {
            delete[] data;
            data = nullptr;
            size = 0;
            capacity = 0;
            throw std::invalid_argument("This number does not belong to hex system");
        }
        if (!validZero && size != 0 && elem == '0' && index != 0)
        {
            ++insignificantZeros;
            --index;
            continue;
        }
        validZero = true;
        data[index] = elem;
        --index;
    }
    size = t.size() - insignificantZeros;
}

Hex::Hex(const std::string& t)
{
    size = t.size();
    capacity = size * 2;
    data = new unsigned char[capacity];

    size_t index = size - 1;
    size_t insignificantZeros = 0;
    bool validZero = false;

    for (const auto elem : t)
    {
        if (!isHex(elem))
        {
            delete[] data;
            data = nullptr;
            size = 0;
            capacity = 0;
            throw std::invalid_argument("This number does not belong to hex system");
        }
        if (!validZero && size != 0 && elem == '0' && index != 0)
        {
            ++insignificantZeros;
            --index;
            continue;
        }
        validZero = true;
        data[index] = elem;
        --index;
    }
    size = t.size() - insignificantZeros;
}

Hex::Hex(const Hex& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new unsigned char[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

Hex::Hex(Hex&& other) noexcept
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;
    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;
}

Hex::~Hex() noexcept
{
    size = 0;
    capacity = 0;
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

size_t Hex::hexToDecimal() const
{
    size_t temp = 0;
    size_t result = 0;
    for (size_t i = 0; i < size; ++i)
    {
        result = result + hexCharToInt(data[i]) * pow(16, temp);
        ++temp;
    }
    return result;
}

std::string Hex::getValue() const
{
    std::string result(size, '\0');
    for (size_t i = 0; i < size; ++i)
    {
        if (data[i] != '\0')
        {
            result[size - i - 1] = static_cast<char>(data[i]);
        }
    }
    return result;
}


std::ostream& operator<<(std::ostream& os, const Hex& hex)
{
    for (int i = hex.size - 1; i >= 0; --i)
    {
        os << hex.data[i];
    }
    return os;
}


bool Hex::operator==(const Hex& other) const
{
    size_t left = hexToDecimal();
    size_t right = other.hexToDecimal();
    if (left == right)
    {
        return true;
    }
    return false;
}

bool Hex::operator!=(const Hex& other) const
{
    return !(*this == other);
}

bool Hex::operator<(const Hex& other) const
{
    size_t left = hexToDecimal();
    size_t right = other.hexToDecimal();
    if (left < right)
    {
        return true;
    }
    return false;
}

bool Hex::operator>=(const Hex& other) const
{
    return !(*this < other);
}

bool Hex::operator>(const Hex& other) const
{
    return (*this >= other) && (*this != other);
}

bool Hex::operator<=(const Hex& other) const
{
    return !(*this > other);
}


Hex& Hex::operator=(const Hex& other)
{
    if (this != &other)
    {
        if (capacity < other.capacity)
        {
            reallocate(other.capacity);
        }

        size = other.size;
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Hex& Hex::operator=(Hex&& other) noexcept
{
    if (this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        delete[] data;
        data = other.data;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

Hex Hex::operator+=(const Hex& other)
{
    if (capacity < other.capacity)
    {
        reallocate(other.capacity);
    }

    std::string result;
    int carry = 0;

    int i = 0;
    int j = 0;

    while (i < size || j < other.size || carry != 0)
    {
        int sum = carry;

        if (i < size)
        {
            sum += hexCharToInt(data[i]);
            ++i;
        }

        if (j < other.size)
        {
            sum += hexCharToInt(other.data[j]);
            ++j;
        }

        carry = sum / 16;
        sum %= 16;

        result = intToHexChar(sum) + result;
    }

    size = result.size();

    for (size_t i = 0; i < size; ++i)
    {
        data[size - 1 - i] = result[i];
    }

    return *this;
}

Hex Hex::operator+(const Hex& other) const
{
    Hex result = *this;
    result += other;
    return result;
}


Hex Hex::operator-=(const Hex& other)
{
    if (*this < other)
    {
        throw std::logic_error("Size of left less than size of right with unsigned numbers");
    }

    if (other.size == 0)
    {
        return *this;
    }

    std::string result;
    int borrow = 0;

    int i = 0;
    int j = 0;

    while (i < size || j < other.size)
    {
        int digits = (i < size) ? hexCharToInt(data[i]) : 0;
        int otherDigits = (j < other.size) ? hexCharToInt(other.data[j]) : 0;

        digits -= borrow;

        if (digits < otherDigits)
        {
            digits += 16;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int diff = digits - otherDigits;

        result = result + intToHexChar(diff);

        ++i;
        ++j;
    }

    bool validZero = false;
    for (int i = result.size() - 1; i >= 0 && result.size() != 1; --i)
    {
        if (result[i] == '0' && !validZero && i != 0)
        {
            result.erase(result.begin() + i);
            continue;
        }
        validZero = true;
    }

    size = result.size();

    for (size_t i = 0; i < size; ++i)
    {
        data[i] = result[i];
    }

    return *this;
}

Hex Hex::operator-(const Hex& other) const
{
    Hex result = *this;
    result -= other;
    return result;
}




