#ifndef UNIT_H
#define UNIT_H

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

    int get_id(void);
    int get_x(void);
    int get_y(void);
    char get_letter(void);

    // here's better getter and setter
    // int &x() { return x; }
    // const int &x() const { return x; }

    bool deal(int damage);

    std::string denote(void);
};

#endif