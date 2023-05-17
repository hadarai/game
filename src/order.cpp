#include "order.hpp"

std::string Order::denote(void)
{
    std::string output = std::to_string(unit_id) + " " + action + " ";
    switch (action)
    {
    case 'M':
        output.append(std::to_string(parameters.move.x) + " " + std::to_string(parameters.move.y));
        break;
    case 'A':
        output.append(std::to_string(parameters.attack.prey_id));
        break;
    case 'B':
        output.append(std::to_string(parameters.build.letter));
        break;
    }
    return output;
}
