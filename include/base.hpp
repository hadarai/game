#ifndef BASE_H
#define BASE_H

#include <string>

#include "unit.hpp"

class Base : public Unit
{
public:
    const char letter = 'B';
    const int max_hit_points = 200;
    char produced_unit_letter;
    int hit_points;

    Base(int _id,
         int _x,
         int _y,
         char _whose,
         char _letter,
         int _hit_points,
         char _produced_unit_letter);
    Base(const Base &obj) = default; // copy constructor
    ~Base() = default;
    std::string denote(void);
};

#endif