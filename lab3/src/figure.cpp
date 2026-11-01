#include "figure.h"

Figure::Figure(const std::string& name)
{
    this->name = name;
}

const std::string& Figure::getName() const
{
    return name;
}

Figure::~Figure() = default;

