#include "units.hpp"

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
int Unit::get_x(void)
{
    return x;
}
int Unit::get_y(void)
{
    return y;
}

Base::Base(int _id,
           int _x,
           int _y,
           char _whose,
           char _letter,
           int _hit_points,
           char _produced_unit_letter) : Unit(_id,
                                              _x,
                                              _y,
                                              _whose,
                                              _letter,
                                              _hit_points),
                                         produced_unit_letter(_produced_unit_letter)
{
    produced_unit_letter = _produced_unit_letter;
    std::cout
        << "I build a base!\n";
}

std::string Base::denote(void)
{
    return Unit::denote() + " " +
           std::string(1, produced_unit_letter);
}

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

std::string Unit::denote(void)
{
    return std::string(1, whose) + " " +
           std::string(1, letter) + " " +
           std::to_string(id) + " " +
           std::to_string(x) + " " +
           std::to_string(y) + " " +
           std::to_string(hit_points);
}
