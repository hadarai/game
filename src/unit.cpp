#include "unit.hpp"

Unit::Unit(int _id,
           int _x,
           int _y,
           char _whose,
           char _letter,
           int _hit_points) : id(_id),
                              x(_x),
                              y(_y),
                              whose(_whose),
                              letter(_letter),
                              hit_points(_hit_points)
{
}

bool Unit::field_in_circle(int _x, int _y, int _r)
{
    return abs(x - _x) + abs(y - _y);
}

bool Unit::field_in_move_distance(int _x, int _y)
{
    return field_in_circle(_x, _y, speed);
}
bool Unit::field_in_attack_range(int _x, int _y)
{
    return field_in_circle(_x, _y, range);
}

void Unit::move_to(int _x, int _y)
{
    x = _x;
    y = _y;
}

bool Unit::does_it_stand_here(int _x, int _y)
{
    return x == _x && y == _y;
}
int Unit::get_id(void)
{
    return id;
}
int Unit::get_x(void)
{
    return x;
}
int Unit::get_y(void)
{
    return y;
}

char Unit::get_letter(void)
{
    return letter;
}

bool Unit::deal(int damage)
{
    hit_points -= hit_points;
    return hit_points;
}

std::string Unit::denote(void)
{
    return std::string(1, whose) + " " +
           std::string(1, letter) + " " +
           std::to_string(id) + " " +
           std::to_string(x) + " " +
           std::to_string(y) + " " +
           std::to_string(hit_points);
}
