#ifndef UNITS_H
#define UNITS_H

#include <iostream>
#include <string>

#define MY_UNIT 'P'
#define ENEMY_UNIT 'E'

class Unit
{
private:
    // int id;
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

    std::string denote(void);
};

// class Knight : public Unit
// {
// public:
//     Knight(int id)
//     {
//         id = id;
//         letter = 'K';
//         max_hit_points = 70;
//         speed = 5;
//         cost = 400;
//         range = 1;
//         time_to_build = 5;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Swordsman : public Unit
// {
//     Swordsman()
//     {
//         letter = 'S';
//         hit_points = 60;
//         speed = 2;
//         cost = 250;
//         range = 1;
//         time_to_build = 3;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Archer : public Unit
// {
//     Archer()
//     {
//         letter = 'A';
//         hit_points = 40;
//         speed = 2;
//         cost = 250;
//         range = 5;
//         time_to_build = 3;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Pikeman : public Unit
// {
//     Pikeman()
//     {
//         letter = 'P';
//         hit_points = 50;
//         speed = 2;
//         cost = 200;
//         range = 2;
//         time_to_build = 3;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Ram : public Unit
// {
//     Ram()
//     {
//         letter = 'R';
//         hit_points = 90;
//         speed = 2;
//         cost = 500;
//         range = 1;
//         time_to_build = 4;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Catapult : public Unit
// {
//     Catapult()
//     {
//         letter = 'C';
//         hit_points = 50;
//         speed = 2;
//         cost = 800;
//         range = 7;
//         time_to_build = 6;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

// class Worker : public Unit
// {
//     Worker()
//     {
//         letter = 'W';
//         hit_points = 20;
//         speed = 2;
//         cost = 100;
//         range = 1;
//         time_to_build = 2;
//     }
//     std::string denote() const override
//     {
//         return std::format("{0} {1}", MY_UNIT, letter)
//     }
// };

#endif