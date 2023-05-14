#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include "units.hpp"
#include <memory>

#define NUMBER_OF_UNITS 7
const std::array<char, NUMBER_OF_UNITS> available_unit_letters = {'K', 'S', 'A', 'P', 'C', 'R', 'W'};

class Game
{
private:
    int time_limit;
    int money;
    std::unique_ptr<Base> my_base;
    std::unique_ptr<Base> enemy_base;

    std::vector<std::vector<char>>
        map;
    std::vector<std::shared_ptr<Unit>> my_units;
    std::vector<std::shared_ptr<Unit>> enemy_units;

public:
    int X;
    int Y;
    std::string orders_filename;

    Game(
        std::string map_filename,
        std::string status_filename,
        std::string orders_filename,
        int time_limit);   // constructor
    Game(const Game &obj); // copy constructor
    ~Game();               // destructor

    void print(void);
    std::vector<Game> generate_my_legal_moves(void);
    void hit_a_unit(Unit unit, Unit enemy);
};

#endif