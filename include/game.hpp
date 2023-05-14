#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include "units.hpp"
#include <memory>

class Game
{
private:
    int time_limit;
    int money;
    std::unique_ptr<Base> my_base;
    std::unique_ptr<Base> enemy_base;

    std::vector<std::vector<char>>
        map;
    std::vector<std::shared_ptr<Unit>> units;

public:
    int X;
    int Y;
    std::string orders_filename;

    Game(
        std::string map_filename,
        std::string status_filename,
        std::string orders_filename,
        int time_limit);
    ~Game();

    void print(void);
};

#endif