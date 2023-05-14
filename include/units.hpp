#ifndef UNITS_H
#define UNITS_H

#include <iostream>
#include <string>

#define MY_UNIT 'P'
#define ENEMY_UNIT 'E'

class Unit
{
private:
    char letter;
    int
        id,
        max_hit_points,
        cost,
        speed,
        range,
        time_to_build;

    int hit_points;

    int x, y;
    char whose;

public:
    Unit(int _id,
         int _x,
         int _y,
         char _whose,
         char _letter,
         int _hit_points);

    Unit(const Unit &obj) = default; // copy constructor
    virtual ~Unit()
    {
    }

    std::string denote(void);
};

class Base : private Unit
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
    std::string denote(void);
};

#endif