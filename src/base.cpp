#include "base.hpp"

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
}

std::string Base::denote(void)
{
    return Unit::denote() + " " +
           std::string(1, produced_unit_letter);
}

void Base::produce_an_unit(char letter)
{
    if (produced_unit_letter != 0)
        throw "Unit already produced!\n";
    else
        produced_unit_letter = letter;
}
