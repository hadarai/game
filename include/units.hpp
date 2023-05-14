#ifndef UNITS_H
#define UNITS_H

#include <iostream>
#include <string>

#define MY_UNIT 'P'
#define ENEMY_UNIT 'E'

class Unit
{
private:
    int x, y;
    char whose,
        letter;
    int hit_points;
    int
        id,
        max_hit_points,
        cost,
        speed,
        range,
        time_to_build;

    bool field_in_circle(int _x, int _y, int _r);

public:
    Unit(int _id,
         int _x,
         int _y,
         char _whose,
         char _letter,
         int _hit_points);

    Unit(const Unit &obj) = default; // copy constructor
    ~Unit() = default;
    bool field_in_move_distance(int _x, int _y);
    bool field_in_attack_range(int _x, int _y);
    void move_to(int _x, int _y);
    bool does_it_stand_here(int _x, int _y);
    int get_x(void);
    int get_y(void);

    bool hit(int damage);

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
    ~Base() = default;
    std::string denote(void);
};

#endif