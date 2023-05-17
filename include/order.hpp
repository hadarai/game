#ifndef ORDER_H
#define ORDER_H

#include "unit.hpp"

struct move_t
{
    int x;
    int y;
};
struct attack_t
{
    int prey_id;
};
struct build_t
{
    char letter;
};

union parameters_t
{
    struct move_t move;
    struct attack_t attack;
    struct build_t build;
};

class Order
{
public:
    int unit_id;
    char action;
    parameters_t parameters;
    std::string denote(void);
};

#endif
