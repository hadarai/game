#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>

#include "game.hpp"

class Mediator
{
private:
    /* data */
    const uint MAX_TURNS = 1000;
    std::string
        executable_filename,
        map_filename,
        status_filename,
        orders_filename;
    uint first_player_turns = 0, second_player_turns = 0;

public:
    Mediator(std::string _executable_filename, std::string _map_filename, std::string _status_filename, std::string _orders_filename);
    ~Mediator() = default;

    void loop(void);
};

#endif
