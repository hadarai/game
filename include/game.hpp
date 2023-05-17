#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <cctype>
#include <map>
#include <algorithm>

#include "unit.hpp"
#include "base.hpp"
#include "order.hpp"

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
    // std::vector<std::shared_ptr<Unit>> my_units;
    // std::vector<std::shared_ptr<Unit>> enemy_units;
    std::map<int, std::shared_ptr<Unit>> my_units;    // search by id
    std::map<int, std::shared_ptr<Unit>> enemy_units; // search by id

    static std::map<std::pair<char, char>, int> create_damages()
    {
        std::map<std::pair<char, char>, int> m;
        m.emplace(std::pair('K', 'K'), 35);
        m.emplace(std::pair('K', 'S'), 35);
        m.emplace(std::pair('K', 'A'), 35);
        m.emplace(std::pair('K', 'P'), 35);
        m.emplace(std::pair('K', 'C'), 35);
        m.emplace(std::pair('K', 'R'), 35);
        m.emplace(std::pair('K', 'W'), 35);
        m.emplace(std::pair('K', 'B'), 35);

        m.emplace(std::pair('S', 'K'), 30);
        m.emplace(std::pair('S', 'S'), 30);
        m.emplace(std::pair('S', 'A'), 30);
        m.emplace(std::pair('S', 'P'), 20);
        m.emplace(std::pair('S', 'C'), 20);
        m.emplace(std::pair('S', 'R'), 30);
        m.emplace(std::pair('S', 'W'), 30);
        m.emplace(std::pair('S', 'B'), 30);

        m.emplace(std::pair('A', 'K'), 15);
        m.emplace(std::pair('A', 'S'), 15);
        m.emplace(std::pair('A', 'A'), 15);
        m.emplace(std::pair('A', 'P'), 20);
        m.emplace(std::pair('A', 'C'), 10);
        m.emplace(std::pair('A', 'R'), 10);
        m.emplace(std::pair('A', 'W'), 15);
        m.emplace(std::pair('A', 'B'), 15);

        m.emplace(std::pair('P', 'K'), 35);
        m.emplace(std::pair('P', 'S'), 15);
        m.emplace(std::pair('P', 'A'), 15);
        m.emplace(std::pair('P', 'P'), 15);
        m.emplace(std::pair('P', 'C'), 15);
        m.emplace(std::pair('P', 'R'), 10);
        m.emplace(std::pair('P', 'W'), 15);
        m.emplace(std::pair('P', 'B'), 10);

        m.emplace(std::pair('C', 'K'), 40);
        m.emplace(std::pair('C', 'S'), 40);
        m.emplace(std::pair('C', 'A'), 40);
        m.emplace(std::pair('C', 'P'), 40);
        m.emplace(std::pair('C', 'C'), 40);
        m.emplace(std::pair('C', 'R'), 40);
        m.emplace(std::pair('C', 'W'), 40);
        m.emplace(std::pair('C', 'B'), 50);

        m.emplace(std::pair('R', 'K'), 10);
        m.emplace(std::pair('R', 'S'), 10);
        m.emplace(std::pair('R', 'A'), 10);
        m.emplace(std::pair('R', 'P'), 10);
        m.emplace(std::pair('R', 'C'), 10);
        m.emplace(std::pair('R', 'R'), 10);
        m.emplace(std::pair('R', 'W'), 10);
        m.emplace(std::pair('R', 'B'), 50);

        m.emplace(std::pair('W', 'K'), 5);
        m.emplace(std::pair('W', 'S'), 5);
        m.emplace(std::pair('W', 'A'), 5);
        m.emplace(std::pair('W', 'P'), 5);
        m.emplace(std::pair('W', 'C'), 5);
        m.emplace(std::pair('W', 'R'), 5);
        m.emplace(std::pair('W', 'W'), 5);
        m.emplace(std::pair('W', 'B'), 1);
        return m;
    }
    static const std::map<std::pair<char, char>, int> calculate_damage;

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
    void pretty_print(void);

    std::vector<Order> generate_legal_orders(void);

    void execute_an_order(Order order);
    void make_a_move(int id, int x, int y);
    void hit_a_unit(Unit unit, Unit enemy);

    void save_orders_to_file(std::string orders_filename, std::vector<Order> orders);

};

#endif
