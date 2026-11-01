#ifndef OOP_HEX_H
#define OOP_HEX_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

class Hex
{
public:
    Hex();
    Hex(const size_t & n, unsigned char t = 0);
    Hex(const std::initializer_list<unsigned char> &t);
    Hex(const std::string &t);

    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    virtual ~Hex();

    bool operator==(const Hex &other) const;
    bool operator!=(const Hex &other) const;
    bool operator<(const Hex &other) const;
    bool operator<=(const Hex &other) const;
    bool operator>(const Hex &other) const;
    bool operator>=(const Hex &other) const;

    Hex operator+(const Hex &other) const;
    Hex operator-(const Hex &other) const;

    Hex& operator=(const Hex &other);
    Hex& operator=(Hex&&) noexcept ;
    Hex operator+=(const Hex &other);
    Hex operator-=(const Hex &other);

    size_t getSize() const noexcept;
    unsigned char* getData() const noexcept;

    size_t hexToDecimal() const;
    std::string getValue() const;

    friend std::ostream& operator<<(std::ostream &os, const Hex &hex);

private:
    size_t size;
    size_t capacity;
    unsigned char* data;

    void reallocate(const size_t &newCapacity);
};

bool isHex(unsigned char c);
int hexCharToInt(unsigned char c);
char intToHexChar(int c);

#endif //OOP_HEX_H