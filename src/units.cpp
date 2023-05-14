#include "units.hpp"

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
